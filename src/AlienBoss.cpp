#include "GentooEngine.h"
#include "AlienBoss.h"
#include "MinionBoss.h"

int AlienBoss::shotSpiralId = 0;

AlienBoss::AlienBoss (GameObject& associated, int minionCount): Alien(associated, minionCount) {
    delete sprite;
    sprite = new Sprite(associated, ALIEN_BOSS_SPRITE);

    shotStylesCooldown = ALIEN_BOSS_SHOT_COOLDOWN;
    shotStylesBulletSpeed = MINION_BOSS_BULLET_SPEED;
    ShotStyle initialStyle = SINGLE;

    hp = ALIEN_BOSS_START_HP;

    float startTime = ALIEN_SHOT_COOLDOWN + ALIEN_TIMER_START;
    restTimer = Timer(ALIEN_MOVEMENT_COOLDOWN, startTime);
    cooldown = Timer(shotStylesCooldown[initialStyle], startTime);
    shotStyle = initialStyle;
}

void AlienBoss::Start () {
    State& gameState = Game::GetInstance().GetCurrentState();
    GameObject* minion;
    float minionArcPlacement;

    for (int i=0; i < minionCount; i++) {
        minion = new GameObject(MINION_LAYER, MINION_LABEL);
        minionArcPlacement = (float)i*((PI*2)/minionCount);
        minion->AddComponent(new MinionBoss(*minion, associated, minionArcPlacement));
        minionArray.push_back(gameState.AddObject(minion));
    }
    penguin = gameState.GetObjectPtr(ALIEN_FOE_LABEL);
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
    BreathAnimation(dt);
}

void AlienBoss::ActionShoot (float dt) {
    MinionBoss* minion;
    
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
            minion = (MinionBoss*)minionArray[i].lock()->GetComponent("Minion");
            minionPosition = minionArray[i].lock()->box.GetPosition();
            angle = Deg2Rad(minionArray[i].lock()->angleDeg + MINION_ANGLEDEG_ADJUST);
            target = minionPosition + Vec2().DirectionFrom(angle);
            minion->Shoot(target, shotStylesBulletSpeed[SINGLE]);
            minion->still = true;
        }
        PlaySoundEffect(MINION_BULLET_SOUND_SHOT, ALIEN_BOSS_SHOT_SFX_TIMES);
    }
    else if (shotStyle == MULTIPLE) {
        float targetDistance = 999999.0f;
        float minionDistance;
        int minionShooterId;

        target = penguin.lock()->box.GetPosition();

        for (int i=0; i < (int)minionArray.size(); i++) {
            minion = (MinionBoss*)minionArray[i].lock()->GetComponent("Minion");
            minionDistance = minion->GetPosition().DistanceTo(target);

            if (minionDistance < targetDistance) {
                targetDistance = minionDistance;
                minionShooterId = i;
            }
        }
        minion = (MinionBoss*)minionArray[minionShooterId].lock()->GetComponent("Minion");
        minion->Shoot(target, shotStylesBulletSpeed[MULTIPLE], MINION_BULLET_SOUND_SHOT);
    }
    
    else if (shotStyle == SPIRAL) {
        Vec2 minionPosition;
        float angle;

        for (int i=0; i < (int)minionArray.size(); i++) {
            minion = (MinionBoss*)minionArray[i].lock()->GetComponent("Minion");
            minionPosition = minionArray[i].lock()->box.GetPosition();
            angle = Deg2Rad(minionArray[i].lock()->angleDeg + MINION_ANGLEDEG_ADJUST);
            target = minionPosition + Vec2().DirectionFrom(angle);
            minion->Shoot(target, shotStylesBulletSpeed[SPIRAL]);
        }
        PlaySoundEffect(MINION_BULLET_SOUND_SHOT, ALIEN_BOSS_SHOT_SFX_TIMES);
    }
}

void AlienBoss::ActionMove (float dt) {
    Vec2 currentPosition = associated.box.GetPosition();

    if (currentPosition.DistanceTo(target) > ALIEN_MINIMUM_DISPLACEMENT) {
        float targetAngle = currentPosition.AngleTo(target);
        speed = currentPosition.DirectionFrom(targetAngle);
        associated.box.Translate(speed * ALIEN_LINEAR_SPEED * dt);
        
        for (int i=0; i < (int)minionArray.size(); i++) {
            ((MinionBoss*)minionArray[i].lock()->GetComponent("Minion"))->still = false;
        }
    }
    else {
        shotStyle = static_cast<ShotStyle>(rand()%shotStylesCooldown.size());
        cooldown = Timer(shotStylesCooldown[shotStyle], shotStylesCooldown[shotStyle]);
        associated.box.SetPosition(target);
        speed = Vec2();
        state = RESTING;
    }
}

void AlienBoss::ExplodeAnimation () {
    GameObject* explosion = new GameObject(ALIEN_DEATH_LAYER, ALIEN_DEATH_LABEL);
    explosion->AddComponent(
        new Sprite(
            *explosion, ALIEN_BOSS_DEATH_SPRITE,
            ALIEN_DEATH_FRAME_COUNT, ALIEN_DEATH_FRAME_TIME,
            ALIEN_DEATH_FRAME_ONESHOT, ALIEN_DEATH_SELFDESTRUCTION
        )
    );
    explosion->box.SetPosition(associated.box.GetPosition());
    Game::GetInstance().GetCurrentState().AddObject(explosion);

    PlaySoundEffect(ALIEN_DEATH_SOUND);
}

void AlienBoss::PlaySoundEffect (std::string soundFileName, int times) {
    GameObject* sfx = new GameObject();
    Sound* sound = new Sound(*sfx, soundFileName);
    sfx->AddComponent(sound);
    Game::GetInstance().GetCurrentState().AddObject(sfx);
    sound->Play(times, ALIEN_BOSS_SFX_SELFDESTRUCTION);
}