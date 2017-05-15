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
    InitGame();

    while (!glfwWindowShouldClose(game.window)) {

        Scene scene = GetScene();
        DrawPOV(&scene, game.buffer);
        ProcessInput();
        nasl_graphics_render(game.buffer);

        glfwSwapBuffers(game.window);

    }

    EndGame();
}
