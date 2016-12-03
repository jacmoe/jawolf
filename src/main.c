/*
*   This file is part of the
*    _                     _  __ 
*   (_) __ ___      _____ | |/ _|
*   | |/ _` \ \ /\ / / _ \| | |_ 
*   | | (_| |\ V  V / (_) | |  _|
*  _/ |\__,_| \_/\_/ \___/|_|_|  
* |__/                           
* 
*   project : https://github.com/jacmoe/jawolf
*
*   Copyright 2016 Jacob Moen
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "gui.h"
#include "script.h"
#include "system.h"
#include "buffer.h"

#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT

int main()
{
    static GLFWwindow *window = NULL;
    int width = 0, height = 0;

   if (!glfwInit()) {
        fprintf(stdout, "[GFLW] failed to init!\n");
        exit(1);
    }

    /* Compute window resolution from the main monitor's */
    //const GLFWvidmode *mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
    //const int width = mode->width / 2;
    //const int height = mode->height / 2;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create window and OpenGL context
    window = glfwCreateWindow(800, 600, "engine", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwGetWindowSize(window, &width, &height);
    glViewport(0, 0, 800, 600);

    // Disable cursor
    //glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    // Init GLEW
    glewExperimental = 1;
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to setup GLEW\n");
        exit(1);
    }
    //window = system_window_init(800, 600);

    //Buffer* buffer = buffer_create(800,600);
    //buffer_pixel_set(buffer, 10,10, BUILDRGB(255,255,255));

    //script();
    gui_init(window);
    gui_fonts();


    /* Mainloop */
    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();

        gui_frame();

        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);
        gui_draw();
        //system_blit(window, buffer);
        glfwSwapBuffers(window);

    }

    gui_shutdown();
    //mb_dispose();
    glfwTerminate();

}
