#include "include/Player.h"
#include "raylib.h"
#include "raymath.h"
#include "include/Animator.h"

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

    linkPos = LevelManagerInstance.GetPlayerPosition();
    DrawPlayerCollider(Input::UP);
}

Player::~Player()
{

}

Player& Player::GetPlayer()
{
    static Player instance;
    return instance;
}

void Player::Update(InputManager& InputManagerInst)
{
    Move(InputManagerInst);
    Draw();
    CheckGateMapColliders();
}

void Player::Move(InputManager& InputManagerInst)
{
    Vector2 direction{};
    
    if(InputManagerInst.AnyKey())
    {
        if(InputManagerInst.GetInput(Input::LEFT))
        {
            ChangeSpriteViewDirection(Input::LEFT);

            if(!CheckMapColliders())
            {
                direction.x += 1.0;
            }
        }
        else if(InputManagerInst.GetInput(Input::RIGHT))
        {
            ChangeSpriteViewDirection(Input::RIGHT);

            if(!CheckMapColliders())
            {
                direction.x -= 1.0;
            }
        }
        else if(InputManagerInst.GetInput(Input::UP))
        {
            ChangeSpriteViewDirection(Input::UP);

            if(!CheckMapColliders())
            {
                direction.y += 1.0;
            }
        }
        else if(InputManagerInst.GetInput(Input::DOWN))
        {
            ChangeSpriteViewDirection(Input::DOWN);

            if(!CheckMapColliders())
            {
                direction.y -= 1.0;
            }
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

    LinkRect.x = linkPos.x;
    LinkRect.y = linkPos.y;
    LinkRect.width = SpriteAnimator.GetFrameRec().width;
    LinkRect.height = SpriteAnimator.GetFrameRec().height;
    
    //Player Rectangle Debug
    //DrawRectangle(LinkRect.x, LinkRect.y, LinkRect.width, LinkRect.height, BLUE);
    
    //Colliders Debug
    DrawRectangle(LinkRectCollider.x, LinkRectCollider.y, LinkRectCollider.width, LinkRectCollider.height, GREEN);

    DrawTexturePro(SpriteAnimator.GetSprite(), source, LinkRect, Vector2{}, 0.0f, WHITE);
    SpriteAnimator.Play();
}

void Player::Destroy()
{
    UnloadTexture(link);
}

void Player::ChangeSpriteViewDirection(Input Direction)
{
    playerView = Direction;
    DrawPlayerCollider(Direction);
}

bool Player::CheckMapColliders()
{
    for(Rectangle rect : LevelManagerInstance.GetCollidersRec())
    {
        if(CheckCollisionRecs(rect, LinkRectCollider))
        {
            return true;
        }
    }

    return false;
}

void Player::CheckGateMapColliders()
{
    for(GateData rect : LevelManagerInstance.GetGateCollidersRec())
    {
        if(CheckCollisionRecs(rect.rec, LinkRectCollider))
        {
            LevelManagerInstance.OnGateCollision(rect);
            linkPos = LevelManagerInstance.GetPlayerPosition();
        }
    }
}

void Player::DrawPlayerCollider(Input Direction)
{
    switch (Direction)
    {
        case Input::UP:
            LinkRectCollider.width = LinkRect.width / 2;
            LinkRectCollider.height = LinkRect.height / 4;
            LinkRectCollider.x = (LinkRect.x + LinkRect.width / 2) - LinkRectCollider.width / 2;
            LinkRectCollider.y = LinkRect.y;
            break;
        case Input::DOWN:
            LinkRectCollider.width = LinkRect.width / 2;
            LinkRectCollider.height = LinkRect.height / 4;
            LinkRectCollider.x = (LinkRect.x + LinkRect.width / 2) - LinkRectCollider.width / 2;
            LinkRectCollider.y = LinkRect.y + LinkRect.width;
            break;
        case Input::LEFT:
            LinkRectCollider.width = LinkRect.width / 4;
            LinkRectCollider.height = LinkRect.height / 2;
            LinkRectCollider.x = LinkRect.x;
            LinkRectCollider.y = (LinkRect.y + LinkRect.height / 2) - LinkRectCollider.height / 2;
            break;
        case Input::RIGHT:
            LinkRectCollider.width = LinkRect.width / 4;
            LinkRectCollider.height = LinkRect.height / 2;
            LinkRectCollider.x = (LinkRect.x + LinkRect.width) - LinkRectCollider.width;
            LinkRectCollider.y = (LinkRect.y + LinkRect.height / 2) - LinkRectCollider.height / 2;;
            break;
    }
}