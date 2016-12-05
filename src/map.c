#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"
//#include "dbg.h"
#include "geometry.h"
#include "image_load.h"
#include <tmx.h>

Map *map_create_empty()
{
    Map *map = malloc(sizeof(struct Map));

    map->walls = NULL;
    map->numwalls = 0;
    map->floortex = image_load("assets/textures/floor.png");
    map->ceiltex = image_load("assets/textures/ceil.png");
    map->walltex = image_load("assets/textures/wall.png");

    return map;
}

unsigned int gid_clear_flags(unsigned int gid)
{
    return gid & TMX_FLIP_BITS_REMOVAL;
}

Map *map_import(const char *path)
{
    Map *map = map_create_empty();

    tmx_map *tmxmap;
    tmxmap = tmx_load(path);
    if (!tmxmap)
        tmx_perror("error");

    tmx_layer *layers = tmxmap->ly_head;

    tmx_image *im;
    unsigned int gid;

    while (layers)
    {
        if ((layers->type == L_LAYER) && (strcmp(layers->name, "walls") == 0))
        {
            printf("Importing walls!\n");
            for (int i = 0; i < tmxmap->height; i++)
            {
                for (int j = 0; j < tmxmap->width; j++)
                {
                    gid = gid_clear_flags(layers->content.gids[(i * tmxmap->width) + j]);
                    if (tmxmap->tiles[gid] != NULL)
                    {
                        im = tmxmap->tiles[gid]->image;
                        printf("gid %d (%d, %d) %s\n", gid, i, j, im->source);
                    }
                }
            }
        }
        layers = layers->next;
    }

    return map;
}

Map *map_load(const char *path)
{
    FILE *f = fopen(path, "r");

    Map *map = map_create_empty();

    Segment seg;
    for (int i = 0;
         fscanf(f, "%lf %lf %lf %lf",
                &seg.start.x, &seg.start.y, &seg.end.x, &seg.end.y) != EOF;
         i++)
    {
        map->walls = realloc(map->walls, ++(map->numwalls) * sizeof(Wall));
        map->walls[i] = (Wall){.seg = seg};
    }

    fclose(f);

    return map;
}
