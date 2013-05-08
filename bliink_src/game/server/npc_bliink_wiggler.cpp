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
	COND_MYCUSTOMCONDITION = LAST_SHARED_CONDITION,
};


//=========================================================
//=========================================================
class CBliinkWiggler : public CAI_BaseNPC
{
	DECLARE_CLASS( CBliinkWiggler, CAI_BaseNPC );

public:
	void	Precache( void );
	void	Spawn( void );
	Class_T Classify( void );
	int		SelectSchedule( void );

	Activity	NPC_TranslateActivity( Activity eNewActivity );

	DECLARE_DATADESC();

	// This is a dummy field. In order to provide save/restore
	// code in this file, we must have at least one field
	// for the code to operate on. Delete this field when
	// you are ready to do your own save/restore for this
	// character.
	int		m_iDeleteThisField;

	DEFINE_CUSTOM_AI;
};

LINK_ENTITY_TO_CLASS( npc_bliink_wiggler, CBliinkWiggler );
IMPLEMENT_CUSTOM_AI( npc_citizen, CBliinkWiggler );


//---------------------------------------------------------
// Save/Restore
//---------------------------------------------------------
BEGIN_DATADESC( CBliinkWiggler )

	DEFINE_FIELD( m_iDeleteThisField, FIELD_INTEGER ),

END_DATADESC()

//-----------------------------------------------------------------------------
// Purpose: Initialize the custom schedules
// Input  :
// Output :
//-----------------------------------------------------------------------------
void CBliinkWiggler::InitCustomSchedules(void) 
{
	INIT_CUSTOM_AI(CBliinkWiggler);

	ADD_CUSTOM_TASK(CBliinkWiggler,		TASK_MYCUSTOMTASK);

	ADD_CUSTOM_SCHEDULE(CBliinkWiggler,	SCHED_MYCUSTOMSCHEDULE);

	//ADD_CUSTOM_ACTIVITY(CBliinkSimpleNPC,	ACT_MYCUSTOMACTIVITY);

	ADD_CUSTOM_CONDITION(CBliinkWiggler,	COND_MYCUSTOMCONDITION);
}

//-----------------------------------------------------------------------------
// Purpose: 
//
//
//-----------------------------------------------------------------------------
void CBliinkWiggler::Precache( void )
{
	PrecacheModel( "models/player/blue_player.mdl" );

	BaseClass::Precache();
}

//-----------------------------------------------------------------------------
// Purpose: 
//
//
//-----------------------------------------------------------------------------
int CBliinkWiggler::SelectSchedule( void )
{
	if (HasCondition(COND_SEE_ENEMY)) {
		/*Msg("I SEE YOUUUUU");*/
		return SCHED_CHASE_ENEMY;
	}

	return SCHED_RUN_RANDOM;
}


//-----------------------------------------------------------------------------
// Purpose: 
//
//
//-----------------------------------------------------------------------------
void CBliinkWiggler::Spawn( void )
{
	Precache();

	SetModel( "models/player/blue_player.mdl" );
	SetHullType(HULL_HUMAN);
	SetHullSizeNormal();

	SetSolid( SOLID_BBOX );
	AddSolidFlags( FSOLID_NOT_STANDABLE );
	SetMoveType( MOVETYPE_STEP );
	SetBloodColor( BLOOD_COLOR_RED );
	m_iHealth			= 20;
	m_flFieldOfView		= 0.5;
	m_NPCState			= NPC_STATE_NONE;

	CapabilitiesClear();
	CapabilitiesAdd( bits_CAP_MOVE_GROUND );

	NPCInit();
}

// Overriding activities with DOD activities
Activity	CBliinkWiggler::NPC_TranslateActivity( Activity eNewActivity )
{
	eNewActivity = BaseClass::NPC_TranslateActivity( eNewActivity );

	if ( eNewActivity == ACT_IDLE )
		return ACT_DOD_STAND_IDLE_PISTOL;
	else if ( eNewActivity == ACT_RUN || eNewActivity == ACT_WALK )
		return ACT_DOD_PRONEWALK_IDLE_RIFLE;

	return eNewActivity;
}


//-----------------------------------------------------------------------------
// Purpose: 
//
//
// Output : 
//-----------------------------------------------------------------------------
Class_T	CBliinkWiggler::Classify( void )
{
	return	CLASS_NONE;
}