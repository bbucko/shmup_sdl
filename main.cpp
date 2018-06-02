#include "Game.h"
#include <thread>

using namespace std::this_thread;
using namespace std::chrono;

const int FPS = 60;
const duration<double, std::milli> DELAY_TIME = milliseconds(1000 / FPS);

int main() {
    auto frameStart = system_clock::now();
    duration<double> frameDuration = milliseconds::zero();

    Game::Instance().init();

    while (Game::Instance().running()) {
        frameStart = system_clock::now();

        Game::Instance().handleEvents();

        Game::Instance().update();

        Game::Instance().render();

        frameDuration = frameStart - system_clock::now();
        if (frameDuration < DELAY_TIME) {
            auto sleep_time = DELAY_TIME - frameDuration;
            sleep_for(sleep_time);
        }
    }

    Game::Instance().terminate();
}
