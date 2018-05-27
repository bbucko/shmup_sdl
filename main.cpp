#include "game.h"

Game *game = nullptr;


int main() {
    game = new Game();

    while (game->running()) {
        game->handleEvents();

        game->update();

        game->render();
    }

    game->terminate();
}
