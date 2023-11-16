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

void Player::update() {
    Sprite::update();

    rect.x += 1;
}