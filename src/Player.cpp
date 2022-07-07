#include "include/Player.h"
#include "raylib.h"
#include "raymath.h"
#include "include/Animator.h"
#include "include/InputManager.h"

Animator SpriteAnimator{"LinkAnimator", 8, 3, 2};
const char* LINK_IDLE_TEXTURE_PATH = "src/resources/spritesheets/character_link_idle.png";
const char* LINK_RUNNING_TEXTURE_PATH = "src/resources/spritesheets/character_link_running.png";

Vector2 linkPos{0.0, 0.0};
Texture2D link;
Texture2D link_idle;
Texture2D link_run;

Input playerView = Input::UP;
PlayerState playerState = PlayerState::IDLE;

float rightleft = 1.0f;

Player::Player()
{
    link_idle = LoadTexture(LINK_IDLE_TEXTURE_PATH);
    link_run = LoadTexture(LINK_RUNNING_TEXTURE_PATH);
    link = link_idle;

    ChangeSpriteViewDirection(Input::UP);
    SpriteAnimator.ChangeSprite(link, 8, 3, 2);

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
        else if(InputManagerInst.GetInput(Input::RIGHT))
        {
            direction.x -= 1.0;
            ChangeSpriteViewDirection(Input::RIGHT);
        }
        else if(InputManagerInst.GetInput(Input::UP))
        {
            direction.y += 1.0;
            ChangeSpriteViewDirection(Input::UP);
        }
        else if(InputManagerInst.GetInput(Input::DOWN))
        {
            direction.y -= 1.0;
            ChangeSpriteViewDirection(Input::DOWN);
        }
    }

    if(Vector2Length(direction) != 0.0)
    {
        linkPos = Vector2Subtract(linkPos, Vector2Scale(Vector2Normalize(direction), Speed));
        playerState = PlayerState::RUN;
    }else
    {
        playerState = PlayerState::IDLE;
    }
}

void Player::Draw()
{
    switch (playerState)
    {
        case PlayerState::IDLE:
            if(link.id != link_idle.id)
            {
                link = link_idle;
                SpriteAnimator.ChangeSprite(link, 8, 3, 2);
            }
            break;
        case PlayerState::RUN:
            if(link.id != link_run.id)
            {
                link = link_run;
                SpriteAnimator.ChangeSprite(link, 6, 3, 5);
            }
        default:
            break;
    }

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


    Rectangle source{SpriteAnimator.GetCurrentFrame() * SpriteAnimator.GetFrameRec().x, SpriteAnimator.GetFrameRec().y, rightleft * SpriteAnimator.GetFrameRec().width, SpriteAnimator.GetFrameRec().height};
    Rectangle linkDest{linkPos.x, linkPos.y, SpriteAnimator.GetFrameRec().width, SpriteAnimator.GetFrameRec().height};
    DrawTexturePro(SpriteAnimator.GetSprite(), source, linkDest, Vector2{}, 0.0f, WHITE);
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