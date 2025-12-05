#include "level.h"


Level::Level(const char* filename) : BaseWindow("Level", WIDTH, HEIGHT) {
    this->tileset = IMG_LoadTexture(renderer, filename);
    
    this->cursorTile = {0, 0, 16, 16};
    this->levelGrid = vector<vector<int>>();
    this->tileId = 0;
    
    this->xOffset = 0;
    this->yOffset = 0;

    this->moveCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_SIZEALL);
    this->drawCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);

    SDL_SetCursor(this->drawCursor);

    this->load();
}

void Level::save() const{
    // Write out a list to a disk file
    ofstream os("data.dat", ios::binary);

    int nbRow = levelGrid.size();

    os.write((const char*)&nbRow, sizeof(int));

    for (int i = 0; i < nbRow; i++) { 
        int rowSize = levelGrid[i].size();

        os.write(reinterpret_cast<const char*>(&rowSize), sizeof(int));

        os.write(reinterpret_cast<const char*>(levelGrid[i].data()), rowSize * sizeof(int));
    }

    os.close();
}

void Level::load() {
    ifstream is("data.dat", ios::binary);
    if(!is) return;
    
    int nbRow, rowSize;

    is.read(reinterpret_cast<char*>(&nbRow), sizeof(int));
    levelGrid.resize(nbRow);

    for(int i = 0; i < nbRow; i++){
        is.read(reinterpret_cast<char*>(&rowSize), sizeof(int));
        levelGrid[i].resize(rowSize);

        is.read(reinterpret_cast<char*>(levelGrid[i].data()), rowSize * sizeof(int));

        i++;
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

            tileDest = {i*16*WIN_SCALE_FACTOR, HEIGHT - j*16*WIN_SCALE_FACTOR, 16*WIN_SCALE_FACTOR, 16*WIN_SCALE_FACTOR};
            addOffset(tileDest);

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
    int tileSize = 16*WIN_SCALE_FACTOR;
    
    switch(event.type){
        case SDL_MOUSEMOTION:
            // Raise window and set focus on hover
            SDL_RaiseWindow(window);
            SDL_SetWindowInputFocus(window);

            cursorTile = tileAtMouse(event.motion.x - xOffset, event.motion.y - yOffset, tileSize);
            addOffset(cursorTile);
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
                    xOriginOffset = event.motion.x - xOffset;
                    yOriginOffset = event.motion.y - yOffset;
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


void Level::update(){
    int x, y;
    if(SDL_GetMouseState(&x, &y) & SDL_BUTTON_MMASK){
        xOffset = x - xOriginOffset;
        yOffset = y - yOriginOffset;
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

void Level::addOffset(SDL_Rect& rect) const{
    rect.x += xOffset;
    rect.y += yOffset;
}

void Level::removeOffset(SDL_Rect& rect) const{
    rect.x -= xOffset/16*WIN_SCALE_FACTOR;
    rect.y -= xOffset/16*WIN_SCALE_FACTOR;
}

bool Level::cursorInBounds() const{
    return (cursorTile.x - xOffset) >= 0 && (HEIGHT - cursorTile.y + yOffset) >= 0;
}