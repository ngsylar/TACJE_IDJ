#include "GentooEngine.h"
#include "AlienBoss.h"

int AlienBoss::shotSpiralId = 0;

AlienBoss::AlienBoss (GameObject& associated, int minionCount): Alien(associated, minionCount) {
    delete sprite;
    sprite = new Sprite(associated, ALIEN_BOSS_SPRITE);

    // shotStylesCooldown = ALIEN_BOSS_SHOT_COOLDOWN;
    shotStylesCooldown = {0.5f, 0.1f, 0.25f, 0.0f};
    ShotStyle initialStyle = SINGLE;

    float startTime = ALIEN_SHOT_COOLDOWN + ALIEN_TIMER_START;
    restTimer = Timer(ALIEN_MOVEMENT_COOLDOWN, startTime);
    cooldown = Timer(shotStylesCooldown[initialStyle], startTime);
    shotStyle = initialStyle;
}

void AlienBoss::Update (float dt) {
    if (damageTaken > 0) {
        hp -= damageTaken;
        damageTaken = 0;
        // SDL_Log("Alien %d", hp);     // remover linha
    }
    if (hp <= 0) {
        ExplodeAnimation();
        associated.RequestDelete();
        return;
    }
    CheckDeadMinions();

    // State Sleeping
    if (penguin.expired()) {
        state = SLEEPING;
    }
    // State Generation
    else if (minionArray.empty()) {
        // gerar novos minions aqui
    }
    // State Resting/Shooting
    if (state == RESTING) {
        ActionRest(dt);
    }
    // State Moving
    else if (state == MOVING) {
        ActionMove(dt);
    }

    associated.angleDeg += (ALIEN_ROTATION_SPEED * dt);
    BreathAnimation(dt);    // sylar's alien breath extra effects
}

void AlienBoss::ActionRest (float dt) {
    cooldown.Update(dt);
    if (cooldown.IsOver() and (not minionArray.empty())) {
        ActionShoot(dt);
        cooldown.Reset();
    }

    restTimer.Update(dt);
    if (restTimer.IsOver()) {
        target = penguin.lock()->box.GetPosition();
        restTimer.Reset();
        state = MOVING;
    }
}

void AlienBoss::ActionShoot (float dt) {
    Minion* minion;
    
    if (shotStyle == SINGLE) {
        Vec2 minionPosition;
        float angle;

        if (shotSpiralId < ALIEN_BOSS_SHOT_SPIRAL_COUNT) {
            cooldown = Timer(shotStylesCooldown[SINGLE]);
            shotSpiralId++;
        } else {
            cooldown = Timer(ALIEN_SHOT_COOLDOWN);
            shotSpiralId = 0;
            return;
        }

        for (int i=0; i < (int)minionArray.size(); i++) {
            minion = (Minion*)minionArray[i].lock()->GetComponent("Minion");
            minionPosition = minionArray[i].lock()->box.GetPosition();
            angle = Deg2Rad(minionArray[i].lock()->angleDeg + MINION_ANGLEDEG_ADJUST);
            target = minionPosition + Vec2().DirectionFrom(angle);
            minion->Shoot(target);
        }
    }
    else if (shotStyle == MULTIPLE) {
        float targetDistance = 999999.0f;
        float minionDistance;
        int minionShooterId;

        target = penguin.lock()->box.GetPosition();

        for (int i=0; i < (int)minionArray.size(); i++) {
            minion = (Minion*)minionArray[i].lock()->GetComponent("Minion");
            minionDistance = minion->GetPosition().DistanceTo(target);

            if (minionDistance < targetDistance) {
                targetDistance = minionDistance;
                minionShooterId = i;
            }
        }
        minion = (Minion*)minionArray[minionShooterId].lock()->GetComponent("Minion");
        minion->Shoot(target);
    }
    
    else if (shotStyle == SPIRAL) {
        Vec2 minionPosition;
        float angle;

        for (int i=0; i < (int)minionArray.size(); i++) {
            minion = (Minion*)minionArray[i].lock()->GetComponent("Minion");
            minionPosition = minionArray[i].lock()->box.GetPosition();
            angle = Deg2Rad(minionArray[i].lock()->angleDeg + MINION_ANGLEDEG_ADJUST);
            target = minionPosition + Vec2().DirectionFrom(angle);
            minion->Shoot(target);
        }
    }
}

void AlienBoss::ActionMove (float dt) {
    Vec2 currentPosition = associated.box.GetPosition();

    if (currentPosition.DistanceTo(target) > ALIEN_MINIMUM_DISPLACEMENT) {
        float targetAngle = currentPosition.AngleTo(target);
        speed = currentPosition.DirectionFrom(targetAngle);
        associated.box.Translate(speed * ALIEN_LINEAR_SPEED * dt);
    }
    else {
        shotStyle = static_cast<ShotStyle>(rand()%shotStylesCooldown.size());
        cooldown = Timer(shotStylesCooldown[shotStyle], shotStylesCooldown[shotStyle]);
        associated.box.SetPosition(target);
        speed = Vec2();
        state = RESTING;
    }
}