#include "level.h"


Level::Level(const char* tileset_filename, const char* level_filename) : BaseWindow("Level", WIDTH, HEIGHT) {
    this->tileset = IMG_LoadTexture(renderer, tileset_filename);

    if (! tileset){
        cout << "invalid image format" << endl;
        exit(-1);
    }

    // Allow alpha
    SDL_SetTextureBlendMode(tileset, SDL_BLENDMODE_BLEND);

    this->cursorTile = {0, 0, 16, 16};
    this->levelGrid = vector<vector<int>>();
    this->tileId = 0;

    this->moveCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
    this->drawCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);

    SDL_SetCursor(this->drawCursor);
    
    this->level_filename = level_filename;
    this->load();
}

void Level::save() const{
    // Write out a list to a disk file
    ofstream os(this->level_filename, ios::binary);

    int nbRow = levelGrid.size();

    os.write(LEVEL_HEADER, sizeof(char)*HEADER_LENGTH);

    os.write((const char*)&nbRow, sizeof(int));

    for (int i = 0; i < nbRow; i++) { 
        int rowSize = levelGrid[i].size();

        os.write(reinterpret_cast<const char*>(&rowSize), sizeof(int));

        os.write(reinterpret_cast<const char*>(levelGrid[i].data()), rowSize * sizeof(int));
    }

    os.close();
}

void Level::load() {
    cout << "before" << endl;
    ifstream is(this->level_filename, ios::binary);
    if(!is) return;
    
    char header[HEADER_LENGTH];

    is.read(header, sizeof(char)*HEADER_LENGTH);

    if(strcmp(header, LEVEL_HEADER)){
        cout << "invalid level" << endl;
        exit(-1);
    }
    
    int nbRow, rowSize;

    is.read(reinterpret_cast<char*>(&nbRow), sizeof(int));
    levelGrid.resize(nbRow);
    
    for(int i = 0; i < nbRow; i++){
        is.read(reinterpret_cast<char*>(&rowSize), sizeof(int));
        levelGrid[i].resize(rowSize);
        cout << "after" << endl;
        is.read(reinterpret_cast<char*>(levelGrid[i].data()), rowSize * sizeof(int));
    }

    is.close();
}

void Level::draw() const{
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer); //Not really clearing, more like filling

    SDL_Rect tileDest;
    SDL_Rect tileSrc;

    for(int i=0; i < levelGrid.size(); i++){
        for (int j=0; j < levelGrid[i].size(); j++){
            tileSrc = this->getTileFromID(levelGrid[i][j]);

            tileDest = canevasToScreenspace({i*16*WIN_SCALE_FACTOR, HEIGHT - j*16*WIN_SCALE_FACTOR, 16*WIN_SCALE_FACTOR, 16*WIN_SCALE_FACTOR});

            SDL_RenderCopy(renderer, tileset, &tileSrc, &tileDest);
        }
    }

    tileSrc = this->getTileFromID(tileId);
    
    // Cursor
    if(this->cursorInBounds()){
        SDL_RenderCopy(renderer, tileset, &tileSrc, &cursorTile);
    }

    SDL_RenderPresent(renderer);
}

void Level::handleEvents(const SDL_Event& event){
    // Handle base events with parent class
    BaseWindow::handleEvents(event);

    int tileSize = 16*WIN_SCALE_FACTOR;
    
    switch(event.type){
        case SDL_MOUSEMOTION:
            cursorTile = canevasToScreenspace(tileAtMouse(event.motion.x - xOffset, event.motion.y - yOffset, tileSize));
            break;

        case SDL_MOUSEBUTTONDOWN:
            switch(event.button.button){
                case SDL_BUTTON_LEFT:
                    if(this->cursorInBounds()){
                        addTile((cursorTile.x - xOffset)/tileSize, (HEIGHT - cursorTile.y + yOffset)/tileSize);
                    }
                    break;
                
                case SDL_BUTTON_MIDDLE:
                    SDL_SetCursor(this->moveCursor);
                    break;
            }
            break;

        case SDL_MOUSEBUTTONUP:
            switch(event.button.button){
                case SDL_BUTTON_MIDDLE:
                    SDL_SetCursor(this->drawCursor);
                    break;
            }
            break;
    }
}

void Level::addTile(int x, int y){
    if( x < 0 || y < 0) return;

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

bool Level::cursorInBounds() const{
    return (cursorTile.x - xOffset) >= 0 && (HEIGHT - cursorTile.y + yOffset) >= 0;
}