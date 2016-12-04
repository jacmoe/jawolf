#include <float.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"
#include "color.h"
//#include "dbg.h"
#include "defs.h"
#include "draw.h"
#include "system.h"
#include "geometry.h"
#include "map.h"


// Doom's version of Bresenham
void draw_line(Buffer *b, int x0, int y0, int x1, int y1, uint32_t color) {
    int dx = x1 - x0;
    int ax = 2 * abs(dx);
    int sx = dx < 0 ? -1 : 1;

    int dy = y1 - y0;
    int ay = 2 * abs(dy);
    int sy = dy < 0 ? -1 : 1;

    int x = x0;
    int y = y0;

    if (ax > ay) {
        int d = ay - ax / 2;
        while (1) {
            buffer_pixel_set(b, x, y, color);
            if (x == x1) return;

            if (d >= 0) {
                y += sy;
                d -= ax;
            }
            x += sx;
            d += ay;
        }
    } else {
        int d = ax - ay / 2;
        while (1) {
            buffer_pixel_set(b, x, y, color);
            if (y == y1) return;

            if (d >= 0) {
                x += sx;
                d -= ay;
            }
            y += sy;
            d += ax;
        }
    }
}


// https://en.wikipedia.org/wiki/Midpoint_circle_algorithm
void draw_circle(Buffer *b, int x0, int y0, int radius, uint32_t color) {
    int x = radius;
    int y = 0;
    int decisionOver2 = 1 - x;  // Decision criterion divided by 2 evaluated at x=r, y=0

    while (x >= y) {
        buffer_pixel_set(b,  x + x0,  y + y0, color);
        buffer_pixel_set(b,  y + x0,  x + y0, color);
        buffer_pixel_set(b, -x + x0,  y + y0, color);
        buffer_pixel_set(b, -y + x0,  x + y0, color);
        buffer_pixel_set(b, -x + x0, -y + y0, color);
        buffer_pixel_set(b, -y + x0, -x + y0, color);
        buffer_pixel_set(b,  x + x0, -y + y0, color);
        buffer_pixel_set(b,  y + x0, -x + y0, color);
        y++;

        if (decisionOver2 <= 0) {
            decisionOver2 += 2 * y + 1;  // Change in decision criterion for y -> y+1
        } else {
            x--;
            decisionOver2 += 2 * (y - x) + 1;  // Change for y -> y+1, x -> x-1
        }
    }
}


void draw_segment(Buffer *b, Segment l, uint32_t color) {
    draw_line(b, l.start.x, l.start.y, l.end.x, l.end.y, color);
}


void draw_box(Buffer *buf, Box b, uint32_t color) {
    draw_line(buf, b.left, b.top, b.right, b.top, color);
    draw_line(buf, b.left, b.bottom, b.right, b.bottom, color);
    draw_line(buf, b.left, b.top, b.left, b.bottom, color);
    draw_line(buf, b.right, b.top, b.right, b.bottom, color);
}


void draw_text(Buffer *b, SpriteSheet ascii, int x, int y, const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);

    char text[128] = "";
    vsnprintf(text, 128, fmt, args);

    va_end(args);

    for (int i = 0; i < strlen(text); i++) {
        unsigned char c = text[i];

        int xx = c % 16;
        int yy = c / 16;

        Buffer *bitmap = sprite_get(ascii, xx, yy);

        buffer_blit(b, bitmap, x + i * 8, y);
    }
}


#define FOV DEG2RAD(75)                          // Horizontal Field of View
#define NEAR 1                                   // Near clip plane distance
#define FAR 300                                  // Used to dim light
#define VIEW(w) (((w) / 2.0) / (tan(FOV / 2.0))) // Viewplane distance
#define WALLHEIGHT 64
#define POVHEIGHT (WALLHEIGHT / 2)  // Must be half the wall height.

uint32_t draw_pov(Scene *sce, Buffer *buf) {
    uint32_t start = system_time_get();

    for (int x = 0; x < buf->width; x++) {
        double viewplane_distance = VIEW(buf->width);
        double ray_angle = atan2((x + 0.5) - (buf->width / 2), viewplane_distance);
        double ray_cos = cos(ray_angle);
        double viewcos = viewplane_distance / ray_cos;
        double nearcos = NEAR / ray_cos;

        Line ray = {
            .start = sce->pov->pos,
            .dir = G_Rotate(sce->pov->forward, ray_angle)
        };

        // Iterate over all the walls and use the one that's hit
        // closest to the pov.
        Wall *wall = NULL;
        double distance = DBL_MAX;
        Vector hit;

        for (int i = 0; i < sce->map->numwalls; i++) {
            Wall *w = &sce->map->walls[i];
            Vector h;
            if (G_SegmentRayIntersection(w->seg, ray, &h)) {
                double d = G_Distance(h, sce->pov->pos);
                if (d < distance && d > nearcos) {
                    wall = w;
                    distance = d;
                    hit = h;
                }
            }
        }

        // Wall
        int col_height = 0;
        if (wall) {
            col_height = viewcos * WALLHEIGHT / distance;
            // Everything is *much* easier if col_height is even.
            if (col_height & 1) col_height++;

            int top = (buf->height - col_height) / 2;

            int texel_x = MOD((int)G_Distance(wall->seg.start, hit), sce->map->walltex->width);
            for (int i = 0; i < col_height; i++) {
                int y = top + i;
                if (y < 0 || y >= buf->height) continue;

                int texel_y = WALLHEIGHT * i / col_height;
                uint32_t c = sce->map->walltex->pixels[texel_y * sce->map->walltex->width + texel_x];
                if (distance > FAR) {
                    c = color_scale(c, FAR / distance);
                }

                buffer_pixel_set(buf, x, y, c);
            }
        }

        // Floor & ceiling
        for (int h = (buf->height - col_height) / 2; h > 0; h--) {
            double texel_distance = (POVHEIGHT * viewcos) / ((buf->height / 2) - h);
            Vector texel_world_pos = G_Sum(sce->pov->pos, G_Scale(texel_distance, ray.dir));

            int texel_x = MOD((int)texel_world_pos.x, sce->map->floortex->width);
            int texel_y = MOD((int)texel_world_pos.y, sce->map->floortex->height);

            uint32_t color = sce->map->floortex->pixels[texel_y * sce->map->floortex->width + texel_x];
            if (texel_distance > FAR) {
                color = color_scale(color, FAR / texel_distance);
            }
            buffer_pixel_set(buf, x, buf->height - h, color);

            texel_x = MOD((int)texel_world_pos.x, sce->map->ceiltex->width);
            texel_y = MOD((int)texel_world_pos.y, sce->map->ceiltex->height);

            color = sce->map->ceiltex->pixels[texel_y * sce->map->ceiltex->width + texel_x];
            if (texel_distance > FAR) {
                color = color_scale(color, FAR / texel_distance);
            }
            buffer_pixel_set(buf, x, h - 1, color);
        }
    }

    return system_time_get() - start;
}
