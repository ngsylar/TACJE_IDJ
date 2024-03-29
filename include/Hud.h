#ifndef HUD_H
#define HUD_H

#include "Component.h"
#include "CameraFollower.h"
#include "Sprite.h"

#define HUD_LABEL           "HUD"
#define HUD_PLAYER_LABEL    "Player"
#define HUD_SPRITE_NORMAL   "assets/hud/normal.k3y"
#define HUD_SPRITE_SUPER    "assets/hud/super.k3y"
#define HUD_SPRITE_HPBAR    "assets/hud/hp.k3y"
#define HUD_SPRITE_CDBAR    "assets/hud/cooldown.k3y"
#define HUD_POSITION_HPBAR  71.0f, 25.0f
#define HUD_POSITION_CDBAR  71.0f, 42.0f
#define HUD_LAYER_BAR       100
#define HUD_LAYER           99

class Hud: public Component {
    private:
        friend class GameData;

        GameObject* hudHp,* hudCd;
        Sprite* sprite;

    public:
        Hud(GameObject& associated, GameObject& player);
        ~Hud();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
};

class HudHp: public Component {
    private:
        friend class Hud;

        CameraFollower* camera;
        std::weak_ptr<GameObject> player;
        Sprite* sprite;
        int barSize;

    public:
        HudHp(GameObject& associated, GameObject& player);
        ~HudHp();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
};

class HudCd: public Component {
    private:
        friend class Hud;

        CameraFollower* camera;
        std::weak_ptr<GameObject> player;
        Sprite* sprite;
        int barSize;

    public:
        HudCd(GameObject& associated, GameObject& player);
        ~HudCd();
        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
};

#endif