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
    static GLFWwindow *window;
    //static struct nk_context ctx;

    window = system_window_init(800, 600);

    Buffer* buffer = buffer_create(800,600);
    buffer_pixel_set(buffer, 10,10, BUILDRGB(255,255,255));
    buffer_pixel_set(buffer, 10,11, BUILDRGB(255,255,255));
    buffer_pixel_set(buffer, 10,12, BUILDRGB(255,255,255));
    buffer_pixel_set(buffer, 10,13, BUILDRGB(255,255,255));
    buffer_pixel_set(buffer, 10,14, BUILDRGB(255,255,255));
    buffer_pixel_set(buffer, 10,15, BUILDRGB(255,255,255));
    buffer_pixel_set(buffer, 10,16, BUILDRGB(255,255,255));
    buffer_pixel_set(buffer, 10,17, BUILDRGB(255,255,255));
    buffer_pixel_set(buffer, 10,18, BUILDRGB(255,255,255));
    buffer_pixel_set(buffer, 10,19, BUILDRGB(255,255,255));
    buffer_pixel_set(buffer, 10,20, BUILDRGB(255,255,255));
    buffer_pixel_set(buffer, 10,21, BUILDRGB(255,255,255));
    buffer_pixel_set(buffer, 10,22, BUILDRGB(255,255,255));
    buffer_pixel_set(buffer, 10,23, BUILDRGB(255,255,255));


    script();

    //gui_init(window, &ctx);
    //gui_fonts_init();
 
    /* Mainloop */
    while (!glfwWindowShouldClose(window))
    {
        int width = 0, height = 0;

        /* Manage events */
        glfwPollEvents();


        glfwGetWindowSize(window, &width, &height);
        //glViewport(0, 0, width, height);
        //glClear(GL_COLOR_BUFFER_BIT);

        //gui_frame(&ctx);
        //gui_draw();
        //glfwSwapBuffers(window);
        system_blit(window, buffer);

    }

    //gui_shutdown();
    mb_dispose();
    glfwTerminate();
    return EXIT_SUCCESS;
}
