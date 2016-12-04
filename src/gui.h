#ifndef GUI_H
#define GUI_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

void gui_init(GLFWwindow *window);
void gui_frame();
void gui_draw();
void gui_shutdown();

#endif /* GUI_H */
