#include "tileset.h"

Tileset::Tileset(const char* filename, Level &level) : BaseWindow::BaseWindow(filename), level(level){
    this->tileset = IMG_LoadTexture(renderer, filename);

    int w, h;
    SDL_QueryTexture(tileset, NULL, NULL, &w, &h);

    SDL_SetWindowSize(window, w*SCALE_FAC, h*SCALE_FAC);

    this->currentTile = {0, 0, 16*SCALE_FAC, 16*SCALE_FAC};
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
                currentTile = tileAtMouse(event.motion.x/SCALE_FAC, event.motion.y/SCALE_FAC, 16);
                level.setSrcTile(currentTile);

                scaleRect(currentTile, SCALE_FAC);
            }
            break;
    }
}

void scaleRect(SDL_Rect& src, int scale){
    src = {
        src.x * scale,
        src.y *scale,
        src.w * scale,
        src.h * scale
    };
}
