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
#include <stdint.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <assert.h>
#include <math.h>
#include <limits.h>
#include <time.h>
#include <GL/glew.h>
#include "GLFW/glfw3.h"

#include "forge.h"

#include "gui.h"
#include "script.h"
#include "system.h"
#include "buffer.h"



int main()
{
    GLFWwindow *window = 0;
    //struct nk_context *ctx;

    window = system_window_init(800, 600);

    Buffer* buffer = buffer_create(800,600);
    buffer_pixel_set(buffer, 10,10, 0x00FF00);
    buffer_pixel_set(buffer, 10,11, 0x00FF00);
    buffer_pixel_set(buffer, 10,12, 0x00FF00);
    buffer_pixel_set(buffer, 10,13, 0x00FF00);
    buffer_pixel_set(buffer, 10,14, 0x00FF00);
    buffer_pixel_set(buffer, 10,15, 0x00FF00);
    buffer_pixel_set(buffer, 10,16, 0x00FF00);
    buffer_pixel_set(buffer, 10,17, 0x00FF00);
    buffer_pixel_set(buffer, 10,18, 0x00FF00);
    buffer_pixel_set(buffer, 10,19, 0x00FF00);

    script();

    //ctx = gui_init(window);

    /* Mainloop */
    while (!glfwWindowShouldClose(window))
    {
        int width = 0, height = 0;

        /* Manage events */
        glfwPollEvents();

        //gui_frame(ctx);

        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);
        glClear(GL_COLOR_BUFFER_BIT);

        //gui_draw(window);
        //glfwSwapBuffers(window);
        system_blit(window, buffer);

    }

    //gui_shutdown();
    mb_dispose();
    glfwTerminate();
    return EXIT_SUCCESS;
}
