#ifndef PENGUIN_CANNON_H
#define PENGUIN_CANNON_H

#include "Timer.h"
#include "Component.h"
#include "Sprite.h"                     // sylar's boss fight
#include "Sound.h"                      // sylar's extra sfx

#define PENGUINC_SPRITE                 "assets/img/cubngun.png"
#define PENGUINC_SHOT_SOUND             "assets/audio/cannonshot.wav"
#define PENGUINC_SHOT_COOLDOWN          0.5f
#define PENGUINC_SHOT_TIMESTART         -4.0f
#define PENGUINC_CENTER_OFFSET          -36.0f, 0.0f
#define PENGUINC_LAYER                  3

#define PENGUINC_BULLET_LABEL           "Projectile"
#define PENGUINC_BULLET_SOUND_SHOT      ""
#define PENGUINC_BULLET_SOUND_HIT       "assets/audio/snowball.wav"
#define PENGUINC_BULLET_SPRITE          "assets/img/penguinbullet.png"
#define PENGUINC_BULLET_FRAME_COUNT     4
#define PENGUINC_BULLET_FRAME_TIME      0.06f
#define PENGUINC_BULLET_FRAME_ONESHOT   true
#define PENGUINC_BULLET_OFFSET          90.0f, 0.0f
#define PENGUINC_BULLET_TARGETS         {"Enemy"}
#define PENGUINC_BULLET_SPEED           600.0f
#define PENGUINC_BULLET_RANGE           2000.0f
#define PENGUINC_BULLET_DAMAGE          20
#define PENGUINC_BULLET_LAYER           2

class PenguinCannon: public Component {
    protected:
        std::weak_ptr<GameObject> pbody;
        float angle;
        Timer cooldown;

        Sprite* sprite;     // sylar's boss fight
        Sound* shotSound;   // sylar's extra sfx
    
    public:
        PenguinCannon(GameObject& associated, GameObject& penguinBody);
        virtual void Start();
        virtual void Update(float dt);
        virtual void Render();
        virtual void Shoot(Vec2 target);
        virtual void NotifyCollision(GameObject& other);
        float GetRelativeCooldown();
        int GetHP();
        bool Is(std::string type);
};

#endif