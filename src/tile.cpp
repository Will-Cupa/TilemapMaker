#include "tile.h"

Tile::Tile(int tileId, int tileSize, const void *pixels, Uint32 format){
    id = tileId;
    horizontalHeights = new int[tileSize];
    verticalHeights = new int[tileSize];

    fill(horizontalHeights, horizontalHeights + tileSize, 0);
    fill(verticalHeights, verticalHeights + tileSize, 0);

    cout << "id :" << tileId << endl;
    calculateHeights(tileSize, pixels, format);
}

void Tile::calculateHeights(int tileSize, const void *pixels, Uint32 format){
    Uint32 *upixels = (Uint32*) pixels;
    
    Uint32 alphaMask, *dumped; // We can't pass NULL so we use a dump pointer
    int bpp;

    cout << SDL_GetPixelFormatName(format) << endl;

    SDL_PixelFormatEnumToMasks(format, &bpp , dumped, dumped, dumped, &alphaMask);

    // manipulate pixels

    for (int i = 0; i < tileSize * tileSize; i++)
    {
        if(upixels[i] & alphaMask) {
            verticalHeights[i%16]++;
            horizontalHeights[i/16]++;
        };
    }

    for (int i = 0; i < tileSize; i++)
    {
        cout << verticalHeights[i] << ", " << horizontalHeights[i] << endl;
    }
    
    cout << "tile read" << endl;
}
