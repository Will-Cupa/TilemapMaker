#ifndef _BASE_WINDOW_H_
#define _BASE_WINDOW_H_

#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

class BaseWindow{
protected:
    SDL_Window *window;
    SDL_Renderer *renderer;

public:
    BaseWindow(const char* windowName, int width=0, int height=0);

    int getWindowId() const;

    virtual void draw() const = 0;

    virtual void handleEvents(const SDL_Event& event);

    void destroy();
};

SDL_Rect tileAtMouse(int x, int y, int tileSize);

void scaleRect(SDL_Rect& src, int scale);
#endif
