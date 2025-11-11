#include <SDL2/SDL.h>
#include <iostream>
#include "tileset.h"
#include "level.h"

using namespace std;

int main(int argc, char *argv[]){
    int init = SDL_Init(SDL_INIT_EVERYTHING);

    if (init < 0){
        cout << "SDL not initialized properly error code :" << init << endl;
        return init;
    };

    cout << "initiated" << endl;

    Level level = Level("./tileset/tileset_tropical.png");
    Tileset tileset = Tileset("./tileset/tileset_tropical.png", level);

    bool running = true;

    SDL_Event event;

    const int tilesetId = tileset.getWindowId();
    const int mainWinId = level.getWindowId();

    while(running){
        //Events input
        while(SDL_PollEvent(&event)){
            if(event.window.windowID == mainWinId){
                level.handleEvents(event);
            }else if(event.window.windowID == tilesetId){
                tileset.handleEvents(event);
            }
        }

        //Update

        //Draw
        tileset.draw();
        level.draw();
    }

    level.destroy();
    tileset.destroy();
    SDL_Quit();

    return 0;
}

//to compile
// g++ src/*.cpp -ID:\C++Libraries\SDL2\include -LD:\C++Libraries\SDL2\lib -lmingw32 -lSDL2main -lSDL2 -o bin/main

//g++ src/*.cpp -IZ:\personal\SDL2Library\include -LZ:\personal\SDL2Library\lib -lmingw32 -lSDL2main -lSDL2 -o bin/main
