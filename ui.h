#ifndef CONNECT4_UI_H
#define CONNECT4_UI_H

#include <functional>
#include <string>
#include <clocale>
#include <unistd.h>
#include <sys/ttycom.h>
#include <sys/ioctl.h>
#include "view_controllers/base.h"
#include "view_controller_factory.h"
#include "ui_state.h"

class UI {
public:
    void eventLoop();
    void render();
    static std::pair<int, int> getWindowSize() noexcept;
    constexpr void exitProgram() noexcept { exitFlag = true; }

    static UI * getInstance () noexcept {
        if (instance == nullptr)
            instance = new UI;

        return instance;
    }

    static void onWindowResize(int) noexcept;
    void stateTransition(State state);

    ~UI() noexcept;
    UI(const UI &) = delete;
    UI & operator=(const UI &) = delete;
private:
    static UI *instance;
    UI() noexcept;

    const State firstState = StateMainMenu;
    State currentState = firstState;

    int sizeX = 0, sizeY = 0;
    std::unique_ptr<BaseViewController> currentViewController;
    bool exitFlag = false, windowResized = false;

    void resize() noexcept;
};

#endif //CONNECT4_UI_H
