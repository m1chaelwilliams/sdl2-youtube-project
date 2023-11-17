#include "contentmanager.h"

#ifdef DEBUG
#include <iostream>
#endif

ContentManager::~ContentManager() {
#ifdef DEBUG
        std::cout << "Destructing ContentManager..." << std::endl << std::endl;
#endif


}

void ContentManager::free_all() {
#ifdef DEBUG
    std::cout << "Freeing all content in ContentManager (cm)" << std::endl;
#endif
    for (auto& texture : textures) {
#ifdef DEBUG
        std::cout << "Destroying texture: " << texture.first << std::endl;
#endif

        SDL_DestroyTexture(texture.second);
    }
    textures.clear();

    for (auto& font : fonts) {
#ifdef DEBUG
        std::cout << "Destroying font: " << font.first << std::endl;
#endif
        TTF_CloseFont(font.second);
    }
    fonts.clear();
}

SDL_Texture* ContentManager::load_texture(SDL_Renderer* renderer_ptr, SDL_Surface* surf, const char* name, bool free_surf) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_ptr, surf);
    textures[name] = texture;

    if (free_surf) {
        SDL_FreeSurface(surf);
    }

    return texture;
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
    auto it = textures.find(key);
    if (it != textures.end()) {
        return it->second;
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

// fonts

TTF_Font* ContentManager::load_font(const char* filename, int size, const char* name) {
    TTF_Font* font = TTF_OpenFont(filename, size);

    if (!font) {
#ifdef DEBUG
        std::cout << "Failed to open font: " << filename << std::endl;
#endif
        return nullptr;
    }

    const char* key = "";

    if (name) {
        key = name;
    } else {
        key = filename;
    }

    fonts[key] = font;

    return font;
}

TTF_Font* ContentManager::get_font(const char* name) {
    auto it = fonts.find(name);

    if (it != fonts.end()) {
        return it->second;
    }
    return nullptr;
}