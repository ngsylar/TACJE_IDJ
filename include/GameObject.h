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
        bool HasRenderIndex();
        void SetRenderIndex(int index);
        int GetRenderIndex();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(std::string type);
        void NotifyCollision(GameObject& other);
        static bool CompareLayers(
            std::weak_ptr<GameObject>& goA,
            std::weak_ptr<GameObject>& goB
        );
};

#endif