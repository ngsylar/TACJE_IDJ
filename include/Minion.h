#ifndef MINION_H
#define MINION_H

#include "Component.h"
#include "Sprite.h"                     // sylar's boss fight

#define MINION_LABEL                    "Enemy"
#define MINION_SPRITE                   "assets/img/minion.png"
#define MINION_ARC_RADIUS               120.0f, 0.0f
#define MINION_ARC_SPEED                0.25f
#define MINION_SCALE_MIN                0.66f
#define MINION_SCALE_MAX                1.06f
#define MINION_HP_MODIFIER              20
#define MINION_ANGLEDEG_ADJUST          -90.0f
#define MINION_LAYER                    5

#define MINION_BULLET_LABEL             "Projectile"
#define MINION_BULLET_SOUND_SHOT        "assets/audio/fireshot.wav"
#define MINION_BULLET_SOUND_HIT         "assets/audio/fireimpact.wav"
#define MINION_BULLET_SPRITE            "assets/img/minionbullet2.png"
#define MINION_BULLET_FRAME_COUNT       3
#define MINION_BULLET_FRAME_TIME        0.06f
#define MINION_BULLET_FRAME_ONESHOT     false
#define MINION_BULLET_TARGETS           {"Player"}
#define MINION_BULLET_SPEED             600.0f
#define MINION_BULLET_RANGE             2000.0f
#define MINION_BULLET_DAMAGE            5
#define MINION_BULLET_LAYER             6

#define MINION_DEATH_LABEL              "Explosion"
#define MINION_DEATH_SOUND              "assets/audio/boomMinion.wav"
#define MINION_DEATH_SOUND_TIMES        1
#define MINION_DEATH_SPRITE             "assets/img/miniondeath.png"
#define MINION_DEATH_FRAME_COUNT        4
#define MINION_DEATH_FRAME_TIME         0.06f
#define MINION_DEATH_FRAME_ONESHOT      true
#define MINION_DEATH_SELFDESTRUCTION    true
#define MINION_DEATH_LAYER              7

class Minion: public Component {
    protected:
        std::weak_ptr<GameObject> alienCenter;
        float arc, scale;
        int hp, damageTaken;

        Sprite* sprite;         // sylar's boss fight
        bool playDeathSound;    // sylar's extra sfx
    
    public:
        Minion(
            GameObject& associated,
            GameObject& alienCenter,
            float arcOffsetDeg=0.0f,
            float scale=1.0f
        );
        virtual void Start();
        virtual void Update(float dt);
        virtual void Render();
        virtual void Shoot(Vec2 target);
        virtual void ExplodeAnimation();
        virtual void NotifyCollision(GameObject& other);
        Vec2 GetPosition();
        int GetHP();
        bool IsDead();
        bool Is(std::string type);
};

#endif