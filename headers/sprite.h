#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>
#include "eventhandler.h"

class Sprite {
public:
    SDL_Texture* texture;
    SDL_Rect rect;
    SDL_Rect source_rect;

    Sprite(
        SDL_Texture* texture, 
        SDL_Rect rect,
        SDL_Rect source_rect
    );
    ~Sprite();

    virtual void update(EventHandler* eh);
    virtual void draw(
        SDL_Renderer* renderer_ptr, 
        float offsetX = 0, 
        float offsetY = 0
    );
};

#endif