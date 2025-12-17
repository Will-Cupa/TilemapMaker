#ifndef _TILESET_H_
#define _TILESET_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include <vector>

#include "base_window.h"
#include "level.h"
#include "tile.h"

using namespace std;

const int SCALE_FAC = 5, TILE_SIZE = 16;

class Tileset: public BaseWindow{
private:
    SDL_Texture *tileset;
    SDL_Rect currentTile;
    Level &level;
    vector<Tile> tileList;

public:
    Tileset(const char* filename, Level &level);

    void draw() const override;

    void handleEvents(const SDL_Event &event) override;

    int getIDFromTile(int x, int y, int tileSize) const;
};

#endif
