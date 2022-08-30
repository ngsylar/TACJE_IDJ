#ifndef TITLE_STATE_H
#define TITLE_STATE_H

#include "State.h"
#include "Music.h"

#define TITLESCREEN_LABEL   "TitleScreen"
#define TITLESCREEN_SPRITE  "assets/img/title.jpg"
#define TITLESCREEN_MUSIC   "assets/audio/endStateWin.ogg"
#define TITLESCREEN_LAYER   0

class TitleState: public State {
    private:
        Music music;
    
    public:
        TitleState();
        void Start();
        void Update(float dt);
        void Pause();
        void Resume();
};

#endif