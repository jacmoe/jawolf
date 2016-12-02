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

void gui_init(GLFWwindow *window);
void gui_fonts();
void gui_frame();
void gui_draw();
void gui_shutdown();

#endif /* GUI_H */
