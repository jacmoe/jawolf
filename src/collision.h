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
//------------------------------------------------------------------------------
// Collision detection and response
//------------------------------------------------------------------------------
#ifndef _COLLISION_
#define _COLLISION_

#include "map.h"
#include "nasl_geometry.h"


// Contains information about a collision event.
typedef struct Collision {
    Mobile mob;         // Status of the Mobile before handling collisions
    Vector point;       // Point of collision
    Wall *wall;         // Wall that got hit
    double t0;          // Time to collision
    double distance;    // Distance to collision
} Collision;


// Returns a Mobile representing the movement of mob in map after handling
// collisions.
Mobile Co_Move(Map *map, Mobile mob);

// Checks if mob will hit anything in map.
//
// Returns 1 and stores the collision info in collision if there's a collision.
// Returns 0 otherwise.
int Co_CheckCollision(Map *map, Mobile mob, Collision *collision);

#endif
