#include "Sprite.h"
#include "Game.h"
#include "Camera.h"
#include "Resources.h"

Sprite::Sprite (GameObject& associated): Component(associated) {
    selfDestruction = false;
    texture = nullptr;
}

Sprite::Sprite (
    GameObject& associated, std::string file,
    int frameCount, float frameTime, bool oneshot, bool destruct
): Sprite(associated) {
    Open(file, frameCount, frameTime, oneshot, destruct);
}

Sprite::~Sprite () {}

void Sprite::Open (
    std::string file,
    int frameCount, float frameTime, bool oneshot, bool destruct
) {
    texture = Resources::GetImage(file);
    scale = Vec2(SPRITE_DEFAULT_SCALE);

    int qtexture = SDL_QueryTexture(
        texture, nullptr, nullptr,
        &width, &height
    );
    if (qtexture == SPRITE_ERROR) {
        SDL_Log("SDL_QueryTexture: %s", SDL_GetError());
        exit(1);
    }
    
    this->frameCount = frameCount;
    frameTimer = Timer(frameTime);
    frameOneshot = oneshot;
    selfDestruction = destruct;
    currentFrame = 0;

    frameWidth = width / frameCount;
    SetClip(SPRITE_CLIP_START_POINT, frameWidth, height);
    associated.box.SetSize((float)frameWidth, (float)height);
}

void Sprite::SetClip (int x, int y, int w, int h) {
    clipRect = SDL_Rect{x, y, w, h};
}

void Sprite::Render () {
    Render(
        (int)associated.box.x-Camera::pos.x,
        (int)associated.box.y-Camera::pos.y
    );
}

void Sprite::Render (int startX, int startY) {
    SDL_Rect dstrect = SDL_Rect{
        startX, startY,
        (int)associated.box.w, (int)associated.box.h
    };

    int rendercpy = SDL_RenderCopyEx(
        Game::GetInstance().GetRenderer(),
        texture, &clipRect, &dstrect,
        associated.angleDeg, nullptr,
        SDL_FLIP_NONE
    );

    if (rendercpy == SPRITE_ERROR) {
        SDL_Log("SDL_RenderCopy: %s", SDL_GetError());
        exit(1);
    }
}

void Sprite::SetScale (float scaleX, float scaleY) {
    Vec2 size = Vec2((float)frameWidth, (float)height);
    Vec2 position = associated.box.GetCenter();
    scale = Vec2(scaleX, scaleY);
    
    associated.box.SetSize(size.x*scale.x, size.y*scale.y);
    associated.box.SetPosition(position);
}

void Sprite::SetScale (float scale) {
    SetScale(scale, scale);
}

Vec2 Sprite::GetScale () {
    return scale;
}

int Sprite::GetWidth () {
    return (frameWidth * (int)scale.x);
}

int Sprite::GetHeight () {
    return (height * (int)scale.y);
}

void Sprite::SetFrame (int frame) {
    currentFrame = frame % frameCount;
    clipRect.x = currentFrame * frameWidth;
}

void Sprite::SetFrameTime (float frameTime) {
    frameTimer = Timer(frameTime, frameTimer.Get());
}

void Sprite::SetFrameCount (int frameCount) {
    this->frameCount = frameCount;
    frameWidth = width / frameCount;
    currentFrame = 0;
    
    clipRect.x = currentFrame;
    clipRect.w = frameWidth;

    associated.box.w = (float)frameWidth * scale.x;
}

void Sprite::Update (float dt) {
    if (frameTimer.HasInterval()) {
        frameTimer.Update(dt);

        if (frameTimer.IsOver()) {
            SetFrame(currentFrame+1);
            frameTimer.Reset();
            
            if ((currentFrame == frameCount-1) and frameOneshot) {
                frameTimer.SetResetTime(0.0f);

                if (selfDestruction)
                    associated.RequestDelete();
            }
        }
    }
}

bool Sprite::IsOpen () {
    return (texture != nullptr);
}

bool Sprite::Is (std::string type) {
    return (type == "Sprite");
}