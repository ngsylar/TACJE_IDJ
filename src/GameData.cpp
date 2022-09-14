#include "GentooEngine.h"
#include "GameData.h"
#include "Hud.h"

std::weak_ptr<GameObject> GameData::hud;
bool GameData::movementAllowed = false;
bool GameData::playerVictory = false;
bool GameData::stageStatePop = false;

void GameData::UpdateHudHp (float dt) {
    if (hud.expired()) return;
    ((Hud*)hud.lock()->GetComponent("Hud"))->hudHp->Update(dt);
}

void GameData::UpdateHudCd (float dt) {
    if (hud.expired()) return;
    ((Hud*)hud.lock()->GetComponent("Hud"))->hudCd->Update(dt);
}

bool GameData::PlayerVictory () {
    return playerVictory;
}

bool GameData::StageStatePopRequested () {
    return stageStatePop;
}