#include "base_window.h"

BaseWindow::BaseWindow(const char* windowName, int width, int height){
    this->window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);

    if (window == nullptr){
        cout << "Failed to create window" << endl;
    }

    this->xOffset = 0;
    this->yOffset = 0;
    this->xOldOffset = 0;
    this->yOldOffset = 0;

    cout << "window created" << endl;

    this->renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    if (renderer == nullptr){
        cout << "Failed to create renderer" << endl;
    }

    cout << "Renderer created" << endl;

    SDL_SetWindowResizable(window, SDL_TRUE);
}


void BaseWindow::handleEvents(const SDL_Event& event){
    switch (event.type){
        // This case will only work for single window app
        case SDL_QUIT:
            SDL_DestroyWindow(window);
            SDL_DestroyRenderer(renderer);
            break;

        case SDL_MOUSEMOTION:
            // Raise window and set focus on hover
            SDL_RaiseWindow(window);
            SDL_SetWindowInputFocus(window);
            break;
        
         case SDL_MOUSEBUTTONDOWN:
            switch(event.button.button){
                case SDL_BUTTON_MIDDLE:
                    // Save old offset
                    xOldOffset = event.motion.x - xOffset;
                    yOldOffset = event.motion.y - yOffset;
                    break;
            }
            
            break;
    }
}

void BaseWindow::update(){
    int x, y;
    if(SDL_GetMouseState(&x, &y) & SDL_BUTTON_MMASK){
        // Displace the grid
        xOffset = x - xOldOffset;
        yOffset = y - yOldOffset;
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
