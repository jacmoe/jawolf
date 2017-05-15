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
#ifndef _MAP_
#define _MAP_

#include "nasl_buffer.h"
#include "nasl_geometry.h"

// Represents anything that can move.
// It has a size, represented by the radius of a surrounding circle.
typedef struct Mobile {
    Vector pos;
    Vector vel;
    Vector forward;  // *Must* be a versor
    double radius;
} Mobile;

typedef struct {
    Segment seg;
} Wall;

typedef struct Map {
    Wall *walls;
    int numwalls;

    Buffer *floortex;
    Buffer *ceiltex;
    Buffer *walltex;
} Map;

typedef struct Scene {
    Mobile *pov;
    Map *map;
} Scene;


Map *M_Load(const char *path);


#endif
