#include "Game.h"
#include <thread>

using namespace std::this_thread;
using namespace std::chrono;

const int FPS = 60;
const duration<double, std::milli> DELAY_TIME = milliseconds(1000 / FPS);

int main() {
    auto frameStart = system_clock::now();

    Game *pGame = Game::Instance();

    duration<double> frameDuration = milliseconds::zero();

    pGame->init();
    while (pGame->running()) {
        frameStart = system_clock::now();

        pGame->handleEvents();
        pGame->update();
        pGame->render();

        frameDuration = frameStart - system_clock::now();
        if (frameDuration < DELAY_TIME) {
            auto sleep_time = DELAY_TIME - frameDuration;
            sleep_for(sleep_time);
            std::cout << "Sleeping for: " << sleep_time.count() << std::endl;
        }
    }

    pGame->terminate();
}
