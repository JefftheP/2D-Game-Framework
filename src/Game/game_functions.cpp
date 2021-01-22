#include "../Engine/engine_functions.h"
#include "game_functions.h"
#include "game_globals.h"
#include "game_character_states.h"

Game::GameCharacter *character = NULL;
Engine::EngineRenderer *renderer = NULL;
Engine::EngineTexture *bg = NULL;
Engine::EngineFont *font = NULL;

SDL_Color white = {0xFF, 0xFF, 0xFF, 0xFF};

#define INTRO_FRAMES 20
#define IDLE_FRAMES 13
#define WALK_F_FRAMES 10
#define WALK_B_FRAMES 10

#define FLOOR_PLANE 875

Engine::EngineSprite introSprites[INTRO_FRAMES];
Engine::EngineSprite idleSprites[IDLE_FRAMES];
Engine::EngineSprite walkForwardSprites[IDLE_FRAMES];
Engine::EngineSprite walkBackwardSprites[IDLE_FRAMES];

// Horizontal Line
SDL_Point a;
SDL_Point b;

// Vertical Line
SDL_Point a2;
SDL_Point b2;

// Boundary points
SDL_Point TL = {0, 0};
SDL_Point BR = {0, 0};
unsigned int animMod = 0;
SDL_Rect frameRect;

SDL_Rect *Game::GetCamera()
{
    return Game::CAMERA;
}

void Game::Init()
{
    bg = new Engine::EngineTexture("images/KOF-XIII-Burnt-Remains-Stage.jpg");
    BR.x = bg->GetWidth();
    BR.y = bg->GetHeight();

    character = new Game::GameCharacter(300, FLOOR_PLANE);
    font = new Engine::EngineFont("fonts/OpenSans-Bold.ttf", 28);

    for (int i = 0; i < INTRO_FRAMES; i++)
    {
        std::string path = "images/venom/intro/" + std::to_string(i) + ".png";
        SDL_Log("loading sprite:");
        SDL_Log(path.c_str());

        introSprites[i] = Engine::EngineSprite(new Engine::EngineTexture(path.c_str()));
        introSprites[i].xOffset = -1 * introSprites[i].r.w / 2;
        introSprites[i].yOffset = -1 * introSprites[i].r.h;
    }
    Game::IntroState *intro = new Game::IntroState(new Engine::EngineAnimation(introSprites, INTRO_FRAMES));

    for (int i = 0; i < IDLE_FRAMES; i++)
    {
        std::string path = "images/venom/idle/" + std::to_string(i) + ".png";
        idleSprites[i] = Engine::EngineSprite(new Engine::EngineTexture(path.c_str()));
        idleSprites[i].xOffset = -65;
        idleSprites[i].yOffset = -1 * idleSprites[i].r.h;
    }
    Game::IdleState *idle = new Game::IdleState(new Engine::EngineAnimation(idleSprites, IDLE_FRAMES, true, Engine::AnimiationOrientation::LEFT));

    for (int i = 0; i < WALK_F_FRAMES; i++)
    {
        std::string path = "images/venom/walk_forward/" + std::to_string(i) + ".png";
        walkForwardSprites[i] = Engine::EngineSprite(new Engine::EngineTexture(path.c_str()));
        walkForwardSprites[i].xOffset = -1 * walkForwardSprites[i].r.w / 2;
        walkForwardSprites[i].yOffset = -1 * walkForwardSprites[i].r.h;
    }

    Game::WalkingForwardState *walkingForward = new Game::WalkingForwardState(new Engine::EngineAnimation(walkForwardSprites, WALK_F_FRAMES, true, Engine::AnimiationOrientation::LEFT));

    for (int i = 0; i < WALK_B_FRAMES; i++)
    {
        std::string path = "images/venom/walk_backward/" + std::to_string(i) + ".png";
        walkBackwardSprites[i] = Engine::EngineSprite(new Engine::EngineTexture(path.c_str()));
        walkBackwardSprites[i].xOffset = -1 * walkBackwardSprites[i].r.w / 2;
        walkBackwardSprites[i].yOffset = -1 * walkBackwardSprites[i].r.h;
    }
    Game::WalkingBackwardState *walkingBackward = new Game::WalkingBackwardState(new Engine::EngineAnimation(walkBackwardSprites, WALK_B_FRAMES, true, Engine::AnimiationOrientation::LEFT));

    character->SetStateManager(intro);
    character->SetStateManager(idle);
    character->SetStateManager(walkingForward);
    character->SetStateManager(walkingBackward);
    character->SetState(Game::GameCharacterState::INTRO);
}

int Game::Update(Engine::EngineTick *tick)
{
    unsigned int buttonMask = Game::ReadInputs();
    character->Update(buttonMask);

    /// TODO: implement the Game Update Record strategy

    Game::Render();
    return 0;
}

unsigned int Game::ReadInputs()
{
    SDL_Event e;

    unsigned int buttonMask = 0;
    while (SDL_PollEvent(&e) != 0)
    {
        if (e.type == SDL_QUIT)
        {
            Engine::Stop();
            Game::Close();
        }

        if (e.type = SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_1:
                Game::SetAnimationMod(1);
                break;
            case SDLK_2:
                Game::SetAnimationMod(2);
                break;
            case SDLK_3:
                Game::SetAnimationMod(3);
                break;
            case SDLK_4:
                Game::SetAnimationMod(4);
                break;
            case SDLK_5:
                Game::SetAnimationMod(5);
                break;
            case SDLK_0:
                Game::SetAnimationMod(30);
                break;
                // case SDLK_r:
                //     SDL_Log("---------------------Did reset---------------------");
                //     intro->Reset();
                //     currAnim = intro;
                //     break;
            }

            if (e.key.keysym.sym == SDLK_UP && e.key.state == SDL_PRESSED)
            {
                buttonMask = buttonMask | Game::ButtonState::PRESS_UP;
                SDL_Log("press up : %u", e.key.type);
            }
            else if (e.key.keysym.sym == SDLK_DOWN && e.key.state == SDL_PRESSED)
            {
                buttonMask = buttonMask | Game::ButtonState::PRESS_DOWN;
                SDL_Log("press down");
            }

            if (e.key.keysym.sym == SDLK_LEFT && e.key.state == SDL_PRESSED)
            {
                buttonMask = buttonMask | Game::ButtonState::PRESS_LEFT;
                SDL_Log("press left");
            }
            else if (e.key.keysym.sym == SDLK_RIGHT && e.key.state == SDL_PRESSED)
            {
                buttonMask = buttonMask | Game::ButtonState::PRESS_RIGHT;
                SDL_Log("press right");
            }

            // if (e.key.keysym.sym == SDLK_w)
            // {
            //     int y2 = camera.y - 1 * scale;
            //     if (y2 >= TL.y && y2 <= BR.y)
            //     {
            //         camera.y = y2;
            //     }
            // }
            // else if (e.key.keysym.sym == SDLK_s)
            // {
            //     int y2 = camera.y + 1 * scale;
            //     if (y2 >= TL.y && y2 <= BR.y - camera.h)
            //     {
            //         camera.y = y2;
            //     }
            // }

            // if (e.key.keysym.sym == SDLK_a)
            // {
            //     int x2 = camera.x - 1 * scale;
            //     if (x2 >= TL.x && x2 <= BR.x)
            //     {
            //         camera.x = x2;
            //     }
            // }
            // else if (e.key.keysym.sym == SDLK_d)
            // {
            //     int x2 = camera.x + 1 * scale;
            //     if (x2 >= TL.x && x2 <= BR.x - camera.w)
            //     {
            //         camera.x = x2;
            //     }
            // }
        }

        if (e.type = SDL_KEYUP)
        {
            if (e.key.keysym.sym == SDLK_UP && e.key.state == SDL_RELEASED)
            {
                buttonMask = buttonMask | Game::ButtonState::RELEASE_UP;
                SDL_Log("release button up: %u", e.key.type);
            }
            else if (e.key.keysym.sym == SDLK_DOWN && e.key.state == SDL_RELEASED)
            {
                buttonMask = buttonMask | Game::ButtonState::RELEASE_DOWN;
                SDL_Log("release button down");
            }

            if (e.key.keysym.sym == SDLK_LEFT && e.key.state == SDL_RELEASED)
            {
                buttonMask = buttonMask | Game::ButtonState::RELEASE_LEFT;
                SDL_Log("release button left");
            }
            else if (e.key.keysym.sym == SDLK_RIGHT && e.key.state == SDL_RELEASED)
            {
                buttonMask = buttonMask | Game::ButtonState::RELEASE_RIGHT;
                SDL_Log("release button right");
            }

            // if (e.key.keysym.sym == SDLK_w)
            // {
            //     int y2 = camera.y - 1 * scale;
            //     if (y2 >= TL.y && y2 <= BR.y)
            //     {
            //         camera.y = y2;
            //     }
            // }
            // else if (e.key.keysym.sym == SDLK_s)
            // {
            //     int y2 = camera.y + 1 * scale;
            //     if (y2 >= TL.y && y2 <= BR.y - camera.h)
            //     {
            //         camera.y = y2;
            //     }
            // }

            // if (e.key.keysym.sym == SDLK_a)
            // {
            //     int x2 = camera.x - 1 * scale;
            //     if (x2 >= TL.x && x2 <= BR.x)
            //     {
            //         camera.x = x2;
            //     }
            // }
            // else if (e.key.keysym.sym == SDLK_d)
            // {
            //     int x2 = camera.x + 1 * scale;
            //     if (x2 >= TL.x && x2 <= BR.x - camera.w)
            //     {
            //         camera.x = x2;
            //     }
            // }
        }
    }

    return buttonMask;
}

int Game::Close()
{
    delete renderer;
    renderer = NULL;

    delete bg;
    bg = NULL;

    delete font;
    font = NULL;

    return 0;
}

int Game::Render()
{
    Engine::EngineRenderer *renderer = Engine::GetWindowRenderer();
    renderer->RenderStart();
    renderer->Render(bg, Game::CAMERA);

    SDL_Rect *clip = &(character->GetCurrentStateManager()->GetAnimation()->GetCurrentClip()->r);

    character->Render(renderer);

    renderer->RenderFinalize();
    return 0;
}

unsigned int Game::GetAnimationMod()
{
    return Game::ANIMATION_MOD;
}

void Game::SetAnimationMod(unsigned int animMod)
{
    Game::ANIMATION_MOD = animMod;
}

unsigned int Game::GetRenderScale()
{

    return Game::RENDER_SCALE;
}

void Game::SetCamera(SDL_Rect *camera)
{
    Game::CAMERA = camera;
}

Engine::EngineTexture *Game::GetFrameTexture(Engine::EngineAnimation *animation)
{
    return new Engine::EngineTexture(std::to_string(animation->currentFrame), font, &white);
}

SDL_Point *Game::GetBoundaryPoint()
{
    return &BR;
}

void Game::InputBufferClear(InputBufferEntry *buffer, unsigned int entries)
{
    for (int i = 0; i < entries; i++)
    {
        buffer->dir = Game::DirectionNotation::NEUTRAL;
        buffer->dir_store = 0;
        buffer->buttonMask = 0;
        for (int j = 0; j < Game::Buttons::TOTAL_BUTTONS; j++)
        {
            buffer->buttonStore[j] = 0;
        }
        ++buffer;
    }
}

void Game::InputBufferInsert(InputBufferEntry *entry, InputBufferEntry *buffer, unsigned int entries)
{
    InputBufferEntry oldEntry = {};
    InputBufferEntry newEntry = {};

    // load first new entry
    newEntry.dir = entry->dir;
    newEntry.dir_store = entry->dir_store;
    newEntry.buttonMask = entry->buttonMask;

    for (int j = 0; j < Game::Buttons::TOTAL_BUTTONS; j++)
    {
        newEntry.buttonStore[j] = entry->buttonStore[j];
    }

    for (int i = 0; i < entries; i++)
    {
        // load current buffer entry into old entry
        oldEntry.dir = buffer->dir;
        oldEntry.dir_store = buffer->dir_store;
        oldEntry.buttonMask = buffer->buttonMask;

        for (int j = 0; j < Game::Buttons::TOTAL_BUTTONS; j++)
        {
            oldEntry.buttonStore[j] = buffer->buttonStore[j];
        }

        // load new entry into buffer

        buffer->dir = newEntry.dir;
        buffer->dir_store = newEntry.dir_store;
        buffer->buttonMask = newEntry.buttonMask;

        for (int j = 0; j < Game::Buttons::TOTAL_BUTTONS; j++)
        {
            buffer->buttonStore[j] = newEntry.buttonStore[j];
        }

        // load oldEntry entry into newEntry
        newEntry.dir = oldEntry.dir;
        newEntry.dir_store = oldEntry.dir_store;
        newEntry.buttonMask = oldEntry.buttonMask;

        for (int j = 0; j < Game::Buttons::TOTAL_BUTTONS; j++)
        {
            newEntry.buttonStore[j] = oldEntry.buttonStore[j];
        }
        // increment buffer pointer
        ++buffer;
    }
}
