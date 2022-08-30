#ifndef RESOURCES_H
#define RESOURCES_H

#include <memory>
#include <unordered_map>
#include <string>

#define INCLUDE_SDL
#define INCLUDE_SDL_MIXER
#include "SDL_include.h"

class Resources {
    private:
        static std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> imageTable;
        static std::unordered_map<std::string, std::shared_ptr<Mix_Music>> musicTable;
        static std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> soundTable;
    
    public:
        static std::shared_ptr<SDL_Texture> GetImage(std::string file);
        static std::shared_ptr<Mix_Music> GetMusic(std::string file);
        static std::shared_ptr<Mix_Chunk> GetSound(std::string file);
        static void ClearUniqueImages();
        static void ClearUniqueMusics();
        static void ClearUniqueSounds();
        static void ClearUniques();
        static void ClearAll();
};

#endif