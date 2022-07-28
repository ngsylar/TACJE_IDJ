#ifndef CAMERA_H
#define CAMERA_H

#include "GameObject.h"

#define CAMERA_SPEED 200.0f

class Camera {
    private:
        static GameObject* focus;
    
    public:
        static Vec2 pos, speed;

        static void Follow(GameObject* newFocus);
        static void Unfollow();
        static void Update(float dt);
};

#endif