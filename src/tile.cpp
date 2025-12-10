#include "tile.h"

Tile::Tile(SDL_Texture *tileImage, int tileSize){
    horizontalHeights = create2DArray(tileSize);
    verticalHeights = create2DArray(tileSize);


}

int** create2DArray(int size){
    int** array = new int *[size];
    
    for (int i = 0; i < size; i++){
        array[i] = new int[size];
    }

    return array;
}

int** calculateHeights(SDL_Texture *tileImage){
    void *pixels;

    SDL_QueryTexture(tileImage, NULL, NULL, &w, &h);
    SDL_LockTexture(tileImage, NULL, &pixels, NULL);
    
    Uint32 *upixels = (Uint32*) pixels;

    // you will need to know the color of the pixel even if it's transparent
    Uint32 transparent = SDL_MapRGBA(SDL_GetWindowSurface(window)->format, r, g, b, 0x00);

    // manipulate pixels
    for (int i = 0; i < w * h; i++)
    {
        if (upixels[i] == transparent)
            // do stuff
    }
}