#include "game_functions.h"
#include "game_globals.h"
#include "../Engine/engine_functions.h"

Game::GameCharacter *character = NULL;
Engine::EngineRenderer *renderer = NULL;
Engine::EngineTexture *bg = NULL;
Engine::EngineFont *font = NULL;

SDL_Color white = {0xFF, 0xFF, 0xFF, 0xFF};

#define INTRO_FRAMES 20
#define IDLE_FRAMES 13
#define FLOOR_PLANE 875
SDL_Rect introRects[INTRO_FRAMES];
SDL_Rect idleRects[IDLE_FRAMES];

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

    character = new Game::GameCharacter(300, FLOOR_PLANE, new Engine::EngineTexture("images/venom.png"));
    font = new Engine::EngineFont("fonts/OpenSans-Bold.ttf", 28);

    int baseX = 8;
    int baseY = 15;
    int rowW = 109;
    int endY = 160;

    // introRects[0] = {baseX, baseY, 109, row0H};
    // introRects[1] = {148, baseY, 109, row0H};
    // introRects[2] = {291, baseY, 109, row0H};
    // introRects[3] = {429, baseY, 111, row0H};
    // introRects[4] = {569, baseY, 112, row0H};
    // introRects[5] = {704, baseY, 115, row0H};
    // introRects[6] = {843, baseY, 116, row0H};
    // introRects[7] = {986, baseY, 124, row0H};

    introRects[0] = {9, baseY, rowW, 0};
    introRects[1] = {148, baseY, rowW, 0};
    introRects[2] = {291, baseY, rowW, 0};
    introRects[3] = {431, 8, rowW, 0};
    introRects[4] = {569, baseY, 112, 0};
    introRects[5] = {704, baseY, 115, 0};
    introRects[6] = {843, baseY, 116, 0};
    introRects[7] = {986, baseY, 124, 0};

    for (int i = 0; i < 8; i++)
    {
        introRects[i].h = endY - introRects[i].y;
    }

    baseX = 7;
    baseY = 173;
    endY = 318;
    rowW = 111;

    introRects[8] = {baseX, baseY, 119, 0};
    introRects[9] = {146, baseY, 112, 0};
    introRects[10] = {277, baseY, rowW, 0};
    introRects[11] = {411, baseY, rowW, 0};
    introRects[12] = {546, baseY, rowW, 0};
    introRects[13] = {679, 173, rowW, 0};
    introRects[14] = {807, baseY, rowW, 0};
    introRects[15] = {942, baseY, rowW, 0};
    introRects[16] = {1075, baseY, rowW, 0};

    for (int i = 8; i < 17; i++)
    {
        introRects[i].h = endY - introRects[i].y;
    }

    baseX = 4;
    baseY = 331;
    endY = 453;

    introRects[17] = {baseX, baseY, 130, 0};
    introRects[18] = {165, baseY, 139, 0};
    introRects[19] = {327, baseY, 143, 0};

    for (int i = 17; i < 20; i++)
    {
        introRects[i].h = endY - introRects[i].y;
    }

    baseX = 5;
    baseY = 519;
    endY = 638;
    rowW = 132;

    idleRects[0] = {baseX, baseY, rowW, 0};
    idleRects[1] = {150, 529, 142, 0};
    idleRects[2] = {312, 533, 152, 0};
    idleRects[3] = {490, 544, 153, 0};
    idleRects[4] = {674, 545, 155, 0};
    idleRects[5] = {859, 548, 151, 0};
    idleRects[6] = {1042, 549, 141, 0};

    for (int i = 0; i < 7; i++)
    {
        idleRects[i].h = endY - idleRects[i].y;
    }

    baseX = 5;
    baseY = 683;
    endY = 771;
    rowW = 144;

    idleRects[7] = {baseX, baseY, rowW, 0};
    idleRects[8] = {172, 681, 146, 0};
    idleRects[9] = {340, 677, 153, 0};
    idleRects[10] = {520, 671, 145, 0};
    idleRects[11] = {698, 665, 153, 0};
    idleRects[12] = {879, 658, 146, 0};

    for (int i = 7; i < 13; i++)
    {
        idleRects[i].h = endY - idleRects[i].y;
    }

    // initialYPoint = BROCK_Y + introRects[0].h;
    // initialXPoint = BROCK_X + (introRects[0].w / 2);

    character->SetAnimation(Game::GameCharacterState::INTRO, introRects, INTRO_FRAMES);
    character->SetAnimation(Game::GameCharacterState::IDLE, idleRects, IDLE_FRAMES, true, Engine::AnimiationOrientation::LEFT);
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

    SDL_Rect *clip = character->GetCurrentAnimation()->GetCurrentClip();

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
