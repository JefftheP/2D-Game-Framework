#pragma once

#include <SDL.h>
#include "../Engine/engine_structs.h"

namespace Game
{
    struct Vector2D
    {
        float x;
        float y;
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
    };

    // TODO: This is too restricting, I'll expand this  as needed to be a bit more dynamic.
    enum GameCharacterState
    {
        INTRO,
        IDLE,
        WALK_FORWARD,
        RUN,
        WALK_BACKWARD,
        JUMP,
        LAND,
        TOTAL
    };

    struct GameCharacter
    {
        SDL_Point playerPos;
        // TL corner to star drawing at;
        SDL_Point drawPoint;
        float acceleration;
        float currSpeed;
        float maxSpeed;
        Vector2D v;
        SDL_Rect onScreen;
        GameCharacterState currState;
        unsigned int someCounter = 1;
        unsigned int button_state = 0;

        Engine::EngineTexture *texture = NULL;
        Engine::EngineAnimation *animations[GameCharacterState::TOTAL];

        GameCharacter();
        GameCharacter(int x, int y, Engine::EngineTexture *texture);
        ~GameCharacter();

        void SetAcceleration(float a);
        void SetMaxSpeed(float a);
        void SetState(GameCharacterState state);

        void Init(Engine::EngineTexture *texture, Engine::EngineAnimation *animations[Game::GameCharacterState::TOTAL] = NULL);
        void SetTexture(Engine::EngineTexture *texture);
        void SetAnimation(GameCharacterState state, SDL_Rect *rects, unsigned int totalCount, bool isLooped = false, Engine::AnimiationOrientation orientation = Engine::AnimiationOrientation::CENTER);
        void Animate(Game::GameCharacterState newState);
        void Render(Engine::EngineRenderer *renderer);
        void Move(Vector2D move);
        void Update(unsigned int buttonMask);

        Engine::EngineAnimation *GetCurrentAnimation();
    };
} // namespace Game
