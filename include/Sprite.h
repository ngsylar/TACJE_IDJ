#ifndef SPRITE_H
#define SPRITE_H

#define INCLUDE_SDL
#include "SDL_include.h"

#include "Component.h"

#define SPRITE_ERROR            -1
#define SPRITE_CLIP_START_POINT 0, 0
#define SPRITE_DEFAULT_SCALE    1.0f, 1.0f

class Sprite: public Component {
    private:
        SDL_Texture* texture;
        SDL_Rect clipRect;
        int width, height;
        Vec2 scale;
        // int frameCount;
        // float frameTime;
        // int currentFrame;
        // float timeElapsed;

    public:
        Sprite(GameObject& associated);
        Sprite(
            GameObject& associated, std::string file,
            int frameCount=1, float frameTime=1.0f
        );
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
        // void SetFrame(int frame);
        // void SetFrameCount(int frameCount);
        // void SetFrameTime(float frameTime);
        void Update(float dt);
        bool IsOpen();
        bool Is(std::string type);
};

#endif