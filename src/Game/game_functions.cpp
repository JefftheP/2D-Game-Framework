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
#define FLOOR_PLANE 875
Engine::EngineSprite introRects[INTRO_FRAMES];
Engine::EngineSprite idleRects[IDLE_FRAMES];

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

    introRects[0] = Engine::EngineSprite{9, baseY, rowW, 0};
    introRects[1] = Engine::EngineSprite{148, baseY, rowW, 0};
    introRects[2] = Engine::EngineSprite{291, baseY, rowW, 0};
    introRects[3] = Engine::EngineSprite{431, 8, rowW, 0};
    introRects[4] = Engine::EngineSprite{569, baseY, 112, 0};
    introRects[5] = Engine::EngineSprite{704, baseY, 115, 0};
    introRects[6] = Engine::EngineSprite{843, baseY, 116, 0};
    introRects[7] = Engine::EngineSprite{986, baseY, 124, 0};

    for (int i = 0; i < 8; i++)
    {
        introRects[i].r.h = endY - introRects[i].r.y;
    }

    baseX = 7;
    baseY = 173;
    endY = 318;
    rowW = 111;

    introRects[8] = Engine::EngineSprite{baseX, baseY, 119, 0};
    introRects[9] = Engine::EngineSprite{146, baseY, 112, 0};
    introRects[10] = Engine::EngineSprite{277, baseY, rowW, 0};
    introRects[11] = Engine::EngineSprite{411, baseY, rowW, 0};
    introRects[12] = Engine::EngineSprite{546, baseY, rowW, 0};
    introRects[13] = Engine::EngineSprite{679, 173, rowW, 0};
    introRects[14] = Engine::EngineSprite{807, baseY, rowW, 0};
    introRects[15] = Engine::EngineSprite{942, baseY, rowW, 0};
    introRects[16] = Engine::EngineSprite{1075, baseY, rowW, 0};

    for (int i = 8; i < 17; i++)
    {
        introRects[i].r.h = endY - introRects[i].r.y;
    }

    baseX = 4;
    baseY = 331;
    endY = 453;

    introRects[17] = Engine::EngineSprite{baseX, baseY, 130, 0};
    introRects[18] = Engine::EngineSprite{165, baseY, 139, 0};
    introRects[19] = Engine::EngineSprite{327, baseY, 143, 0};

    for (int i = 17; i < 20; i++)
    {
        introRects[i].r.h = endY - introRects[i].r.y;
    }

    for (int i = 0; i < 20; i++)
    {
        introRects[i].xOffset = -1 * introRects[i].r.w / 2;
        introRects[i].yOffset = -1 * introRects[i].r.h;
    }

    baseX = 5;
    baseY = 519;
    endY = 638;
    rowW = 132;

    idleRects[0] = Engine::EngineSprite{baseX, baseY, rowW, 0};
    idleRects[1] = Engine::EngineSprite{150, 529, 142, 0};
    idleRects[2] = Engine::EngineSprite{312, 533, 152, 0};
    idleRects[3] = Engine::EngineSprite{490, 544, 153, 0};
    idleRects[4] = Engine::EngineSprite{674, 545, 155, 0};
    idleRects[5] = Engine::EngineSprite{859, 548, 151, 0};
    idleRects[6] = Engine::EngineSprite{1042, 549, 141, 0};

    for (int i = 0; i < 7; i++)
    {
        idleRects[i].r.h = endY - idleRects[i].r.y;
    }

    baseX = 5;
    baseY = 683;
    endY = 771;
    rowW = 144;

    idleRects[7] = Engine::EngineSprite{baseX, baseY, rowW, 0};
    idleRects[8] = Engine::EngineSprite{172, 681, 146, 0};
    idleRects[9] = Engine::EngineSprite{340, 677, 153, 0};
    idleRects[10] = Engine::EngineSprite{520, 671, 145, 0};
    idleRects[11] = Engine::EngineSprite{698, 665, 153, 0};
    idleRects[12] = Engine::EngineSprite{879, 658, 146, 0};

    for (int i = 7; i < 13; i++)
    {
        idleRects[i].r.h = endY - idleRects[i].r.y;
    }

    for (int i = 0; i < 13; i++)
    {
        idleRects[i].xOffset = -65;
        idleRects[i].yOffset = -1 * idleRects[i].r.h;
    }

    // initialYPoint = BROCK_Y + introRects[0].h;
    // initialXPoint = BROCK_X + (introRects[0].w / 2);

    Game::IntroState *intro = new Game::IntroState(new Engine::EngineAnimation(character->texture, introRects, INTRO_FRAMES));
    Game::IdleState *idle = new Game::IdleState(new Engine::EngineAnimation(character->texture, idleRects, IDLE_FRAMES, true, Engine::AnimiationOrientation::LEFT));

    character->SetStateManager(intro);
    character->SetStateManager(idle);
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
