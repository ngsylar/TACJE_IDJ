#include "State.h"
#include "Resources.h"
#include "TileMap.h"
#include "Sound.h"
#include "Face.h"
#include "Vec2.h"

State::State () {
    GameObject* bg;
    Sprite* bgSprite;

    quitRequested = false;
    music.Open(MUS_BG);
    music.Play(MUS_REPEAT_ON);

    bg = new GameObject();
    bgSprite = new Sprite(*bg, SPR_BG);
    bg->AddComponent(bgSprite);
    objectArray.emplace_back(bg);

    bg->box = Rect(
        SPR_START_X, SPR_START_Y,
        bgSprite->GetWidth(), bgSprite->GetHeight()
    );
}

State::~State () {
    objectArray.clear();
}

void State::LoadAssets () {
    GameObject* gameMap;
    TileSet* gameMapTset;
    TileMap* gameMapTmap;

    gameMap = new GameObject();
    gameMapTset = new TileSet(*gameMap, TSET_GAMEMAP, TDIM_GAMEMAP);
    gameMapTmap = new TileMap(*gameMap, gameMapTset, TMAP_GAMEMAP);
    gameMap->box = Rect(SPR_START_X, SPR_START_Y, TDIM_GAMEMAP);
    gameMap->AddComponent(gameMapTmap);
    objectArray.emplace_back(gameMap);
}

void State::ClearResources () {
    Resources::ClearImages();
    Resources::ClearMusics();
    Resources::ClearSounds();
}

void State::Update (float dt) {
    Input();
    for (unsigned i=0; i < objectArray.size(); i++) {
        objectArray[i]->Update(dt);
    }

    for (int i=(int)objectArray.size()-1; i >= 0; i--) {
        if (objectArray[i]->IsDead()) {
            objectArray.erase(objectArray.begin()+i);
        }
    }
}

void State::Render () {
    for (unsigned i=0; i < objectArray.size(); i++) {
        objectArray[i]->Render();
    }
}

bool State::QuitRequested () {
    return quitRequested;
}

void State::AddObject (int pX, int pY) {
    GameObject* obj = new GameObject();
    Sprite* sprite = new Sprite(*obj, SPR_ENEMY);
    Sound* sound = new Sound(*obj, SND_ENEMY);
    Face* face = new Face(*obj);

    obj->AddComponent(sprite);
    obj->AddComponent(sound);
    obj->AddComponent(face);
    objectArray.emplace_back(obj);

    int pW = sprite->GetWidth();
    int pH = sprite->GetHeight();
    obj->box = Rect(pX-pW/2, pY-pH/2, pW, pH);
}

// edit: remover essa funcao no proximo commit
void State::Input() {
    SDL_Event event;
    int mouseX, mouseY;

    // Obtenha as coordenadas do mouse
    SDL_GetMouseState(&mouseX, &mouseY);

    // SDL_PollEvent retorna 1 se encontrar eventos, zero caso contrário
    while (SDL_PollEvent(&event)) {

        // Se o evento for quit, setar a flag para terminação
        if(event.type == SDL_QUIT) {
            quitRequested = true;
        }

        // Se o evento for clique...
        if(event.type == SDL_MOUSEBUTTONDOWN) {

            // Percorrer de trás pra frente pra sempre clicar no objeto mais de cima
            for(int i = (int)objectArray.size() - 1; i >= 0; --i) {
                // Obtem o ponteiro e casta pra Face.
                GameObject* go = (GameObject*) objectArray[i].get();
                // Nota: Desencapsular o ponteiro é algo que devemos evitar ao máximo.
                // O propósito do unique_ptr é manter apenas uma cópia daquele ponteiro,
                // ao usar get(), violamos esse princípio e estamos menos seguros.
                // Esse código, assim como a classe Face, é provisório. Futuramente, para
                // chamar funções de GameObjects, use objectArray[i]->função() direto.

                if(go->box.Contains( (float)mouseX, (float)mouseY ) ) {
                    Face* face = (Face*)go->GetComponent( "Face" );
                    if ( nullptr != face ) {
                        // Aplica dano
                        face->Damage(std::rand() % 10 + 10);
                        // Sai do loop (só queremos acertar um)
                        break;
                    }
                }
            }
        }
        if( event.type == SDL_KEYDOWN ) {
            // Se a tecla for ESC, setar a flag de quit
            if( event.key.keysym.sym == SDLK_ESCAPE ) {
                quitRequested = true;
            }
            // Se não, crie um objeto
            else {
                Vec2 objPos = Vec2( 200, 0 ).GetRotated( -PI + PI*(rand() % 1001)/500.0 ) + Vec2( (float)mouseX, (float)mouseY );
                AddObject((int)objPos.x, (int)objPos.y);
            }
        }
    }
}