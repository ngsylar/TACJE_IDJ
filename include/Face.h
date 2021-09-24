#ifndef FACE_H
#define FACE_H

#include "Component.h"

#define FCE_INIT_HP 30

class Face: public Component {
    private:
        int hitpoints;
        
    public:
        Face(GameObject& associated);
        ~Face();
        void Damage(int damage);
        void Update(float dt);
        void Render();
        bool Is(std::string type);
};

#endif