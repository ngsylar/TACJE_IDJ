#ifndef ALIEN_BOSS_H
#define ALIEN_BOSS_H

#include "Alien.h"

#define ALIEN_BOSS_SPRITE                   "assets/img/boss.png"
#define ALIEN_BOSS_START_HP                 1000
#define ALIEN_BOSS_MINION_COUNT             {6, 5}
#define ALIEN_BOSS_SHOT_COOLDOWN            {0.5f, 0.1f, 0.25f, 0.0f}
#define ALIEN_BOSS_SHOT_SPIRAL_COUNT        3
#define ALIEN_BOSS_DEATH_SPRITE             "assets/img/bossdeath.png"

class AlienBoss: public Alien {
    private:
        enum ShotStyle {SINGLE, MULTIPLE, SPIRAL, SQUAD};

        std::vector<float> shotStylesCooldown, shotStylesBulletSpeed;
        ShotStyle shotStyle;
        static int shotSpiralId;

        void ActionShoot(float dt);
        void ActionMove(float dt);
        void ExplodeAnimation();
    
    public:
        AlienBoss(GameObject& associated, int minionCount);
        void Start();
        void Update(float dt);
};

#endif