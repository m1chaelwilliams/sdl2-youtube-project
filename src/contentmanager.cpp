#include "contentmanager.h"

#ifdef DEBUG
#include <iostream>
#endif

ContentManager::~ContentManager() {
#ifdef DEBUG
        std::cout << "Destructing ContentManager..." << std::endl << std::endl;
#endif

    for (auto& texture : textures) {

#ifdef DEBUG
        std::cout << "Destroying texture: " << texture.first << std::endl;
#endif

        SDL_DestroyTexture(texture.second);
    }
    textures.clear();
}

SDL_Texture* ContentManager::load_texture(SDL_Renderer* renderer_ptr, const char* filename, const char* name) {
    SDL_Surface* surf = IMG_Load(filename);

    if (!surf) {
#ifdef DEBUG
        std::cout << "Failed to load surface: " << filename << std::endl;
#endif
        return nullptr; 
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_ptr, surf);
    SDL_FreeSurface(surf);

    if (!texture) {
#ifdef DEBUG
        std::cout << "Failed to load texture: " << filename << std::endl;
#endif
        return nullptr;
    }

    const char* key = "";
    if (name) {
        key = name;
    } else {
        key = filename;
    }

    textures[key] = texture; 

#ifdef DEBUG
    std::cout << "Loaded texture: " << key << " successfully!" << std::endl;
#endif

    return texture;
}

SDL_Texture* ContentManager::get_texture(const char* key) {
    if (textures.find(key) != textures.end()) {
        return textures[key];
    }
    return nullptr;
}

SDL_Rect ContentManager::get_rect(const char* filename) {
    SDL_Rect rect{0,0,0,0};

    SDL_Surface* surf = IMG_Load(filename);

    if (!surf) {
        return rect;
    }

    SDL_FreeSurface(surf);

    rect.w = surf->w;
    rect.h = surf->h;

    return rect;
}

