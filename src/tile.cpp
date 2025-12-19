#include "tile.h"

Tile::Tile(int tileId, int tileSize, const void *pixels){
    id = tileId;
    horizontalHeights = create2DArray(tileSize);
    verticalHeights = create2DArray(tileSize);

    calculateVerticalHeight(tileSize, pixels);
}

int** Tile::calculateVerticalHeight(int tileSize, const void *pixels){
    Uint32 *upixels = (Uint32*) pixels;
    // manipulate pixels
    for (int i = 0; i < tileSize * tileSize; i++)
    {
        if (upixels[i] & 0x000F){
            cout << (upixels[i] & 0xFF0000) << endl;
        }

        
    }

    return NULL;
}

int** create2DArray(int size){
    int** array = new int *[size];
    
    for (int i = 0; i < size; i++){
        array[i] = new int[size];
    }

    return array;
}