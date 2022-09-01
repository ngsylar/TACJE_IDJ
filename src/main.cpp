#include "GentooEngine.h"
// #include "OpeningScene.h"
#include "TitleState.h" // remover

// editar: tratar erros
int main (int argc, char* argv[]) {
    // Game::GetInstance().AddState(new OpeningScene());
    Game::GetInstance().AddState(new TitleState());
    Game::GetInstance().Run();
    Game::DeleteInstance();
    return 0;
}