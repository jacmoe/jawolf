//------------------------------------------------------------------------------
// Functions to abstract dependencies
//------------------------------------------------------------------------------

#ifndef _SYSTEM_
#define _SYSTEM_

#include <stdint.h>

#include <GLFW/glfw3.h>

#include "buffer.h"

GLFWwindow *system_window_init(int width, int height);
uint32_t system_time_get();
uint32_t system_blit(GLFWwindow *window, Buffer *buf);

#endif
