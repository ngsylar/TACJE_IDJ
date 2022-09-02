#ifndef END_STATE_H
#define END_STATE_H

#include "State.h"
#include "Music.h"

#define GAMEOVER_LABEL                  "GameOver"
#define GAMEOVER_VICTORY_SPRITE         "assets/img/win.jpg"
#define GAMEOVER_VICTORY_MUSIC          "assets/audio/endStateWin.ogg"
#define GAMEOVER_DEFEAT_SPRITE          "assets/img/lose.jpg"
#define GAMEOVER_DEFEAT_MUSIC           "assets/audio/endStateLose.ogg"
#define GAMEOVER_LAYER                  0

#define GAMEOVER_TEXT_CONTENT_KEYS      "ESC                                                             SPACE"
#define GAMEOVER_TEXT_CONTENT_STATES      "Back                                                                                                         Try Again"
#define GAMEOVER_TEXT_FONT_FILE         "assets/font/Call_me_maybe.ttf"
#define GAMEOVER_TEXT_FONT_SIZE_KEYS    48
#define GAMEOVER_TEXT_FONT_SIZE_STATES  30
#define GAMEOVER_TEXT_DISPLAY_TIME      0.75f
#define GAMEOVER_TEXT_CONCEAL_TIME      0.5f
#define GAMEOVER_TEXT_POSITION_KEYS     512.0f, 270.0f
#define GAMEOVER_TEXT_POSITION_STATES   512.0f, 310.0f
#define GAMEOVER_TEXT_LAYER             2
#define GAMEOVER_TEXT_SHADOW_KEYS       514.0f, 271.0f
#define GAMEOVER_TEXT_SHADOW_STATES     514.0f, 311.0f
#define GAMEOVER_TEXT_SHADOW_LAYER      1

class EndState: public State {
    private:
        Music music;
    
    public:
        EndState();
        void LoadAssets();
        void Start();
        void Update(float dt);
};

#endif