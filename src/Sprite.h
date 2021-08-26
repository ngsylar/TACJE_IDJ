#include <string>

#define INCLUDE_SDL_IMAGE
#include "SDL_include.h"

#ifndef SPRITE_H
#define SPRITE_H

class Sprite {
    private:
        SDL_Texture* texture;
        SDL_Rect clipRect;
        int width, height;

    public:
        Sprite();
        Sprite(std::string file);
        ~Sprite();
        void Open(std::string file);
        void SetClip(int x, int y, int w, int h);
        void Render(int x, int y);
        int GetWidth();
        int GetHeight();
        bool IsOpen();
};

#endif