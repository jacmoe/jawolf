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

#include "game.h"
#include "input.h"

static void _action_quit(KeyEvent kev)
{
    glfwSetWindowShouldClose(game.window, 1);
}

static void _action_forwards(KeyEvent kev)
{
    if (kev.action == GLFW_PRESS)
    {
        game.forward = 1;
    }
    else if (kev.action == GLFW_RELEASE)
    {
        game.forward = 0;
    }
}

static void _action_backwards(KeyEvent kev)
{
    if (kev.action == GLFW_PRESS)
    {
        game.backward = 1;
    }
    else if (kev.action == GLFW_RELEASE)
    {
        game.backward = 0;
    }
}

static void _action_strafe_left(KeyEvent kev)
{
    if (kev.action == GLFW_PRESS)
    {
        game.strafe_left = 1;
    }
    else if (kev.action == GLFW_RELEASE)
    {
        game.strafe_left = 0;
    }
}

static void _action_strafe_right(KeyEvent kev)
{
    if (kev.action == GLFW_PRESS)
    {
        game.strafe_right = 1;
    }
    else if (kev.action == GLFW_RELEASE)
    {
        game.strafe_right = 0;
    }
}

static void _action_turn_left(KeyEvent kev)
{
    if (kev.action == GLFW_PRESS)
    {
        game.turn_left = 1;
    }
    else if (kev.action == GLFW_RELEASE)
    {
        game.turn_left = 0;
    }
}

static void _action_turn_right(KeyEvent kev)
{
    if (kev.action == GLFW_PRESS)
    {
        game.turn_right = 1;
    }
    else if (kev.action == GLFW_RELEASE)
    {
        game.turn_right = 0;
    }
}

KeyMap* actions_get_default_keymap()
{
    KeyMap* keymap = malloc(sizeof(KeyMap));
    keymap->numbinds = 7;

    keymap->binds = malloc(sizeof(KeyBind) * keymap->numbinds);
    keymap->binds[0] = (KeyBind){GLFW_KEY_Q, _action_quit};
    keymap->binds[1] = (KeyBind){GLFW_KEY_W, _action_forwards};
    keymap->binds[2] = (KeyBind){GLFW_KEY_S, _action_backwards};
    keymap->binds[3] = (KeyBind){GLFW_KEY_LEFT, _action_strafe_left};
    keymap->binds[4] = (KeyBind){GLFW_KEY_RIGHT, _action_strafe_right};
    keymap->binds[5] = (KeyBind){GLFW_KEY_A, _action_turn_left};
    keymap->binds[6] = (KeyBind){GLFW_KEY_D, _action_turn_right};

    return keymap;
}
