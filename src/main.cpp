#include "Game.h"

int main (int argc, char *argv[]) {
    Game* game = Game::GetInstance("Coisado", 962, 572);
    game = Game::GetInstance("Um titulo ae", 962, 572);

    SDL_Event event;
    while (true) {
        if(SDL_PollEvent(&event) && (event.type == SDL_QUIT)) {
            break;
        }
    }
    delete game;

    game = Game::GetInstance("Um titulo ae", 962, 572);
    while (true) {
        if(SDL_PollEvent(&event) && (event.type == SDL_QUIT)) {
            break;
        }
    }
    delete game;

    return 0;
}