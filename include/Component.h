#ifndef COMPONENT_H
#define COMPONENT_H

#include "GameObject.h"

class Component {
    protected:
        GameObject& associated;

    public:
        Component(GameObject& associated);
        virtual ~Component();
        virtual void Start();
        virtual void Update(float dt) = 0;
        virtual void Render() = 0;
        virtual bool Is(std::string type) = 0;
};

#endif