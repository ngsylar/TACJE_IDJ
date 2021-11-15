#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <memory>
#include <string>
#include <vector>

#include "Rect.h"

class Component;

#define PI              3.1415926535
#define BG_MUS          "assets/audio/stageState.ogg"
#define BG_SPR          "assets/img/ocean.jpg"
#define FACE_SPR        "assets/img/penguinface.png"
#define FACE_SND        "assets/audio/boom.wav"
#define ALIEN_SPR       "assets/img/alien.png"
#define MINION_SPR      "assets/img/minion.png"
#define BULLET1_SPR     "assets/img/minionbullet1.png"
#define GAMEMAP_TSET    "assets/img/tileset.png"
#define GAMEMAP_TMAP    "assets/map/tileMap.txt"
#define GAMEMAP_TDIM    64, 64

class GameObject {
    private:
        std::vector<std::unique_ptr<Component>> components;
        bool isDead;
    
    public:
        Rect box;
        bool started;

        GameObject();
        ~GameObject();
        void Start();
        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(std::string type);
};

#endif