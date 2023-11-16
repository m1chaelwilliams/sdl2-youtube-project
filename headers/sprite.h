#ifndef SPRITE_H
#define SPRITE_H

#include <SDL2/SDL.h>

class Sprite {
public:
    Sprite(
        SDL_Texture* texture, 
        SDL_Rect rect,
        SDL_Rect source_rect
    );
    ~Sprite();

    virtual void update();
    virtual void draw(
        SDL_Renderer* renderer_ptr, 
        float offsetX = 0, 
        float offsetY = 0
    );
protected:
    SDL_Texture* texture;
    SDL_Rect rect;
    SDL_Rect source_rect;
};

#endif