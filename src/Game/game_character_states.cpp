#include "game_character_states.h"
#include "game_movement.h"

using namespace Game;

Game::GameCharacterState CharacterStateManager::GetState()
{
    return this->id;
}

Engine::EngineAnimation *CharacterStateManager::GetAnimation()
{
    return this->animation;
}

////////////////////////
//  IntroStateManager //
////////////////////////

void Game::IntroStateInit(GameCharacter *character)
{
    IntroState *state = (IntroState *)(character->GetCurrentStateManager());
    character->aniCounter = 0;
    state->GetAnimation()->Reset();
}

void Game::IntroStateUpdate(GameCharacter *character)
{
    IntroState *state = (IntroState *)(character->GetCurrentStateManager());
    if (state->GetAnimation()->IsComplete())
    {
        character->SetState(Game::GameCharacterState::IDLE);
    }
}

void Game::IntroStateCleanup(GameCharacter *character)
{
    // noop
}

IntroState::IntroState(Engine::EngineAnimation *animation)
{
    this->animation = animation;
    this->id = GameCharacterState::INTRO;
    SDL_Log("in intro state constructor: %u", this->id);
    this->init = Game::IntroStateInit;
    this->update = Game::IntroStateUpdate;
    this->cleanup = Game::IntroStateCleanup;
}

IntroState::~IntroState() {}

////////////////////////
//  IdleStateManager //
////////////////////////

void Game::IdleStateInit(GameCharacter *character)
{
    IdleState *state = (IdleState *)(character->GetCurrentStateManager());
    character->aniCounter = 0;
    state->GetAnimation()->Reset();
}

void Game::IdleStateUpdate(GameCharacter *character)
{
    IdleState *state = (IdleState *)(character->GetCurrentStateManager());
    Game::InputBufferEntry entry = character->inputBuffer[0];
    bool buttonPressed = entry.dir != Game::DirectionNotation::NEUTRAL;

    if (character->button_state & Game::ButtonState::PRESS_RIGHT)
    {
        state->cleanup(character);
        character->SetState(Game::GameCharacterState::WALKING_FORWARD);
        character->GetCurrentStateManager()->update(character);
        return;
    }
    else if (character->button_state & Game::ButtonState::PRESS_LEFT)
    {
        state->cleanup(character);
        character->SetState(Game::GameCharacterState::WALKING_BACKWARD);
        character->GetCurrentStateManager()->update(character);
        return;
    }

    if (character->button_state & Game::ButtonState::PRESS_UP)
    {
        character->v.y = -1;
    }
    else if (character->button_state & Game::ButtonState::PRESS_DOWN)
    {
        character->v.y = 1;
    }

    if (buttonPressed)
    {
        // SDL_Log("buttons pressed");
        character->Move(character->v);
    }
    else
    {
        if (character->currSpeed > 1.f)
        {
            SDL_Log("decelerate x: %u | y: %u", character->v.x, character->v.y);
            character->currSpeed = Game::Move(&(character->playerPos), &(character->v), character->currSpeed, -20.f);
        }
        else if (character->currSpeed < 1.f)
        {
            SDL_Log("snapped to 0");

            // Snap to 1.f
            character->currSpeed = 1.f;
            character->v.y = 0;
            character->v.x = 0;
        }
    }
}

void Game::IdleStateCleanup(GameCharacter *character)
{
}

IdleState::IdleState(Engine::EngineAnimation *animation)
{
    this->animation = animation;
    this->id = GameCharacterState::IDLE;
    this->init = Game::IdleStateInit;
    this->update = Game::IdleStateUpdate;
    this->cleanup = Game::IdleStateCleanup;
}
IdleState::~IdleState() {}

///////////////////////////
// BlockingStateManager //
//////////////////////////

void Game::BlockingStateInit(GameCharacter *character)
{
}
void Game::BlockingStateUpdate(GameCharacter *character)
{
}
void Game::BlockingStateCleanup(GameCharacter *character)
{
}

BlockingState::BlockingState(Engine::EngineAnimation *animation)
{
    this->animation = animation;
    this->id = GameCharacterState::BLOCKING;
    this->init = Game::BlockingStateInit;
    this->update = Game::BlockingStateUpdate;
    this->cleanup = Game::BlockingStateCleanup;
}
BlockingState::~BlockingState() {}

///////////////////////////
//  ReelingStateManager //
/////////////////////////

void Game::ReelingStateInit(GameCharacter *character)
{
}
void Game::ReelingStateUpdate(GameCharacter *character)
{
}
void Game::ReelingStateCleanup(GameCharacter *character)
{
}

ReelingState::ReelingState(Engine::EngineAnimation *animation)
{
    this->animation = animation;
    this->id = GameCharacterState::REELING;
    this->init = Game::ReelingStateInit;
    this->update = Game::ReelingStateUpdate;
    this->cleanup = Game::ReelingStateCleanup;
}
ReelingState::~ReelingState() {}

//////////////////////////////////
//  WalkingForwardStateManager //
////////////////////////////////

void Game::WalkingForwardStateInit(GameCharacter *character)
{
    WalkingForwardState *state = (WalkingForwardState *)(character->GetCurrentStateManager());
    character->aniCounter = 0;
    state->GetAnimation()->Reset();
}

void Game::WalkingForwardStateUpdate(GameCharacter *character)
{
    WalkingForwardState *state = (WalkingForwardState *)(character->GetCurrentStateManager());
    Game::InputBufferEntry entry = character->inputBuffer[0];
    bool buttonPressed = entry.dir != Game::DirectionNotation::NEUTRAL;

    if (character->button_state & Game::ButtonState::PRESS_RIGHT)
    {
        character->v.x = 1;
        character->v.y = 0;
    }
    else if (character->button_state & Game::ButtonState::PRESS_LEFT)
    {
        state->cleanup(character);
        character->SetState(Game::GameCharacterState::WALKING_BACKWARD);
        character->GetCurrentStateManager()->update(character);
        return;
    }

    if (character->button_state & Game::ButtonState::PRESS_UP)
    {
        character->v.y = -1;
    }
    else if (character->button_state & Game::ButtonState::PRESS_DOWN)
    {
        character->v.y = 1;
    }

    if (buttonPressed)
    {
        // SDL_Log("buttons pressed");
        character->Move(character->v);
    }
    else
    {
        state->cleanup(character);
        character->SetState(Game::GameCharacterState::IDLE);
        character->GetCurrentStateManager()->update(character);
        return;
    }
}

void Game::WalkingForwardStateCleanup(GameCharacter *character)
{
}

WalkingForwardState::WalkingForwardState(Engine::EngineAnimation *animation)
{
    this->animation = animation;
    this->id = GameCharacterState::WALKING_FORWARD;
    this->init = Game::WalkingForwardStateInit;
    this->update = Game::WalkingForwardStateUpdate;
    this->cleanup = Game::WalkingForwardStateCleanup;
}
WalkingForwardState::~WalkingForwardState() {}

///////////////////////////////////
//  WalkingBackwardStateManager //
/////////////////////////////////

void Game::WalkingBackwardStateInit(GameCharacter *character)
{
    WalkingBackwardState *state = (WalkingBackwardState *)(character->GetCurrentStateManager());
    character->aniCounter = 0;
    state->GetAnimation()->Reset();
}

void Game::WalkingBackwardStateUpdate(GameCharacter *character)
{
    WalkingBackwardState *state = (WalkingBackwardState *)(character->GetCurrentStateManager());
    Game::InputBufferEntry entry = character->inputBuffer[0];
    bool buttonPressed = entry.dir != Game::DirectionNotation::NEUTRAL;

    if (character->button_state & Game::ButtonState::PRESS_RIGHT)
    {
        state->cleanup(character);
        character->SetState(Game::GameCharacterState::WALKING_FORWARD);
        character->GetCurrentStateManager()->update(character);
        return;
    }
    else if (character->button_state & Game::ButtonState::PRESS_LEFT)
    {
        character->v.x = -1;
        character->v.y = 0;
    }

    if (character->button_state & Game::ButtonState::PRESS_UP)
    {
        character->v.y = -1;
    }
    else if (character->button_state & Game::ButtonState::PRESS_DOWN)
    {
        character->v.y = 1;
    }

    if (buttonPressed)
    {
        // SDL_Log("buttons pressed");
        character->Move(character->v);
    }
    else
    {
        state->cleanup(character);
        character->SetState(Game::GameCharacterState::IDLE);
        character->GetCurrentStateManager()->update(character);
        return;
    }
}
void Game::WalkingBackwardStateCleanup(GameCharacter *character)
{
}

WalkingBackwardState::WalkingBackwardState(Engine::EngineAnimation *animation)
{
    this->animation = animation;
    this->id = GameCharacterState::WALKING_BACKWARD;
    this->init = Game::WalkingBackwardStateInit;
    this->update = Game::WalkingBackwardStateUpdate;
    this->cleanup = Game::WalkingBackwardStateCleanup;
}
WalkingBackwardState::~WalkingBackwardState() {}

///////////////////////////
//  JumpingStateManager //
/////////////////////////

void Game::JumpingStateInit(GameCharacter *character)
{
}
void Game::JumpingStateUpdate(GameCharacter *character)
{
}
void Game::JumpingStateCleanup(GameCharacter *character)
{
}

JumpingState::JumpingState(Engine::EngineAnimation *animation)
{
    this->animation = animation;
    this->id = GameCharacterState::JUMPING;
    this->init = Game::JumpingStateInit;
    this->update = Game::JumpingStateUpdate;
    this->cleanup = Game::JumpingStateCleanup;
}
JumpingState::~JumpingState() {}

///////////////////////////
//  FallingStateManager //
/////////////////////////

void Game::FallingStateInit(GameCharacter *character)
{
}
void Game::FallingStateUpdate(GameCharacter *character)
{
}
void Game::FallingStateCleanup(GameCharacter *character)
{
}

FallingState::FallingState(Engine::EngineAnimation *animation)
{
    this->animation = animation;
    this->id = GameCharacterState::FALLING;
    this->init = Game::FallingStateInit;
    this->update = Game::FallingStateUpdate;
    this->cleanup = Game::FallingStateCleanup;
}
FallingState::~FallingState() {}

////////////////////////////////
//  SuperJumpingStateManager //
//////////////////////////////

void Game::SuperJumpingStateInit(GameCharacter *character)
{
}
void Game::SuperJumpingStateUpdate(GameCharacter *character)
{
}
void Game::SuperJumpingStateCleanup(GameCharacter *character)
{
}

SuperJumpingState::SuperJumpingState(Engine::EngineAnimation *animation)
{
    this->animation = animation;
    this->id = GameCharacterState::SUPER_JUMPING;
    this->init = Game::SuperJumpingStateInit;
    this->update = Game::SuperJumpingStateUpdate;
    this->cleanup = Game::SuperJumpingStateCleanup;
}
SuperJumpingState::~SuperJumpingState() {}

///////////////////////////
//  RunningStateManager //
/////////////////////////

void Game::RunningStateInit(GameCharacter *character)
{
}
void Game::RunningStateUpdate(GameCharacter *character)
{
}
void Game::RunningStateCleanup(GameCharacter *character)
{
}

RunningState::RunningState(Engine::EngineAnimation *animation)
{
    this->animation = animation;
    this->id = GameCharacterState::RUNNING;
    this->init = Game::RunningStateInit;
    this->update = Game::RunningStateUpdate;
    this->cleanup = Game::RunningStateCleanup;
}
RunningState::~RunningState() {}

///////////////////////////
//  LandingStateManager //
/////////////////////////

void Game::LandingStateInit(GameCharacter *character)
{
}
void Game::LandingStateUpdate(GameCharacter *character)
{
}
void Game::LandingStateCleanup(GameCharacter *character)
{
}

LandingState::LandingState(Engine::EngineAnimation *animation)
{
    this->animation = animation;
    this->id = GameCharacterState::LANDING;
    this->init = Game::LandingStateInit;
    this->update = Game::LandingStateUpdate;
    this->cleanup = Game::LandingStateCleanup;
}
LandingState::~LandingState() {}

///////////////////////////
//  SlidingStateManager //
/////////////////////////

void Game::SlidingStateInit(GameCharacter *character)
{
}
void Game::SlidingStateUpdate(GameCharacter *character)
{
}
void Game::SlidingStateCleanup(GameCharacter *character)
{
}

SlidingState::SlidingState(Engine::EngineAnimation *animation)
{
    this->animation = animation;
    this->id = GameCharacterState::SLIDING;
    this->init = Game::SlidingStateInit;
    this->update = Game::SlidingStateUpdate;
    this->cleanup = Game::SlidingStateCleanup;
}
SlidingState::~SlidingState() {}

/////////////////////////////
//  AttackingStateManager //
///////////////////////////

void Game::AttackingStateInit(GameCharacter *character)
{
}
void Game::AttackingStateUpdate(GameCharacter *character)
{
}
void Game::AttackingStateCleanup(GameCharacter *character)
{
}

AttackingState::AttackingState(Engine::EngineAnimation *animation)
{
    this->animation = animation;
    this->id = GameCharacterState::ATTACKING;
    this->init = Game::AttackingStateInit;
    this->update = Game::AttackingStateUpdate;
    this->cleanup = Game::AttackingStateCleanup;
}
AttackingState::~AttackingState() {}