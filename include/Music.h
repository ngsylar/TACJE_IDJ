#ifndef MUSIC_H
#define MUSIC_H

#include <string>

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#define MUSIC_REPEAT_ON     -1
#define MUSIC_FADE_TIME     1500
#define MUSIC_STOP_TIME     0
#define MUSIC_ERROR_PLAY    -1
#define MUSIC_ERROR_FADE    0

class Music {
    private:
        Mix_Music* music;

    public:
        Music();
        Music(std::string file);
        ~Music();
        void Play(int times=MUSIC_REPEAT_ON);
        void Stop(int msToStop=MUSIC_FADE_TIME);
        void Open(std::string file);
        bool IsOpen();
};

#endif