#include "Music.h"

#define REPEAT_ON -1
#define FADE_TIME 1500
#define STOP_TIME 0
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
    Stop(STOP_TIME);
    Mix_FreeMusic(music);
}

void Music::Open (std::string file) {
    music = Mix_LoadMUS(file.c_str());
    if (music == nullptr) {
        SDL_Log("Mix_LoadMUS: %s", SDL_GetError());
    }
}

void Music::Play (int times=REPEAT_ON) {
    if (Mix_PlayMusic(music, times) == ERROR_PLAY) {
        SDL_Log("Mix_PlayMusic: %s", SDL_GetError());
    }
}

void Music::Stop (int mToStop=FADE_TIME) {
    if (Mix_FadeOutMusic(mToStop) == ERROR_FADE) {
        SDL_Log("Mix_PlayMusic: %s", SDL_GetError());
    }
}

bool Music::IsOpen () {
    return (music != nullptr);
}