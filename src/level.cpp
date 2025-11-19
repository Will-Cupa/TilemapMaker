#include "level.h"


Level::Level(const char* filename) : BaseWindow("Level", WIDTH, HEIGHT) {
    this->tileset = IMG_LoadTexture(renderer, filename);
    this->cursorTile = {0, 0, 16, 16};
    this->levelGrid = vector<vector<int>>();
    this->tileId = 0;
}

void Level::draw() const{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer); //Not really clearing, more like filling

    SDL_Rect tileDest;
    SDL_Rect tileSrc;

    for(int i=0; i < levelGrid.size(); i++){
        for (int j=0; j < levelGrid[i].size(); j++){
            tileSrc = this->getTileFromID(levelGrid[i][j]);

            tileDest = {i*16*WIN_SCALE_FACTOR, j*16*WIN_SCALE_FACTOR, 16*WIN_SCALE_FACTOR, 16*WIN_SCALE_FACTOR};
            SDL_RenderCopy(renderer, tileset, &tileSrc, &tileDest);
        }
    }

    tileSrc = this->getTileFromID(tileId);
    // Cursor
    SDL_RenderCopy(renderer, tileset, &tileSrc, &cursorTile);

    SDL_RenderPresent(renderer);
}

void Level::handleEvents(const SDL_Event& event){
    int tileSize = 16*WIN_SCALE_FACTOR;
    switch (event.type){
        case SDL_QUIT:
            // TODO
            break;

        case SDL_MOUSEMOTION:
            // Raise window and set focus on hover
            SDL_RaiseWindow(window);
            SDL_SetWindowInputFocus(window);

            cursorTile = tileAtMouse(event.motion.x, event.motion.y, tileSize);
            break;

        case SDL_MOUSEBUTTONDOWN:
            if(event.button.button == SDL_BUTTON_LEFT){
                addTile(cursorTile.x/tileSize, cursorTile.y/tileSize);
            }
    }
}

void Level::addTile(int x, int y){
    while(levelGrid.size() <= x){
        levelGrid.push_back({});
    }

    while(levelGrid[x].size() <= y){
        levelGrid[x].push_back(0);
    }

    levelGrid[x][y] = this->tileId;
}

void Level::setTileId(int id){
    this->tileId = id;
}

SDL_Rect Level::getTileFromID(int id) const{

    if(id==0){
        return {};
    }

    int w, h;
    SDL_QueryTexture(tileset, NULL, NULL, &w, &h);

    id -= 1;
    w/=16;
    h/=16;

    if(id/w < h){
        return {(id%w)*16, (id/w)*16, 16, 16};
    }

    return {(id%w)*16, (h-1)*16, 16, 16};
}


void Level::displayGrid() const{
    cout << "---------------"<< endl;
    for(int i=0; i < levelGrid.size(); i++){
        cout << "row : ";
        for (int j=0; j < levelGrid[i].size(); j++){
            cout << levelGrid[i][j] << " ";
        }
        cout << endl;
    }
}