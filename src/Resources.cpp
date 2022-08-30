#include "GentooEngine.h"

std::unordered_map<std::string, std::shared_ptr<SDL_Texture>> Resources::imageTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Music>> Resources::musicTable;
std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>> Resources::soundTable;

std::shared_ptr<SDL_Texture> Resources::GetImage (std::string file) {
    SDL_Texture* texture;

    if (imageTable.find(file) == imageTable.end()) {
        texture = IMG_LoadTexture(Game::GetInstance().GetRenderer(), file.c_str());

        if (texture == nullptr) {
            SDL_Log("IMG_LoadTexture: %s", SDL_GetError());
            return nullptr;
        } else
            imageTable[file] = std::shared_ptr<SDL_Texture>(
                texture, [](SDL_Texture* pointer) {SDL_DestroyTexture(pointer);}
            );
    }
    return imageTable[file];
}

std::shared_ptr<Mix_Music> Resources::GetMusic (std::string file) {
    Mix_Music* music;

    if (musicTable.find(file) == musicTable.end()) {
        music = Mix_LoadMUS(file.c_str());

        if (music == nullptr) {
            SDL_Log("Mix_LoadMUS: %s", SDL_GetError());
            return nullptr;
        } else
            musicTable[file] = std::shared_ptr<Mix_Music>(
                music, [](Mix_Music* pointer) {Mix_FreeMusic(pointer);}
            );
    }
    return musicTable[file];
}

std::shared_ptr<Mix_Chunk> Resources::GetSound (std::string file) {
    Mix_Chunk* chunk;

    if (soundTable.find(file) == soundTable.end()) {
        chunk = Mix_LoadWAV(file.c_str());

        if (chunk == nullptr) {
            SDL_Log("Mix_LoadWAV: %s", SDL_GetError());
            return nullptr;
        } else
            soundTable[file] = std::shared_ptr<Mix_Chunk>(
                chunk, [](Mix_Chunk* pointer) {Mix_FreeChunk(pointer);}
            );
    }
    return soundTable[file];
}

void Resources::ClearUniqueImages () {
    std::unordered_map<std::string, std::shared_ptr<SDL_Texture>>::iterator it;
    it = imageTable.begin();
    
    while (it != imageTable.end()) {
        if (it->second.unique())
            it = imageTable.erase(it);
        else it++;
    }
}

void Resources::ClearUniqueMusics () {
    std::unordered_map<std::string, std::shared_ptr<Mix_Music>>::iterator it;
    it = musicTable.begin();

    while (it != musicTable.end()) {
        if (it->second.unique())
            it = musicTable.erase(it);
        else it++;
    }
}

void Resources::ClearUniqueSounds () {
    std::unordered_map<std::string, std::shared_ptr<Mix_Chunk>>::iterator it;
    it = soundTable.begin();

    while (it != soundTable.end()) {
        if (it->second.unique())
            it = soundTable.erase(it);
        else it++;
    }
}

void Resources::ClearUniques () {
    ClearUniqueSounds();
    ClearUniqueMusics();
    ClearUniqueImages();
}

void Resources::ClearAll () {
    imageTable.clear();
    musicTable.clear();
    soundTable.clear();
}