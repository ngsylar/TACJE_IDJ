#ifndef PAUSE_SCENE_H
#define PAUSE_SCENE_H

#include "State.h"
#include "StageState.h"

#define PAUSESCREEN_LABEL       "PauseScreen"
#define PAUSESCREEN_SPRITE      "assets/ui/pause.k3y"
#define PAUSESCREEN_POSITION    0, 0
#define PAUSESCREEN_LAYER       0

class PauseScene: public State {
    private:
        StageState* gameplayScene;
        GameObject* pauseScreen;
    
    public:
        PauseScene(StageState* gameplayScene);
        ~PauseScene();
        void Start();
        void Update(float dt);
};

#endif