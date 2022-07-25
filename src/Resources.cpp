#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#include "Resources.h"
#include "Game.h"

std::unordered_map<std::string, SDL_Texture*> Resources::imageTable;
std::unordered_map<std::string, Mix_Music*> Resources::musicTable;
std::unordered_map<std::string, Mix_Chunk*> Resources::soundTable;

SDL_Texture* Resources::GetImage (std::string file) {
    SDL_Texture* texture;

    if (imageTable.find(file) == imageTable.end()) {
        texture = IMG_LoadTexture(
            Game::GetInstance().GetRenderer(), file.c_str()
        );
        if (texture == nullptr) {
            SDL_Log("IMG_LoadTexture: %s", SDL_GetError());
            exit(1);
        } else {
            imageTable[file] = texture;
        }
        return texture;
        
    } else {
        return imageTable[file];
    }
}

Mix_Music* Resources::GetMusic (std::string file) {
    Mix_Music* music;

    if (musicTable.find(file) == musicTable.end()) {
        music = Mix_LoadMUS(file.c_str());
        if (music == nullptr) {
            SDL_Log("Mix_LoadMUS: %s", SDL_GetError());
        } else {
            musicTable[file] = music;
        }
        return music;
        
    } else {
        return musicTable[file];
    }
}

Mix_Chunk* Resources::GetSound (std::string file) {
    Mix_Chunk* chunk;

    if (soundTable.find(file) == soundTable.end()) {
        chunk = Mix_LoadWAV(file.c_str());
        if (chunk == NULL) {
            SDL_Log("Mix_LoadWAV: %s", SDL_GetError());
        } else {
            soundTable[file] = chunk;
        }
        return chunk;
        
    } else {
        return soundTable[file];
    }
}

void Resources::ClearImages () {
    std::unordered_map<std::string, SDL_Texture*>::iterator texture;
    for (texture=imageTable.begin(); texture!=imageTable.end(); texture++) {
        SDL_DestroyTexture(texture->second);
    }
    imageTable.clear();
}

void Resources::ClearMusics () {
    std::unordered_map<std::string, Mix_Music*>::iterator music;
    for (music=musicTable.begin(); music!=musicTable.end(); music++) {
        Mix_FreeMusic(music->second);
    }
    musicTable.clear();
}

void Resources::ClearSounds () {
    std::unordered_map<std::string, Mix_Chunk*>::iterator chunk;
    for (chunk=soundTable.begin(); chunk!=soundTable.end(); chunk++) {
        Mix_FreeChunk(chunk->second);
    }
    soundTable.clear();
}