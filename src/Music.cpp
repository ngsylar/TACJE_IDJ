#include "Music.h"

#define REPEAT_ST_ON -1
#define FADE_DURATION 1500
#define INSTANT_FADE 0
#define ERROR_PLAY -1
#define ERROR_FADE 0

Music::Music () {
    music = nullptr;
}

Music::Music (std::string file) {
    music = nullptr;
    Open(file);
}

Music::~Music () {
    Stop(INSTANT_FADE);
    Mix_FreeMusic(music);
}

void Music::Open (std::string file) {
    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        SDL_Log("Mix_LoadMUS: %s", SDL_GetError());
    }
}

void Music::Play (int times=REPEAT_ST_ON) {
    if (Mix_PlayMusic(music, times) == ERROR_PLAY) {
        SDL_Log("Mix_PlayMusic: %s", SDL_GetError());
    }
}

void Music::Stop (int mToStop=FADE_DURATION) {
    if (Mix_FadeOutMusic(mToStop) == ERROR_FADE) {
        SDL_Log("Mix_PlayMusic: %s", SDL_GetError());
    }
}

bool Music::IsOpen () {
    if (music) return true;
    return false;
}