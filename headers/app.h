#ifndef APP_H
#define APP_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <vector>
#include "eventhandler.h"
#include "scenemanager.h"
#include "contentmanager.h"
#include "musicplayer.h"

namespace se {
    class IApp {
        private:
            bool running;
            int width, height;
            int x, y;
            const char* title;
            SDL_Surface* icon_surface;

            bool app_initialized;
            bool init();
            bool create_display();
            bool create_renderer();
        public:
            void resize(int width, int height);
            void set_title(const char* title);
            void set_icon(const char* filename);
            void set_window_position(int x, int y);
            void center_window();

            int get_width() const;
            int get_height() const;
            int get_window_pos_x() const;
            int get_window_pos_y() const;
            const char* get_title() const;

            void close();
        protected:
            virtual void on_load() = 0;
            virtual void on_unload() = 0;
            virtual void on_update() = 0;
            virtual void on_draw() = 0;
        public:
            IApp(
                int width = 600,
                int height = 400,
                const char* title = "App",
                int window_pos_x = SDL_WINDOWPOS_CENTERED,
                int window_pos_y = SDL_WINDOWPOS_CENTERED
            );
            ~IApp();
            int run();

            managers::SceneManager* get_scene_manager() {return &scene_manager;}
            managers::ContentManager* get_content_manager() {return &content_manager;}
            managers::EventHandler* get_event_handler() {return &event_handler;}
            managers::MusicPlayer* get_music_player() {return &music_player;}
            SDL_Renderer* get_renderer() {return renderer_ptr;}
        protected:
            SDL_Window* window_ptr;
            SDL_Renderer* renderer_ptr;

            managers::SceneManager scene_manager;
            managers::ContentManager content_manager;
            managers::EventHandler event_handler;
            managers::MusicPlayer music_player;
    };
}

#endif