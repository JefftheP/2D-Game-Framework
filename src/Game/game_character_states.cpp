#include "game_character_states.h"

using namespace Game;

////////////////////////
//  IntroStateManager //
////////////////////////

void Game::IntroStateInit(GameCharacter *character)
{
}

void Game::IntroStateUpdate(GameCharacter *character)
{
}

void Game::IntroStateCleanup(GameCharacter *character)
{
}

IntroState::IntroState(Engine::EngineAnimation *animation)
{
    this->animation = animation;
    this->id = GameCharacterState::INTRO;
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
}

void Game::IdleStateUpdate(GameCharacter *character)
{
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
}
void Game::WalkingForwardStateUpdate(GameCharacter *character)
{
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
}
void Game::WalkingBackwardStateUpdate(GameCharacter *character)
{
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