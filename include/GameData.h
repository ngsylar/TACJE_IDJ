#ifndef GAME_DATA_H
#define GAME_DATA_H

class GameData {
    private:
        friend class StageState;
        friend class PauseScene;
        static bool playerVictory;
        static bool stageStatePop;
    
    public:
        static bool PlayerVictory();
        static bool StageStatePopRequested();
};

#endif