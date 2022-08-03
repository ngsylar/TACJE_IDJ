#ifndef PENGUIN_CANNON_H
#define PENGUIN_CANNON_H

#include "Component.h"

#define PENGUINC_SPRITE "assets/img/cubngun.png"

class PenguinCannon: public Component {
    private:
        std::weak_ptr<GameObject> pbody;
        float angle;
    
    public:
        PenguinCannon(GameObject& associated, GameObject& penguinBody);
        void Update(float dt);
        void Render();
        void Shoot(Vec2 target);
        bool Is(std::string type);
};

#endif