//------------------------------------------------------------------------------
// Functions to abstract dependencies
//------------------------------------------------------------------------------

#ifndef _SYSTEM_
#define _SYSTEM_

#include <stdint.h>

#include "buffer.h"
#include "geometry.h"


//------------------------------------------------------------------------------
// Init / Shutdown
//------------------------------------------------------------------------------

// Initializes SDL. Creates a resizable window and handles resize events.
void system_init(const char *title, int width, int height);

// Just calls SDL_Quit.
void system_quit();



//------------------------------------------------------------------------------
// Video
//------------------------------------------------------------------------------

// Set to 1 to set fullscreen.
void system_fullscreen(int flag);

// Update the screen with the contents of buf. Returns the time it took in ms.
uint32_t system_blit(Buffer *buf);



//------------------------------------------------------------------------------
// Input
//------------------------------------------------------------------------------

// A Tick contains all the input info needed to process one gametick.
typedef struct Tick {
    int forward;            // 1 forward, -1 backwards
    int strafe;             // 1 right, -1 left
    int turn;               // 1 clockwise, -1 anticlockwise
    int relative_mouse_x;   // > 0 clockwise, < 0 anticlockwise
} Tick;


// Returns a vector with the position of the mouse in buffer coordinates.
Vector system_mousepos_get(Buffer *buf);

// Set to 1 to keep the mouse inside the window.
void system_mouse_grab(int flag);

Tick system_tick_get();



//------------------------------------------------------------------------------
// Image loading
//------------------------------------------------------------------------------

// Load the image given by path into a Buffer.
Buffer *system_image_load(const char *path);



//------------------------------------------------------------------------------
// Time
//------------------------------------------------------------------------------

// Returns the time since S_Init() in milliseconds.
uint32_t system_time_get();

// Sleep for at least ms milliseconds.
// Count on a granularity of at least 10 millisecods.
void system_sleep(uint32_t ms);

#endif
