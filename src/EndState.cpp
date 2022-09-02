#include "GentooEngine.h"
#include "EndState.h"
#include "TitleState.h"
#include "StageState.h"
#include "GameData.h"

EndState::EndState () {
    GameObject* screen = new GameObject(GAMEOVER_LAYER, GAMEOVER_LABEL);
    Sprite* sprite = new Sprite(
        *screen, GameData::PlayerVictory()? GAMEOVER_VICTORY_SPRITE : GAMEOVER_DEFEAT_SPRITE
    );
    screen->AddComponent(sprite);
    AddObject(screen);
}

void EndState::LoadAssets () {
    GameObject* finalText;
    Text* text;

    finalText = new GameObject(GAMEOVER_TEXT_LAYER, GAMEOVER_LABEL);
    text = new Text(
        *finalText, GAMEOVER_TEXT_CONTENT_KEYS,
        GAMEOVER_TEXT_FONT_FILE, GAMEOVER_TEXT_FONT_SIZE_KEYS,
        Text::BLENDED, TEXT_COLOR_YELLOW,
        GAMEOVER_TEXT_DISPLAY_TIME, GAMEOVER_TEXT_CONCEAL_TIME
    );
    finalText->AddComponent(text);
    finalText->box.SetPosition(GAMEOVER_TEXT_POSITION_KEYS);
    AddObject(finalText);

    finalText = new GameObject(GAMEOVER_TEXT_SHADOW_LAYER, GAMEOVER_LABEL);
    text = new Text(
        *finalText, GAMEOVER_TEXT_CONTENT_KEYS,
        GAMEOVER_TEXT_FONT_FILE, GAMEOVER_TEXT_FONT_SIZE_KEYS,
        Text::BLENDED, TEXT_COLOR_SHADOW,
        GAMEOVER_TEXT_DISPLAY_TIME, GAMEOVER_TEXT_CONCEAL_TIME
    );
    finalText->AddComponent(text);
    finalText->box.SetPosition(GAMEOVER_TEXT_SHADOW_KEYS);
    AddObject(finalText);

    finalText = new GameObject(GAMEOVER_TEXT_LAYER, GAMEOVER_LABEL);
    text = new Text(
        *finalText, GAMEOVER_TEXT_CONTENT_STATES,
        GAMEOVER_TEXT_FONT_FILE, GAMEOVER_TEXT_FONT_SIZE_STATES,
        Text::BLENDED, TEXT_COLOR_YELLOW,
        GAMEOVER_TEXT_DISPLAY_TIME, GAMEOVER_TEXT_CONCEAL_TIME
    );
    finalText->AddComponent(text);
    finalText->box.SetPosition(GAMEOVER_TEXT_POSITION_STATES);
    AddObject(finalText);

    finalText = new GameObject(GAMEOVER_TEXT_SHADOW_LAYER, GAMEOVER_LABEL);
    text = new Text(
        *finalText, GAMEOVER_TEXT_CONTENT_STATES,
        GAMEOVER_TEXT_FONT_FILE, GAMEOVER_TEXT_FONT_SIZE_STATES,
        Text::BLENDED, TEXT_COLOR_SHADOW,
        GAMEOVER_TEXT_DISPLAY_TIME, GAMEOVER_TEXT_CONCEAL_TIME
    );
    finalText->AddComponent(text);
    finalText->box.SetPosition(GAMEOVER_TEXT_SHADOW_STATES);
    AddObject(finalText);

    music.Open(GameData::PlayerVictory()? GAMEOVER_VICTORY_MUSIC : GAMEOVER_DEFEAT_MUSIC);
}

void EndState::Start () {
    Camera::Reset();
    music.Play();
}

void EndState::Update (float dt) {
    InputManager& input = InputManager::GetInstance();

    if ((not Mix_PlayingMusic()) or input.KeyPress(KEY_ESCAPE)) {
        Game::GetInstance().AddState(new TitleState());
        popRequested = true;
        return;
    }
    if ((input.KeyPress(KEY_SPACE)) or input.MousePress(MOUSE_BUTTON_LEFT)) {
        Game::GetInstance().AddState(new StageState());
        popRequested = true;
        return;
    }
}