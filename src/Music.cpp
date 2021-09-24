#include "Music.h"
#include "Resources.h"

Music::Music () {
    music = nullptr;
}

Music::Music (std::string file) {
    music = nullptr;
    Open(file);
}

Music::~Music () {}

void Music::Open (std::string file) {
    music = Resources::GetMusic(file);
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