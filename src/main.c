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

#include "game.h"

int main() {
    game_init();

    while (!glfwWindowShouldClose(game.window)) {

        Scene scene = game_get_scene();
        game_draw_pov(&scene, game.buffer);
        input_process();
        nasl_graphics_render(game.buffer);

        glfwSwapBuffers(game.window);

    }

    game_end();
}
