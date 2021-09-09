#ifndef SPRITE_H
#define SPRITE_H

#include <string>

#define INCLUDE_SDL
#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#include "Component.h"

class Sprite: public Component {
    private:
        SDL_Texture* texture;
        SDL_Rect clipRect;
        int width, height;

    public:
        Sprite(GameObject& associated);
        Sprite(GameObject& associated, std::string file);
        ~Sprite();
        void Open(std::string file);
        void SetClip(int x, int y, int w, int h);
        void Render();
        int GetWidth();
        int GetHeight();
        bool IsOpen();
        void Update(float dt);
        bool Is(std::string type);
};

#endif