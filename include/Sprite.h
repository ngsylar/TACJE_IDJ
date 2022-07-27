#ifndef SPRITE_H
#define SPRITE_H

#define INCLUDE_SDL
#include "SDL_include.h"

#include "Component.h"

#define SPR_START_X 0
#define SPR_START_Y 0
#define SPR_ERROR   -1

class Sprite: public Component {
    private:
        SDL_Texture* texture;
        SDL_Rect clipRect;
        int width, height;
        Vec2 scale;

    public:
        Sprite(GameObject& associated);
        Sprite(GameObject& associated, std::string file);
        ~Sprite();
        void Open(std::string file);
        void SetClip(int x, int y, int w, int h);
        void Render();
        void Render(int startX, int startY);
        void SetScale(float scaleX, float scaleY);
        void SetScale(float scale);
        Vec2 GetScale();
        int GetWidth();
        int GetHeight();
        bool IsOpen();
        void Update(float dt);
        bool Is(std::string type);
};

#endif