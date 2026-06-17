#include "tileset.h"

Tileset::Tileset(const char* filename, Level &level) : BaseWindow::BaseWindow(filename), level(level){
    this->tileset = IMG_LoadTexture(renderer, filename);

    if (! tileset){
        cout << "invalid image format" << endl;
        exit(-1);
    }

    Uint32 format;

    SDL_QueryTexture(tileset, &format, NULL, &tileset_w, &tileset_h);

    SDL_SetWindowSize(window, tileset_w*SCALE_FAC, tileset_h*SCALE_FAC);

    this->currentTile = {0, 0, TILE_SIZE*SCALE_FAC, TILE_SIZE*SCALE_FAC};
    this->level = level;

    this->createTiles(IMG_Load(filename), tileset_h/TILE_SIZE, tileset_w/TILE_SIZE, format);
}

void Tileset::createTiles(SDL_Surface *tileset, int h_tiles, int v_tiles, Uint32 format){
    SDL_Rect rect;
    Tile t;

    void *pixels = SDL_malloc(TILE_SIZE * TILE_SIZE * tileset->format->BytesPerPixel);
    // SDL_free(?)
    for(int y=0; y < v_tiles; y++){
        for(int x=0; x < h_tiles; x++){
            rect = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            
            memcpy(pixels, tileset->pixels + (y * TILE_SIZE * tileset->pitch) + (x * TILE_SIZE * tileset->format->BytesPerPixel), TILE_SIZE * TILE_SIZE * tileset->format->BytesPerPixel);
            
            // y*w + x + 1 formula to get tile id from pos 
            tileList.emplace_back(y*h_tiles + x + 1, TILE_SIZE, pixels, tileset->format->format);
        }
    }
}

void Tileset::draw() const{
    SDL_Rect rect = {xOffset, yOffset, tileset_w*SCALE_FAC, tileset_h*SCALE_FAC};
    SDL_Rect cursor = canevasToScreenspace(currentTile);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, tileset, NULL, &rect);

    SDL_RenderDrawRect(renderer, &cursor);
    SDL_RenderPresent(renderer);
}


void Tileset::handleEvents(const SDL_Event& event){
    // Handle base events with parent class
    BaseWindow::handleEvents(event);

    switch (event.type){
        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT){
                currentTile = tileAtMouse(event.motion.x - xOffset, event.motion.y - yOffset, TILE_SIZE*SCALE_FAC);
                level.setTileId(this->getIDFromTile((event.motion.x-xOffset)/SCALE_FAC, (event.motion.y-yOffset)/SCALE_FAC, TILE_SIZE));
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
