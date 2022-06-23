#pragma once
#include <vector>

enum Input
{
    UP,
    DOWN,
    LEFT,
    RIGHT,
    ESC,
    BACK,
    ENTER,
    TOTAL
};

class InputManager
{
public:
    static InputManager& GetManager();
    void UpdateInput();
    bool GetInput(Input keyToCheck);
private:
    InputManager();
    ~InputManager();
    std::vector<bool>input;

    InputManager(InputManager const&) = delete;
    void operator = (InputManager const&) = delete;
};
