#include "raylib.h"
#include "include/Animator.h"

int windowsDimensions[2]{768, 704};
const char* MAP_TEXTURE_PATH = "src/resources/maps/map_01.png";
const char* LINK_TEXTURE_PATH = "src/resources/spritesheets/character_link_idle.png";
Animator SpriteAnimator{"LinkAnimator", 4, 3, 10};

int main()
{
    InitWindow(windowsDimensions[0], windowsDimensions[1], "Zelda Clone Game");

    Texture2D map = LoadTexture(MAP_TEXTURE_PATH);
    
    Texture2D link = LoadTexture(LINK_TEXTURE_PATH);
    Vector2 linkPos{
        windowsDimensions[0] / 2.0f - (0.5f * link.width / 4.0f),
        windowsDimensions[1] / 2.0f - (0.5f * link.height / 3.0f)
    };

    float rightLeft{1.0f};
    SpriteAnimator.AssignSprite(link);


    SetTargetFPS(60);
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(BLACK);

        SpriteAnimator.Play();

        float mapTextureScaleMultiplier = 1.5;
        Vector2 mapPos{0.0, windowsDimensions[1] - (map.height * mapTextureScaleMultiplier)};
        DrawTextureEx(map, mapPos, 0.0, mapTextureScaleMultiplier, WHITE);

        Rectangle linkDest{linkPos.x, linkPos.y, mapTextureScaleMultiplier * link.width / 4, mapTextureScaleMultiplier * link.height / 3};

        DrawTexturePro(SpriteAnimator.GetSprite(), SpriteAnimator.GetFrameRec(), linkDest, Vector2{}, 0.0f, WHITE);

        EndDrawing();
    }

    UnloadTexture(map);
    UnloadTexture(link);

    CloseWindow();
}