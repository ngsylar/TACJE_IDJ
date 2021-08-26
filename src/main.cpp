#include "Game.h"

#define WINDOWTITLE "150126760 Gabriel Rocha Fontenele"
#define WINDOWSIZE 1024, 600

int main (int argc, char* argv[]) {
    Game& game = Game::GetInstance(
        WINDOWTITLE, WINDOWSIZE
    );

    game.Run();
    delete &game;

    return 0;
}