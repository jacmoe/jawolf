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
#include <stdlib.h>

#include "collision.h"
#include "nasl_defs.h"
#include "nasl_geometry.h"
#include "nasl_graphics.h"

#include "game.h"
#include "input.h"

static void _dispatch_event(KeyEvent kev)
{
    for (int i = 0; i < game.keymap->numbinds; i++)
    {
        KeyBind *bind = &game.keymap->binds[i];

        if (bind->key == kev.key)
        {
            bind->action(kev);
            break;
        }
    }
}

uint32_t input_process()
{
    uint32_t start = 1000 * glfwGetTime();//S_GetTime();

    glfwPollEvents();

    Command cmd = game_build_command();
    game_run_command(cmd);

    return /*S_GetTime()*/ 1000 * glfwGetTime() - start;
}

void input_key_cb(GLFWwindow *window, int key, int scancode, int action, int mods)
{
    KeyEvent kev = {key, action, mods};

    _dispatch_event(kev);
}
