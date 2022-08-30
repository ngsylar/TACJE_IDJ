#ifndef STAGE_STATE_H
#define STAGE_STATE_H

#include "State.h"
#include "Music.h"

#define BACKGROUND_LABEL            "Background"
#define BACKGROUND_SPRITE           "assets/img/ocean.jpg"
#define BACKGROUND_MUSIC            "assets/audio/stageState.ogg"
#define BACKGROUND_LAYER            -1

#define GAMEMAP_LABEL               "GameMap"
#define GAMEMAP_TILESET             "assets/img/tileset.png"
#define GAMEMAP_TILESET_TILE_SIZE   64, 64
#define GAMEMAP_TILEMAP0            "assets/map/tileMap0.txt"
#define GAMEMAP_TILEMAP1            "assets/map/tileMap1.txt"
#define GAMEMAP_START_POSITION      0.0f, 0.0f
#define GAMEMAP_TILEMAP0_LAYER      0
#define GAMEMAP_TILEMAP1_LAYER      8

class StageState: public State {
    private:
        friend class PauseScene;
        // GameObject* pauseScreen;
        // TileSet* tileSet;
        Music music;

        // // sylar's extra layer rendering
        // std::vector<std::weak_ptr<GameObject>> renderingArray;
        // bool scheduleLayerSort;

    public:
        StageState();
        ~StageState();
        void LoadAssets();
        void Start();
        void Update(float dt);
        void Pause();
        void Resume();
};

#endif