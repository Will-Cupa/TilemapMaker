#ifndef _TILE_H_
#define _TILE_H_

#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

class Tile{
private:
    int id, *horizontalHeights, *verticalHeights;

public:
    Tile() = default;

    Tile(int tileId, int tileSize, const void *pixels, Uint32 format);

    void calculateHeights(int tileSize, const void *pixels, Uint32 format);
};

int** create2DArray(const int size);

#endif