#include "GentooEngine.h"
#include "OpeningScene.h"
#include "InMemoriam.h"

int main (int argc, char* argv[]) {
    Game::GetInstance().AddState(new OpeningScene());
    Game::GetInstance().Run();

    // nota: dedicatoria
    Game::GetInstance().AddState(new InMemoriam());
    Game::GetInstance().Run();

    Game::DeleteInstance();
    return 0;
}