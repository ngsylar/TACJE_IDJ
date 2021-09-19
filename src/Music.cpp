#include "Music.h"

Music::Music () {
    music = nullptr;
}

Music::Music (std::string file) {
    music = nullptr;
    Open(file);
}

Music::~Music () {
    Stop(MUS_STOP_TIME);
    Mix_FreeMusic(music);
}

void Music::Open (std::string file) {
    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        SDL_Log("Mix_LoadMUS: %s", SDL_GetError());
    }
}

void Music::Play (int times) {
    if (Mix_PlayMusic(music, times) == MUS_ERROR_PLAY) {
        SDL_Log("Mix_PlayMusic: %s", SDL_GetError());
    }
}

void Music::Stop (int msToStop) {
    if (Mix_FadeOutMusic(msToStop) == MUS_ERROR_FADE) {
        SDL_Log("Mix_PlayMusic: %s", SDL_GetError());
    }
}

bool Music::IsOpen () {
    return (music != nullptr);
}