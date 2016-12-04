//------------------------------------------------------------------------------
// Sprite sheets
//------------------------------------------------------------------------------
#ifndef _SPRITES_
#define _SPRITES_

#include "buffer.h"

typedef struct SpriteSheet {
    Buffer **sprites;
    int rows, cols;
    int width, height;
} SpriteSheet;


SpriteSheet sprite_load(const char *path, int rows, int cols);
Buffer *sprite_get(SpriteSheet ss, int x, int y);
void sprite_delete(SpriteSheet ss);

#endif
