#include "Bullet.h"
#include "Sprite.h"

Bullet::Bullet (
    GameObject& associated,
    float angle,
    float speed,
    int damage,
    float maxDistance,
    std::string spriteName
): Component(associated) {
    
    Sprite* sprite = new Sprite(associated, spriteName);
    associated.AddComponent(sprite);

    this->speed = Vec2().Direction(angle) * speed;
    this->damage = damage;
    this->distanceLeft = maxDistance;
}

void Bullet::Update (float dt) {
    if (distanceLeft > 0) {
        Vec2 displacement = speed * dt;

        associated.box.x += displacement.x;
        associated.box.y += displacement.y;
        
        distanceLeft -= Vec2().Distance(displacement);

    } else {
        associated.RequestDelete();
    }
}

void Bullet::Render () {}

bool Bullet::Is (std::string type) {
    return (type == "Bullet");
}

int Bullet::GetDamage () {
    return damage;
}