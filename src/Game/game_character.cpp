#include "game_structs.h"
#include "game_functions.h"

#include <cmath>

unsigned int aniCounter = 0;
SDL_Rect border;

Engine::EngineTexture *frame;
Game::GameCharacter::GameCharacter()
{
    this->playerPos = {};
    this->acceleration = 10.f;
    this->currSpeed = 1.f;
}

Game::GameCharacter::GameCharacter(int x, int y, Engine::EngineTexture *texture)
{
    this->playerPos = {x, y};
    this->currSpeed = 1.f;
    this->acceleration = 10.f;
    this->texture = texture;
}

Game::GameCharacter::~GameCharacter()
{
    if (this->texture != NULL)
    {
        delete this->texture;
        this->texture = NULL;
    }

    if (frame != NULL)
    {
        delete frame;
        frame = NULL;
    }

    for (int i = 0; i < Game::GameCharacterState::TOTAL; i++)
    {
        if (this->animations[i] != NULL)
        {
            delete this->animations[i];
            this->animations[i] = NULL;
        }
    }
}

void Game::GameCharacter::Init(Engine::EngineTexture *texture, Engine::EngineAnimation *animations[Game::GameCharacterState::TOTAL])
{
    if (animations != NULL)
    {
        for (int i = 0; i > Game::GameCharacterState::TOTAL; i++)
        {
            this->animations[i] = animations[i];
        }
    }

    this->texture = texture;
}

void Game::GameCharacter::SetTexture(Engine::EngineTexture *texture)
{
    this->texture = texture;
}

void Game::GameCharacter::SetAnimation(GameCharacterState state, SDL_Rect *rects, unsigned int totalCount, bool isLooped, Engine::AnimiationOrientation orientation)
{
    this->animations[state] = new Engine::EngineAnimation(this->texture, rects, totalCount, isLooped, orientation);
}

void Game::GameCharacter::Render(Engine::EngineRenderer *renderer)
{
    Engine::EngineAnimation *currAnim = this->GetCurrentAnimation();
    SDL_Rect *clip = currAnim->GetCurrentClip();
    SDL_Rect *camera = Game::GetCamera();
    int scale = Game::GetRenderScale();

    if (currAnim->orientation == Engine::AnimiationOrientation::CENTER)
    {
        onScreen.y = this->playerPos.y - (clip->h * scale);
        onScreen.x = this->playerPos.x - ((clip->w * scale) / 2) - camera->x;
        // lastX = brockOnScreen.x;
    }
    else
    {
        onScreen.y = this->playerPos.y - (clip->h * scale);
        onScreen.x = this->playerPos.x;
    }

    // Horizontal Line
    SDL_Point a = {1, this->playerPos.y};
    SDL_Point b = {1599, this->playerPos.y};

    // Vertical Line
    SDL_Point a2 = {this->playerPos.x, 1};
    SDL_Point b2 = {this->playerPos.x, 899};

    onScreen.w = clip->w * Game::GetRenderScale();
    onScreen.h = clip->h * Game::GetRenderScale();

    renderer->Render(this->texture, clip, &onScreen);
    renderer->DrawRect(&onScreen);

    border.x = onScreen.x + 5;
    border.y = onScreen.y + 5;
    border.w = frame->GetWidth();
    border.h = frame->GetHeight();

    renderer->Render(frame, NULL, &border);
    renderer->DrawLine(&a, &b);
    renderer->DrawLine(&a2, &b2);
}

void Game::GameCharacter::SetAcceleration(float a)
{
    this->acceleration = a;
}

void Game::GameCharacter::SetMaxSpeed(float a)
{
    this->maxSpeed = a;
}

void Game::GameCharacter::SetState(Game::GameCharacterState state)
{
    this->currState = state;
}

void Game::GameCharacter::Move(Vector2D move)
{
    // int forward = 1;
    // int backward = -1;
    float deltaT = 0.016666666666666666; // 60FPS lockstep
    float time = 1 * deltaT;
    // float dual = std::sqrtf(2.f);
    // float coeff = 1.f;

    // if (this->currSpeed < this->maxSpeed)
    // {
    float v0 = this->currSpeed;
    float v1 = v0 + this->acceleration * deltaT;
    float speed = v1;
    this->currSpeed = speed;
    // this->currSpeed = speed;

    // if (std::abs(move.x) + std::abs(move.y) == 2)
    // {
    //     coeff = dual;
    // }
    // if (move.x == 0 && move.y == 0)
    // {
    //     this->currSpeed = 1.f;
    // }

    if (move.x == -1)
    {
        this->playerPos.x -= 1 * speed; //coeff * speed;
    }
    else if (move.x == 1)
    {
        this->playerPos.x += 1 * speed; //coeff * speed;
    }

    if (move.y == -1)
    {
        this->playerPos.y -= 1 * speed; //coeff * speed;
    }
    else if (move.y == 1)
    {
        this->playerPos.y += 1 * speed; //coeff * speed;
    }
    // }
}

void Game::GameCharacter::Update(unsigned int buttonMask)
{
    // SDL_Log("button mask: %u - %u", buttonMask, Game::ButtonState::PRESS_UP | Game::ButtonState::PRESS_DOWN | Game::ButtonState::PRESS_LEFT | Game::ButtonState::PRESS_RIGHT);
    unsigned int newButtonState = 0;
    Game::GameCharacterState newState = this->currState;
    // Game::Vector2D v;

    if ((buttonMask & Game::ButtonState::RELEASE_UP) != Game::ButtonState::RELEASE_UP) // If if up button was not released
    {
        // SDL_Log("in up");
        // keep the same UP state on the character, or the up value that just came in
        newButtonState = newButtonState | std::max(this->button_state & Game::ButtonState::PRESS_UP, buttonMask & Game::ButtonState::PRESS_UP);
    }
    if ((buttonMask & Game::ButtonState::RELEASE_DOWN) != Game::ButtonState::RELEASE_DOWN)
    {
        // SDL_Log("in down");
        newButtonState = newButtonState | std::max(this->button_state & Game::ButtonState::PRESS_DOWN, buttonMask & Game::ButtonState::PRESS_DOWN);
    }
    if ((buttonMask & Game::ButtonState::RELEASE_LEFT) != Game::ButtonState::RELEASE_LEFT)
    {
        // SDL_Log("in left");
        newButtonState = newButtonState | std::max(this->button_state & Game::ButtonState::PRESS_LEFT, buttonMask & Game::ButtonState::PRESS_LEFT);
    }
    if ((buttonMask & Game::ButtonState::RELEASE_RIGHT) != Game::ButtonState::RELEASE_RIGHT)
    {
        // SDL_Log("in right");
        newButtonState = newButtonState | std::max(this->button_state & Game::ButtonState::PRESS_RIGHT, buttonMask & Game::ButtonState::PRESS_RIGHT);
    }

    // SDL_Log("buttons: last: %u | state: %u | bitmask: %u", this->button_state, newButtonState, (newButtonState & (Game::ButtonState::PRESS_UP | Game::ButtonState::PRESS_DOWN | Game::ButtonState::PRESS_LEFT | Game::ButtonState::PRESS_RIGHT)));

    this->button_state = newButtonState;

    bool buttonPressed = (this->button_state & (Game::ButtonState::PRESS_UP | Game::ButtonState::PRESS_DOWN | Game::ButtonState::PRESS_LEFT | Game::ButtonState::PRESS_RIGHT)) > 0;

    if (this->button_state & Game::ButtonState::PRESS_RIGHT)
    {
        v.x = 1;
        v.y = 0;
        // newState = Game::GameCharacterState::WALK_FORWARD;
    }
    else if (this->button_state & Game::ButtonState::PRESS_LEFT)
    {
        v.x = -1;
        v.y = 0;
        // newState = Game::GameCharacterState::WALK_BACKWARD;
    }

    if (this->button_state & Game::ButtonState::PRESS_UP)
    {
        v.y = -1;
    }
    else if (this->button_state & Game::ButtonState::PRESS_DOWN)
    {
        v.y = 1;
    }

    if (buttonPressed)
    {
        // SDL_Log("buttons pressed");
        this->Move(v);
    }
    else
    {
        if (
            this->currState != GameCharacterState::INTRO ||
            (this->currState == GameCharacterState::INTRO &&
             this->animations[GameCharacterState::INTRO]->IsComplete()))
        {
            if (this->currSpeed > 1.f)
            {
                SDL_Log("decelerate x: %u | y: %u", v.x, v.y);
                // Decelerate

                // int forward = 1;
                // int backward = -1;
                float deltaT = 0.016666666666666666; // 60FPS lockstep
                float time = 1 * deltaT;
                float deceleration = 3.f;
                // float dual = std::sqrtf(2.f);
                // float coeff = 1.f;

                // if (this->currSpeed < this->maxSpeed)
                // {
                float v0 = this->currSpeed;
                float v1 = v0 - deceleration * deltaT;
                float speed = v1;
                this->currSpeed = speed;
                // this->currSpeed = speed;

                // if (std::abs(move.x) + std::abs(move.y) == 2)
                // {
                //     coeff = dual;
                // }
                // if (v.x == 0 && v.y == 0)
                // {
                //     this->currSpeed = 1.f;
                // }

                if (v.x == -1)
                {
                    this->playerPos.x -= 1 * speed; //coeff * speed;
                }
                else if (v.x == 1)
                {
                    this->playerPos.x += 1 * speed; //coeff * speed;
                }

                if (v.y == -1)
                {
                    this->playerPos.y -= 1 * speed; //coeff * speed;
                }
                else if (v.y == 1)
                {
                    this->playerPos.y += 1 * speed; //coeff * speed;
                }
                // }
            }
            else if (this->currSpeed < 1.f)
            {
                // Snap to 1.f
                this->currSpeed = 1.f;
            }
            // else
            // {
            // }
            // SDL_Log("-------------NOTHING------------");
            newState = Game::GameCharacterState::IDLE;
        }
    }

    this->Animate(newState);
}

Engine::EngineAnimation *Game::GameCharacter::GetCurrentAnimation()
{
    return this->animations[this->currState];
}

void Game::GameCharacter::Animate(Game::GameCharacterState newState)
{
    if (newState != this->currState)
    {
        if (currState != GameCharacterState::INTRO)
        {
            this->animations[this->currState]->Reset();
        }
        this->animations[newState]->Reset();
        this->someCounter = 1;
        this->currState = newState;
        aniCounter = 0;
    }
    else
    {
        this->someCounter++;
        if (aniCounter % Game::GetAnimationMod() == 0)
        {
            if (frame != NULL)
            {
                delete frame;
            }
            frame = Game::GetFrameTexture(this->GetCurrentAnimation());
            this->animations[this->currState]->Advance();
        }
        ++aniCounter;
    }
}