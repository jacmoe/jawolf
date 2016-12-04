#include <stdlib.h>

#include "buffer.h"
#include "image_load.h"
#include "sprite.h"


SpriteSheet sprite_load(const char *path, int rows, int cols) {
    Buffer *b = image_load(path);

    SpriteSheet ss = {
        .rows = rows,
        .cols = cols,
        .width =  b->width / cols,
        .height = b->height / rows,
        .sprites = malloc(sizeof(Buffer *) * rows * cols)
    };

    for (int j = 0; j < rows; j++) {
        for (int i = 0; i < cols; i++) {
            Buffer *sprite = buffer_get_subbuffer(
                    b, i * ss.width, j * ss.height, ss.width, ss.height
                    );

            ss.sprites[j * cols + i] = sprite;
        }
    }

    buffer_delete(b);

    return ss;
}


Buffer *sprite_get(SpriteSheet ss, int x, int y) {
    return ss.sprites[y * ss.cols + x];
}


void sprite_delete(SpriteSheet ss) {
    for (int i = 0; i < ss.rows * ss.cols; i++) {
        free(ss.sprites[i]);
    }
}
