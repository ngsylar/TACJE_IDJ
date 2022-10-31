#ifndef ALIEN_INTRO_H
#define ALIEN_INTRO_H

#include "AlienBoss.h"

class AlienIntro: public Component {
    public:
        enum EnemyType {ALIEN, BOSS};

        AlienIntro(
            GameObject& associated,
            int minionCount,
            EnemyType type=ALIEN
        );
        void Update(float dt);
        void GenerateNPC();
        bool Is(std::string type);

    private:
        EnemyType type;
        Sprite* sprite;
        float scale;
        int minionCount;
};

#endif