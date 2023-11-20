#ifndef ISCENE_H
#define ISCENE_H

#include <SDL2/SDL.h>
#include "scenemanager.h"
#include "contentmanager.h"
#include "eventhandler.h"
#include "musicplayer.h"
#include "app.h"

namespace se {
    class IScene {
        public:
            IScene(
                IApp* app
            );
            virtual ~IScene();
            virtual void on_load() = 0;
            virtual void on_unload() = 0;
            virtual void on_scene_enter() = 0;
            virtual void on_scene_exit() = 0;
            virtual void on_update() = 0;
            virtual void on_draw() = 0;
        protected:
            IApp* app;
    };
}

#endif