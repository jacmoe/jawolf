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
#include <stdlib.h> // malloc
#include "block.h"

Block* block_create(int wall, Texture* blockTexture, Texture* ceilingTexture)
{
    Block* block = malloc(sizeof(Block));
    return block;
}

void block_destroy(Block* block)
{
    free(block);
}
