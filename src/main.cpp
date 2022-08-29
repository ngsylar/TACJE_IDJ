#include "GentooEngine.h"
#include "StageState.h"

// editar: retirar exits e tratar erros
int main (int argc, char* argv[]) {
    Game::GetInstance().AddState(new StageState());
    Game::GetInstance().Run();
    Game::DeleteInstance();
    return 0;
}