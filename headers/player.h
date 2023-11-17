#ifndef PLAYER_H
#define PLAYER_H

#include "sprite.h"
#include "utils.h"

class Player : public Sprite {
public:
    Player(
        SDL_Texture* texture, 
        SDL_Rect rect, 
        SDL_Rect source_rect,
        std::vector<Sprite*>* sprites
    );
    void update(EventHandler* eh) override;
private:
    std::vector<Sprite*>* sprites;
};

#endif