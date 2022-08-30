#include "GentooEngine.h"
#include "TitleState.h"

// editar: retirar exits e tratar erros
int main (int argc, char* argv[]) {
    Game::GetInstance().AddState(new TitleState());
    Game::GetInstance().Run();
    Game::DeleteInstance();
    return 0;
}