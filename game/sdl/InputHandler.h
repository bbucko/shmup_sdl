#ifndef SHMUP_INPUTHANDLER_H
#define SHMUP_INPUTHANDLER_H


class InputHandler {

private:
    InputHandler() = default;

    ~ InputHandler() = default;

    const Uint8 *m_keystates;

public:

    void update();

    void onKeyDown();

    void onKeyUp();

    bool isKeyDown(SDL_Scancode key) const;

    static InputHandler &Instance() {
        static InputHandler instance;
        return instance;
    }
};


#endif //SHMUP_INPUTHANDLER_H
