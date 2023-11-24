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
            Uint32 window_flags;

            SDL_Window* window_ptr;
            SDL_Renderer* renderer_ptr;

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

            int run();
            void close();
        protected:
            virtual void on_load() = 0;
            virtual void on_unload() = 0;
            virtual void on_update() = 0;
            virtual void on_draw() = 0;
            void sync_fps(int fps);
        public:
            IApp(
                int width = 600,
                int height = 400,
                const char* title = "App",
                int window_pos_x = SDL_WINDOWPOS_CENTERED,
                int window_pos_y = SDL_WINDOWPOS_CENTERED,
                Uint32 window_flags = SDL_WINDOW_SHOWN
            );
            ~IApp();
            

            int get_width() const;
            int get_height() const;
            int get_window_pos_x() const;
            int get_window_pos_y() const;
            const char* get_title() const;

            managers::SceneManager* get_scene_manager();
            managers::ContentManager* get_content_manager();
            managers::EventHandler* get_event_handler();
            managers::MusicPlayer* get_music_player();
            SDL_Renderer* get_renderer() const;
            SDL_Window* get_window() const;
        protected:
            managers::SceneManager scene_manager;
            managers::ContentManager content_manager;
            managers::EventHandler event_handler;
            managers::MusicPlayer music_player;
        private:
            // fps stuff
            Uint64 begin_time;
            Uint64 end_time;
    };
}

#endif