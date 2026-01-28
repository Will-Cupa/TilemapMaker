#include "tile.h"

Tile::Tile(int tileId, int tileSize, const void *pixels, Uint32 format){
    id = tileId;
    horizontalHeights = create2DArray(tileSize);
    verticalHeights = create2DArray(tileSize);

    cout << "id :" << tileId << endl;
    calculateVerticalHeight(tileSize, pixels, format);
}

int** Tile::calculateVerticalHeight(int tileSize, const void *pixels, Uint32 format){
    Uint32 *upixels = (Uint32*) pixels;
    
    Uint32 alphaMask, *dumped; // We can't pass NULL so we use a dump pointer
    int bpp;

    cout << SDL_GetPixelFormatName(format) << endl;

    SDL_PixelFormatEnumToMasks(format, &bpp , dumped, dumped, dumped, &alphaMask);

    // manipulate pixels

    for (int i = 0; i < tileSize * tileSize; i++)
    {
        cout << (upixels[i] & alphaMask) << endl;
    }

    // cout << "tile read" << endl;

    return NULL;
}

int** create2DArray(int size){
    int** array = new int *[size];
    
    for (int i = 0; i < size; i++){
        array[i] = new int[size];
    }

    return array;
}