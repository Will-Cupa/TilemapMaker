#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <vector>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "base_window.h"

using namespace std;

const int HEIGHT = 672, WIDTH = 960, WIN_SCALE_FACTOR = 3;

class Level : public BaseWindow{
private:
    vector<vector<int>> levelGrid;
    SDL_Rect cursorTile;
    SDL_Rect srcTile;
    SDL_Texture *tileset;

public:

    Level(const char* filename);

    void draw() const override;

    void handleEvents(const SDL_Event& event) override;

    void setSrcTile(SDL_Rect tile);

    void addTile(int x, int y);

    SDL_Rect getTileFromID(int id) const;
};

#endif
