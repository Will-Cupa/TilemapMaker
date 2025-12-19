#include "tileset.h"

Tileset::Tileset(const char* filename, Level &level) : BaseWindow::BaseWindow(filename), level(level){
    this->tileset = IMG_LoadTexture(renderer, filename);

    int w, h;
    SDL_QueryTexture(tileset, NULL, NULL, &w, &h);

    SDL_SetWindowSize(window, w*SCALE_FAC, h*SCALE_FAC);

    this->currentTile = {0, 0, TILE_SIZE*SCALE_FAC, TILE_SIZE*SCALE_FAC};
    this->level = level;

    this->createTiles(16, 16);
}

void Tileset::createTiles(int w, int h){
    SDL_Rect rect;
    const Uint32 format = SDL_PIXELFORMAT_RGBA8888;
    const int bpp = SDL_BYTESPERPIXEL(format);

    void *pixels = new int[h * w * bpp];
    int pitch = w * bpp;

    SDL_SetRenderTarget(renderer, tileset);

    h /= TILE_SIZE;
    w /= TILE_SIZE;

    for(int x=0; x < h; x++){
        for(int y=0; y < w; y++){
            rect = {x, y, TILE_SIZE, TILE_SIZE};
            SDL_RenderReadPixels(renderer, &rect, format, pixels, pitch);

            // y*w + x + 1 formula to get tile id from pos 
            tileList.push_back(Tile(y*w + x + 1, TILE_SIZE, pixels));
        }
    }
}

void Tileset::draw() const{
    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, tileset, NULL, NULL);

    SDL_RenderDrawRect(renderer, &currentTile);
    SDL_RenderPresent(renderer);
}


void Tileset::handleEvents(const SDL_Event& event){
    switch (event.type){
        case SDL_MOUSEMOTION:
            // Raise window and set focus on hover
            SDL_RaiseWindow(window);
            SDL_SetWindowInputFocus(window);
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
