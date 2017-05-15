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
#ifndef _GAME_
#define _GAME_


#include "nasl_buffer.h"
#include "collision.h"
#include "map.h"

#include "input.h"

// Player command
typedef struct Command
{
    Vector velocity;
    double turn;
} Command;

#define MAXEVENTS 64

// Contains all the game global state
typedef struct Game
{
    GLFWwindow *window;
    Buffer *buffer;

    Map *map;      // Current Map
    Mobile player; // Player

    // --- Input ---
    KeyMap *keymap; // Current KeyMap

    int forward;
    int backward;
    int strafe_left;
    int strafe_right;

    int turn_left;
    int turn_right;
} Game;

extern Game game;

void InitGame();
void EndGame();
uint32_t DrawPOV(Scene *sce, Buffer *buf);
Scene GetScene();
Command BuildCommand();
void RunCommand(Command cmd);

#endif
