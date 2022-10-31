#ifndef MINION_INTRO_H
#define MINION_INTRO_H

#include "MinionBoss.h"

class MinionIntro: public Component {
    public:
        enum EnemyType {MINION, BOSS};

        MinionIntro(
            GameObject& associated,
            GameObject& alienCenter,
            int arrayIndex,
            float arcOffsetDeg=0.0f,
            float scale=1.0f,
            EnemyType type=MINION
        );
        void Start();
        void Update(float dt);
        void GenerateNPC();
        bool Is(std::string type);

    private:
        std::weak_ptr<GameObject> alienCenter;
        int arrayIndex;
        EnemyType type;
        float arc, scale;
        Vec2 position;
};

#endif