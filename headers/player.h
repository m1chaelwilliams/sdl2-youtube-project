#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"

class Player : public Sprite {
public:
    Player(
        SDL_Texture* texture, 
        SDL_Rect rect, 
        SDL_Rect source_rect
    );
    void update(EventHandler* eh) override;
};

#endif