#ifndef END_STATE_H
#define END_STATE_H

#include "State.h"
#include "Music.h"

#define GAMEOVER_LABEL          "GameOver"
#define GAMEOVER_VICTORY_SPRITE "assets/img/win.jpg"
#define GAMEOVER_VICTORY_MUSIC  "assets/audio/endStateWin.ogg"
#define GAMEOVER_DEFEAT_SPRITE  "assets/img/lose.jpg"
#define GAMEOVER_DEFEAT_MUSIC   "assets/audio/endStateLose.ogg"
#define GAMEOVER_LAYER          0

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