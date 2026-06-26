#ifndef _BASE_WINDOW_H_
#define _BASE_WINDOW_H_

#include <SDL2/SDL.h>
#include <iostream>

using namespace std;

const float ZOOM_AMOUNT = 0.1f;

class BaseWindow{
protected:
    int xOffset, yOffset, xOldOffset, yOldOffset;
    float zoom;
    SDL_Window *window;
    SDL_Renderer *renderer;

public:
    BaseWindow(const char* windowName, int width=0, int height=0);

    int getWindowId() const;

    SDL_Rect canevasToScreenspace(const SDL_Rect& rect) const;

    virtual void draw() const = 0;

    virtual void handleEvents(const SDL_Event& event);

    virtual void update();

    void destroy();
};

SDL_Rect tileAtMouse(int x, int y, int tileSize);

void scaleRect(SDL_Rect& src, int scale);
#endif
