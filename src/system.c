//#define GLEW_STATIC
//#include <GL/glew.h>

#include "geometry.h"
#include "buffer.h"
#include "system.h"
#include "dbg.h"

static const char *vertexSource = "#version 330 core\n"
"\n"
"in vec2 position;\n"
"in vec2 texcoord;\n"
"\n"
"out vec3 Color;\n"
"out vec2 Texcoord;\n"
"\n"
"void main() {\n"
"    Texcoord = texcoord;\n"
"    gl_Position = vec4(position, 0.0, 1.0);\n"
"}";

static const char *fragmentSource = "#version 330 core\n"
"\n"
"in vec2 Texcoord;\n"
"\n"
"out vec4 outColor;\n"
"\n"
"uniform sampler2D tex;\n"
"\n"
"void main() {\n"
"    outColor = texture(tex, Texcoord);\n"
"}";

// Flags
static int resizef;


void system_fullscreen(int flag) {

}


void s_mouse_grab(int flag) {
    
}


void system_init(const char *title, int width, int height) {

}


void system_quit() {

}


Tick system_tick_get() {

    Tick t = {0};

    return t;
}


uint32_t system_blit(Buffer *buf) {
    uint32_t start = system_time_get();

    // if (resizef) {
    //     resizef = 0;

    //     int winwidth, winheight;
    //     //SDL_GetWindowSize(window, &winwidth, &winheight);

    //     glViewport(0, 0, winwidth, winheight);
    // }

    // glTexSubImage2D(
    //         GL_TEXTURE_2D,
    //         0, 0,
    //         0,
    //         buf->width, buf->height,
    //         GL_RGBA, GL_UNSIGNED_BYTE,
    //         buf->pixels
    //         );

    // glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    //SDL_GL_SwapWindow(window);

    return system_time_get() - start;
}


Vector system_mousepos_get(Buffer *buf) {
    int mx, my;
    int winwidth = 0;
    int winheight = 0;
    return (Vector){ mx * buf->width / winwidth, my * buf->height / winheight };
}


// http://sdl.beuc.net/sdl.wiki/Pixel_Access
uint32_t pixel_get(SDL_Surface *surface, int x, int y) {
    int bpp = surface->format->BytesPerPixel;
    // Here p is the address to the pixel we want to retrieve.
    uint8_t *p = (uint8_t *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp) {
        case 1:
            return *p;
            break;

        case 2:
            return *(uint16_t *)p;
            break;

        case 3:
            if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
                return p[0] << 16 | p[1] << 8 | p[2];
            } else {
                return p[0] | p[1] << 8 | p[2] << 16;
            }
            break;

        case 4:
            return *(uint32_t *)p;
            break;

        default:
            return 0;  // shouldn't happen, but avoids warnings.
    }
}


Buffer *system_image_load(const char *path) {
    SDL_Surface *tex_surf = IMG_Load(path);
    check(tex_surf,
            "Error loading texture. IMG_GetError(): %s\n", IMG_GetError());

    Buffer *t = buffer_create(tex_surf->w, tex_surf->h);

    for (int y = 0; y < tex_surf->h; y++) {
        for (int x = 0; x < tex_surf->w; x++) {
            uint32_t pixel = pixel_get(tex_surf, x, y);

            uint8_t red, green, blue;
            SDL_GetRGB(pixel, tex_surf->format, &red, &green, &blue);

            t->pixels[y * t->width + x] = BUILDRGB(red, green, blue);
        }
    }

    SDL_FreeSurface(tex_surf);

    return t;
}


uint32_t system_time_get() {
    return SDL_GetTicks();
}


void system_sleep(uint32_t ms) {
    SDL_Delay(ms);
}
