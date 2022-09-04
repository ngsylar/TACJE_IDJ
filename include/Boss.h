#ifndef BOSS_H
#define BOSS_H

#include "Component.h"
#include "Sprite.h"                 // sylar's extra positioning

#define BOSS_LABEL                  "Enemy"
#define BOSS_SPRITE                 "assets/img/boss.png"
#define BOSS_START_HP               400
#define BOSS_LINEAR_SPEED           200.0f
#define BOSS_MINIMUM_DISTANCE       10.0f
#define BOSS_ROTATION_SPEED         20.0f
#define BOSS_LAYER                  4
#define BOSS_MINION_COUNT           5
#define BOSS_FOE_LABEL              "Player"
#define BOSS_TIMER_START            -2.0f
#define BOSS_MOVEMENT_COOLDOWN      6.0f
#define BOSS_SHOT_COOLDOWN          0.75f

#define BOSS_DEATH_LABEL            "Explosion"
#define BOSS_DEATH_SOUND            "assets/audio/boomAlien.wav"
#define BOSS_DEATH_SOUND_TIMES      1
#define BOSS_DEATH_SPRITE           "assets/img/bossdeath.png"
#define BOSS_DEATH_FRAME_COUNT      4
#define BOSS_DEATH_FRAME_TIME       0.06f
#define BOSS_DEATH_FRAME_ONESHOT    true
#define BOSS_DEATH_SELFDESTRUCTION  true
#define BOSS_DEATH_LAYER            7

class Alien: public Component {
    private:
        enum AlienState {RESTING, MOVING, SLEEPING};
        // enum ShotStyle {SINGLE, MULTIPLE, SPIRAL};

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
        void BreathAnimation(float dt);

    public:
        Alien(GameObject& associated, int minionCount);
        ~Alien();
        void Start();
        void Update(float dt);
        void Render();
        int GetHP();
        void ExplodeAnimation();
        void NotifyCollision(GameObject& other);
        static int GetAlienCount();
        bool Is(std::string type);
};

#endif