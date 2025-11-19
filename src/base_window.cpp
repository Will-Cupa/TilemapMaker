#include "base_window.h"

BaseWindow::BaseWindow(const char* windowName, int width, int height){
    this->window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if (window == nullptr){
        cout << "Failed to create window" << endl;
    }

    cout << "window created" << endl;

    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr){
        cout << "Failed to create renderer" << endl;
    }

    cout << "Renderer created" << endl;
}


void BaseWindow::handleEvents(const SDL_Event& event){
    switch (event.type){
        case SDL_QUIT:
            // TODO
            break;

        case SDL_MOUSEMOTION:
            // Raise window and set focus on hover
            SDL_RaiseWindow(window);
            SDL_SetWindowInputFocus(window);
            break;
    }
}


int BaseWindow::getWindowId() const{
    return SDL_GetWindowID(window);
}


void BaseWindow::destroy(){
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}


SDL_Rect tileAtMouse(int x, int y, int tileSize){
    // Round to nearest 16 multiple
    return {x/tileSize * tileSize, y/tileSize * tileSize, tileSize, tileSize};
}
