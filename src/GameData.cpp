#include "GentooEngine.h"
#include "GameData.h"

bool GameData::playerVictory = false;
bool GameData::stageStatePop = false;

bool GameData::PlayerVictory () {
    return playerVictory;
}

bool GameData::StageStatePopRequested () {
    return stageStatePop;
}