#include <SDL2/SDL.h>
#include <iostream>
#include "tileset.h"
#include "level.h"
#include "tinyfiledialogs.h"

using namespace std;

const char * imgExtensionFilter[2] = { "*.png", "*.jpg" };
const char * levelExtensionFilter[1] = { "*.lvl" };

char * getUserFilepath(const char * msg, const char ** fileFilter, const char * filterDesc, int filterCount){
    const char* path = tinyfd_openFileDialog(msg, ".", filterCount, fileFilter, filterDesc, false);

    if (! path){
        exit(-1);
    }

    return strdup(path);
}

int main(int argc, char *argv[]){
    int init = SDL_Init(SDL_INIT_EVERYTHING);

    if (init < 0){
        cout << "SDL not initialized properly error code :" << init << endl;
        return init;
    };

    cout << "initiated" << endl;

    char* levelPath = getUserFilepath("choose the level to edit", levelExtensionFilter, "level files", 1);

    char* imgPath  = getUserFilepath("choose the tileset to use", imgExtensionFilter, "image files", 2);


    Level level = Level(imgPath, levelPath);
    free(levelPath);

    Tileset tileset = Tileset(imgPath, level);
    free(imgPath);

    bool running = true;

    SDL_Event event;

    const int tilesetId = tileset.getWindowId();
    const int mainWinId = level.getWindowId();

    const Uint8 *clavier = SDL_GetKeyboardState(NULL);

    while(running){
        //Events input
        while(SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT || (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE)){
                running = false;
            }
          
            if(event.type ==SDL_KEYDOWN){
                level.save();
                if(clavier[SDL_SCANCODE_A])
                {
                    cout << "A pressed" << endl;
                }
            }

            if(event.window.windowID == mainWinId){
                level.handleEvents(event);
            }else if(event.window.windowID == tilesetId){
                tileset.handleEvents(event);
            }
        }

        //Update
        level.update();
        //Draw
        tileset.draw();
        level.draw();
    }

    level.destroy();
    tileset.destroy();
    SDL_Quit();

    return 0;
}

