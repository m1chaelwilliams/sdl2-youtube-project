#include "sprite.h"

#include "debugutils.h"

Sprite::Sprite(
    SDL_Texture* texture,
    SDL_Rect rect,
    SDL_Rect source_rect
) : texture(texture),
    rect(rect),
    source_rect(source_rect)
{

}

Sprite::~Sprite() {
    LOG("Deallocating sprite!");
}

void Sprite::update(EventHandler* eh) {
    
}

void Sprite::draw(SDL_Renderer* renderer_ptr, float offsetX, float offsetY) {
    // apply offset
    rect.x += offsetX;
    rect.y += offsetY;

    SDL_RenderCopy(
        renderer_ptr, 
        texture, 
        &source_rect, 
        &rect
    );

    // undo offset
    rect.x -= offsetX;
    rect.y -= offsetY;
}