#include "game_structs.h"
#include "game_functions.h"
#include "game_movement.h"

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

    for (int i = 0; i < Game::GameCharacterState::TOTAL_STATES; i++)
    {
        if (this->animations[i] != NULL)
        {
            delete this->animations[i];
            this->animations[i] = NULL;
        }
    }
}

void Game::GameCharacter::Init(Engine::EngineTexture *texture, Engine::EngineAnimation *animations[Game::GameCharacterState::TOTAL_STATES])
{
    if (animations != NULL)
    {
        for (int i = 0; i > Game::GameCharacterState::TOTAL_STATES; i++)
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

void Game::GameCharacter::SetAnimation(GameCharacterState state, Engine::EngineSprite *sprites, unsigned int totalCount, bool isLooped, Engine::AnimiationOrientation orientation)
{
    this->animations[state] = new Engine::EngineAnimation(this->texture, sprites, totalCount, isLooped, orientation);
}

void Game::GameCharacter::Render(Engine::EngineRenderer *renderer)
{
    Engine::EngineAnimation *currAnim = this->GetCurrentAnimation();
    Engine::EngineSprite *clip = currAnim->GetCurrentClip();
    SDL_Rect *clipR = &(clip->r);
    SDL_Rect *camera = Game::GetCamera();
    int scale = Game::GetRenderScale();

    // if (currAnim->orientation == Engine::AnimiationOrientation::CENTER)
    // {
    //     onScreen.y = this->playerPos.y - (clip->h * scale);
    //     onScreen.x = this->playerPos.x - ((clip->w * scale) / 2) - camera->x;
    //     // lastX = brockOnScreen.x;
    // }
    // else
    // {
    //     onScreen.y = this->playerPos.y - (clip->h * scale);
    //     onScreen.x = this->playerPos.x;
    // }

    onScreen.y = this->playerPos.y + clip->GetYOffset(scale);
    onScreen.x = this->playerPos.x + clip->GetXOffset(scale); //- camera->x;

    // Horizontal Line
    SDL_Point a = {1, this->playerPos.y};
    SDL_Point b = {1599, this->playerPos.y};

    // Vertical Line
    SDL_Point a2 = {this->playerPos.x, 1};
    SDL_Point b2 = {this->playerPos.x, 899};

    onScreen.w = clipR->w * Game::GetRenderScale();
    onScreen.h = clipR->h * Game::GetRenderScale();

    renderer->Render(this->texture, clipR, &onScreen);
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
    this->currSpeed = Game::Move(&(this->playerPos), &(this->v), this->currSpeed, this->acceleration);
    SDL_Rect *cam = Game::GetCamera();
    SDL_Point camPoint = {cam->x, cam->y};
    SDL_Point *boundary = Game::GetBoundaryPoint();
    Game::Move(&camPoint, &(this->v), (this->currSpeed * 0.80), (this->acceleration * 0.80));

    if (camPoint.x < 0)
    {
        camPoint.x = 0;
    }
    if (camPoint.y < 0)
    {
        camPoint.y = 0;
    }
    if (camPoint.x > boundary->x - cam->w)
    {
        camPoint.x = boundary->x - cam->w;
    }
    if (camPoint.y > boundary->y - cam->h)
    {
        camPoint.y = boundary->y - cam->h;
    }

    cam->x = camPoint.x;
    cam->y = camPoint.y;
}

void Game::GameCharacter::Update(unsigned int buttonMask)
{
    // SDL_Log("button mask: %u - %u", buttonMask, Game::ButtonState::PRESS_UP | Game::ButtonState::PRESS_DOWN | Game::ButtonState::PRESS_LEFT | Game::ButtonState::PRESS_RIGHT);
    unsigned int newButtonState = 0;
    Game::GameCharacterState newState = this->currState;
    // Game::Vector2D v;

    if ((buttonMask & Game::ButtonState::RELEASE_UP) != Game::ButtonState::RELEASE_UP) // if up button was not released
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

    InputBufferEntry entry = {};
    entry.buttonMask = this->button_state;
    entry.dir_store = 1;

    if (this->button_state & Game::ButtonState::PRESS_RIGHT)
    {
        this->v.x = 1;
        this->v.y = 0;
        // newState = Game::GameCharacterState::WALK_FORWARD;
        entry.dir = DirectionNotation::FORWARD;
    }
    else if (this->button_state & Game::ButtonState::PRESS_LEFT)
    {
        this->v.x = -1;
        this->v.y = 0;
        // newState = Game::GameCharacterState::WALK_BACKWARD;
        entry.dir = DirectionNotation::BACK;
    }

    if (this->button_state & Game::ButtonState::PRESS_UP)
    {
        this->v.y = -1;
        if (entry.dir == DirectionNotation::BACK)
        {
            entry.dir = DirectionNotation::UP_BACK;
        }
        else if (entry.dir == DirectionNotation::FORWARD)
        {
            entry.dir = DirectionNotation::UP_FORWARD;
        }
        else
        {
            entry.dir = DirectionNotation::UP;
        }
    }
    else if (this->button_state & Game::ButtonState::PRESS_DOWN)
    {
        this->v.y = 1;
        if (entry.dir == DirectionNotation::BACK)
        {
            entry.dir = DirectionNotation::DOWN_BACK;
        }
        else if (entry.dir == DirectionNotation::FORWARD)
        {
            entry.dir = DirectionNotation::DOWN_FORWARD;
        }
        else
        {
            entry.dir = DirectionNotation::DOWN;
        }
    }

    // check for direction store
    if (this->inputBuffer[0].dir == entry.dir)
    {
        entry.dir_store = this->inputBuffer[0].dir_store + 1;
        SDL_Log("Dir store: %u", entry.dir_store);
    }

    Game::InputBufferInsert(&entry, this->inputBuffer);

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
                this->currSpeed = Game::Move(&(this->playerPos), &(this->v), this->currSpeed, -20.f);
            }
            else if (this->currSpeed < 1.f)
            {
                // Snap to 1.f
                this->currSpeed = 1.f;
                this->v.y = 0;
                this->v.x = 0;
            }

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