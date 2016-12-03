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
#include "script.h"
#include "system.h"
#include "buffer.h"

GLFWwindow *window = NULL;

int main()
{

    window = system_window_init(800, 600);

    Buffer* buffer = buffer_create(800,600);
    buffer_pixel_set(buffer, 10,10, BUILDRGB(255,255,255));

    script();


    /* Mainloop */
    while (!glfwWindowShouldClose(window))
    {

        glfwPollEvents();

        //system_blit(window, buffer);
        glfwSwapBuffers(window);

    }

    mb_dispose();
    glfwTerminate();

}
