#include "../area.h"
#include "sprite/npc/Paragoomba.h"
#include "sprite/npc/Goomba.h"
#include "sprite/npc/Goompa.h"

#define NAMESPACE A(tutorial_paragoomba)

extern s32 N(DefaultAnims)[];
extern s32 N(LeftWingAnims)[];
extern s32 N(RightWingAnims)[];
extern EvtScript N(EVS_Init_Tutorial);
extern EvtScript N(EVS_Idle);
extern EvtScript N(EVS_TakeTurn);
extern EvtScript N(EVS_HandleEvent);
extern EvtScript N(EVS_KnockDown);

extern s32 A(downed_goomba_tutorial_DefaultAnims)[];
extern EvtScript A(downed_goomba_tutorial_EVS_Init);

enum N(ActorPartIDs) {
    PRT_MAIN            = 1, // body after being downed (must use same name as Goomba part #1)
    PRT_FLYING          = 2, // body while flying
    PRT_DUMMY_WING_L    = 3, // temporary wing while being downed
    PRT_DUMMY_WING_R    = 4, // temporary wing while being downed
};

enum N(ActorParams) {
    DMG_AIR_KICK        = 1,
};

s32 N(DownedDefense)[] = {
    ELEMENT_NORMAL,   0,
    ELEMENT_END,
};

s32 N(FlyingDefense)[] = {
    ELEMENT_NORMAL,   0,
    ELEMENT_END,
};

s32 N(DownedStatusTable)[] = {
    STATUS_KEY_NORMAL,              0,
    STATUS_KEY_DEFAULT,             0,
    STATUS_KEY_SLEEP,             100,
    STATUS_KEY_POISON,            100,
    STATUS_KEY_FROZEN,            100,
    STATUS_KEY_DIZZY,             100,
    STATUS_KEY_FEAR,              100,
    STATUS_KEY_STATIC,            100,
    STATUS_KEY_PARALYZE,          100,
    STATUS_KEY_SHRINK,            100,
    STATUS_KEY_STOP,              100,
    STATUS_TURN_MOD_DEFAULT,        0,
    STATUS_TURN_MOD_SLEEP,          0,
    STATUS_TURN_MOD_POISON,         0,
    STATUS_TURN_MOD_FROZEN,         0,
    STATUS_TURN_MOD_DIZZY,          0,
    STATUS_TURN_MOD_FEAR,           0,
    STATUS_TURN_MOD_STATIC,         0,
    STATUS_TURN_MOD_PARALYZE,       0,
    STATUS_TURN_MOD_SHRINK,         0,
    STATUS_TURN_MOD_STOP,           0,
    STATUS_END,
};

s32 N(FlyingStatusTable)[] = {
    STATUS_KEY_NORMAL,              0,
    STATUS_KEY_DEFAULT,             0,
    STATUS_KEY_SLEEP,             100,
    STATUS_KEY_POISON,             80,
    STATUS_KEY_FROZEN,            100,
    STATUS_KEY_DIZZY,             100,
    STATUS_KEY_FEAR,               80,
    STATUS_KEY_STATIC,             80,
    STATUS_KEY_PARALYZE,          100,
    STATUS_KEY_SHRINK,            100,
    STATUS_KEY_STOP,              100,
    STATUS_TURN_MOD_DEFAULT,        0,
    STATUS_TURN_MOD_SLEEP,          0,
    STATUS_TURN_MOD_POISON,         0,
    STATUS_TURN_MOD_FROZEN,         0,
    STATUS_TURN_MOD_DIZZY,          1,
    STATUS_TURN_MOD_FEAR,           0,
    STATUS_TURN_MOD_STATIC,         0,
    STATUS_TURN_MOD_PARALYZE,       0,
    STATUS_TURN_MOD_SHRINK,         0,
    STATUS_TURN_MOD_STOP,           0,
    STATUS_END,
};

ActorPartBlueprint N(ActorParts)[] = {
    {
        .flags = ACTOR_PART_FLAG_INVISIBLE | ACTOR_PART_FLAG_NO_TARGET,
        .index = PRT_MAIN,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 20 },
        .opacity = 255,
        .idleAnimations = A(downed_goomba_tutorial_DefaultAnims),
        .defenseTable = N(DownedDefense),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, -10 },
    },
    {
        .flags = ACTOR_PART_FLAG_MULTI_TARGET,
        .index = PRT_FLYING,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { 0, 24 },
        .opacity = 255,
        .idleAnimations = N(DefaultAnims),
        .defenseTable = N(FlyingDefense),
        .eventFlags = ACTOR_EVENT_FLAG_GROUNDABLE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, -10 },
    },
    {
        .flags = ACTOR_PART_FLAG_INVISIBLE | ACTOR_PART_FLAG_NO_TARGET,
        .index = PRT_DUMMY_WING_L,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -16, 24 },
        .opacity = 255,
        .idleAnimations = N(LeftWingAnims),
        .defenseTable = N(DownedDefense),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, -10 },
    },
    {
        .flags = ACTOR_PART_FLAG_INVISIBLE | ACTOR_PART_FLAG_NO_TARGET,
        .index = PRT_DUMMY_WING_R,
        .posOffset = { 0, 0, 0 },
        .targetOffset = { -16, 24 },
        .opacity = 255,
        .idleAnimations = N(RightWingAnims),
        .defenseTable = N(DownedDefense),
        .eventFlags = ACTOR_EVENT_FLAGS_NONE,
        .elementImmunityFlags = 0,
        .projectileTargetOffset = { 0, -10 },
    },
};

ActorBlueprint NAMESPACE = {
    .flags = ACTOR_FLAG_FLYING,
    .type = ACTOR_TYPE_PARAGOOMBA,
    .level = ACTOR_LEVEL_PARAGOOMBA,
    .maxHP = 2,
    .partCount = ARRAY_COUNT(N(ActorParts)),
    .partsData = N(ActorParts),
    .initScript = &N(EVS_Init_Tutorial),
    .statusTable = N(FlyingStatusTable),
    .escapeChance = 90,
    .airLiftChance = 100,
    .hurricaneChance = 100,
    .spookChance = 100,
    .upAndAwayChance = 95,
    .spinSmashReq = 0,
    .powerBounceChance = 100,
    .coinReward = 1,
    .size = { 36, 26 },
    .healthBarOffset = { 0, 0 },
    .statusIconOffset = { -10, 20 },
    .statusTextOffset = { 10, 20 },
};

s32 N(DefaultAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_Paragoomba_Idle,
    STATUS_KEY_STONE,     ANIM_Paragoomba_Still,
    STATUS_KEY_SLEEP,     ANIM_Paragoomba_Sleep,
    STATUS_KEY_POISON,    ANIM_Paragoomba_Idle,
    STATUS_KEY_STOP,      ANIM_Paragoomba_Still,
    STATUS_KEY_STATIC,    ANIM_Paragoomba_Idle,
    STATUS_KEY_PARALYZE,  ANIM_Paragoomba_Still,
    STATUS_KEY_DIZZY,     ANIM_Paragoomba_Dizzy,
    STATUS_KEY_FEAR,      ANIM_Paragoomba_Dizzy,
    STATUS_END,
};

s32 N(ShuffleAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_Paragoomba_Run,
    STATUS_KEY_STONE,     ANIM_Paragoomba_Still,
    STATUS_KEY_SLEEP,     ANIM_Paragoomba_Sleep,
    STATUS_KEY_POISON,    ANIM_Paragoomba_Idle,
    STATUS_KEY_STOP,      ANIM_Paragoomba_Still,
    STATUS_KEY_STATIC,    ANIM_Paragoomba_Run,
    STATUS_KEY_PARALYZE,  ANIM_Paragoomba_Still,
    STATUS_KEY_DIZZY,     ANIM_Paragoomba_Dizzy,
    STATUS_KEY_FEAR,      ANIM_Paragoomba_Dizzy,
    STATUS_END,
};

s32 N(LeftWingAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_Paragoomba_LWingStill,
    STATUS_END,
};

s32 N(RightWingAnims)[] = {
    STATUS_KEY_NORMAL,    ANIM_Paragoomba_RWingStill,
    STATUS_END,
};

EvtScript N(EVS_Init) = {
    EVT_CALL(BindTakeTurn, ACTOR_SELF, EVT_PTR(N(EVS_TakeTurn)))
    EVT_CALL(BindIdle, ACTOR_SELF, EVT_PTR(N(EVS_Idle)))
    EVT_CALL(BindHandleEvent, ACTOR_SELF, EVT_PTR(N(EVS_HandleEvent)))
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_Idle) = {
    EVT_LABEL(10)
        EVT_CALL(RandInt, 80, LVar0)
        EVT_ADD(LVar0, 80)
        EVT_LOOP(LVar0)
            EVT_LABEL(0)
                EVT_CALL(GetStatusFlags, ACTOR_SELF, LVar1)
                EVT_IF_FLAG(LVar1, STATUS_FLAGS_IMMOBILIZED)
                    EVT_WAIT(1)
                    EVT_GOTO(0)
                EVT_END_IF
            EVT_WAIT(1)
        EVT_END_LOOP
        EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        EVT_ADD(LVar0, 5)
        EVT_CALL(SetActorIdleSpeed, ACTOR_SELF, EVT_FLOAT(0.6))
        EVT_CALL(SetIdleAnimations, ACTOR_SELF, PRT_FLYING, EVT_PTR(N(ShuffleAnims)))
        EVT_CALL(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
        EVT_CALL(IdleFlyToGoal, ACTOR_SELF, 0, -5, EASING_LINEAR)
        EVT_LOOP(20)
            EVT_LABEL(1)
                EVT_CALL(GetStatusFlags, ACTOR_SELF, LVar1)
                EVT_IF_FLAG(LVar1, STATUS_FLAGS_IMMOBILIZED)
                    EVT_WAIT(1)
                    EVT_GOTO(1)
                EVT_END_IF
            EVT_WAIT(1)
        EVT_END_LOOP
        EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
        EVT_SUB(LVar0, 5)
        EVT_CALL(SetActorIdleSpeed, ACTOR_SELF, EVT_FLOAT(0.6))
        EVT_CALL(SetIdleGoal, ACTOR_SELF, LVar0, LVar1, LVar2)
        EVT_CALL(IdleFlyToGoal, ACTOR_SELF, 0, -5, EASING_LINEAR)
        EVT_CALL(SetIdleAnimations, ACTOR_SELF, PRT_FLYING, EVT_PTR(N(DefaultAnims)))
        EVT_LOOP(40)
            EVT_LABEL(2)
                EVT_CALL(GetStatusFlags, ACTOR_SELF, LVar1)
                EVT_IF_FLAG(LVar1, STATUS_FLAGS_IMMOBILIZED)
                    EVT_WAIT(1)
                    EVT_GOTO(2)
                EVT_END_IF
            EVT_WAIT(1)
        EVT_END_LOOP
        EVT_GOTO(10)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_Paragoomba_GoHome) = {
    EVT_CALL(ResetAllActorSounds, ACTOR_SELF)
    EVT_CALL(SetGoalToHome, ACTOR_SELF)
    EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(7.0))
    EVT_CALL(FlyToGoal, ACTOR_SELF, 0, 1, EASING_SIN_OUT)
    EVT_CALL(SetAnimation, ACTOR_SELF, PRT_FLYING, ANIM_Paragoomba_Idle)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_HandleEvent) = {
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    EVT_CALL(GetLastEvent, ACTOR_SELF, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_OR_EQ(EVENT_HIT_COMBO)
        EVT_CASE_OR_EQ(EVENT_HIT)
            EVT_SET_CONST(LVar0, PRT_FLYING)
            EVT_SET_CONST(LVar1, ANIM_Paragoomba_Hurt)
            EVT_EXEC_WAIT(EVS_Enemy_Hit)
            EVT_CALL(GetBattlePhase, LVar0)
            EVT_IF_EQ(LVar0, PHASE_FIRST_STRIKE)
                EVT_CALL(GetEncounterTrigger, LVar0)
                EVT_IF_EQ(LVar0, ENCOUNTER_TRIGGER_HAMMER)
                    EVT_EXEC_WAIT(N(EVS_KnockDown))
                EVT_END_IF
            EVT_END_IF
        EVT_END_CASE_GROUP
        EVT_CASE_EQ(EVENT_BURN_HIT)
            EVT_SET_CONST(LVar0, PRT_FLYING)
            EVT_SET_CONST(LVar1, ANIM_Paragoomba_BurnHurt)
            EVT_SET_CONST(LVar2, ANIM_Paragoomba_BurnStill)
            EVT_EXEC_WAIT(EVS_Enemy_BurnHit)
        EVT_CASE_EQ(EVENT_BURN_DEATH)
            EVT_SET_CONST(LVar0, PRT_FLYING)
            EVT_SET_CONST(LVar1, ANIM_Paragoomba_BurnHurt)
            EVT_SET_CONST(LVar2, ANIM_Paragoomba_BurnStill)
            EVT_EXEC_WAIT(EVS_Enemy_BurnHit)
            EVT_SET_CONST(LVar0, PRT_FLYING)
            EVT_SET_CONST(LVar1, ANIM_Paragoomba_BurnStill)
            EVT_EXEC_WAIT(EVS_Enemy_Death)
            EVT_RETURN
        EVT_CASE_EQ(EVENT_FALL_TRIGGER)
            EVT_SET_CONST(LVar0, PRT_FLYING)
            EVT_SET_CONST(LVar1, ANIM_Paragoomba_Hurt)
            EVT_EXEC_WAIT(EVS_Enemy_Hit)
            EVT_EXEC_WAIT(N(EVS_KnockDown))
        EVT_CASE_EQ(EVENT_15)
            EVT_SET_CONST(LVar0, PRT_FLYING)
            EVT_SET_CONST(LVar1, ANIM_Paragoomba_BurnHurt)
            EVT_SET_CONST(LVar2, ANIM_Paragoomba_BurnStill)
            EVT_EXEC_WAIT(EVS_Enemy_BurnHit)
            EVT_EXEC_WAIT(N(EVS_KnockDown))
        EVT_CASE_EQ(EVENT_SHOCK_HIT)
            EVT_SET_CONST(LVar0, PRT_FLYING)
            EVT_SET_CONST(LVar1, ANIM_Paragoomba_Electrocute)
            EVT_EXEC_WAIT(EVS_Enemy_ShockHit)
            EVT_SET_CONST(LVar0, PRT_FLYING)
            EVT_SET_CONST(LVar1, ANIM_Paragoomba_Hurt)
            EVT_EXEC_WAIT(EVS_Enemy_JumpBack)
            EVT_CALL(SetAnimation, ACTOR_SELF, PRT_FLYING, ANIM_Paragoomba_Dizzy)
            EVT_EXEC_WAIT(N(EVS_Paragoomba_GoHome))
        EVT_CASE_EQ(EVENT_SHOCK_DEATH)
            EVT_SET_CONST(LVar0, PRT_FLYING)
            EVT_SET_CONST(LVar1, ANIM_Paragoomba_Electrocute)
            EVT_EXEC_WAIT(EVS_Enemy_ShockHit)
            EVT_SET_CONST(LVar0, PRT_FLYING)
            EVT_SET_CONST(LVar1, ANIM_Paragoomba_HurtStill)
            EVT_EXEC_WAIT(EVS_Enemy_Death)
            EVT_RETURN
        EVT_CASE_EQ(EVENT_STAR_BEAM)
        EVT_CASE_OR_EQ(EVENT_ZERO_DAMAGE)
        EVT_CASE_OR_EQ(EVENT_IMMUNE)
        EVT_CASE_OR_EQ(EVENT_AIR_LIFT_FAILED)
            EVT_SET_CONST(LVar0, PRT_FLYING)
            EVT_SET_CONST(LVar1, ANIM_Paragoomba_Idle)
            EVT_EXEC_WAIT(EVS_Enemy_NoDamageHit)
        EVT_END_CASE_GROUP
        EVT_CASE_EQ(EVENT_DEATH)
            EVT_SET_CONST(LVar0, PRT_FLYING)
            EVT_SET_CONST(LVar1, ANIM_Paragoomba_Hurt)
            EVT_EXEC_WAIT(EVS_Enemy_Hit)
            EVT_WAIT(10)
            EVT_SET_CONST(LVar0, PRT_FLYING)
            EVT_SET_CONST(LVar1, ANIM_Paragoomba_HurtStill)
            EVT_EXEC_WAIT(EVS_Enemy_Death)
            EVT_RETURN
        EVT_CASE_EQ(EVENT_BEGIN_FIRST_STRIKE)
            EVT_CALL(SetActorPos, ACTOR_SELF, 20, 0, 0)
            EVT_CALL(HPBarToCurrent, ACTOR_SELF)
        EVT_CASE_EQ(EVENT_END_FIRST_STRIKE)
            EVT_CALL(SetAnimation, ACTOR_SELF, PRT_FLYING, ANIM_Paragoomba_Run)
            EVT_EXEC_WAIT(N(EVS_Paragoomba_GoHome))
            EVT_CALL(HPBarToHome, ACTOR_SELF)
        EVT_CASE_EQ(EVENT_RECOVER_STATUS)
            EVT_SET_CONST(LVar0, PRT_FLYING)
            EVT_SET_CONST(LVar1, ANIM_Paragoomba_Idle)
            EVT_EXEC_WAIT(EVS_Enemy_Recover)
        EVT_CASE_EQ(EVENT_SCARE_AWAY)
            EVT_CALL(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_FLYING, FALSE)
            EVT_SET_CONST(LVar0, PRT_FLYING)
            EVT_SET_CONST(LVar1, ANIM_Paragoomba_Run)
            EVT_SET_CONST(LVar2, ANIM_Paragoomba_Hurt)
            EVT_EXEC_WAIT(EVS_Enemy_ScareAway)
            EVT_RETURN
        EVT_CASE_EQ(EVENT_BEGIN_AIR_LIFT)
            EVT_SET_CONST(LVar0, PRT_FLYING)
            EVT_SET_CONST(LVar1, ANIM_Paragoomba_Run)
            EVT_EXEC_WAIT(EVS_Enemy_AirLift)
        EVT_CASE_EQ(EVENT_BLOW_AWAY)
            EVT_SET_CONST(LVar0, PRT_FLYING)
            EVT_SET_CONST(LVar1, ANIM_Paragoomba_Hurt)
            EVT_EXEC_WAIT(EVS_Enemy_BlowAway)
            EVT_RETURN
        EVT_CASE_DEFAULT
    EVT_END_SWITCH
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_RESTART)
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_TakeTurn) = {
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_DISABLE)
    EVT_CALL(SetTargetActor, ACTOR_SELF, ACTOR_PLAYER)
    EVT_CALL(SetGoalToTarget, ACTOR_SELF)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_ENEMY_APPROACH)
    EVT_CALL(BattleCamTargetActor, ACTOR_SELF)
    EVT_CALL(func_8024ECF8, BTL_CAM_MODEY_MINUS_1, BTL_CAM_MODEX_1, FALSE)
    EVT_CALL(SetAnimation, ACTOR_SELF, PRT_FLYING, ANIM_Paragoomba_Run)
    EVT_CALL(SetGoalToTarget, ACTOR_SELF)
    EVT_CALL(AddGoalPos, ACTOR_SELF, 50, 0, 0)
    EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(6.0))
    EVT_CALL(FlyToGoal, ACTOR_SELF, 0, -4, EASING_LINEAR)
    EVT_CALL(EnemyTestTarget, ACTOR_SELF, LVar0, 0, 0, 1, BS_FLAGS1_10)
    EVT_SWITCH(LVar0)
        EVT_CASE_OR_EQ(HIT_RESULT_MISS)
        EVT_CASE_OR_EQ(HIT_RESULT_LUCKY)
            EVT_SET(LVarA, LVar0)
            EVT_WAIT(10)
            EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_66)
            EVT_CALL(SetBattleCamZoom, 300)
            EVT_CALL(BattleCamTargetActor, ACTOR_SELF)
            EVT_CALL(func_8024ECF8, BTL_CAM_MODEY_MINUS_1, BTL_CAM_MODEX_1, FALSE)
            EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_PARAGOOMBA_PREDIVE)
            EVT_CALL(SetActorSounds, ACTOR_SELF, ACTOR_SOUND_JUMP, SOUND_NONE, 0)
            EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(5.0))
            EVT_CALL(SetActorJumpGravity, ACTOR_SELF, EVT_FLOAT(1.8))
            EVT_CALL(SetAnimation, ACTOR_SELF, PRT_FLYING, ANIM_Paragoomba_Dive)
            EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            EVT_CALL(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            EVT_CALL(JumpToGoal, ACTOR_SELF, 10, FALSE, FALSE, FALSE)
            EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_PARAGOOMBA_DIVE)
            EVT_CALL(SetActorSounds, ACTOR_SELF, ACTOR_SOUND_FLY, SOUND_NONE, SOUND_NONE)
            EVT_CALL(SetGoalToTarget, ACTOR_SELF)
            EVT_SUB(LVar0, 80)
            EVT_SET(LVar1, 20)
            EVT_CALL(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(8.0))
            EVT_CALL(SetAnimation, ACTOR_SELF, PRT_FLYING, ANIM_Paragoomba_Dive)
            EVT_CALL(FlyToGoal, ACTOR_SELF, 0, -10, EASING_QUADRATIC_OUT)
            EVT_THREAD
                EVT_LOOP(4)
                    EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_PARAGOOMBA_FLY)
                    EVT_WAIT(4)
                EVT_END_LOOP
            EVT_END_THREAD
            EVT_CALL(SetAnimation, ACTOR_SELF, PRT_FLYING, ANIM_Paragoomba_Miss)
            EVT_CALL(AddActorDecoration, ACTOR_SELF, PRT_FLYING, 0, ACTOR_DECORATION_SWEAT)
            EVT_CALL(SetAnimationRate, ACTOR_SELF, PRT_FLYING, EVT_FLOAT(3.0))
            EVT_WAIT(10)
            EVT_IF_EQ(LVarA, HIT_RESULT_LUCKY)
                EVT_CALL(EnemyTestTarget, ACTOR_SELF, LVar0, DAMAGE_TYPE_TRIGGER_LUCKY, 0, 0, 0)
            EVT_END_IF
            EVT_WAIT(10)
            EVT_CALL(SetAnimationRate, ACTOR_SELF, PRT_FLYING, EVT_FLOAT(1.0))
            EVT_CALL(UseBattleCamPreset, BTL_CAM_DEFAULT)
            EVT_CALL(ResetAllActorSounds, ACTOR_SELF)
            EVT_CALL(YieldTurn)
            EVT_CALL(SetAnimation, ACTOR_SELF, PRT_FLYING, ANIM_Paragoomba_Run)
            EVT_CALL(SetActorYaw, ACTOR_SELF, 180)
            EVT_EXEC_WAIT(N(EVS_Paragoomba_GoHome))
            EVT_CALL(SetActorYaw, ACTOR_SELF, 0)
            EVT_CALL(RemoveActorDecoration, ACTOR_SELF, PRT_FLYING, 0)
            EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_RESTART)
            EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
            EVT_RETURN
        EVT_END_CASE_GROUP
        EVT_CASE_DEFAULT
            EVT_WAIT(10)
            EVT_CALL(UseBattleCamPreset, BTL_CAM_PRESET_66)
            EVT_CALL(SetBattleCamZoom, 300)
            EVT_CALL(BattleCamTargetActor, ACTOR_SELF)
            EVT_CALL(func_8024ECF8, BTL_CAM_MODEY_MINUS_1, BTL_CAM_MODEX_1, FALSE)
            EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_PARAGOOMBA_PREDIVE)
            EVT_CALL(SetActorSounds, ACTOR_SELF, ACTOR_SOUND_JUMP, SOUND_NONE, 0)
            EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(5.0))
            EVT_CALL(SetActorJumpGravity, ACTOR_SELF, EVT_FLOAT(1.8))
            EVT_CALL(SetAnimation, ACTOR_SELF, PRT_FLYING, ANIM_Paragoomba_Dive)
            EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            EVT_CALL(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
            EVT_CALL(JumpToGoal, ACTOR_SELF, 10, FALSE, FALSE, FALSE)
            EVT_CALL(PlaySoundAtActor, ACTOR_SELF, SOUND_PARAGOOMBA_DIVE)
            EVT_CALL(SetActorSounds, ACTOR_SELF, ACTOR_SOUND_FLY, SOUND_NONE, SOUND_NONE)
            EVT_CALL(SetGoalToTarget, ACTOR_SELF)
            EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(8.0))
            EVT_CALL(SetAnimation, ACTOR_SELF, PRT_FLYING, ANIM_Paragoomba_Dive)
            EVT_CALL(FlyToGoal, ACTOR_SELF, 0, -10, EASING_LINEAR)
    EVT_END_SWITCH
    EVT_WAIT(2)
    EVT_CALL(EnemyDamageTarget, ACTOR_SELF, LVar0, 0, 0, 0, DMG_AIR_KICK, BS_FLAGS1_SP_EVT_ACTIVE)
    EVT_SWITCH(LVar0)
        EVT_CASE_OR_EQ(HIT_RESULT_HIT)
        EVT_CASE_OR_EQ(HIT_RESULT_NO_DAMAGE)
            EVT_CALL(UseBattleCamPreset, BTL_CAM_DEFAULT)
            EVT_CALL(SetGoalToTarget, ACTOR_SELF)
            EVT_CALL(AddGoalPos, ACTOR_SELF, 50, 10, 0)
            EVT_CALL(SetActorSpeed, ACTOR_SELF, EVT_FLOAT(6.0))
            EVT_CALL(SetAnimation, ACTOR_SELF, PRT_FLYING, ANIM_Paragoomba_Run)
            EVT_CALL(FlyToGoal, ACTOR_SELF, 0, -10, EASING_LINEAR)
            EVT_CALL(ResetAllActorSounds, ACTOR_SELF)
            EVT_WAIT(5)
            EVT_CALL(YieldTurn)
            EVT_CALL(SetAnimation, ACTOR_SELF, PRT_FLYING, ANIM_Paragoomba_Run)
            EVT_EXEC_WAIT(N(EVS_Paragoomba_GoHome))
        EVT_END_CASE_GROUP
    EVT_END_SWITCH
    EVT_CALL(EnableIdleScript, ACTOR_SELF, IDLE_SCRIPT_RESTART)
    EVT_CALL(UseIdleAnimation, ACTOR_SELF, TRUE)
    EVT_RETURN
    EVT_END
};

#include "common/StartRumbleWithParams.inc.c"

EvtScript N(EVS_KnockDown) = {
    EVT_CALL(HideHealthBar, ACTOR_SELF)
    EVT_CALL(SetPartFlags, ACTOR_SELF, PRT_FLYING, ACTOR_PART_FLAG_INVISIBLE | ACTOR_PART_FLAG_4 | ACTOR_PART_FLAG_NO_TARGET)
    EVT_CALL(SetPartFlags, ACTOR_SELF, PRT_DUMMY_WING_L, ACTOR_PART_FLAG_4 | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION)
    EVT_CALL(SetPartFlags, ACTOR_SELF, PRT_DUMMY_WING_R, ACTOR_PART_FLAG_4 | ACTOR_PART_FLAG_NO_TARGET | ACTOR_PART_FLAG_USE_ABSOLUTE_POSITION)
    EVT_CALL(SetPartFlags, ACTOR_SELF, PRT_MAIN, ACTOR_PART_FLAG_4 | ACTOR_PART_FLAG_MULTI_TARGET)
    EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_CALL(SetPartPos, ACTOR_SELF, PRT_DUMMY_WING_L, LVar0, LVar1, LVar2)
    EVT_CALL(SetPartDispOffset, ACTOR_SELF, PRT_DUMMY_WING_L, -9, 7, -2)
    EVT_CALL(SetPartPos, ACTOR_SELF, PRT_DUMMY_WING_R, LVar0, LVar1, LVar2)
    EVT_CALL(SetPartDispOffset, ACTOR_SELF, PRT_DUMMY_WING_R, 11, 7, -2)
    EVT_CALL(GetLastEvent, ACTOR_SELF, LVar0)
    EVT_IF_EQ(LVar0, EVENT_15)
        EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Goomba_BurnStill)
    EVT_ELSE
        EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Goomba_Hurt)
    EVT_END_IF
    EVT_CALL(SetActorSounds, ACTOR_SELF, ACTOR_SOUND_JUMP, SOUND_FALL_QUICK, 0)
    EVT_CALL(GetActorPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_SET(LVar1, 0)
    EVT_CALL(SetActorJumpGravity, ACTOR_SELF, EVT_FLOAT(0.8))
    EVT_CALL(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_CALL(JumpToGoal, ACTOR_SELF, 15, FALSE, TRUE, FALSE)
    EVT_CALL(N(StartRumbleWithParams), 100, 10)
    EVT_THREAD
        EVT_CALL(ShakeCam, CAM_BATTLE, 0, 5, EVT_FLOAT(0.3))
    EVT_END_THREAD
    EVT_CALL(ResetActorSounds, ACTOR_SELF, ACTOR_SOUND_JUMP)
    EVT_CALL(GetLastEvent, ACTOR_SELF, LVar3)
    EVT_IF_EQ(LVar3, EVENT_15)
        EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Goomba_Hurt)
        EVT_CALL(GetActorPos, ACTOR_SELF, LVar3, LVar4, LVar5)
        EVT_ADD(LVar4, 10)
        EVT_ADD(LVar5, 5)
        EVT_PLAY_EFFECT(EFFECT_SMOKE_BURST, 0, LVar3, LVar4, LVar5, EVT_FLOAT(1.0), 10, 0)
    EVT_END_IF
    EVT_CALL(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_CALL(JumpToGoal, ACTOR_SELF, 10, FALSE, TRUE, FALSE)
    EVT_CALL(SetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_CALL(JumpToGoal, ACTOR_SELF, 5, FALSE, TRUE, FALSE)
    EVT_LOOP(10)
        EVT_CALL(SetPartFlagBits, ACTOR_SELF, PRT_DUMMY_WING_L, ACTOR_PART_FLAG_INVISIBLE, TRUE)
        EVT_CALL(SetPartFlagBits, ACTOR_SELF, PRT_DUMMY_WING_R, ACTOR_PART_FLAG_INVISIBLE, TRUE)
        EVT_WAIT(1)
        EVT_CALL(SetPartFlagBits, ACTOR_SELF, PRT_DUMMY_WING_L, ACTOR_PART_FLAG_INVISIBLE, FALSE)
        EVT_CALL(SetPartFlagBits, ACTOR_SELF, PRT_DUMMY_WING_R, ACTOR_PART_FLAG_INVISIBLE, FALSE)
        EVT_WAIT(1)
    EVT_END_LOOP
    EVT_CALL(SetPartFlagBits, ACTOR_SELF, PRT_DUMMY_WING_L, ACTOR_PART_FLAG_INVISIBLE, TRUE)
    EVT_CALL(SetPartFlagBits, ACTOR_SELF, PRT_DUMMY_WING_R, ACTOR_PART_FLAG_INVISIBLE, TRUE)
    EVT_CALL(GetIndexFromHome, ACTOR_SELF, LVar0)
    EVT_MOD(LVar0, 4)
    EVT_CALL(SetGoalToIndex, ACTOR_SELF, LVar0)
    EVT_CALL(GetGoalPos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_CALL(SetHomePos, ACTOR_SELF, LVar0, LVar1, LVar2)
    EVT_CALL(SetAnimation, ACTOR_SELF, PRT_MAIN, ANIM_Goomba_Idle)
    EVT_CALL(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_FLYING, FALSE)
    EVT_CALL(SetStatusTable, ACTOR_SELF, EVT_PTR(N(DownedStatusTable)))
    EVT_CALL(SetActorType, ACTOR_SELF, ACTOR_TYPE_GOOMBA)
    EVT_EXEC_WAIT(A(downed_goomba_tutorial_EVS_Init))
    EVT_CALL(SetActorFlagBits, ACTOR_SELF, ACTOR_FLAG_TYPE_CHANGED, TRUE)
    EVT_CALL(HPBarToHome, ACTOR_SELF)
    EVT_CALL(ResetAllActorSounds, ACTOR_SELF)
    EVT_RETURN
    EVT_END
};

// downed paragoombas are handled via a special nested goomba import
#define NESTED_GOOMBA_INCLUDE
#define NAMESPACE A(downed_goomba_tutorial)
#include "battle/common/actor/goomba.inc.c"

// everything above this point is identical to paragoomba

#define NAMESPACE A(tutorial_paragoomba)
extern EvtScript N(EVS_HandlePhase);

EvtScript N(EVS_Init_Tutorial) = {
    EVT_CALL(BindTakeTurn, ACTOR_SELF, EVT_PTR(N(EVS_TakeTurn)))
    EVT_CALL(BindIdle, ACTOR_SELF, EVT_PTR(N(EVS_Idle)))
    EVT_CALL(BindHandleEvent, ACTOR_SELF, EVT_PTR(N(EVS_HandleEvent)))
    EVT_CALL(BindHandlePhase, ACTOR_SELF, EVT_PTR(N(EVS_HandlePhase)))
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_TutorialScene) = {
    EVT_CALL(SetActorYaw, ACTOR_PLAYER, 30)
    EVT_WAIT(1)
    EVT_CALL(SetActorYaw, ACTOR_PLAYER, 60)
    EVT_WAIT(1)
    EVT_CALL(SetActorYaw, ACTOR_PLAYER, 90)
    EVT_WAIT(1)
    EVT_CALL(SetActorYaw, ACTOR_PLAYER, 120)
    EVT_WAIT(1)
    EVT_CALL(SetActorYaw, ACTOR_PLAYER, 150)
    EVT_WAIT(1)
    EVT_CALL(SetActorYaw, ACTOR_PLAYER, 180)
    EVT_WAIT(5)
    EVT_CALL(UseBattleCamPreset, BTL_CAM_DEFAULT)
    EVT_CALL(MoveBattleCamOver, 10)
    EVT_CALL(ActorSpeak, MSG_CH0_00B8, ACTOR_PARTNER, 0, ANIM_Goompa_Talk, ANIM_Goompa_Idle)
    EVT_SET(GF_Tutorial_FlyingEnemy, TRUE)
    EVT_CALL(SetActorYaw, ACTOR_PLAYER, 150)
    EVT_WAIT(1)
    EVT_CALL(SetActorYaw, ACTOR_PLAYER, 120)
    EVT_WAIT(1)
    EVT_CALL(SetActorYaw, ACTOR_PLAYER, 90)
    EVT_WAIT(1)
    EVT_CALL(SetActorYaw, ACTOR_PLAYER, 60)
    EVT_WAIT(1)
    EVT_CALL(SetActorYaw, ACTOR_PLAYER, 30)
    EVT_WAIT(1)
    EVT_CALL(SetActorYaw, ACTOR_PLAYER, 0)
    EVT_WAIT(5)
    EVT_RETURN
    EVT_END
};

EvtScript N(EVS_HandlePhase) = {
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, FALSE)
    EVT_CALL(EnableIdleScript, ACTOR_PARTNER, IDLE_SCRIPT_DISABLE)
    EVT_CALL(GetBattlePhase, LVar0)
    EVT_SWITCH(LVar0)
        EVT_CASE_EQ(PHASE_PLAYER_BEGIN)
            EVT_IF_EQ(GF_Tutorial_FlyingEnemy, FALSE)
                EVT_EXEC_WAIT(N(EVS_TutorialScene))
            EVT_END_IF
    EVT_END_SWITCH
    EVT_CALL(EnableIdleScript, ACTOR_PARTNER, IDLE_SCRIPT_ENABLE)
    EVT_CALL(UseIdleAnimation, ACTOR_PARTNER, TRUE)
    EVT_RETURN
    EVT_END
};
