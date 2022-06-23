#include "include/Player.h"
#include "raylib.h"
#include "raymath.h"
#include "include/Animator.h"
#include "include/InputManager.h"

Animator SpriteAnimator{"LinkAnimator", 4, 3, 10};
const char* LINK_TEXTURE_PATH = "src/resources/spritesheets/character_link_idle.png";
Vector2 linkPos{0.0, 0.0};
Texture2D link;

Player::Player()
{
    link = LoadTexture(LINK_TEXTURE_PATH);
    SpriteAnimator.AssignSprite(link);

    linkPos.x = GetScreenWidth() / 2.0f - (0.5f * link.width / 4.0f);
    linkPos.y = GetScreenHeight() / 2.0f - (0.5f * link.height / 3.0f);
}

Player::~Player()
{

}

void Player::Update(InputManager& InputManagerInst)
{
    SpriteAnimator.Play();
    Move(InputManagerInst);
}

void Player::Move(InputManager& InputManagerInst)
{
    Vector2 direction{};
    if(InputManagerInst.GetInput(Input::LEFT)) direction.x += 1.0;
    if(InputManagerInst.GetInput(Input::RIGHT)) direction.x -= 1.0;
    if(InputManagerInst.GetInput(Input::UP)) direction.y += 1.0;
    if(InputManagerInst.GetInput(Input::DOWN)) direction.y -= 1.0;

    if(Vector2Length(direction) != 0.0)
    {
        linkPos = Vector2Subtract(linkPos, Vector2Normalize(direction));
    }

    Rectangle linkDest{linkPos.x, linkPos.y, 1.5 * link.width / 4, 1.5 * link.height / 3};

    DrawTexturePro(SpriteAnimator.GetSprite(), SpriteAnimator.GetFrameRec(), linkDest, Vector2{}, 0.0f, WHITE);
}

void Player::Destroy()
{
    UnloadTexture(link);
}