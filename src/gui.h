#ifndef GUI_H
#define GUI_H

#include <stdint.h>

#include <GLFW/glfw3.h>

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT

#include "3rd_party/nuklear.h"

struct nk_context* gui_init(GLFWwindow *window);
void gui_frame(struct nk_context *ctx);
void gui_draw();
void gui_shutdown(void);

#endif /* GUI_H */
