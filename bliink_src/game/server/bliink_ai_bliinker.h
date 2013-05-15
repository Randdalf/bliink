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
#include "bliink_player.h"
#include "bliink_exp_orb.h"

//=========================================================
//=========================================================
class CBliinkRoamingSpawner;

class CBliinkBliinker : public CAI_BaseNPC
{
	DECLARE_CLASS( CBliinkBliinker, CAI_BaseNPC );

public:
	void	Precache( void );
	void	Spawn( void );
	Class_T Classify( void );
	int		SelectSchedule( void );
	void	OnChangeActivity( Activity eNewActivity );
	void	NPCThink( void );
	void	Event_Killed( const CTakeDamageInfo &info );
	void	SetSpawner( CBliinkRoamingSpawner* cbrs);

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
	CBliinkRoamingSpawner* spawner;
	bool swap;

	DEFINE_CUSTOM_AI;
};