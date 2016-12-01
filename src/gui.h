#ifndef GUI_H
#define GUI_H

#include <stdint.h>

#include <GLFW/glfw3.h>

void gui_init(GLFWwindow *window);
void gui_frame(void);
void gui_draw();
void gui_shutdown(void);

#endif /* GUI_H */
