#include "Game.h"
#include <thread>
#include <base/InputHandler.h>

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

        InputHandler::Instance().update();

        Game::Instance().update();

        Game::Instance().render();

        frameDuration = frameStart - system_clock::now();
        if (frameDuration < DELAY_TIME) {
            auto sleep_time = DELAY_TIME - frameDuration;
            sleep_for(sleep_time);
            std::cout << "Sleeping for: " << sleep_time.count() << std::endl;
        }
    }

    Game::Instance().terminate();
}
