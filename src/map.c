#include <stdio.h>
#include <stdlib.h>

#include "map.h"
//#include "dbg.h"
#include "geometry.h"
#include "image_load.h"

Map *map_create_empty() {
    Map *map = malloc(sizeof(struct Map));

    map->walls = NULL;
    map->numwalls = 0;
    map->floortex = image_load("floor.png");
    map->ceiltex = image_load("ceil.png");
    map->walltex = image_load("wall.png");

    return map;
}


Map *map_load(const char *path) {
    FILE *f = fopen(path, "r");

    Map *map = map_create_empty();

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
