#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <algorithm>
#include <vector>

#include "Component.h"
#include "Rect.h"

class GameObject {
    private:
        std::vector<Component*> components;
        bool isDead;
    
    public:
        Rect box;

        GameObject();
        ~GameObject();
        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(std::string type);
};

#endif