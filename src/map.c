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
    map->floortex = nasl_image_load("assets/textures/floor.png");
    map->ceiltex = nasl_image_load("assets/textures/ceil.png");
    map->walltex = nasl_image_load("assets/textures/wall.png");

    return map;
}


Map *M_Load(const char *path) {
    FILE *f = fopen(path, "r");

    Map *map = CreateEmptyMap();

    Segment seg;
    for (int i = 0;
            fscanf(f, "%lf %lf %lf %lf",
                &seg.start.x, &seg.start.y, &seg.end.x, &seg.end.y) != EOF;
            i++)
    {
        map->walls = realloc(map->walls, ++(map->numwalls) * sizeof(Wall));
        map->walls[i] = (Wall){ .seg = seg };
    }

    fclose(f);

    return map;
}
