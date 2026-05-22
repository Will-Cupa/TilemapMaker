#include <SDL2/SDL.h>
#include <iostream>
#include "tileset.h"
#include "level.h"
#include "tinyfiledialogs.h"

using namespace std;

char const * imgExtensionFilter[2] = { "*.png", "*.jpg" };
char const * levelExtensionFilter[1] = { "*.lvl" };

int main(int argc, char *argv[]){
    int init = SDL_Init(SDL_INIT_EVERYTHING);

    if (init < 0){
        cout << "SDL not initialized properly error code :" << init << endl;
        return init;
    };

    cout << "initiated" << endl;

    const char* path = tinyfd_openFileDialog("choose the level to edit", ".", 1, levelExtensionFilter, "level files", 1);

    if (! path){
        return 0;
    }

    char* levelPath = strdup(path);

    path = tinyfd_openFileDialog("choose the tileset to use", ".", 2, imgExtensionFilter, "image files", 1);

    if (! path){
        return 0;
    }

    char* imgPath = strdup(path);

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

