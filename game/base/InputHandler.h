#ifndef SHMUP_INPUTHANDLER_H
#define SHMUP_INPUTHANDLER_H


class InputHandler {

private:
    InputHandler() = default;

    ~ InputHandler() = default;

public:

    void update();

    void onKeyDown();

    void onKeyUp();

    static InputHandler &Instance() {
        static InputHandler instance;
        return instance;
    }

    bool isKeyDown(SDL_Scancode key);

    Uint8 *m_keystate;
    const Uint8 *m_keystates;
};


#endif //SHMUP_INPUTHANDLER_H
