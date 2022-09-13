#include "GentooEngine.h"
#include "GameData.h"
#include "Hud.h"

std::weak_ptr<GameObject> GameData::hud;
bool GameData::playerVictory = false;
bool GameData::stageStatePop = false;

void GameData::UpdateHud (float dt) {
    if (hud.expired()) return;
    ((Hud*)hud.lock()->GetComponent("Hud"))->hudHp->Update(dt);
} 

bool GameData::PlayerVictory () {
    return playerVictory;
}

bool GameData::StageStatePopRequested () {
    return stageStatePop;
}