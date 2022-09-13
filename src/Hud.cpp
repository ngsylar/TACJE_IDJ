#include "GentooEngine.h"
#include "Hud.h"
#include "PenguinBody.h"

Hud::Hud (GameObject& associated, GameObject& player): Component(associated) {
    CameraFollower* camera = new CameraFollower(associated);
    sprite = new Sprite(associated, HUD_SPRITE_NORMAL);
    associated.AddComponent(camera);

    hudHp = new GameObject(HUD_LAYER_BAR, HUD_LABEL);
    hudHp->AddComponent(new HudHp(*hudHp, player));
}

HudHp::HudHp (GameObject& associated, GameObject& player): Component(associated) {
    camera = new CameraFollower(associated);
    associated.AddComponent(camera);

    sprite = new Sprite(associated, HUD_SPRITE_HPBAR);
    camera->offset = Vec2(HUD_POSITION_HPBAR);
    
    State& state = Game::GetInstance().GetCurrentState();
    std::weak_ptr<GameObject> hud = state.GetObjectPtr(&associated);

    this->player = Game::GetInstance().GetCurrentState().GetObjectPtr(&player);
}

Hud::~Hud () {
    delete hudHp;
    delete sprite;
}

HudHp::~HudHp () {
    delete sprite;
}

void Hud::Start () {
    hudHp->Start();
}

void HudHp::Start () {
    int hp = ((PenguinBody*)player.lock()->GetComponent("PenguinBody"))->GetHP();
    barSize = associated.box.w;
    float value = 0.01f * hp * barSize;
    sprite->SetClip(0, 0, (int)std::ceil(value), (int)associated.box.h);
    associated.box.SetSize(std::ceil(value), associated.box.h);
}

void Hud::Update (float dt) {
    ((HudHp*)hudHp->GetComponent("HudHp"))->camera->Update(dt);
}

void HudHp::Update (float dt) {
    if (player.expired()) {
        sprite->SetClip(0, 0, 0, 0);
        sprite->SetScale(0.0f, 0.0f);
    }
    int hp = ((PenguinBody*)player.lock()->GetComponent("PenguinBody"))->GetHP();
    float value = 0.01f * hp * barSize;
    sprite->SetClip(0, 0, (int)std::ceil(value), (int)associated.box.h);
    associated.box.SetSize(std::ceil(value), associated.box.h);
}

void Hud::Render () {
    sprite->Render();
    hudHp->Render();
}

void HudHp::Render () {
    sprite->Render();
}

bool Hud::Is (std::string type) {
    return (type == "Hud");
}

bool HudHp::Is (std::string type) {
    return (type == "HudHp");
}