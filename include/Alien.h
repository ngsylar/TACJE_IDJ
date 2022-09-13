#ifndef ALIEN_H
#define ALIEN_H

#include "Component.h"
#include "Sprite.h"                     // sylar's extra positioning

#define ALIEN_LABEL                     "Enemy"
#define ALIEN_SPRITE                    "assets/img/alien.png"
#define ALIEN_START_HP                  200
#define ALIEN_LINEAR_SPEED              200.0f
#define ALIEN_ROTATION_SPEED            20.0f
#define ALIEN_MINIMUM_DISPLACEMENT      10.0f
#define ALIEN_CENTER_OFFSET             -7.0f, 1.0f
#define ALIEN_LAYER                     4
#define ALIEN_MINION_COUNT              6
#define ALIEN_TIMER_START               -2.0f
#define ALIEN_MOVEMENT_COOLDOWN         6.0f
#define ALIEN_SHOT_COOLDOWN             0.75f
#define ALIEN_FOE_LABEL                 "Player"

#define ALIEN0_START_POSITION           512, 300
#define ALIEN1_START_POSITION           1070, 760
#define ALIEN2_START_POSITION           286, 920

#define ALIEN_DEATH_LABEL               "Explosion"
#define ALIEN_DEATH_SOUND               "assets/audio/boomAlien.wav"
#define ALIEN_DEATH_SOUND_TIMES         1
#define ALIEN_DEATH_SPRITE              "assets/img/aliendeath.png"
#define ALIEN_DEATH_FRAME_COUNT         4
#define ALIEN_DEATH_FRAME_TIME          0.06f
#define ALIEN_DEATH_FRAME_ONESHOT       true
#define ALIEN_DEATH_SELFDESTRUCTION     true
#define ALIEN_DEATH_LAYER               7

class Alien: public Component {
    protected:
        enum AlienState {RESTING, MOVING, SLEEPING};

        int hp, damageTaken;
        AlienState state;
        Timer restTimer, cooldown;
        Vec2 target, speed;
        static int alienCount;
        int minionCount;
        std::vector<std::weak_ptr<GameObject>> minionArray;
        std::weak_ptr<GameObject> penguin;
        
        // sylar's alien breath extra effects
        Sprite* sprite;
        bool breathIn;

        void CheckDeadMinions();
        virtual void ActionRest(float dt);
        virtual void ActionShoot();
        virtual void ActionMove(float dt);
        virtual void BreathAnimation(float dt);
        virtual void ExplodeAnimation();

    public:
        Alien(GameObject& associated, int minionCount);
        ~Alien();
        virtual void Start();
        virtual void Update(float dt);
        virtual void Render();
        virtual void NotifyCollision(GameObject& other);
        Vec2 GetScale();
        int GetHP();
        static int GetAlienCount();
        bool Is(std::string type);
};

#endif