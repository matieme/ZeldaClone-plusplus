#include "include/InputManager.h"
#include "raylib.h"
#include<stdio.h>

std::vector<KeyboardKey> KeysContainer;

InputManager& InputManager::GetManager()
{
    static InputManager instance;
    return instance;
}

InputManager::~InputManager()
{

}

InputManager::InputManager()
{
    KeysContainer.resize(Input::TOTAL);
    input.resize(Input::TOTAL);

    KeysContainer.at(UP)=KeyboardKey::KEY_UP;
    KeysContainer.at(DOWN)=KeyboardKey::KEY_DOWN;
    KeysContainer.at(LEFT)=KeyboardKey::KEY_LEFT;
    KeysContainer.at(RIGHT)=KeyboardKey::KEY_RIGHT;
    KeysContainer.at(ESC)=KeyboardKey::KEY_LEFT_CONTROL;
    KeysContainer.at(BACK)=KeyboardKey::KEY_BACKSPACE;
    KeysContainer.at(ENTER)=KeyboardKey::KEY_ENTER;
}


bool InputManager::GetInput(Input keyToCheck)
{
    return input.at(keyToCheck);
}

void InputManager::UpdateInput()
{
    for(int i =0; i < Input::TOTAL; i++)
    {
        if(IsKeyDown(KeysContainer.at((Input)i)) != true)
        {
            input.at((Input)i) = false;
        }

        if(IsKeyPressed(KeysContainer.at((Input)i)) == true)
        {
            printf("pressed %i \n", (Input)i);

            input.at((Input)i) = true;
        }
    }
}