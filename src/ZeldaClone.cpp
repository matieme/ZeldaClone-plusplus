#include "raylib.h"
#include "include/Player.h"
#include "include/InputManager.h"
#include "include/LevelManager.h"

int windowsDimensions[2]{512, 448};

int main()
{
    InputManager& InputManagerInstance = InputManager::GetManager();
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(windowsDimensions[0], windowsDimensions[1], "Zelda Clone Game");
    
    LevelManager& LevelManagerInstance = LevelManager::GetManager();

    Player link = Player::GetPlayer();

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        InputManagerInstance.UpdateInput();
        BeginDrawing();
        ClearBackground(BLACK);

        LevelManagerInstance.Update();

        link.Update(InputManagerInstance);

        EndDrawing();
    }

    //UnloadTexture(map);
    link.Destroy();
    CloseWindow();
}