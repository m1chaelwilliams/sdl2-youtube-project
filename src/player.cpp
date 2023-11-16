#include "player.h"
#include <iostream>

Player::Player(
    SDL_Texture* texture,
    SDL_Rect rect,
    SDL_Rect source_rect
) : Sprite(
    texture,
    rect,
    source_rect
)
{

}

void Player::update(EventHandler* eh) {
    Sprite::update(eh);

    if (eh->is_key_down(SDLK_RIGHT)) {
        rect.x += 1;
    }
    if (eh->is_key_pressed(SDLK_LEFT)) {
        rect.x += 1;
    }
}