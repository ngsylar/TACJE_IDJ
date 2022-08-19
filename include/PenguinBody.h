#ifndef PENGUIN_BODY_H
#define PENGUIN_BODY_H

#include "Component.h"

#define PENGUINB_SPRITE         "assets/img/penguin.png"
#define PENGUINB_START_POSITION 704, 640
#define PENGUINB_START_HP       100
#define PENGUINB_MAX_SPEED      600.0f
#define PENGUINB_ACCELERATION   200.0f
#define PENGUINB_ROTATION_SPEED 90.0f

// sylar's extra positioning
#define PENGUINB_ARC_DISTANCE   1.0f, 0.0f

class PenguinBody: public Component {
    private:
        std::weak_ptr<GameObject> pcannon;
        Vec2 speed;
        float angle, linearSpeed, rotationRadSpeed;
        int hp;
        
        // sylar's extra positioning
        Vec2 position, arcPlacement, center, arcDisplacement;
        float deltaAngle;
    
    public:
        static PenguinBody* player;

        PenguinBody(GameObject& associated);
        ~PenguinBody();
        void Start();
        void Update(float dt);
        void Render();
        void NotifyCollision(GameObject& other);
        bool Is(std::string type);

        // sylar's extra positioning
        Vec2 GetPosition();
};

#endif