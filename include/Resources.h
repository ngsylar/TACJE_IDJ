#ifndef RESOURCES_H
#define RESOURCES_H

#include <string>
#include <unordered_map>

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

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

class Resources {
    private:
        static std::unordered_map<std::string, SDL_Texture*> imageTable;
        static std::unordered_map<std::string, Mix_Music*> musicTable;
        static std::unordered_map<std::string, Mix_Chunk*> soundTable;
    
    public:
        static SDL_Texture* GetImage(std::string file);
        static Mix_Music* GetMusic(std::string file);
        static Mix_Chunk* GetSound(std::string file);
        static void ClearImages();
        static void ClearMusics();
        static void ClearSounds();
};

#endif