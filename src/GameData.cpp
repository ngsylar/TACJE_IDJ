#include "GentooEngine.h"
#include "GameData.h"
#include "Hud.h"

std::weak_ptr<GameObject> GameData::hud;
bool GameData::playerVictory = false;
bool GameData::stageStatePop = false;

// editar: GAMBIARRA BRABA
bool GameData::movementAllowed = false;
bool GameData::bossAllowed = true;
int GameData::kills = 0;

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