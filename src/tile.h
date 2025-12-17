#ifndef _TILE_H_
#define _TILE_H_

#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

class Tile{
private:
    int id, **horizontalHeights, **verticalHeights;

public:
    Tile(int tileId, int tileSize, const void *pixels);

    int** calculateVerticalHeight(const void *pixels);
};

int** create2DArray(int size);

#endif