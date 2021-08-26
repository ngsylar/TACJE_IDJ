#include "Music.h"

#define REPEAT_ST_ON -1
#define FADE_DURATION 1500

Music::Music () {
    this->music = nullptr;
}

Music::Music (std::string file) {
    this->music = nullptr;
    this->Open(file);
}

Music::~Music () {
    this->Stop(0);
    Mix_FreeMusic(this->music);
}

void Music::Open (std::string file) {
    this->music = Mix_LoadMUS(file.c_str());
    if (!this->music) {
        SDL_Log("Mix_LoadMUS error: %s", SDL_GetError());
        exit(1);
    }
}

void Music::Play (int times=REPEAT_ST_ON) {
    if (this->music) {
        Mix_PlayMusic(this->music, times);
    }
}

void Music::Stop (int mToStop=FADE_DURATION) {
    Mix_FadeOutMusic(mToStop);
}

bool Music::IsOpen () {
    if (music) return true;
    return false;
}