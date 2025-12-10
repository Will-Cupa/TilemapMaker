#ifndef _TILE_H_
#define _TILE_H_

#include <SDL2/SDL.h>

class Tile{
private:
    int **horizontalHeights;
    int **verticalHeights;

public:
    Tile(SDL_Texture *tileImage, int tileSize);
};

int** create2DArray(int size);

#endif