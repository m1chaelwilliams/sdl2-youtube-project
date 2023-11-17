#include "player.h"
#include <iostream>

Player::Player(
    SDL_Texture* texture,
    SDL_Rect rect,
    SDL_Rect source_rect,
    std::vector<Sprite*>* sprites
) : Sprite(
    texture,
    rect,
    source_rect
    ),
    sprites(sprites)
{

}

void Player::update(EventHandler* eh) {
    Sprite::update(eh);

    int changeX = 0;

    if (eh->is_key_down(SDLK_RIGHT)) {
        changeX += 1;
    }
    if (eh->is_key_down(SDLK_LEFT)) {
        changeX -= 1;
    }

    rect.x += changeX;

    for (const auto& sprite : *sprites) {
        if (sprite != this && intersects(rect, sprite->rect)) {
            rect.x -= changeX;
            break;
        }
    }

    int changeY = 0;
    
    if (eh->is_key_down(SDLK_UP)) {
        changeY -= 1;
    }
    if (eh->is_key_down(SDLK_DOWN)) {
        changeY += 1;
    }
    
    rect.y += changeY;

    for (const auto& sprite : *sprites) {
        if (sprite != this && intersects(rect, sprite->rect)) {
            rect.y -= changeY;
            break;
        }
    }
}