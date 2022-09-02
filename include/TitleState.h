#ifndef TITLE_STATE_H
#define TITLE_STATE_H

#include "State.h"
#include "Music.h"

#define TITLESCREEN_LABEL                   "TitleScreen"
#define TITLESCREEN_MUSIC_FILE              "assets/audio/endStateWin.ogg"
#define TITLESCREEN_SPRITE_FILE             "assets/img/title.jpg"
#define TITLESCREEN_SPRITE_LAYER            0

#define TITLESCREEN_TEXT_CONTENT            "Pressione Espaco"
#define TITLESCREEN_TEXT_FONT_FILE          "assets/font/Call_me_maybe.ttf"
#define TITLESCREEN_TEXT_FONT_SIZE          48
#define TITLESCREEN_TEXT_DISPLAY_TIME       0.75f
#define TITLESCREEN_TEXT_CONCEAL_TIME       0.5f
#define TITLESCREEN_TEXT_POSITION           512.0f, 510.0f
#define TITLESCREEN_TEXT_LAYER              2
#define TITLESCREEN_TEXT_SHADOW_POSITION    514.0f, 511.0f
#define TITLESCREEN_TEXT_SHADOW_LAYER       1

class TitleState: public State {
    // private:
    //     Music music;
    
    public:
        TitleState();
        void LoadAssets();
        void Start();
        void Update(float dt);
        void Pause();
        void Resume();
};

#endif