#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <memory>
#include <string>
#include <vector>

#include "Rect.h"

class Component;

class GameObject {
    private:
        std::vector<std::unique_ptr<Component>> components;
        bool started, isDead;
        // int renderId;
    
    public:
        std::string label;
        Rect box;
        float angleDeg;
        int layer;

        GameObject(int layer=0, std::string label="");
        ~GameObject();
        void Start();
        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        // void SetRenderIndex(int index);
        // int GetRenderIndex();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(std::string type);
        void NotifyCollision(GameObject& other);
        static bool CompareLayers(
            std::shared_ptr<GameObject>& goA,
            std::shared_ptr<GameObject>& goB
        );
};

#endif