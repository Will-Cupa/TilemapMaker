#ifndef _LEVEL_H_
#define _LEVEL_H_

#include <vector>
#include <fstream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "base_window.h"

#define LEVEL_HEADER "RETROSWING_ENGINE_LEVEL"
#define HEADER_LENGTH 24

using namespace std;

const int HEIGHT = 672, WIDTH = 960, WIN_SCALE_FACTOR = 3;

class Level : public BaseWindow{
private:
    vector<vector<int>> levelGrid;
    SDL_Rect cursorTile;
    SDL_Texture *tileset;
    SDL_Cursor *moveCursor;
    SDL_Cursor *drawCursor;
    int tileId, xOffset, yOffset, xOriginOffset, yOriginOffset;
    bool middleMouse;

public:

    Level(const char* tileset_filename, const char * level_filename);

    void save() const;

    void load(const char* level_filename);

    void draw() const override;

    void handleEvents(const SDL_Event& event) override;

    void update();

    void setTileId(int id);

    void addTile(int x, int y);

    void addOffset(SDL_Rect& rect) const;

    void removeOffset(SDL_Rect& rect) const;

    SDL_Rect getTileFromID(int id) const;

    void displayGrid() const;

    bool cursorInBounds() const;
};

#endif
