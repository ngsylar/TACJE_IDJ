#ifndef PENGUIN_BODY_H
#define PENGUIN_BODY_H

#include "Component.h"

#define PENGUINB_LABEL                  "Player"
#define PENGUINB_SPRITE                 "assets/img/penguin.png"
#define PENGUINB_START_POSITION         704.0f, 640.0f
#define PENGUINB_START_HP               100
#define PENGUINB_MAX_SPEED              600.0f
#define PENGUINB_MIN_SPEED              -300.0f
#define PENGUINB_ACCELERATION           200.0f
#define PENGUINB_ROTATION_SPEED         90.0f
#define PENGUINB_LAYER                  1

#define PENGUINB_DEATH_LABEL            "Explosion"
#define PENGUINB_DEATH_SOUND            "assets/audio/boom.wav"
#define PENGUINB_DEATH_SOUND_TIMES      1
#define PENGUINB_DEATH_SPRITE           "assets/img/penguindeath.png"
#define PENGUINB_DEATH_FRAME_COUNT      5
#define PENGUINB_DEATH_FRAME_TIME       0.06f
#define PENGUINB_DEATH_FRAME_ONESHOT    true
#define PENGUINB_DEATH_SELFDESTRUCTION  true
#define PENGUINB_DEATH_LAYER            7

// sylar's extra positioning
#define PENGUINB_CENTER_OFFSET          -6.0f, 0.0f

class PenguinBody: public Component {
    private:
        Rect stageLimits;
        std::weak_ptr<GameObject> pcannon;
        Vec2 speed;
        float angle, linearSpeed, rotationRadSpeed;
        int hp, damageTaken;
    
    public:
        PenguinBody(GameObject& associated);
        ~PenguinBody();
        void Start();
        void Update(float dt);
        void Render();
        void ExplodeAnimation();
        void NotifyCollision(GameObject& other);
        float GetRelativeCooldown();
        int GetHP();
        bool Is(std::string type);
};

#endif