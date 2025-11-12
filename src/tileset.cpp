#include "tileset.h"

Tileset::Tileset(const char* filename, Level &level) : BaseWindow::BaseWindow(filename), level(level){
    this->tileset = IMG_LoadTexture(renderer, filename);

    int w, h;
    SDL_QueryTexture(tileset, NULL, NULL, &w, &h);

    SDL_SetWindowSize(window, w*SCALE_FAC, h*SCALE_FAC);

    this->currentTile = {0, 0, TILE_SIZE*SCALE_FAC, TILE_SIZE*SCALE_FAC};
    this->level = level;
}


void Tileset::draw() const{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, tileset, NULL, NULL);

    SDL_RenderDrawRect(renderer, &currentTile);
    SDL_RenderPresent(renderer);
}


void Tileset::handleEvents(const SDL_Event& event){
    switch (event.type){
        case SDL_QUIT:
            // TODO
            break;

        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT){
                currentTile = tileAtMouse(event.motion.x, event.motion.y, TILE_SIZE*SCALE_FAC);
                level.setTileId(this->getIDFromTile(event.motion.x/SCALE_FAC, event.motion.y/SCALE_FAC, TILE_SIZE));
            }
            break;
    }
}

int Tileset::getIDFromTile(int x, int y, int tileSize) const{
    int w;
    SDL_QueryTexture(tileset, NULL, NULL, &w, NULL);

    // row * colMax + col (+ 1 to account for 0 being air)
    return (y/tileSize) * (w/tileSize) + (x/tileSize) + 1;
}
