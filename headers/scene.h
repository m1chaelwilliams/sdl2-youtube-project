#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include "scenemanager.h"
#include "contentmanager.h"

class Scene {
    public:
        Scene(SDL_Renderer* renderer_ptr, SceneManager* sm, ContentManager* cm);
        ~Scene();
        virtual void on_load();
        virtual void on_unload();
        virtual void update();
        virtual void draw();
    private:
        SceneManager* sm;
        ContentManager* cm;
        SDL_Texture* texture;
        SDL_Renderer* renderer_ptr;
};

#endif