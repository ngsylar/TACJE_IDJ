#include "Game.h"

int main (int argc, char* argv[]) {
    Game& game = Game::GetInstance(
        "150126760 Gabriel Rocha Fontenele",
        1024, 600
    );

    game.Run();
    delete &game;

    return 0;
}