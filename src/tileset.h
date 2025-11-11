#ifndef _TILESET_H_
#define _TILESET_H_

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>

#include "base_window.h"
#include "level.h"

using namespace std;

const int SCALE_FAC = 5;

class Tileset: public BaseWindow{
private:
    SDL_Texture *tileset;
    SDL_Rect currentTile;
    Level &level;

public:
    Tileset(const char* filename, Level &level);

    void draw() const override;

    void handleEvents(const SDL_Event &event) override;
};

#endif
