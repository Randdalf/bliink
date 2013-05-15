#include "cbase.h"
#include "bliink_npc_roaming_spawner.h"
#include "bliink_ai_bliinker.h"
#include "bliink_ai_walker.h"
#include "bliink_ai_crawler.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

#define SPAWNER_PLAYER_SEARCH_RADIUS 256

LINK_ENTITY_TO_CLASS( bliink_npc_roaming_spawner, CBliinkRoamingSpawner  );

// Start of our data description for the class
BEGIN_DATADESC( CBliinkRoamingSpawner  )

	DEFINE_INPUTFUNC( FIELD_VOID, "BeginSpawning", BeginSpawning ),
	DEFINE_KEYFIELD( m_bIsCamp, FIELD_BOOLEAN, "is_camp"),
	DEFINE_KEYFIELD( m_bHasLegs, FIELD_BOOLEAN, "has_legs"),

END_DATADESC()

// An input functions which tells us to begin spawning.
void CBliinkRoamingSpawner::BeginSpawning( inputdata_t &inputdata )
{
	Msg("SPAWN MY PRETTY\n");
	SetNextThink( gpGlobals->curtime );
}

CBliinkRoamingSpawner::CBliinkRoamingSpawner( void )
{
	Msg("SPAWN MY PRETTY\n");
	m_bNPCAlive = false;
}

// Attempts to perform a spawning.
void CBliinkRoamingSpawner::Think( void )
{
	Msg("SPAWN MY PRETTY\n");
	if( !m_bNPCAlive && CanSpawnNPC() )
		SpawnNPC();
	
	SetNextThink( gpGlobals->curtime + 20 );
}


// Sets up the item types to be used when spawning.
void CBliinkRoamingSpawner::Spawn( void )
{
	if (m_bIsCamp) m_szNPCname = "npc_bliink_walker";
	else if (! m_bHasLegs) m_szNPCname = "npc_bliink_crawler";
	else m_szNPCname = "npc_bliink_bliinker";
}

bool CBliinkRoamingSpawner::CanSpawnNPC( void )
{
	/*if( gEntList.FindEntityByClassnameNearest("player", GetAbsOrigin(), SPAWNER_PLAYER_SEARCH_RADIUS) )
	{
		return false;
	}*/

	/*CBaseEntity* pEnt = pEnt = UTIL_EntitiesInPVS( this, NULL );

	while( pEnt )
	{
		if( pEnt->IsPlayer() )
		{
			Msg("Couldn't spawn because player could see me.\n");
			return false;
		}

		pEnt = UTIL_EntitiesInPVS( this, pEnt );
	}*/

	return true;
}

// Spawns item(s).
void CBliinkRoamingSpawner::SpawnNPC( void )
{	
	CBaseEntity* npc;
	Vector spawnOrigin = GetAbsOrigin();
	//QAngle spawnAngles = GetAbsAngles() + QAngle(0, 0, RandomFloat()*360.0f);
	QAngle spawnAngles = GetAbsAngles() + QAngle(0, RandomFloat()*360.0f, 0);

	Msg("SPAWN MY PRETTY\n");
	npc = CBaseEntity::CreateNoSpawn( m_szNPCname, spawnOrigin, spawnAngles);

	DispatchSpawn(npc);

	if (m_bIsCamp) {
		((CBliinkWalker*)npc)->SetSpawner(this);
	} else if (!m_bHasLegs) {
		((CBliinkCrawler*)npc)->SetSpawner(this);
	} else {
		((CBliinkBliinker*)npc)->SetSpawner(this);
	}

	m_bNPCAlive = true;
}

void CBliinkRoamingSpawner::NPCDied( void ) {
	m_bNPCAlive = false;
}