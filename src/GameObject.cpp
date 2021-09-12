#include "GameObject.h"

GameObject::GameObject () {
    isDead = false;
}

GameObject::~GameObject () {
    for (
        std::vector<Component*>::reverse_iterator cpt_ptr = components.rbegin();
        cpt_ptr != components.rend();
        cpt_ptr++
    ) {
        delete *cpt_ptr;
    }
    components.clear();
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
    components.push_back(cpt);
}

void GameObject::RemoveComponent (Component* cpt) {
    std::vector<Component*>::iterator cpt_ptr;
    cpt_ptr = std::find(components.begin(), components.end(), cpt);
    if (*cpt_ptr == cpt) {
        components.erase(cpt_ptr);
    }
}

Component* GameObject::GetComponent (std::string type) {
    for (int i=0; i < (int)components.size(); i++) {
        if (components[i]->Is(type)) {
            return components[i];
        }
    }
    return nullptr;
}