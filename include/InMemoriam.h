#ifndef IN_MEMORIAM_STATE_H
#define IN_MEMORIAM_STATE_H

#include "Timer.h"
#include "State.h"

#define IM_LAA_LABEL    "InMemoriam"
#define IM_LAA_SPRITE   "assets/ui/gameover.k3y"
#define IM_LAA_MUSIC    "assets/ui/silence.wav"
#define IM_LAA_TIME     2.0f
#define IM_LAA_LAYER    0

class InMemoriam: public State {
    private:
        Timer screenTimer;
    
    public:
        InMemoriam();
        void LoadAssets();
        void Start();
        void Update(float dt);
        void RenderBase();
        std::weak_ptr<GameObject> AddObject(GameObject* object);
};

#endif