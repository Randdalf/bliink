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
#include "bliink_exp_orb.h"

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
	SCHED_RECORD_HOME = LAST_SHARED_SCHEDULE,
	SCHED_RETURN_TO_SPAWN,
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
	COND_MYCUSTOMCONDITION = LAST_SHARED_CONDITION,
};


//=========================================================
//=========================================================
class CBliinkRobbler : public CAI_BaseNPC
{
	DECLARE_CLASS( CBliinkRobbler, CAI_BaseNPC );

public:
	void	Precache( void );
	void	Spawn( void );
	Class_T Classify( void );
	int		SelectSchedule( void );
	void	OnChangeActivity( Activity eNewActivity );
	void	NPCThink( void );
	void	Event_Killed( const CTakeDamageInfo &info );
	virtual float GetIdealSpeed( void ) const;

	Activity	NPC_TranslateActivity( Activity eNewActivity );

	DECLARE_DATADESC();

	// This is a dummy field. In order to provide save/restore
	// code in this file, we must have at least one field
	// for the code to operate on. Delete this field when
	// you are ready to do your own save/restore for this
	// character.
	int		m_iDeleteThisField;
	int justSpawned;
	float attackTime;

	DEFINE_CUSTOM_AI;
};

LINK_ENTITY_TO_CLASS( npc_bliink_robbler, CBliinkRobbler );
//IMPLEMENT_CUSTOM_AI( npc_citizen, CBliinkRobbler );


//---------------------------------------------------------
// Save/Restore
//---------------------------------------------------------
BEGIN_DATADESC( CBliinkRobbler )

	DEFINE_FIELD( m_iDeleteThisField, FIELD_INTEGER ),

END_DATADESC()

//-----------------------------------------------------------------------------
// Purpose: Initialize the custom schedules
// Input  :
// Output :
//-----------------------------------------------------------------------------
/*void CBliinkRobbler::InitCustomSchedules(void) 
{
	INIT_CUSTOM_AI(CBliinkRobbler);

	ADD_CUSTOM_TASK(CBliinkRobbler,		TASK_MYCUSTOMTASK);

	ADD_CUSTOM_SCHEDULE(CBliinkRobbler,	SCHED_MYCUSTOMSCHEDULE);

	//ADD_CUSTOM_ACTIVITY(CBliinkSimpleNPC,	ACT_MYCUSTOMACTIVITY);

	ADD_CUSTOM_CONDITION(CBliinkRobbler,	COND_MYCUSTOMCONDITION);
}*/

//-----------------------------------------------------------------------------
// Purpose: 
//
//
//-----------------------------------------------------------------------------
void CBliinkRobbler::Precache( void )
{
	PrecacheModel("models/creeps/neutral_creeps/n_creeps_forest_troll/bliink_creep_forest_troll.mdl");

	BaseClass::Precache();
}

//=========================================================
// > RETURN_TO_SPAWN
//=========================================================
AI_BEGIN_CUSTOM_NPC( npc_bliink_robbler, CBliinkRobbler)
	DEFINE_SCHEDULE
	(
		SCHED_RETURN_TO_SPAWN,

		"	Tasks"
		"		TASK_GET_PATH_TO_LASTPOSITION	0"
		"		TASK_RUN_PATH					0"
		"		TASK_WAIT_FOR_MOVEMENT			0"
		""
		"	Interrupts"
		"		COND_HEAR_DANGER"
		"		COND_NEW_ENEMY"
		"		COND_SEE_ENEMY"
	)

	DEFINE_SCHEDULE
	(
		SCHED_RECORD_HOME,

		"	Tasks"
		"		TASK_STORE_LASTPOSITION	0"
	)

AI_END_CUSTOM_NPC()

//-----------------------------------------------------------------------------
// Purpose: 
//
//
//-----------------------------------------------------------------------------
int CBliinkRobbler::SelectSchedule( void )
{
	if (justSpawned == 0) {
		justSpawned = 1;
		//Msg("location stored");
		return SCHED_RECORD_HOME;
	} else if (HasCondition(COND_SEE_ENEMY)) {
		//Msg("I SEE YOUUUUU\n");
		if ( HasCondition(COND_CAN_MELEE_ATTACK1) ) {
			Msg("HIIIIIIIIIIIIYA!!!\n");
			return SCHED_MELEE_ATTACK1;
		}
		return SCHED_CHASE_ENEMY;
	}
	//Msg("going home");
	return SCHED_RETURN_TO_SPAWN;
}

//-----------------------------------------------------------------------------
// Purpose: 
//
//
//-----------------------------------------------------------------------------
void CBliinkRobbler::Spawn( void )
{
	Precache();

	SetModel( "models/creeps/neutral_creeps/n_creeps_forest_troll/bliink_creep_forest_troll.mdl" );
	SetHullType(HULL_HUMAN);
	SetHullSizeNormal();

	SetSolid( SOLID_BBOX );
	AddSolidFlags( FSOLID_NOT_STANDABLE );
	SetMoveType( MOVETYPE_STEP );
	SetBloodColor( BLOOD_COLOR_RED );
	m_iHealth			= 100;
	m_flFieldOfView		= 0.1;
	m_NPCState			= NPC_STATE_NONE;

	CapabilitiesClear();
	CapabilitiesAdd( bits_CAP_MOVE_GROUND | bits_CAP_INNATE_MELEE_ATTACK1 );

	NPCInit();
	justSpawned = 0;
}

// Overriding activities with DOTA activities
Activity	CBliinkRobbler::NPC_TranslateActivity( Activity eNewActivity )
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

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CBliinkRobbler::OnChangeActivity( Activity eNewActivity )
{
	if (eNewActivity == ACT_MELEE_ATTACK1) {
		attackTime = gpGlobals->curtime + 0.25;
		//Msg("%f KK\n", attackTime);
	}

	BaseClass::OnChangeActivity( eNewActivity );
}


void CBliinkRobbler::NPCThink( void ) {
	if (gpGlobals->curtime > attackTime && attackTime > 0) {
		CBaseEntity *pHurt = NULL;
		// Try to hit them with a trace
		Vector vecMins = GetHullMins();
		Vector vecMaxs = GetHullMaxs();
		vecMins.z = vecMins.x;
		vecMaxs.z = vecMaxs.x;
		pHurt = CheckTraceHullAttack( 64, vecMins, vecMaxs, 15, DMG_CLUB );
		attackTime = -1;
		//Msg("HAAATTTAAAACKKKK!!!\n");
	}

	BaseClass::NPCThink();
}


//-----------------------------------------------------------------------------
// Purpose: 
//
//
// Output : 
//-----------------------------------------------------------------------------
Class_T	CBliinkRobbler::Classify( void )
{
	return	CLASS_NONE;
}

float CBliinkRobbler::GetIdealSpeed( void ) const
{
	//Msg("GETTING SPEEEEEEEEEEED\n");
	//BaseClass::GetIdealSpeed();
	return 195.0;
	//return BaseClass::GetIdealSpeed();
}


void CBliinkRobbler::Event_Killed( const CTakeDamageInfo &info )
{
	BaseClass::Event_Killed( info );

	spawnRandomOrbs( GetAbsOrigin() + Vector(0,0,32.0f), 640.0f, 3, 5, 3, 17 );
	
	Remove();
}