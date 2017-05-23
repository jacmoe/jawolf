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
#ifndef JAWOLF_TEXTURE_H
#define JAWOLF_TEXTURE_H

#include <stdint.h>
#include "nasl_buffer.h"

typedef struct Texture
{
    int size;
    int size_exponent;
    Buffer* buffer;
    uint32_t avg_color;
} Texture;

#endif //JAWOLF_TEXTURE_H
