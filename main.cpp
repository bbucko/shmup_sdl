#include "Game.h"

static Game game;

int main() {

    game.init();

    while (game.running()) {
        game.handleEvents();
        game.update();
        game.render();
    }

    game.terminate();
}
