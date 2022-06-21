#include "raylib.h"

int windowsDimensions[2]{800,600};


int main()
{
    InitWindow(windowsDimensions[0], windowsDimensions[1], "Zelda Clone Game");

    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(WHITE);

  

        EndDrawing();
    }

    CloseWindow();
}