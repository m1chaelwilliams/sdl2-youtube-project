#include "contentmanager.h"

#include "debugutils.h"

ContentManager::~ContentManager() {
    LOG("Destructing ContentManager...");
}

void ContentManager::free_all() {
    
    LOG("Freeing all content in ContentManager (cm)");

    for (auto& texture : textures) {

        LOG("Destroying texture: " << texture.second);

        SDL_DestroyTexture(texture.second);
    }
    textures.clear();

    for (auto& font : fonts) {
        
        LOG("Destroying font: " << font.first);

        TTF_CloseFont(font.second);
    }
    fonts.clear();

    for (auto& m : music) {
        LOG("Destroying music: " << m.first);

        Mix_FreeMusic(m.second);
    }

    for (auto& c : sound_fx) {
        LOG("Destroying sound fx " << c.second);

        Mix_FreeChunk(c.second);
    }
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
        LOG("Failed to load surface: " << filename);

        return nullptr; 
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_ptr, surf);
    SDL_FreeSurface(surf);

    if (!texture) {
        LOG("Failed to load texture: " << filename);

        return nullptr;
    }

    const char* key = "";
    if (name) {
        key = name;
    } else {
        key = filename;
    }

    textures[key] = texture; 

    LOG("Loaded texture: " << key << " successfully!");

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
        LOG("Failed to open font: " << filename);

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

Mix_Music* ContentManager::load_music(const char* filename, const char* name) {
    Mix_Music* m = Mix_LoadMUS(filename);

    if (!m) {
        LOG("failed to open music file: " << filename);
        return nullptr;
    }
    LOG("loaded music: " << filename);

    music[name] = m;

    return m;
}

Mix_Music* ContentManager::get_music(const char* name) {
    auto it = music.find(name);
    if (it != music.end()) {
        return it->second;
    }
    return nullptr;
}

Mix_Chunk* ContentManager::load_sound_fx(const char* filename, const char* name) {
    Mix_Chunk* c = Mix_LoadWAV(filename);

    if (!c) {
        LOG("failed to open music file: " << filename);
        return nullptr;
    }
    LOG("loaded sound fx: " << filename);

    sound_fx[name] = c;

    return c;
}

Mix_Chunk* ContentManager::get_sound_fx(const char* name) {
    auto it = sound_fx.find(name);
    if (it != sound_fx.end()) {
        return it->second;
    }
    return nullptr;
}