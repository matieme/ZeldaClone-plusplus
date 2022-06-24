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

    /// <summary>Returns true while the user holds down the key identified by "keyToCheck".</summary>
	/// <param name="keyToCheck">The key identifier listed on the Input enum.</param>
    bool GetInput(Input keyToCheck);
    
  	/// <summary>Returns true the first frame the user hits any key button.</summary>
    bool AnyKey();
private:
    InputManager();
    ~InputManager();
    std::vector<bool>input;

    InputManager(InputManager const&) = delete;
    void operator = (InputManager const&) = delete;
};
