#ifndef GAME_DATA_H
#define GAME_DATA_H

#include <memory>

#include "GameObject.h"

class GameData {
    private:
        friend class StageState;
        friend class PauseScene;

        static std::weak_ptr<GameObject> hud;
        static bool playerVictory;
        static bool stageStatePop;
    
    public:
        static void UpdateHudHp(float dt);
        static void UpdateHudCd(float dt);
        static bool PlayerVictory();
        static bool StageStatePopRequested();
};

#endif