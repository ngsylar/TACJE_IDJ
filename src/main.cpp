#include "GentooEngine.h"
#include "OpeningScene.h"
#include "InMemoriam.h"

// editar: tratar erros
int main (int argc, char* argv[]) {
    Game::GetInstance().AddState(new OpeningScene());
    Game::GetInstance().Run();
    Game::GetInstance().AddState(new InMemoriam());
    Game::GetInstance().Run();
    Game::DeleteInstance();
    return 0;
}