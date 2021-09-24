#include "Sound.h"
#include "Resources.h"

Sound::Sound (GameObject& associated): Component(associated) {
    chunk = nullptr;
}

Sound::Sound (GameObject& associated, std::string file): Sound(associated) {
    Open(file);
}

Sound::~Sound () {}

void Sound::Open (std::string file) {
    chunk = Resources::GetSound(file);
    channel = SND_AUTOCHANNEL;
}

void Sound::Play (int times) {
    int loops;

    loops = times - ((times > 0)? 1:0);
    channel = Mix_PlayChannel(channel, chunk, loops);
    if (channel == SND_ERROR_PLAY) {
        SDL_Log("Mix_PlayChannel: %s", SDL_GetError());
    }
}

void Sound::Stop () {
    if (chunk and Mix_Playing(channel)) {
        Mix_HaltChannel(channel);
    }
}

bool Sound::IsOpen () {
    return (chunk != nullptr);
}

bool Sound::Playing () {
    return Mix_Playing(channel);
}

void Sound::Update (float dt) {}

void Sound::Render () {}

bool Sound::Is (std::string type) {
    return (type == "Sound");
}