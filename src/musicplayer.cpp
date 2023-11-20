#include "musicplayer.h"
#include "debugutils.h"

MusicPlayer::MusicPlayer() {
    front = nullptr;
    volume = MIX_MAX_VOLUME / 2;

    LOG("music player initialized!");
}

MusicPlayer::~MusicPlayer() {
    clear_queue();

    LOG("Music player destructed!");
}

void MusicPlayer::add_to_queue(Mix_Music* track, int num_loops) {
    MusicNode* newTrack = new MusicNode;
    newTrack->track = track;
    newTrack->num_loops = num_loops;
    newTrack->next = nullptr;

    LOG("Added track!");

    if (!front) {
        front = newTrack;
        return;
    }

    MusicNode* curr = front;
    while (curr->next) {
        curr = curr->next;
    }
    curr->next = newTrack;
}

void MusicPlayer::stop() {
    if (is_playing()) {
        Mix_HaltMusic();
    }
}

void MusicPlayer::pause() {
    if (!is_paused()) {
        Mix_PauseMusic();
    }
}

void MusicPlayer::play() {
    Mix_VolumeMusic(volume);

    if (is_empty()) {
        LOG("music player is empty!");
        return;
    }

    Mix_PlayMusic(front->track, front->num_loops);
}

void MusicPlayer::resume() {
    if (is_paused()) {
        Mix_ResumeMusic();
    }
}

bool MusicPlayer::track_finished() const {
    return !Mix_PausedMusic() && !Mix_PlayingMusic();
}

void MusicPlayer::next_track() {
    if (is_empty()) {
        LOG("music player is empty!");
        return;
    }

    LOG("Stopping track");

    stop();

    LOG("Deleting track");

    MusicNode* target = front;
    front = front->next;
    delete target;

    LOG("Playing next track");

    play();
}

void MusicPlayer::clear_queue() {
    LOG("Clearing track queue...");

    while (front) {
        LOG("Deallocating track node");

        MusicNode* target = front;
        front = front->next;
        delete target;
    }
    front = nullptr;
}

void MusicPlayer::restart(int num_loops) {
    if (!is_empty()) {
        Mix_PlayMusic(front->track, num_loops);
    }
}

void MusicPlayer::adjust_volume(int value) {
    volume += value;
    Mix_VolumeMusic(volume);
}

void MusicPlayer::set_volume(int value) {
    volume = value;
    Mix_VolumeMusic(volume);
}

int MusicPlayer::get_volume() const {
    return volume;
}

bool MusicPlayer::is_empty() const {
    return front == nullptr;
}

bool MusicPlayer::is_playing() const {
    return Mix_PlayingMusic() && !Mix_PausedMusic();
}

bool MusicPlayer::is_paused() const {
    return Mix_PausedMusic();
}