#include "raylib.h"
#include "include/Player.h"
#include "include/InputManager.h"

int windowsDimensions[2]{768, 704};
const char* MAP_TEXTURE_PATH = "src/resources/maps/map_01.png";

int main()
{
    InputManager& InputManagerInstance = InputManager::GetManager();
    InitWindow(windowsDimensions[0], windowsDimensions[1], "Zelda Clone Game");

    Texture2D map = LoadTexture(MAP_TEXTURE_PATH);
    
    Player link = Player();

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        InputManagerInstance.UpdateInput();
        BeginDrawing();
        ClearBackground(BLACK);

        float mapTextureScaleMultiplier = 1.5;
        Vector2 mapPos{0.0, windowsDimensions[1] - (map.height * mapTextureScaleMultiplier)};
        DrawTextureEx(map, mapPos, 0.0, mapTextureScaleMultiplier, WHITE);

        link.Update(InputManagerInstance);

        EndDrawing();
    }

    UnloadTexture(map);
    link.Destroy();
    CloseWindow();
}