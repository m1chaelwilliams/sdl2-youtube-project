#ifndef SCENE_H
#define SCENE_H

#include <SDL2/SDL.h>
#include "scenemanager.h"
#include "contentmanager.h"
#include "eventhandler.h"

class Scene {
    public:
        Scene(
            SDL_Renderer* renderer_ptr, 
            SceneManager* sm, 
            ContentManager* cm,
            EventHandler* eh
        );
        virtual ~Scene();
        virtual void on_load();
        virtual void on_unload();
        virtual void update();
        virtual void draw();
    protected:
        SceneManager* sm;
        ContentManager* cm;
        EventHandler* eh;
        SDL_Texture* texture;
        SDL_Renderer* renderer_ptr;
};

#endif