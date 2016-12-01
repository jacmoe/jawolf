#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "buffer.h"
#include "system.h"

static void error_callback(int e, const char *d)
{
    printf("Error %d: %s\n", e, d);
}

GLFWwindow *system_window_init(int width, int height) {
    glfwSetErrorCallback(error_callback);

    glfwInit();

    /* Compute window resolution from the main monitor's */
    //const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    //const int width = mode->width / 2;
    //const int height = mode->height / 2;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create window and OpenGL context
    GLFWwindow *window = glfwCreateWindow(width, height, "engine", NULL, NULL);
    glfwMakeContextCurrent(window);

    // Disable cursor
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // Init GLEW
    glewExperimental = GL_TRUE;
    glewInit();

    //InitOpenGL(width, height);

    return window;
}


uint32_t system_time_get() {
    return 1000 * glfwGetTime();
}


uint32_t system_blit(GLFWwindow *window, Buffer *buf) {
    uint32_t start = system_time_get();

    glTexSubImage2D(
            GL_TEXTURE_2D,              // target
            0,                          // level of detail
            0, 0,                       // xoffset, yoffset
            buf->width, buf->height,    // width, height
            GL_RGBA, GL_UNSIGNED_BYTE,  // format, type
            buf->pixels                 // pixels
            );
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glfwSwapBuffers(window);

    return system_time_get() - start;
}
