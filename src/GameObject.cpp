#include "GameObject.h"
#include "Component.h"

GameObject::GameObject (int layer, std::string label) {
    isDead = false;
    started = false;
    angleDeg = 0.0f;

    this->label = label;
    this->layer = layer;
}

GameObject::~GameObject () {
    components.clear();
}

void GameObject::Start () {
    for (int i=0; i < (int)components.size(); i++)
        components[i]->Start();
    started = true;
}

void GameObject::Update (float dt) {
    for (int i=0; i < (int)components.size(); i++) {
        components[i]->Update(dt);
    }
}

void GameObject::Render () {
    for (int i=0; i < (int)components.size(); i++) {
        components[i]->Render();
    }
}

bool GameObject::IsDead () {
    return isDead;
}

void GameObject::RequestDelete () {
    isDead = true;
}

void GameObject::AddComponent (Component* cpt) {
    components.emplace_back(cpt);
    if (started) {
        cpt->Start();
    }
}

void GameObject::RemoveComponent (Component* cpt) {
    for (int i=((int)components.size())-1; i >= 0; i--) {
        if (components[i].get() == cpt)
            components.erase(components.begin()+i);
    }
}

Component* GameObject::GetComponent (std::string type) {
    for (int i=0; i < (int)components.size(); i++) {
        if (components[i]->Is(type))
            return components[i].get();
    }
    return nullptr;
}

void GameObject::NotifyCollision (GameObject& other) {
    for (int i=0; i < (int)components.size(); i++) {
        components[i]->NotifyCollision(other);
    }
}

bool GameObject::CompareLayers (
    std::weak_ptr<GameObject>& goA,
    std::weak_ptr<GameObject>& goB
) {
    return (goA.lock()->layer < goB.lock()->layer);
}