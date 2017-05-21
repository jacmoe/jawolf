/*
*   This file is part of the
*    _                     _  __ 
*   (_) __ ___      _____ | |/ _|
*   | |/ _` \ \ /\ / / _ \| | |_ 
*   | | (_| |\ V  V / (_) | |  _|
*  _/ |\__,_| \_/\_/ \___/|_|_|  
* |__/                           
* 
*   project : https://github.com/jacmoe/jawolf
*
*   Copyright 2016 - 2017 Jacob Moen
*
*/
#include <math.h>
#include <float.h>

#include "map.h"
#include "nasl_graphics.h"
#include "nasl_defs.h"

#include "actions.h"
#include "game.h"

Game game;

#define WIDTH 320
#define HEIGHT 240

#define FOV DEG2RAD(75)                          // Horizontal Field of View
#define NEAR 1                                   // Near clip plane distance
#define FAR 300                                  // Used to dim light
#define VIEW(w) (((w) / 2.0) / (tan(FOV / 2.0))) // Viewplane distance
#define WALLHEIGHT 64
#define POVHEIGHT (WALLHEIGHT / 2)  // Must be half the wall height.

#define SPEED 6

void game_init()
{
    nasl_graphics_init(WIDTH, HEIGHT, "Jawolf test", 0, 3);
    game.window = nasl_graphics_get_window();
    glfwSwapInterval(1);
    glfwSetKeyCallback(game.window, input_key_cb);
    game.buffer = nasl_buffer_create(WIDTH, HEIGHT);

    game.player.vel = (Vector){0, 0};
    game.player.forward = (Vector){1, 0};
    game.player.radius = 8;

    //game.map = map_load("assets/levels/level.map");
    game.map = map_import("assets/levels/text.map");
    game.player.pos = (Vector){game.map->player_x, game.map->player_y};
    game.player.forward = G_Rotate(game.player.forward, DEG2RAD(90));
    game.keymap = actions_get_default_keymap();
}

void game_end()
{
    glfwTerminate();
}

Scene game_get_scene()
{
    Scene scene = {
        .pov = &game.player,
        .map = game.map};

    return scene;
}

static Buffer* get_texture(SpriteSheet textures, int idx)
{
    int col = idx % textures.cols;
    int row = idx / textures.cols;
    return nasl_sprite_get(textures, row, col);
}

uint32_t game_draw_pov(Scene *sce, Buffer *buf)
{
    uint32_t start = (uint32_t)1000 * glfwGetTime();//S_GetTime();

    for (int x = 0; x < buf->width; x++)
    {
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

        for (int i = 0; i < sce->map->numwalls; i++)
        {
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
        if (wall)
        {
            col_height = viewcos * WALLHEIGHT / distance;
            // Everything is *much* easier if col_height is even.
            if (col_height & 1) col_height++;

            int top = (buf->height - col_height) / 2;

            Buffer* texture = get_texture(sce->map->textures, wall->tex_idx);

            int texel_x = MOD((int)G_Distance(wall->seg.start, hit), texture->width);
            for (int i = 0; i < col_height; i++)
            {
                int y = top + i;
                if (y < 0 || y >= buf->height) continue;

                int texel_y = WALLHEIGHT * i / col_height;
                uint32_t color = texture->pixels[texel_y * texture->width + texel_x];
                if (distance > FAR)
                {
                    color = nasl_color_scale(color, FAR / distance);
                }

                nasl_buffer_set_pixel(buf, x, y, color);
            }
        }

        // Floor & ceiling
        for (int h = (buf->height - col_height) / 2; h > 0; h--)
        {
            double texel_distance = (POVHEIGHT * viewcos) / ((buf->height / 2) - h);
            Vector texel_world_pos = G_Sum(sce->pov->pos, G_Scale(texel_distance, ray.dir));

            Buffer* floor_texture = get_texture(sce->map->textures, sce->map->floortex);

            int texel_x = MOD((int)texel_world_pos.x, floor_texture->width);
            int texel_y = MOD((int)texel_world_pos.y, floor_texture->height);

            uint32_t color = floor_texture->pixels[texel_y * floor_texture->width + texel_x];
            if (texel_distance > FAR)
            {
                color = nasl_color_scale(color, FAR / texel_distance);
            }
            nasl_buffer_set_pixel(buf, x, buf->height - h, color);

            Buffer* ceil_texture = get_texture(sce->map->textures, sce->map->ceiltex);

            texel_x = MOD((int)texel_world_pos.x, ceil_texture->width);
            texel_y = MOD((int)texel_world_pos.y, ceil_texture->height);

            color = ceil_texture->pixels[texel_y * ceil_texture->width + texel_x];
            if (texel_distance > FAR)
            {
                color = nasl_color_scale(color, FAR / texel_distance);
            }
            nasl_buffer_set_pixel(buf, x, h - 1, color);
        }
    }

    return 1000 * glfwGetTime() - start;//S_GetTime() - start;
}


Command game_build_command()
{
    Command cmd;

    if (game.turn_left && game.turn_right)
    {
        cmd.turn = 0;
    }
    else if (game.turn_left)
    {
        cmd.turn = -0.05;
    }
    else if (game.turn_right)
    {
        cmd.turn = 0.05;
    }
    else
    {
        cmd.turn = 0;
    }

    Vector fwd = game.player.forward;
    Vector side = G_Perpendicular(fwd);

    Vector forward_vel;
    if (game.forward && game.backward)
    {
        forward_vel = (Vector){0, 0};
    }
    else if (game.forward)
    {
        forward_vel = fwd;
    }
    else if (game.backward)
    {
        forward_vel = N(fwd);
    }
    else
    {
        forward_vel = (Vector){0, 0};
    }

    Vector side_vel;
    if (game.strafe_left && game.strafe_right)
    {
        side_vel = (Vector){0, 0};
    }
    else if (game.strafe_right)
    {
        side_vel = side;
    }
    else if (game.strafe_left)
    {
        side_vel = N(side);
    }
    else
    {
        side_vel = (Vector){0, 0};
    }

    cmd.velocity = G_Scale(SPEED, G_Sum(forward_vel, side_vel));

    return cmd;
}

void game_run_command(Command cmd)
{
    game.player.forward = G_Rotate(game.player.forward, cmd.turn);
    game.player.vel = cmd.velocity;
    game.player.pos = collision_move(game.map, game.player).pos;
}
