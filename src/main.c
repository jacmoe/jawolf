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
#include "map_dumper.h"
#include "map.h"

int main()
{
    static GLFWwindow *window = NULL;

    window = system_window_init(800, 600);

    Buffer* buffer = buffer_create(800,600);
    buffer_pixel_set(buffer, 10,10, BUILDRGB(255,255,255));

    script_init();
    script_run("assets/scripts/init.bas");

    //map_dump("assets/levels/one.tmx");

    map_import("assets/levels/one.tmx");

    gui_init(window);


    /* Mainloop */
    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();

        gui_frame();

        glClear(GL_COLOR_BUFFER_BIT);
        gui_draw();
        system_blit(window, buffer);

    }

    gui_shutdown();
    script_shutdown();
    buffer_delete(buffer);
    glfwTerminate();

}
