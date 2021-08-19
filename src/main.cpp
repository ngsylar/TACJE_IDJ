#include <iostream>
#include "Game.h"

int main (int argc, char *argv[]) {
    Game& gameboi = Game::GetInstance("Um titulo ae", 962, 572);
    std::cout << "bla\n";
    std::cout << "bla\n";
    std::cout << "bla\n";
    std::cout << "bla\n";
    std::cout << "bla\n";
    Game& game = Game::GetInstance("Coisado", 962, 572);

    game.Run();
    delete &game;

    game = Game::GetInstance("Coisado 2", 962, 572);
    game.Run();
    delete &game;

    return 0;
}