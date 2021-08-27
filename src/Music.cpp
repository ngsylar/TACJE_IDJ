#include "Music.h"

#define REPEAT_ST_ON -1
#define FADE_DURATION 1500
#define INSTANT_FADE 0

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
        SDL_Log("Mix_LoadMUS error: %s", SDL_GetError());
        exit(1);
    }
}

void Music::Play (int times=REPEAT_ST_ON) {
    if (music) {
        Mix_PlayMusic(music, times);
    }
}

void Music::Stop (int mToStop=FADE_DURATION) {
    Mix_FadeOutMusic(mToStop);
}

bool Music::IsOpen () {
    if (music) return true;
    return false;
}