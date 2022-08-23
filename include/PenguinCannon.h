#ifndef PENGUIN_CANNON_H
#define PENGUIN_CANNON_H

#include "Component.h"
#include "Sound.h"                      // sylar's extra sfx
#include "Timer.h"
#include "PenguinBody.h"                // sylar's extra positioning

#define PENGUINC_SPRITE                 "assets/img/cubngun.png"
#define PENGUINC_SHOT_SOUND             "assets/audio/cannonshot.wav"
#define PENGUINC_SHOT_COOLDOWN          0.5f
#define PENGUINC_ARC_DISTANCE           5.75f, 0.0f
#define PENGUINC_LAYER                  3

#define PENGUINC_BULLET_LABEL           "Projectile"
#define PENGUINC_BULLET_HIT_SOUND       "assets/audio/snowball.wav"
#define PENGUINC_BULLET_SPRITE          "assets/img/penguinbullet.png"
#define PENGUINC_BULLET_FRAME_COUNT     4
#define PENGUINC_BULLET_FRAME_TIME      0.04f
#define PENGUINC_BULLET_FRAME_ONESHOT   true
#define PENGUINC_BULLET_ARC_DISTANCE    50.0f, 0.0f
#define PENGUINC_BULLET_SPEED           600.0f
#define PENGUINC_BULLET_TARGETS         {"Enemy"}
#define PENGUINC_BULLET_DAMAGE          10
#define PENGUINC_BULLET_LAYER           2

class PenguinCannon: public Component {
    private:
        std::weak_ptr<GameObject> pbody;
        float angle;
        Timer cooldown;

        // sylar's extra positioning
        PenguinBody* pbodyCp;
        Vec2 arcPlacement;

        // sylar's extra sfx
        Sound* shotSound;
    
    public:
        PenguinCannon(GameObject& associated, GameObject& penguinBody);
        void Update(float dt);
        void Render();
        void Shoot(Vec2 target);
        void NotifyCollision(GameObject& other);
        bool Is(std::string type);
};

#endif