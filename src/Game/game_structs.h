#pragma once

#include <SDL.h>
#include "game_defines.h"
#include "../Engine/engine_structs.h"

namespace Game
{
    struct GameCharacter;

    struct Vector2D
    {
        float x;
        float y;
    };

    enum DirectionNotation
    {
        DOWN_BACK = (Uint8)1,
        DOWN = (Uint8)2,
        DOWN_FORWARD = (Uint8)3,
        BACK = (Uint8)4,
        NEUTRAL = (Uint8)5,
        FORWARD = (Uint8)6,
        UP_BACK = (Uint8)7,
        UP = (Uint8)8,
        UP_FORWARD = (Uint8)9,
    };

    enum Buttons
    {
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        TOTAL_BUTTONS
    };

    enum ButtonState
    {
        PRESS_UP = (unsigned int)1,
        RELEASE_UP = (unsigned int)1 << 1,

        PRESS_DOWN = (unsigned int)1 << 2,
        RELEASE_DOWN = (unsigned int)1 << 3,

        PRESS_LEFT = (unsigned int)1 << 4,
        RELEASE_LEFT = (unsigned int)1 << 5,

        PRESS_RIGHT = (unsigned int)1 << 6,
        RELEASE_RIGHT = (unsigned int)1 << 7,

        PRESS_A = (unsigned int)1 << 8,
        RELEASE_A = (unsigned int)1 << 9,

        PRESS_B = (unsigned int)1 << 10,
        RELEASE_B = (unsigned int)1 << 11,

        PRESS_C = (unsigned int)1 << 12,
        RELEASE_C = (unsigned int)1 << 13,

        PRESS_D = (unsigned int)1 << 14,
        RELEASE_D = (unsigned int)1 << 15,

        PRESS_E = (unsigned int)1 << 16,
        RELEASE_E = (unsigned int)1 << 17,

        PRESS_F = (unsigned int)1 << 18,
        RELEASE_F = (unsigned int)1 << 19,

        PRESS_G = (unsigned int)1 << 20,
        RELEASE_G = (unsigned int)1 << 21,

        PRESS_H = (unsigned int)1 << 22,
        RELEASE_H = (unsigned int)1 << 23,
    };

    struct InputBufferEntry
    {
        // Enum to denote which direction is currently pressed
        DirectionNotation dir = DirectionNotation::NEUTRAL;
        // counter for number of frames direction has been held
        Uint8 dir_store;
        // bitfield for determining button change state
        unsigned int buttonMask;
        // how long current buttons have been held
        Uint8 buttonStore[Game::Buttons::TOTAL_BUTTONS];
    };

    // TODO: This is too restricting, I'll expand this  as needed to be a bit more dynamic.
    enum GameCharacterState
    {
        INTRO,
        IDLE,
        //  CROUCHING, // crouching is another state?
        BLOCKING,
        REELING,
        WALKING_FORWARD,
        WALKING_BACKWARD,
        JUMPING,
        FALLING,
        SUPER_JUMPING,
        RUNNING,
        LANDING,
        SLIDING,
        ATTACKING,
        TOTAL_STATES
    };

    typedef void (*StateInit)(GameCharacter *character);
    typedef void (*StateUpdate)(GameCharacter *character);
    typedef void (*StateCleanup)(GameCharacter *character);

    struct CharacterStateManager
    {
        Game::GameCharacterState id;
        Engine::EngineAnimation *animation;
        StateInit init = NULL;
        StateUpdate update = NULL;
        StateCleanup cleanup = NULL;
        Game::GameCharacterState GetState();
        Engine::EngineAnimation *GetAnimation();
    };

    struct GameCharacter
    {
        unsigned int aniCounter = 0;
        SDL_Point playerPos;
        // TL corner to star drawing at;
        SDL_Point drawPoint;
        float acceleration;
        float currSpeed;
        float maxSpeed;
        Vector2D v;
        SDL_Rect onScreen;
        unsigned int someCounter = 1;
        unsigned int button_state = 0;
        InputBufferEntry inputBuffer[INPUT_BUFFER_SIZE];

        // Engine::EngineTexture *texture = NULL;
        CharacterStateManager *currStateManager = NULL;
        CharacterStateManager *stateManagers[GameCharacterState::TOTAL_STATES];

        GameCharacter();
        GameCharacter(int x, int y);
        ~GameCharacter();

        void SetAcceleration(float a);
        void SetMaxSpeed(float a);
        void SetState(GameCharacterState state);

        void Init(CharacterStateManager *states[Game::GameCharacterState::TOTAL_STATES] = NULL);
        void SetStateManager(CharacterStateManager *stateManager);
        void Animate();
        void Render(Engine::EngineRenderer *renderer);
        void Move(Vector2D move);
        void Update(unsigned int buttonMask);
        CharacterStateManager *GetCurrentStateManager();
    };

    struct GameLine
    {
        SDL_Point a;
        SDL_Point b;
    };
} // namespace Game
