#pragma once

#include "game_structs.h"

namespace Game
{
    struct IntroState : CharacterStateManager
    {
        IntroState(Engine::EngineAnimation *animation);
        ~IntroState();
    };

    struct IdleState : CharacterStateManager
    {
        IdleState(Engine::EngineAnimation *animation);
        ~IdleState();
    };
    struct BlockingState : CharacterStateManager
    {
        BlockingState(Engine::EngineAnimation *animation);
        ~BlockingState();
    };

    struct ReelingState : CharacterStateManager
    {
        ReelingState(Engine::EngineAnimation *animation);
        ~ReelingState();
    };

    struct WalkingForwardState : CharacterStateManager
    {
        WalkingForwardState(Engine::EngineAnimation *animation);
        ~WalkingForwardState();
    };

    struct WalkingBackwardState : CharacterStateManager
    {
        WalkingBackwardState(Engine::EngineAnimation *animation);
        ~WalkingBackwardState();
    };

    struct JumpingState : CharacterStateManager
    {
        JumpingState(Engine::EngineAnimation *animation);
        ~JumpingState();
    };

    struct FallingState : CharacterStateManager
    {
        FallingState(Engine::EngineAnimation *animation);
        ~FallingState();
    };

    struct SuperJumpingState : CharacterStateManager
    {
        SuperJumpingState(Engine::EngineAnimation *animation);
        ~SuperJumpingState();
    };

    struct RunningState : CharacterStateManager
    {
        RunningState(Engine::EngineAnimation *animation);
        ~RunningState();
    };

    struct LandingState : CharacterStateManager
    {
        LandingState(Engine::EngineAnimation *animation);
        ~LandingState();
    };

    struct SlidingState : CharacterStateManager
    {
        SlidingState(Engine::EngineAnimation *animation);
        ~SlidingState();
    };

    // This one I need to rethink
    struct AttackingState : CharacterStateManager
    {
        AttackingState(Engine::EngineAnimation *animation);
        ~AttackingState();
    };

    void IntroStateInit(GameCharacter *character);
    void IntroStateUpdate(GameCharacter *character);
    void IntroStateCleanup(GameCharacter *character);

    void IdleStateInit(GameCharacter *character);
    void IdleStateUpdate(GameCharacter *character);
    void IdleStateCleanup(GameCharacter *character);

    void BlockingStateInit(GameCharacter *character);
    void BlockingStateUpdate(GameCharacter *character);
    void BlockingStateCleanup(GameCharacter *character);

    void ReelingStateInit(GameCharacter *character);
    void ReelingStateUpdate(GameCharacter *character);
    void ReelingStateCleanup(GameCharacter *character);

    void WalkingForwardStateInit(GameCharacter *character);
    void WalkingForwardStateUpdate(GameCharacter *character);
    void WalkingForwardStateCleanup(GameCharacter *character);

    void WalkingBackwardStateInit(GameCharacter *character);
    void WalkingBackwardStateUpdate(GameCharacter *character);
    void WalkingBackwardStateCleanup(GameCharacter *character);

    void JumpingStateInit(GameCharacter *character);
    void JumpingStateUpdate(GameCharacter *character);
    void JumpingStateCleanup(GameCharacter *character);

    void FallingStateInit(GameCharacter *character);
    void FallingStateUpdate(GameCharacter *character);
    void FallingStateCleanup(GameCharacter *character);

    void SuperJumpingStateInit(GameCharacter *character);
    void SuperJumpingStateUpdate(GameCharacter *character);
    void SuperJumpingStateCleanup(GameCharacter *character);

    void RunningStateInit(GameCharacter *character);
    void RunningStateUpdate(GameCharacter *character);
    void RunningStateCleanup(GameCharacter *character);

    void LandingStateInit(GameCharacter *character);
    void LandingStateUpdate(GameCharacter *character);
    void LandingStateCleanup(GameCharacter *character);

    void SlidingStateInit(GameCharacter *character);
    void SlidingStateUpdate(GameCharacter *character);
    void SlidingStateCleanup(GameCharacter *character);

    void AttackingStateInit(GameCharacter *character);
    void AttackingStateUpdate(GameCharacter *character);
    void AttackingStateCleanup(GameCharacter *character);

} // namespace Game