//-----------------------------------------------------------------------------
// Functions to draw stuff
//-----------------------------------------------------------------------------

#ifndef _DRAW_
#define _DRAW_

#include <stdint.h>

#include "buffer.h"
#include "color.h"
#include "geometry.h"
#include "map.h"
#include "sprite.h"

void draw_line(Buffer *b, int x0, int y0, int x1, int y1, uint32_t color);
void draw_circle(Buffer *b, int x0, int y0, int radius, uint32_t color);
void draw_segment(Buffer *b, Segment l, uint32_t color);
void draw_box(Buffer *buf, Box b, uint32_t color);
void draw_text(Buffer *b, SpriteSheet ascii, int x, int y, const char *fmt, ...);
uint32_t draw_pov(Scene *sce, Buffer *buf);

#endif
