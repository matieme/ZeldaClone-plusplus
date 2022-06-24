#include "include/Player.h"
#include "raylib.h"
#include "raymath.h"
#include "include/Animator.h"
#include "include/InputManager.h"

Animator SpriteAnimator{"LinkAnimator", 4, 3, 10};
const char* LINK_IDLE_TEXTURE_PATH = "src/resources/spritesheets/character_link_idle.png";
const char* LINK_RUNNING_TEXTURE_PATH = "src/resources/spritesheets/character_link_running.png";

Vector2 linkPos{0.0, 0.0};
Texture2D link;
Input playerView = Input::UP;
PlayerState playerState = PlayerState::IDLE;

float rightleft = 0.0f;

Player::Player()
{
    link = LoadTexture(LINK_IDLE_TEXTURE_PATH);
    SpriteAnimator.AssignSprite(link);

    linkPos.x = GetScreenWidth() / 2.0f - (0.5f * link.width / 4.0f);
    linkPos.y = GetScreenHeight() / 2.0f - (0.5f * link.height / 3.0f);
}

Player::~Player()
{

}

void Player::Update(InputManager& InputManagerInst)
{
    Move(InputManagerInst);
    Draw();
}

void Player::Move(InputManager& InputManagerInst)
{
    Vector2 direction{};
    
    if(InputManagerInst.AnyKey())
    {
        if(InputManagerInst.GetInput(Input::LEFT))
        {
            direction.x += 1.0;
            ChangeSpriteViewDirection(Input::LEFT);
        } 
        if(InputManagerInst.GetInput(Input::RIGHT))
        {
            direction.x -= 1.0;
            ChangeSpriteViewDirection(Input::RIGHT);
        } 
        if(InputManagerInst.GetInput(Input::UP))
        {
            direction.y += 1.0;
            ChangeSpriteViewDirection(Input::UP);
        }
        if(InputManagerInst.GetInput(Input::DOWN))
        {
            direction.y -= 1.0;
            ChangeSpriteViewDirection(Input::DOWN);
        }
    }

    if(Vector2Length(direction) != 0.0)
    {
        linkPos = Vector2Subtract(linkPos, Vector2Normalize(direction));
    }
}

void Player::Draw()
{
    /*
    switch (playerState)
    {
    case LinkState::IDLE:
        link = LoadTexture(LINK_IDLE_TEXTURE_PATH);
        SpriteAnimator.ChangeSprite(link, 4, 3, 10);
        break;
    case LinkState::RUN:
        link = LoadTexture(LINK_RUNNING_TEXTURE_PATH);
        SpriteAnimator.ChangeSprite(link, 6, 3, 10);
    default:
        break;
    }
    */


    switch (playerView)
    {
    case Input::UP:
        SpriteAnimator.GoToRow(2);
        break;
    case Input::DOWN:
        SpriteAnimator.GoToRow(0);
        break;
    case Input::LEFT:
        SpriteAnimator.GoToRow(1);
        rightleft = -1.f;
        break;
    case Input::RIGHT:
        SpriteAnimator.GoToRow(1);
        rightleft = 1.f;
        break;
    }


    //Rectangle source{0.f, 0.f, rightleft * (float)SpriteAnimator.GetSprite().width/ 4, (float)link.height / 3};
    Rectangle linkDest{linkPos.x, linkPos.y, 1.5 * SpriteAnimator.GetFrameRec().width, 1.5 * SpriteAnimator.GetFrameRec().height};
    DrawTexturePro(SpriteAnimator.GetSprite(), SpriteAnimator.GetFrameRec(), linkDest, Vector2{}, 0.0f, WHITE);
    SpriteAnimator.Play();
}

void Player::Destroy()
{
    UnloadTexture(link);
}

void Player::ChangeSpriteViewDirection(Input Direction)
{
    playerView = Direction;
}