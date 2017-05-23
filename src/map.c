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
#include <stdio.h>
#include <stdlib.h>

#include "map.h"
#include "nasl_dbg.h"
#include "nasl_geometry.h"
#include "nasl_image.h"

Map *CreateEmptyMap() {
    Map *map = malloc(sizeof(struct Map));

    map->walls = NULL;
    map->numwalls = 0;
    map->floortex = 2;
    map->ceiltex = 5;
    map->textures = nasl_sprite_load("assets/textures/walls_128.png", 3, 4);

    return map;
}


Map* map_load(const char *path) {
    FILE* f = fopen(path, "r");

    Map* map = CreateEmptyMap();

    Segment seg;
    for (int i = 0;
            fscanf(f, "%lf %lf %lf %lf",
                &seg.start.x, &seg.start.y, &seg.end.x, &seg.end.y) != EOF;
            i++)
    {
        map->walls = realloc(map->walls, ++(map->numwalls) * sizeof(Wall));
        map->walls[i] = (Wall){ .seg = seg, .id = i };
    }

    fclose(f);

    return map;
}

Map* map_import(const char* path)
{
    FILE *f = fopen(path, "rt");

    Map* map = CreateEmptyMap();

    int j, i, pos, map_width, map_height = 0;
    char map_code;

    map_width = map_height = 32;
    char* map_in = calloc(map_width * map_height,sizeof(char));
    for(i = 0; i < map_width * map_height; i++)      // read in the map file
        fscanf(f, "%x", &(map_in[i]));
    fclose(f);

    float x_pos, y_pos = 0;
    float scale = 128.0;//64.0;
    float grid_width = 128.0;//64.0;

    int wall_count = 0;

    for(i = 0;i < map_height; i++)
    {
        for(j = 0;j < map_width; j++)
        {
            pos = (i * map_width) + j;
            map_code = map_in[pos];
            if(map_code == -1)
            {
                map->player_x = (pos % map_width) * scale;
                map->player_y = (pos / map_height) * scale;
                map_code = 0;
            }
            if(map_code)
            {
                //printf("%f,%f\n", (pos % map_width) * scale, (pos / map_height) * scale);
                x_pos = pos % map_width;
                y_pos = pos / map_height;
    
                Segment seg;

                seg.start.x = x_pos * scale;
                seg.start.y = y_pos * scale;
                seg.end.x   = x_pos * scale + grid_width;
                seg.end.y   = y_pos * scale;
                map->walls = realloc(map->walls, ++(map->numwalls) * sizeof(Wall));
                map->walls[wall_count] = (Wall){ .seg = seg, .tex_idx = map_code - 1, .id = wall_count };
                wall_count++;

                seg.start.x = x_pos * scale + grid_width;
                seg.start.y = y_pos * scale;
                seg.end.x   = x_pos * scale + grid_width;
                seg.end.y   = y_pos * scale - grid_width;
                map->walls = realloc(map->walls, ++(map->numwalls) * sizeof(Wall));
                map->walls[wall_count] = (Wall){ .seg = seg, .tex_idx = map_code - 1, .id = wall_count };
                wall_count++;

                seg.start.x = x_pos * scale + grid_width;
                seg.start.y = y_pos * scale - grid_width;
                seg.end.x   = x_pos * scale;
                seg.end.y   = y_pos * scale - grid_width;
                map->walls = realloc(map->walls, ++(map->numwalls) * sizeof(Wall));
                map->walls[wall_count] = (Wall){ .seg = seg, .tex_idx = map_code - 1, .id = wall_count };
                wall_count++;

                seg.start.x = x_pos * scale;
                seg.start.y = y_pos * scale - grid_width;
                seg.end.x   = x_pos * scale;
                seg.end.y   = y_pos * scale;
                map->walls = realloc(map->walls, ++(map->numwalls) * sizeof(Wall));
                map->walls[wall_count] = (Wall){ .seg = seg, .tex_idx = map_code - 1, .id = wall_count };
                wall_count++;
            }
        }
    }
    free(map_in);

    return map;
}
