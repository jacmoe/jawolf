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

char* concat(const char *s1, const char *s2)
{
    char *result = malloc(strlen(s1)+strlen(s2)+1);//+1 for the zero-terminator
    //in real code you would check for errors in malloc here
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

Map *map_import(const char *path)
{
    char* newfile = concat(path, ".map");
    FILE *f = fopen(newfile, "w");

    Map *map = map_create_empty();

    tmx_map *tmxmap;
    tmxmap = tmx_load(path);
    if (!tmxmap)
        tmx_perror("error");

    tmx_layer *layers = tmxmap->ly_head;

    tmx_image *im;
    unsigned int gid;
    float scale = 32.0;
    float grid_width = 32.0;

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
                        fprintf(f, "%f %f %f %f\n",
                                (float)i * scale,
                                (float)j * scale,
                                (float)i * scale + grid_width,
                                (float)j * scale);
                        fprintf(f, "%f %f %f %f\n",
                                (float)i * scale + grid_width,
                                (float)j * scale,
                                (float)i * scale + grid_width,
                                (float)j * scale - grid_width);
                        fprintf(f, "%f %f %f %f\n",
                                (float)i * scale + grid_width,
                                (float)j * scale - grid_width,
                                (float)i * scale,
                                (float)j * scale - grid_width);
                        fprintf(f, "%f %f %f %f\n",
                                (float)i * scale,
                                (float)j * scale - grid_width,
                                (float)i * scale,
                                (float)j * scale);
                    }
                }
            }
        }
        layers = layers->next;
    }
    fclose(f);

    return map_load(newfile);
    //return map;
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
