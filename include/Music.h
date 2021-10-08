#ifndef MUSIC_H
#define MUSIC_H

#include <string>

#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

#define MUS_REPEAT_ON   -1
#define MUS_FADE_TIME   1500
#define MUS_STOP_TIME   0
#define MUS_ERROR_PLAY  -1
#define MUS_ERROR_FADE  0

class Music {
    private:
        Mix_Music* music;

    public:
        Music();
        Music(std::string file);
        ~Music();
        void Play(int times=MUS_REPEAT_ON);
        void Stop(int msToStop=MUS_FADE_TIME);
        void Open(std::string file);
        bool IsOpen();
};

#endif