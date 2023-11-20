// music player (for background music)
// NOTE: MUSIC PLAYER DOES NOT HANDLE MEMORY
// MEMORY IS DELIGATED TO THE CONTENTMANAGER

#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <SDL2/SDL_mixer.h>
#include <vector>
#include <queue>

namespace se::managers {
    class MusicPlayer {
        public:
            MusicPlayer();
            ~MusicPlayer();
            void add_to_queue(Mix_Music* track, int num_loops = 0);
            void stop();
            void pause();
            void resume();
            void play();
            void next_track();
            void clear_queue();
            void restart(int num_loops = 0);
            void adjust_volume(int amount);
            void set_volume(int value);
            int get_volume() const;
            bool track_finished() const;
            bool is_playing() const;
            bool is_paused() const;
            bool is_empty() const;
        private:
            struct MusicNode{
                Mix_Music* track;
                int num_loops;
                MusicNode* next;
            };

            MusicNode* front;

            int volume;
    };
}

#endif