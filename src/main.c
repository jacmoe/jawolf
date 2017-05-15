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
*   Copyright 2016 - 2017 Jacob Moen
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "nasl_graphics.h"
#include "nasl_buffer.h"
#include "nasl_sprite.h"

static int init(int width, int height);
static int shutdown();
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main()
{
    int buffer_width = 320;
    int buffer_height = 240;

    init(buffer_width, buffer_height);

    // Create main buffer
    Buffer* buffer = nasl_buffer_create(buffer_width, buffer_height);
    nasl_buffer_set_mainbuffer(buffer);
    // Clear main buffer to a blue color
    nasl_buffer_clear(buffer, GREY1);

    SpriteSheet textures = nasl_sprite_load("assets/textures/sjswalls2.bmp", 4, 3);

    Buffer* image = nasl_sprite_get(textures, 0, 0);
    nasl_buffer_blit(buffer, image, 10, 10);

    image = nasl_sprite_get(textures, 0, 1);
    nasl_buffer_blit(buffer, image, 15, 60);
    
    image = nasl_sprite_get(textures, 0, 2);
    nasl_buffer_blit(buffer, image, 100, 80);

    image = nasl_sprite_get(textures, 1, 0);
    nasl_buffer_blit(buffer, image, 10, 10);

    image = nasl_sprite_get(textures, 1, 1);
    nasl_buffer_blit(buffer, image, 15, 60);
    
    image = nasl_sprite_get(textures, 3, 2);
    nasl_buffer_blit(buffer, image, 100, 80);

    // Main loop
    while(nasl_graphics_running())
    {
        // Event polling
        nasl_graphics_poll_events();
        // Render the main buffer
        nasl_graphics_render(buffer);
        // Swap buffers
        nasl_graphics_present();
    }

    // Destroy the main buffer
    nasl_buffer_destroy(buffer);

    shutdown();
}

static int init(int width, int height)
{
    nasl_graphics_init(width, height, "Jawolf 0.4", 0, 3);

    glfwSetKeyCallback(nasl_graphics_get_window(), key_callback);

    return 1;
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

static int shutdown()
{
    nasl_graphics_shutdown();

    return 1;
}
