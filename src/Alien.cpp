#include "Alien.h"
#include "Game.h"
#include "Camera.h"
// #include "Sprite.h"      // idj's original alien
#include "Collider.h"
#include "Minion.h"
#include "Bullet.h"

Alien::Alien (GameObject& associated, int nMinions): Component(associated) {

    // Sprite* sprite;      // idj's original alien
    sprite = new Sprite(associated, ALIEN_SPRITE);
    associated.AddComponent(sprite);
    Collider* collider = new Collider(associated);
    associated.AddComponent(collider);

    associated.label = "Enemy";
    this->nMinions = nMinions;
    hp = ALIEN_START_HP;
}

Alien::Action::Action (ActionType type, Vec2 pos) {
    this->type = type;
    this->pos = pos;
}

Alien::~Alien () {
    minionArray.clear();
}

void Alien::Start () {
    GameObject* minion;
    float minionArcPlacement;

    for (int i=0; i < nMinions; i++) {
        minion = new GameObject();
        minionArcPlacement = (float)i*((PI*2)/nMinions);
        minion->AddComponent(new Minion(*minion, associated, minionArcPlacement));
        minionArray.push_back(Game::GetInstance().GetState().AddObject(minion));
    }
}

Alien::Action Alien::ScheduleAction(InputManager* input, Action::ActionType type) {
    Action action(type, input->GetMousePosition());
    return action;
}

void Alien::Update (float dt) {
    InputManager& input = InputManager::GetInstance();
    Minion* minion;
    
    if (hp <= 0) {
        associated.RequestDelete();
        return;
    }
    for (int i=(int)minionArray.size()-1; i >= 0; i--) {
        minion = (Minion*)minionArray[i].lock()->GetComponent("Minion");
        if (minion->IsDead()) {
            minionArray[i].lock()->RequestDelete();
            minionArray.erase(minionArray.begin()+i);
        }
    }
    
    if (input.MousePress(MOUSE_BUTTON_RIGHT)) {
        taskQueue.push(ScheduleAction(&input, Action::MOVE));
    }
    if (input.MousePress(MOUSE_BUTTON_LEFT)) {
        taskQueue.push(ScheduleAction(&input, Action::SHOOT));
    }

    if (not taskQueue.empty()) {
        Action action = taskQueue.front();

        if (action.type == Action::MOVE) {
            Vec2 alienPosition = associated.box.GetCenter();

            if (alienPosition.DistanceTo(action.pos) > ALIEN_PASSING_DISTANCE) {
                float targetAngle = alienPosition.AngleTo(action.pos);
                speed = alienPosition.DirectionFrom(targetAngle);
                associated.box.Translate(speed * ALIEN_LINEAR_SPEED * dt);
            }
            else {
                associated.box.SetPosition(action.pos);
                taskQueue.pop();
                speed = Vec2();
            }
        }
        else if (action.type == Action::SHOOT) {
            if (not minionArray.empty()) {
                float targetDistance = 999999.0f;
                float minionDistance;
                int minionShooterId;

                for (int i=0; i < (int)minionArray.size(); i++) {
                    minion = (Minion*)minionArray[i].lock()->GetComponent("Minion");
                    minionDistance = minion->GetPosition().DistanceTo(action.pos);

                    if (minionDistance < targetDistance) {
                        targetDistance = minionDistance;
                        minionShooterId = i;
                    }
                }
                // minion = (Minion*)minionArray[rand()%nMinions].lock()->GetComponent("Minion");
                minion = (Minion*)minionArray[minionShooterId].lock()->GetComponent("Minion");
                minion->Shoot(action.pos);
            }
            taskQueue.pop();
        }
    }
    associated.angleDeg += (ALIEN_ROTATION_SPEED * dt);

    // sylar's alien breath extra effects
    BreathAnimation(dt);
}

// sylar's alien breath extra effects
void Alien::BreathAnimation (float dt) {
    float currentScale = sprite->GetScale().x;

    if (currentScale <= 1.0f)
        breathIn = true;
    else if (currentScale >= 1.06f)
        breathIn = false;

    if (breathIn) currentScale += (0.08f*dt);
    else currentScale -= (0.08f*dt);
    
    sprite->SetScale(currentScale);
}

void Alien::Render () {}

void Alien::NotifyCollision (GameObject& other) {
    Bullet* bullet = (Bullet*)other.GetComponent("Bullet");
    if ((bullet != nullptr) and bullet->IsTargetingEnemy()) {
        hp -= bullet->GetDamage();
    }
}

bool Alien::Is (std::string type) {
    return (type == "Alien");
}