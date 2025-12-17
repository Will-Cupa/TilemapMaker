#include "tile.h"

Tile::Tile(int tileSize, int tileId, const void *pixels){
    id = tileId;
    horizontalHeights = create2DArray(tileSize);
    verticalHeights = create2DArray(tileSize);

    calculateVerticalHeight(pixels);
}

int** Tile::calculateVerticalHeight(const void *pixels){
    Uint32 *upixels = (Uint32*) pixels;

    // you will need to know the color of the pixel even if it's transparent
    // Uint32 transparent = SDL_MapRGBA(SDL_GetWindowSurface(window)->format, r, g, b, 0x00);

    // manipulate pixels
    // for (int i = 0; i < w * h; i++)
    // {
    //     if (upixels[i] != transparent);

    //     cout << i << endl;
    // }

    return NULL;
}

int** create2DArray(int size){
    int** array = new int *[size];
    
    for (int i = 0; i < size; i++){
        array[i] = new int[size];
    }

    return array;
}