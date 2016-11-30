#ifndef COLOR_H
#define COLOR_H
#include <stdint.h>

// Little-endian
enum Color
{
    BLACK = 0x000000,
    BLUE = 0xFF0000,
    GREEN = 0x00FF00,
    GREY = 0x111111,
    LIGHTGREY = 0x222222,
    RED = 0x0000FF,
    WHITE = 0xFFFFFF,
    YELLOW = 0x00FFFF,

    TRANSPARENT = 0xFFFF00,
};

#define GETR(c) (((c) >> 0) & 0xFF)
#define GETG(c) (((c) >> 8) & 0xFF)
#define GETB(c) (((c) >> 16) & 0xFF)

#define BUILDRGB(r, g, b) ((r) | (g) << 8 | (b) << 16)

uint32_t color_scale(uint32_t color, double intensity);

#endif /* COLOR_H */
