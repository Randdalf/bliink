//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
// This is a skeleton file for use when creating a new 
// NPC. Copy and rename this file for the new
// NPC and add the copy to the build.
//
// Leave this file in the build until we ship! Allowing 
// this file to be rebuilt with the rest of the game ensures
// that it stays up to date with the rest of the NPC code.
//
// Replace occurances of CBliinkSimpleNPC with the new NPC's
// classname. Don't forget the lower-case occurance in 
// LINK_ENTITY_TO_CLASS()
//
//
// ASSUMPTIONS MADE:
//
// You're making a character based on CAI_BaseNPC. If this 
// is not true, make sure you replace all occurances
// of 'CAI_BaseNPC' in this file with the appropriate 
// parent class.
//
// You're making a human-sized NPC that walks.
//
//=============================================================================//
#include "cbase.h"
#include "ai_default.h"
#include "ai_task.h"
#include "ai_schedule.h"
#include "ai_hull.h"
#include "soundent.h"
#include "game.h"
#include "npcevent.h"
#include "entitylist.h"
#include "activitylist.h"
#include "ai_basenpc.h"
#include "engine/IEngineSound.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//=========================================================
// Private activities
//=========================================================
//int	ACT_MYCUSTOMACTIVITY = -1;

//=========================================================
// Custom schedules
//=========================================================
enum
{
	SCHED_MYCUSTOMSCHEDULE = LAST_SHARED_SCHEDULE,
};

//=========================================================
// Custom tasks
//=========================================================
enum 
{
	TASK_MYCUSTOMTASK = LAST_SHARED_TASK,
};


//=========================================================
// Custom Conditions
//=========================================================
enum 
{
	COND_CAN_BE_SEEN = LAST_SHARED_CONDITION,
};


//=========================================================
//=========================================================
class CBliinkBliinker : public CAI_BaseNPC
{
	DECLARE_CLASS( CBliinkBliinker, CAI_BaseNPC );

public:
	void	Precache( void );
	void	Spawn( void );
	Class_T Classify( void );
	int		SelectSchedule( void );
	void	OnChangeActivity( Activity eNewActivity );
	void	HandleAnimEvent( animevent_t *pEvent );
	void	NPCThink( void );

	void GatherConditions ( void );

	Activity	NPC_TranslateActivity( Activity eNewActivity );

	DECLARE_DATADESC();

	// This is a dummy field. In order to provide save/restore
	// code in this file, we must have at least one field
	// for the code to operate on. Delete this field when
	// you are ready to do your own save/restore for this
	// character.
	int		m_iDeleteThisField;
	float attackTime;

	DEFINE_CUSTOM_AI;
};

LINK_ENTITY_TO_CLASS( npc_bliink_bliinker, CBliinkBliinker );
//IMPLEMENT_CUSTOM_AI( npc_citizen,CBliinkBliinker );


//---------------------------------------------------------
// Save/Restore
//---------------------------------------------------------
BEGIN_DATADESC( CBliinkBliinker )

	DEFINE_FIELD( m_iDeleteThisField, FIELD_INTEGER ),

END_DATADESC()

//-----------------------------------------------------------------------------
// Purpose: Initialize the custom schedules
// Input  :
// Output :
//-----------------------------------------------------------------------------
/*void CBliinkBliinker::InitCustomSchedules(void) 
{
	INIT_CUSTOM_AI(CBliinkBliinker);

	ADD_CUSTOM_TASK(CBliinkBliinker,		TASK_MYCUSTOMTASK);

	ADD_CUSTOM_SCHEDULE(CBliinkBliinker,	SCHED_MYCUSTOMSCHEDULE);

	//ADD_CUSTOM_ACTIVITY(CBliinkSimpleNPC,	ACT_MYCUSTOMACTIVITY);

	ADD_CUSTOM_CONDITION(CBliinkBliinker,	COND_MYCUSTOMCONDITION);
}*/

AI_BEGIN_CUSTOM_NPC( npc_bliink_bliinker, CBliinkBliinker )
	DECLARE_CONDITION( COND_CAN_BE_SEEN )
AI_END_CUSTOM_NPC()

//-----------------------------------------------------------------------------
// Purpose: 
//
//
//-----------------------------------------------------------------------------
void CBliinkBliinker::Precache( void )
{
	PrecacheModel( "models/creeps/neutral_creeps/n_creep_ghost_a/n_creep_ghost_a.mdl" );

	BaseClass::Precache();
}

//-----------------------------------------------------------------------------
// Purpose: 
//
//
//-----------------------------------------------------------------------------
int CBliinkBliinker::SelectSchedule( void )
{
	//return BaseClass::SelectCombatSchedule();
	if (HasCondition(COND_ENEMY_FACING_ME)) {
		Msg("YOU CAN SEE MEEEEEEE\n");
	}
	/*if (HasCondition(COND_SEE_ENEMY)) {
		/*Msg("I SEE YOUUUUU");	
		if ( HasCondition(COND_CAN_MELEE_ATTACK1) ) {
			//Msg("HIIIIIIIIIIIIYA!!!");
			return SCHED_MELEE_ATTACK1;
		}
		return SCHED_CHASE_ENEMY;
	}
	return SCHED_RUN_RANDOM;*/
	return SCHED_IDLE_STAND;
	//return BaseClass::SelectSchedule();
}

void CBliinkBliinker::GatherConditions( void ) {
	


	BaseClass::GatherConditions();
}


//-----------------------------------------------------------------------------
// Purpose: 
//
//
//-----------------------------------------------------------------------------
void CBliinkBliinker::Spawn( void )
{
	Precache();
	
	CapabilitiesClear();
	CapabilitiesAdd( bits_CAP_MOVE_GROUND | bits_CAP_INNATE_MELEE_ATTACK1 );

	SetModel( "models/creeps/neutral_creeps/n_creep_ghost_a/n_creep_ghost_a.mdl" );
	SetHullType(HULL_HUMAN);
	SetHullSizeNormal();

	SetSolid( SOLID_BBOX );
	AddSolidFlags( FSOLID_NOT_STANDABLE );
	SetMoveType( MOVETYPE_STEP );
	SetBloodColor( BLOOD_COLOR_RED );
	m_iHealth			= 20;
	m_flFieldOfView		= 0.5;
	m_NPCState			= NPC_STATE_NONE;
	attackTime			= -1;

	NPCInit();
}

// Overriding activities with DOTA activities
Activity	CBliinkBliinker::NPC_TranslateActivity( Activity eNewActivity )
{
	eNewActivity = BaseClass::NPC_TranslateActivity( eNewActivity );

	if ( eNewActivity == ACT_IDLE )
		return ACT_DOTA_IDLE;
	else if ( eNewActivity == ACT_RUN || eNewActivity == ACT_WALK )
		return ACT_DOTA_RUN;
	else if ( eNewActivity == ACT_MELEE_ATTACK1 )
		return ACT_DOTA_ATTACK;

	return eNewActivity;
}

void CBliinkBliinker::HandleAnimEvent( animevent_t *pEvent ) {

	BaseClass:HandleAnimEvent( pEvent );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CBliinkBliinker::OnChangeActivity( Activity eNewActivity )
{
	if (eNewActivity == ACT_MELEE_ATTACK1) {
		attackTime = gpGlobals->curtime + 0.25;
		Msg("%f KK\n", attackTime);
	}

	BaseClass::OnChangeActivity( eNewActivity );
}

void CBliinkBliinker::NPCThink( void ) {
	if (gpGlobals->curtime > attackTime && attackTime > 0) {
		CBaseEntity *pHurt = NULL;
		// Try to hit them with a trace
		Vector vecMins = GetHullMins();
		Vector vecMaxs = GetHullMaxs();
		vecMins.z = vecMins.x;
		vecMaxs.z = vecMaxs.x;
		pHurt = CheckTraceHullAttack( 64, vecMins, vecMaxs, 10, DMG_BLIINKHIT );
		attackTime = -1;
		Msg("HAAATTTAAAACKKKK!!!\n");
	}

	BaseClass::NPCThink();
}


//-----------------------------------------------------------------------------
// Purpose: 
//
//
// Output : 
//-----------------------------------------------------------------------------
Class_T	CBliinkBliinker::Classify( void )
{
	return	CLASS_NONE;
}