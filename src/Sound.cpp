#include "Sound.h"

#define REPEAT_OFF 1
#define ERROR_PLAY -1

Sound::Sound (GameObject& associated): Component(associated) {
    chunk = nullptr;
}

Sound::Sound (GameObject& associated, std::string file): Sound(associated) {
    Open(file);
}

Sound::~Sound () {
    if (chunk) {
        Stop();
        Mix_FreeChunk(chunk);
        chunk = nullptr;
    }
}

void Sound::Open (std::string file) {
    chunk = Mix_LoadWAV(file.c_str());
    if (chunk == NULL) {
        SDL_Log("Mix_LoasWAV: %s", SDL_GetError());
    }
    channel = -1;
}

void Sound::Play (int times=REPEAT_OFF) {
    int loops;

    loops = times - ((times > 0)? 1:0);
    channel = Mix_PlayChannel(channel, chunk, loops);
    if (channel == ERROR_PLAY) {
        SDL_Log("Mix_PlayChannel: %s", SDL_GetError());
    }
}

void Sound::Stop () {
    if (Mix_Playing(channel)) {
        Mix_HaltChannel(channel);
    }
}

bool Sound::IsOpen () {
    return (chunk != nullptr);
}

void Sound::Update (float dt) {}

void Sound::Render () {}

bool Sound::Is (std::string type) {
    return (type == "Sound");
}