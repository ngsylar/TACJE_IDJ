#ifndef OPENING_SCENE_STATE_H
#define OPENING_SCENE_STATE_H

#include "Timer.h"
#include "State.h"

#define OPENING_LABEL           "EngineOpening"
#define OPENING_ENGINE_SPRITE   "assets/ui/engine.k3y"
#define OPENING_PRODUCT_SPRITE  "assets/ui/disclaimer.k3y"
#define OPENING_LAYER           0
#define OPENING_RESET_TIME      5.0f

class OpeningScene: public State {
    private:
        Timer screenTimer;
    
    public:
        OpeningScene();
        void Start();
        void Update(float dt);
        void RenderBase();
};

#endif