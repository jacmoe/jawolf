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
#ifndef JAWOLF_INPUT_H
#define JAWOLF_INPUT_H

#include <stdint.h>

#include "nasl_graphics.h"

#include "nasl_geometry.h"

// Keys:    GLFW_KEY_*
// Actions: GLFW_{PRESS, RELEASE, REPEAT}
// Mods:    GLFW_MOD_{SHIFT, CONTROL, ALT, SUPER}
typedef struct KeyEvent
{
    int key, action, mods;
} KeyEvent;

// Associates a KeyEvent with an action
typedef struct KeyBind
{
    int key;
    void (*action)(KeyEvent kev);
} KeyBind;

// List of KeyBinds
typedef struct KeyMap
{
    int numbinds;
    KeyBind* binds;
} KeyMap;

void input_post_event(KeyEvent kev);
uint32_t input_process();

void input_key_cb(GLFWwindow* window, int key, int scancode, int action, int mods);

#endif // JAWOLF_INPUT_H
