//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: The TF Game rules 
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "bliink_gamerules.h"
#include "ammodef.h"
#include "KeyValues.h"
#include "weapon_sdkbase.h"
#include "bliink_gamevars_shared.h"


#ifdef CLIENT_DLL

	#include "precache_register.h"
	#include "c_bliink_player.h"
	#include "c_bliink_team.h"

#else
	
	#include "voice_gamemgr.h"
	#include "bliink_player.h"
	#include "bliink_team.h"
	#include "sdk_playerclass_info_parse.h"
	#include "player_resource.h"
	#include "mapentities.h"
	#include "sdk_basegrenade_projectile.h"
#endif


// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

ConVar mm_max_players( "mm_max_players", "4", FCVAR_REPLICATED | FCVAR_CHEAT, "Max players for matchmaking system" );

#ifndef CLIENT_DLL

// Defining spawnpoints
class CSpawnPoint : public CPointEntity
{
public:
	bool IsDisabled() { return m_bDisabled; }
	void InputEnable( inputdata_t &inputdata ) { m_bDisabled = false; }
	void InputDisable( inputdata_t &inputdata ) { m_bDisabled = true; }

private:
	bool m_bDisabled;
	DECLARE_DATADESC();
};

BEGIN_DATADESC(CSpawnPoint)

	// Keyfields
	DEFINE_KEYFIELD( m_bDisabled,	FIELD_BOOLEAN,	"StartDisabled" ),

	// Inputs
	DEFINE_INPUTFUNC( FIELD_VOID, "Disable", InputDisable ),
	DEFINE_INPUTFUNC( FIELD_VOID, "Enable", InputEnable ),

END_DATADESC();

	LINK_ENTITY_TO_CLASS( info_player_spawn, CSpawnPoint );

// Defining the cage opener
class CCageOpener : public CLogicalEntity
{
public:
	DECLARE_CLASS( CCageOpener, CLogicalEntity );

	// Outputs
	COutputEvent m_OnOpenCages;

private:
	DECLARE_DATADESC();
};

BEGIN_DATADESC(CCageOpener)
	// Outputs
	DEFINE_OUTPUT(m_OnOpenCages, "OnOpenCages"),
END_DATADESC();

LINK_ENTITY_TO_CLASS( bliink_cage_opener, CCageOpener );

#endif


REGISTER_GAMERULES_CLASS( CBliinkGameRules );


BEGIN_NETWORK_TABLE_NOBASE( CBliinkGameRules, DT_BliinkGameRules )
#if defined ( CLIENT_DLL )
		RecvPropFloat( RECVINFO( m_flGameStartTime ) ),
		RecvPropBool( RECVINFO( m_bCountdownToLive ) ),
		RecvPropBool( RECVINFO( m_bGameIsEnding ) ),
		RecvPropFloat( RECVINFO( m_fLiveTime ) ),
#else
		SendPropFloat( SENDINFO( m_flGameStartTime ), 32, SPROP_NOSCALE ),
		SendPropBool( SENDINFO( m_bCountdownToLive ) ),
		SendPropBool( SENDINFO( m_bGameIsEnding ) ),
		SendPropFloat( SENDINFO( m_fLiveTime ), 32, SPROP_NOSCALE ),
#endif
END_NETWORK_TABLE()

LINK_ENTITY_TO_CLASS( bliink_gamerules, CBliinkGameRulesProxy );
IMPLEMENT_NETWORKCLASS_ALIASED( BliinkGameRulesProxy, DT_BliinkGameRulesProxy )


#ifdef CLIENT_DLL
	void RecvProxy_BliinkGameRules( const RecvProp *pProp, void **pOut, void *pData, int objectID )
	{
		CBliinkGameRules *pRules = BliinkGameRules();
		Assert( pRules );
		*pOut = pRules;
	}

	BEGIN_RECV_TABLE( CBliinkGameRulesProxy, DT_BliinkGameRulesProxy )
		RecvPropDataTable( "bliink_gamerules_data", 0, 0, &REFERENCE_RECV_TABLE( DT_BliinkGameRules ), RecvProxy_BliinkGameRules )
	END_RECV_TABLE()
#else
	void *SendProxy_BliinkGameRules( const SendProp *pProp, const void *pStructBase, const void *pData, CSendProxyRecipients *pRecipients, int objectID )
	{
		CBliinkGameRules *pRules = BliinkGameRules();
		Assert( pRules );
		pRecipients->SetAllRecipients();
		return pRules;
	}

	BEGIN_SEND_TABLE( CBliinkGameRulesProxy, DT_BliinkGameRulesProxy )
		SendPropDataTable( "bliink_gamerules_data", 0, &REFERENCE_SEND_TABLE( DT_BliinkGameRules ), SendProxy_BliinkGameRules )
	END_SEND_TABLE()
#endif

#ifndef CLIENT_DLL
	ConVar sk_plr_dmg_grenade( "sk_plr_dmg_grenade","0");		
#endif

ConVar mp_limitteams( 
	"mp_limitteams", 
	"2", 
	FCVAR_REPLICATED | FCVAR_NOTIFY,
	"Max # of players 1 team can have over another (0 disables check)",
	true, 0,	// MIN value
	true, 30	// MAX value
);

//AI RELATIONSHIPS YEA BOY THIS WILL TOTALLY WORK XD
#ifndef CLIENT_DLL
void CBliinkGameRules::InitDefaultAIRelationships( void )
	{
		int i, j;

		//  Allocate memory for default relationships
		CBaseCombatCharacter::AllocateDefaultRelationships();

		// --------------------------------------------------------------
		// First initialize table so we can report missing relationships
		// --------------------------------------------------------------
		/*for (i=0;i<NUM_AI_CLASSES;i++)
		{
			for (j=0;j<NUM_AI_CLASSES;j++)
			{
				// By default all relationships are neutral of priority zero
				CBaseCombatCharacter::SetDefaultRelationship( (Class_T)i, (Class_T)j, D_NU, 0 );
			}
		}*/

		// ------------------------------------------------------------
		//	> CLASS_NONE
		// ------------------------------------------------------------
		CBaseCombatCharacter::SetDefaultRelationship(CLASS_NONE,				CLASS_NONE,				D_NU, 0);			
		CBaseCombatCharacter::SetDefaultRelationship(CLASS_NONE,				CLASS_PLAYER,			D_HT, 0);			
		CBaseCombatCharacter::SetDefaultRelationship(CLASS_NONE,				CLASS_PROTOSNIPER,		D_NU, 0);
		CBaseCombatCharacter::SetDefaultRelationship(CLASS_NONE,				CLASS_EARTH_FAUNA,		D_NU, 0);

		// ------------------------------------------------------------
		//	> CLASS_PLAYER
		// ------------------------------------------------------------
		CBaseCombatCharacter::SetDefaultRelationship(CLASS_PLAYER,			CLASS_NONE,				D_HT, 0);			
		CBaseCombatCharacter::SetDefaultRelationship(CLASS_PLAYER,			CLASS_PLAYER,			D_NU, 0);			
		CBaseCombatCharacter::SetDefaultRelationship(CLASS_PLAYER,			CLASS_PROTOSNIPER,		D_HT, 0);
		CBaseCombatCharacter::SetDefaultRelationship(CLASS_PLAYER,			CLASS_EARTH_FAUNA,		D_NU, 0);
		
		// ------------------------------------------------------------
		//	> CLASS_PROTOSNIPER
		// ------------------------------------------------------------	
		CBaseCombatCharacter::SetDefaultRelationship(CLASS_PROTOSNIPER,			CLASS_NONE,				D_NU, 0);			
		CBaseCombatCharacter::SetDefaultRelationship(CLASS_PROTOSNIPER,			CLASS_PLAYER,			D_HT, 0);			
		CBaseCombatCharacter::SetDefaultRelationship(CLASS_PROTOSNIPER,			CLASS_PROTOSNIPER,		D_NU, 0);
		CBaseCombatCharacter::SetDefaultRelationship(CLASS_PROTOSNIPER,			CLASS_EARTH_FAUNA,		D_NU, 0);

		// ------------------------------------------------------------
		//	> CLASS_EARTH_FAUNA
		//
		// Hates pretty much everything equally except other earth fauna.
		// This will make the critter choose the nearest thing as its enemy.
		// ------------------------------------------------------------	
		CBaseCombatCharacter::SetDefaultRelationship(CLASS_EARTH_FAUNA,			CLASS_NONE,				D_HT, 0);
		CBaseCombatCharacter::SetDefaultRelationship(CLASS_EARTH_FAUNA,			CLASS_PLAYER,			D_HT, 0);
		CBaseCombatCharacter::SetDefaultRelationship(CLASS_EARTH_FAUNA,			CLASS_PROTOSNIPER,		D_HT, 0);
		CBaseCombatCharacter::SetDefaultRelationship(CLASS_EARTH_FAUNA,			CLASS_EARTH_FAUNA,		D_NU, 0);
	}
#endif

static CSDKViewVectors g_SDKViewVectors(

	Vector( 0, 0, 58 ),			//VEC_VIEW
								
	Vector(-16, -16, 0 ),		//VEC_HULL_MIN
	Vector( 16,  16,  72 ),		//VEC_HULL_MAX
													
	Vector(-16, -16, 0 ),		//VEC_DUCK_HULL_MIN
	Vector( 16,  16, 45 ),		//VEC_DUCK_HULL_MAX
	Vector( 0, 0, 34 ),			//VEC_DUCK_VIEW
													
	Vector(-10, -10, -10 ),		//VEC_OBS_HULL_MIN
	Vector( 10,  10,  10 ),		//VEC_OBS_HULL_MAX
													
	Vector( 0, 0, 14 )			//VEC_DEAD_VIEWHEIGHT
);

const CViewVectors* CBliinkGameRules::GetViewVectors() const
{
	return (CViewVectors*)GetSDKViewVectors();
}

const CSDKViewVectors *CBliinkGameRules::GetSDKViewVectors() const
{
	return &g_SDKViewVectors;
}

#ifdef CLIENT_DLL


#else

// --------------------------------------------------------------------------------------------------- //
// Voice helper
// --------------------------------------------------------------------------------------------------- //

class CVoiceGameMgrHelper : public IVoiceGameMgrHelper
{
public:
	virtual bool		CanPlayerHearPlayer( CBasePlayer *pListener, CBasePlayer *pTalker, bool &bProximity )
	{
		// Dead players can only be heard by other dead team mates
		if ( pTalker->IsAlive() == false )
		{
			if ( pListener->IsAlive() == false )
				return ( pListener->InSameTeam( pTalker ) );

			return false;
		}

		return ( pListener->InSameTeam( pTalker ) );
	}
};
CVoiceGameMgrHelper g_VoiceGameMgrHelper;
IVoiceGameMgrHelper *g_pVoiceGameMgrHelper = &g_VoiceGameMgrHelper;



// --------------------------------------------------------------------------------------------------- //
// Globals.
// --------------------------------------------------------------------------------------------------- //
static const char *s_PreserveEnts[] =
{
	"player",
	"viewmodel",
	"worldspawn",
	"soundent",
	"ai_network",
	"ai_hint",
	"bliink_gamerules",
	"bliink_team_manager",
	"bliink_team_unassigned",
	"bliink_team_blue",
	"bliink_team_red",
	"sdk_player_manager",
	"env_soundscape",
	"env_soundscape_proxy",
	"env_soundscape_triggerable",
	"env_sprite",
	"env_sun",
	"env_wind",
	"env_fog_controller",
	"func_brush",
	"func_wall",
	"func_illusionary",
	"info_node",
	"info_target",
	"info_node_hint",
	"info_player_red",
	"info_player_blue",
	"info_player_spawn",
	"point_viewcontrol",
	"shadow_control",
	"sky_camera",
	"scene_manager",
	"trigger_soundscape",
	"point_commentary_node",
	"func_precipitation",
	"func_team_wall",
	"", // END Marker
};

// --------------------------------------------------------------------------------------------------- //
// Global helper functions.
// --------------------------------------------------------------------------------------------------- //

// World.cpp calls this but we don't use it in SDK.
void InitBodyQue()
{
}


// --------------------------------------------------------------------------------------------------- //
// CBliinkGameRules implementation.
// --------------------------------------------------------------------------------------------------- //

CBliinkGameRules::CBliinkGameRules()
{
	InitTeams();

	m_bLevelInitialized = false;

	m_flGameStartTime = 0;

	// Bliink
	m_bGameIsActive = false;
	m_bCountdownToLive = false;
	m_fLiveTime = 0;
	m_fRestartGameTime = 0;
	m_bGameIsEnding = false;
}

void CBliinkGameRules::ServerActivate()
{
	//Tony; initialize the level
	CheckLevelInitialized();

	//Tony; do any post stuff
	m_flGameStartTime = gpGlobals->curtime;
	if ( !IsFinite( m_flGameStartTime.Get() ) )
	{
		Warning( "Trying to set a NaN game start time\n" );
		m_flGameStartTime.GetForModify() = 0.0f;
	}
}
void CBliinkGameRules::CheckLevelInitialized()
{
	if ( !m_bLevelInitialized )
	{
		m_bLevelInitialized = true;
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
CBliinkGameRules::~CBliinkGameRules()
{
	// Note, don't delete each team since they are in the gEntList and will 
	// automatically be deleted from there, instead.
	g_Teams.Purge();
}

//-----------------------------------------------------------------------------
// Purpose: TF2 Specific Client Commands
// Input  :
// Output :
//-----------------------------------------------------------------------------
bool CBliinkGameRules::ClientCommand( CBaseEntity *pEdict, const CCommand &args )
{
	CBliinkPlayer *pPlayer = ToBliinkPlayer( pEdict );
#if 0
	const char *pcmd = args[0];
	if ( FStrEq( pcmd, "somecommand" ) )
	{
		if ( args.ArgC() < 2 )
			return true;

		// Do something here!

		return true;
	}
	else 
#endif
	// Handle some player commands here as they relate more directly to gamerules state
	if ( pPlayer->ClientCommand( args ) )
	{
		return true;
	}
	else if ( BaseClass::ClientCommand( pEdict, args ) )
	{
		return true;
	}
	return false;
}

//-----------------------------------------------------------------------------
// Purpose: Player has just spawned. Equip them.
//-----------------------------------------------------------------------------

void CBliinkGameRules::RadiusDamage( const CTakeDamageInfo &info, const Vector &vecSrcIn, float flRadius, int iClassIgnore )
{
	RadiusDamage( info, vecSrcIn, flRadius, iClassIgnore, false );
}

// Add the ability to ignore the world trace
void CBliinkGameRules::RadiusDamage( const CTakeDamageInfo &info, const Vector &vecSrcIn, float flRadius, int iClassIgnore, bool bIgnoreWorld )
{
	CBaseEntity *pEntity = NULL;
	trace_t		tr;
	float		flAdjustedDamage, falloff;
	Vector		vecSpot;
	Vector		vecToTarget;
	Vector		vecEndPos;

	Vector vecSrc = vecSrcIn;

	if ( flRadius )
		falloff = info.GetDamage() / flRadius;
	else
		falloff = 1.0;

	int bInWater = (UTIL_PointContents ( vecSrc ,MASK_WATER) ) ? true : false;

	vecSrc.z += 1;// in case grenade is lying on the ground

	// iterate on all entities in the vicinity.
	for ( CEntitySphereQuery sphere( vecSrc, flRadius ); ( pEntity = sphere.GetCurrentEntity() ) != NULL; sphere.NextEntity() )
	{
		if ( pEntity->m_takedamage != DAMAGE_NO )
		{
			// UNDONE: this should check a damage mask, not an ignore
			if ( iClassIgnore != CLASS_NONE && pEntity->Classify() == iClassIgnore )
			{// houndeyes don't hurt other houndeyes with their attack
				continue;
			}

			// blast's don't tavel into or out of water
			if (bInWater && pEntity->GetWaterLevel() == 0)
				continue;
			if (!bInWater && pEntity->GetWaterLevel() == 3)
				continue;

			// radius damage can only be blocked by the world
			vecSpot = pEntity->BodyTarget( vecSrc );



			bool bHit = false;

			if( bIgnoreWorld )
			{
				vecEndPos = vecSpot;
				bHit = true;
			}
			else
			{
				UTIL_TraceLine( vecSrc, vecSpot, MASK_SOLID_BRUSHONLY, info.GetInflictor(), COLLISION_GROUP_NONE, &tr );

				if (tr.startsolid)
				{
					// if we're stuck inside them, fixup the position and distance
					tr.endpos = vecSrc;
					tr.fraction = 0.0;
				}

				vecEndPos = tr.endpos;

				if( tr.fraction == 1.0 || tr.m_pEnt == pEntity )
				{
					bHit = true;
				}
			}

			if ( bHit )
			{
				// the explosion can 'see' this entity, so hurt them!
				//vecToTarget = ( vecSrc - vecEndPos );
				vecToTarget = ( vecEndPos - vecSrc );

				// decrease damage for an ent that's farther from the bomb.
				flAdjustedDamage = vecToTarget.Length() * falloff;
				flAdjustedDamage = info.GetDamage() - flAdjustedDamage;

				if ( flAdjustedDamage > 0 )
				{
					CTakeDamageInfo adjustedInfo = info;
					adjustedInfo.SetDamage( flAdjustedDamage );

					Vector dir = vecToTarget;
					VectorNormalize( dir );

					// If we don't have a damage force, manufacture one
					if ( adjustedInfo.GetDamagePosition() == vec3_origin || adjustedInfo.GetDamageForce() == vec3_origin )
					{
						CalculateExplosiveDamageForce( &adjustedInfo, dir, vecSrc, 1.5	/* explosion scale! */ );
					}
					else
					{
						// Assume the force passed in is the maximum force. Decay it based on falloff.
						float flForce = adjustedInfo.GetDamageForce().Length() * falloff;
						adjustedInfo.SetDamageForce( dir * flForce );
						adjustedInfo.SetDamagePosition( vecSrc );
					}

					pEntity->TakeDamage( adjustedInfo );

					// Now hit all triggers along the way that respond to damage... 
					pEntity->TraceAttackToTriggers( adjustedInfo, vecSrc, vecEndPos, dir );
				}
			}
		}
	}
}

// Starts the game if we have enough players waiting
void CBliinkGameRules::Think()
{
	BaseClass::Think();

	// if waiting for players...
	if( !m_bGameIsActive )
	{
		if( !m_bCountdownToLive && EnoughPlayersToStart() )
		{
			double countdownTime = (double) Bliink_CountdownToLive.GetFloat();
			m_fLiveTime = gpGlobals->curtime + countdownTime;

			m_bCountdownToLive = true;
		}
		else if ( m_bCountdownToLive && !EnoughPlayersToStart() )
		{
			m_bCountdownToLive = false;
		}
		else if( m_bCountdownToLive && EnoughPlayersToStart() && gpGlobals->curtime >= m_fLiveTime )
		{
			Msg("Starting game...\n");
			StartGame();
		}
	}

	// if game is active...
	else if( !m_bGameIsEnding )
	{
		int survivors = 0;

		for(int i=1; i<=gpGlobals->maxClients; i++)
		{
			CBliinkPlayer* pPlayer = ToBliinkPlayer(UTIL_PlayerByIndex(i));

			if( !pPlayer || !pPlayer->IsPlayer() )
				continue;

			//Stuff for for decreasing radius.

			//float now_time = gpGlobals->curtime;

			//float gameTime = now_time - gpGlobals->start_time;

			//gpGlobals->fog_radius = 500.0f - (gameTime*10);

			Vector playerOrigin = pPlayer->GetAbsOrigin();

			vec_t disFromCenter = sqrt((playerOrigin.x * playerOrigin.x)+(playerOrigin.y * playerOrigin.y));

			//if(disFromCenter >= gpGlobals->fog_radius){
			//	Msg("In Fog\n");
			//}

			BliinkPlayerState state = pPlayer->State_Get();

			if( state == STATE_BLIINK_SURVIVOR )
				survivors++;
		}

		if( survivors <= 0 ) // 0 for single player testing
			EndGame();
	}
	
	// if game is ending, wait to restart map
	else
	{
		if( gpGlobals->curtime > m_fRestartGameTime )
		{			
			ChangeLevel();
		}
	}
}

// Checks the number of players we have who are ready to start and if it's
// above the minimum, then start.
bool CBliinkGameRules::EnoughPlayersToStart()
{
	int readyPlayers = 0;

	for(int i=1; i<=gpGlobals->maxClients; i++)
	{
		CBliinkPlayer* pPlayer = ToBliinkPlayer(UTIL_PlayerByIndex(i));

		if( !pPlayer || !pPlayer->IsPlayer() )
			continue;

		if( pPlayer->IsReadyToStart() )
			readyPlayers++;		
	}

	int minPlayers = Bliink_MinPlayers.GetInt();

	if( readyPlayers >= minPlayers)
		return true;
	else
		return false;
}

// Starts the game going by spawning all players into the map
void CBliinkGameRules::StartGame()
{
	m_bGameIsActive = true;
	m_bCountdownToLive = false;

	// Setting players who are ready to 
	for(int i=1; i<=gpGlobals->maxClients; i++)
	{
		CBliinkPlayer* pPlayer = ToBliinkPlayer(UTIL_PlayerByIndex(i));

		if( !pPlayer || !pPlayer->IsPlayer() )
			continue;

		pPlayer->StartGameTransition();
	}

	// Opens the cages when the game starts
	CBaseEntity* pResult = gEntList.FindEntityByClassname(NULL, "bliink_cage_opener");

	if( pResult )
	{
		CCageOpener* pCageOpener = dynamic_cast<CCageOpener*>(pResult);

		if( pCageOpener )
		{
			pCageOpener->m_OnOpenCages.FireOutput(NULL, NULL, 0);
		}
	}

	//initialise the fog.

	//gpGlobals->fog_radius = 500.0f;
	//gpGlobals->start_time = gpGlobals->curtime;
}

// Starts the game going by spawning all players into the map
void CBliinkGameRules::EndGame()
{
	m_bGameIsEnding = true;

	// Setting players who are ready to 
	for(int i=1; i<=gpGlobals->maxClients; i++)
	{
		CBliinkPlayer* pPlayer = ToBliinkPlayer(UTIL_PlayerByIndex(i));

		if( !pPlayer || !pPlayer->IsPlayer() )
			continue;

		pPlayer->EndGameTransition();
	}

	m_fRestartGameTime = gpGlobals->curtime + Bliink_ResultsTime.GetFloat();

	Msg("Ending game...\n");
}

Vector DropToGround( 
					CBaseEntity *pMainEnt, 
					const Vector &vPos, 
					const Vector &vMins, 
					const Vector &vMaxs )
{
	trace_t trace;
	UTIL_TraceHull( vPos, vPos + Vector( 0, 0, -500 ), vMins, vMaxs, MASK_SOLID, pMainEnt, COLLISION_GROUP_NONE, &trace );
	return trace.endpos;
}

CBaseEntity *CBliinkGameRules::GetPlayerSpawnSpot( CBasePlayer *pPlayer )
{
	// get valid spawn point
	CBaseEntity *pSpawnSpot = pPlayer->EntSelectSpawnPoint();

	// drop down to ground
	Vector GroundPos = DropToGround( pPlayer, pSpawnSpot->GetAbsOrigin(), VEC_HULL_MIN, VEC_HULL_MAX );

	// Move the player to the place it said.
	pPlayer->Teleport( &GroundPos, &pSpawnSpot->GetLocalAngles(), &vec3_origin );
	pPlayer->m_Local.m_vecPunchAngle = vec3_angle;

	return pSpawnSpot;
}

// checks if the spot is clear of players
bool CBliinkGameRules::IsSpawnPointValid( CBaseEntity *pSpot, CBasePlayer *pPlayer )
{
	if ( !pSpot->IsTriggered( pPlayer ) )
	{
		return false;
	}

	// Check if it is disabled by Enable/Disable
	CSpawnPoint *pSpawnPoint = dynamic_cast< CSpawnPoint * >( pSpot );
	if ( pSpawnPoint )
	{
		if ( pSpawnPoint->IsDisabled() )
		{
			return false;
		}
	}

	Vector mins = GetViewVectors()->m_vHullMin;
	Vector maxs = GetViewVectors()->m_vHullMax;

	Vector vTestMins = pSpot->GetAbsOrigin() + mins;
	Vector vTestMaxs = pSpot->GetAbsOrigin() + maxs;

	// First test the starting origin.
	return UTIL_IsSpaceEmpty( pPlayer, vTestMins, vTestMaxs );
}

void CBliinkGameRules::PlayerSpawn( CBasePlayer *p )
{	
	CBliinkPlayer *pPlayer = ToBliinkPlayer( p );

	int team = pPlayer->GetTeamNumber();

	if( team == BLIINK_TEAM_SURVIVOR )
	{
		pPlayer->SetModel( BLIINK_SURVIVOR_MODEL );
		pPlayer->GiveDefaultItems();
		pPlayer->SetMaxSpeed( 600 );
	}
	else if ( team == BLIINK_TEAM_STALKER )
	{
		pPlayer->SetModel( BLIINK_STALKER_MODEL );
		pPlayer->GiveDefaultItems();
		pPlayer->SetMaxSpeed( 600 );
	}
	else
	{
		pPlayer->SetModel( SDK_PLAYER_MODEL );
		pPlayer->GiveDefaultItems();
		pPlayer->SetMaxSpeed( 600 );
	}
}

void CBliinkGameRules::InitTeams( void )
{
	Assert( g_Teams.Count() == 0 );

	g_Teams.Purge();	// just in case

	// Create the team managers

	//Tony; we have a special unassigned team incase our mod is using classes but not teams.
	CTeam *pUnassigned = static_cast<CTeam*>(CreateEntityByName( "bliink_team_unassigned" ));
	Assert( pUnassigned );
	pUnassigned->Init( pszTeamNames[TEAM_UNASSIGNED], TEAM_UNASSIGNED );
	g_Teams.AddToTail( pUnassigned );

	//Tony; just use a plain ole bliink_team_manager for spectators
	CTeam *pSpectator = static_cast<CTeam*>(CreateEntityByName( "bliink_team_manager" ));
	Assert( pSpectator );
	pSpectator->Init( pszTeamNames[TEAM_SPECTATOR], TEAM_SPECTATOR );
	g_Teams.AddToTail( pSpectator ); 

	// BLIINK TEAMS
	// Survivor
	CTeam *pSurvivor = static_cast<CTeam*>(CreateEntityByName( "bliink_team_survivor" ));
	Assert( pSurvivor );
	pSurvivor->Init( pszTeamNames[BLIINK_TEAM_SURVIVOR], BLIINK_TEAM_SURVIVOR );
	g_Teams.AddToTail( pSurvivor ); 

	// Stalker
	CTeam *pStalker = static_cast<CTeam*>(CreateEntityByName( "bliink_team_stalker" ));
	Assert( pStalker );
	pStalker->Init( pszTeamNames[BLIINK_TEAM_STALKER], BLIINK_TEAM_STALKER );
	g_Teams.AddToTail( pStalker );
}

/* create some proxy entities that we use for transmitting data */
void CBliinkGameRules::CreateStandardEntities()
{
	// Create the player resource
	g_pPlayerResource = (CPlayerResource*)CBaseEntity::Create( "sdk_player_manager", vec3_origin, vec3_angle );

	// Create the entity that will send our data to the client.
#ifdef _DEBUG
	CBaseEntity *pEnt = 
#endif
		CBaseEntity::Create( "bliink_gamerules", vec3_origin, vec3_angle );
	Assert( pEnt );
}
int CBliinkGameRules::SelectDefaultTeam()
{
	int team = TEAM_UNASSIGNED;
	return team;
}

//-----------------------------------------------------------------------------
// Purpose: determine the class name of the weapon that got a kill
//-----------------------------------------------------------------------------
const char *CBliinkGameRules::GetKillingWeaponName( const CTakeDamageInfo &info, CBliinkPlayer *pVictim, int *iWeaponID )
{
	CBaseEntity *pInflictor = info.GetInflictor();
	CBaseEntity *pKiller = info.GetAttacker();
	CBasePlayer *pScorer = BliinkGameRules()->GetDeathScorer( pKiller, pInflictor, pVictim );

	const char *killer_weapon_name = "world";
	*iWeaponID = SDK_WEAPON_NONE;

	if ( pScorer && pInflictor && ( pInflictor == pScorer ) )
	{
		// If the inflictor is the killer,  then it must be their current weapon doing the damage
		if ( pScorer->GetActiveWeapon() )
		{
			killer_weapon_name = pScorer->GetActiveWeapon()->GetClassname(); 
			if ( pScorer->IsPlayer() )
			{
				*iWeaponID = ToBliinkPlayer(pScorer)->GetActiveSDKWeapon()->GetWeaponID();
			}
		}
	}
	else if ( pInflictor )
	{
		killer_weapon_name = STRING( pInflictor->m_iClassname );

		CWeaponSDKBase *pWeapon = dynamic_cast< CWeaponSDKBase * >( pInflictor );
		if ( pWeapon )
		{
			*iWeaponID = pWeapon->GetWeaponID();
		}
		else
		{
			CBaseGrenadeProjectile *pBaseGrenade = dynamic_cast<CBaseGrenadeProjectile*>( pInflictor );
			if ( pBaseGrenade )
			{
				*iWeaponID = pBaseGrenade->GetWeaponID();
			}
		}
	}

	// strip certain prefixes from inflictor's classname
	const char *prefix[] = { "weapon_", "NPC_", "func_" };
	for ( int i = 0; i< ARRAYSIZE( prefix ); i++ )
	{
		// if prefix matches, advance the string pointer past the prefix
		int len = Q_strlen( prefix[i] );
		if ( strncmp( killer_weapon_name, prefix[i], len ) == 0 )
		{
			killer_weapon_name += len;
			break;
		}
	}

	// grenade projectiles need to be translated to 'grenade' 
	if ( 0 == Q_strcmp( killer_weapon_name, "grenade_projectile" ) )
	{
		killer_weapon_name = "grenade";
	}

	return killer_weapon_name;
}

//-----------------------------------------------------------------------------
// Purpose: 
// Input  : *pVictim - 
//			*pKiller - 
//			*pInflictor - 
//-----------------------------------------------------------------------------
void CBliinkGameRules::DeathNotice( CBasePlayer *pVictim, const CTakeDamageInfo &info )
{
	int killer_ID = 0;

	// Find the killer & the scorer
	CBliinkPlayer *pSDKPlayerVictim = ToBliinkPlayer( pVictim );
	CBaseEntity *pInflictor = info.GetInflictor();
	CBaseEntity *pKiller = info.GetAttacker();
	CBasePlayer *pScorer = GetDeathScorer( pKiller, pInflictor, pVictim );
//	CBliinkPlayer *pAssister = ToBliinkPlayer( GetAssister( pVictim, pScorer, pInflictor ) );

	// Work out what killed the player, and send a message to all clients about it
	int iWeaponID;
	const char *killer_weapon_name = GetKillingWeaponName( info, pSDKPlayerVictim, &iWeaponID );

	if ( pScorer )	// Is the killer a client?
	{
		killer_ID = pScorer->GetUserID();
	}

	IGameEvent * event = gameeventmanager->CreateEvent( "player_death" );

	if ( event )
	{
		event->SetInt( "userid", pVictim->GetUserID() );
		event->SetInt( "attacker", killer_ID );
//		event->SetInt( "assister", pAssister ? pAssister->GetUserID() : -1 );
		event->SetString( "weapon", killer_weapon_name );
		event->SetInt( "weaponid", iWeaponID );
		event->SetInt( "damagebits", info.GetDamageType() );
		event->SetInt( "customkill", info.GetDamageCustom() );
		event->SetInt( "priority", 7 );	// HLTV event priority, not transmitted
		gameeventmanager->FireEvent( event );
	}		
}
#endif


bool CBliinkGameRules::ShouldCollide( int collisionGroup0, int collisionGroup1 )
{
	if ( collisionGroup0 > collisionGroup1 )
	{
		// swap so that lowest is always first
		//swap(collisionGroup0,collisionGroup1);

		// swap so that lowest is always first
		int tmp = collisionGroup0;
		collisionGroup0 = collisionGroup1;
		collisionGroup1 = tmp;
	}

	//Don't stand on COLLISION_GROUP_WEAPON
	if( collisionGroup0 == COLLISION_GROUP_PLAYER_MOVEMENT &&
		collisionGroup1 == COLLISION_GROUP_WEAPON )
	{
		return false;
	}

	return BaseClass::ShouldCollide( collisionGroup0, collisionGroup1 ); 
}

//-----------------------------------------------------------------------------
// Purpose: Init CS ammo definitions
//-----------------------------------------------------------------------------

// shared ammo definition
// JAY: Trying to make a more physical bullet response
#define BULLET_MASS_GRAINS_TO_LB(grains)	(0.002285*(grains)/16.0f)
#define BULLET_MASS_GRAINS_TO_KG(grains)	lbs2kg(BULLET_MASS_GRAINS_TO_LB(grains))

// exaggerate all of the forces, but use real numbers to keep them consistent
#define BULLET_IMPULSE_EXAGGERATION			1	

// convert a velocity in ft/sec and a mass in grains to an impulse in kg in/s
#define BULLET_IMPULSE(grains, ftpersec)	((ftpersec)*12*BULLET_MASS_GRAINS_TO_KG(grains)*BULLET_IMPULSE_EXAGGERATION)


CAmmoDef* GetAmmoDef()
{
	static CAmmoDef def;
	static bool bInitted = false;

	if ( !bInitted )
	{
		bInitted = true;

		for (int i=WEAPON_NONE+1;i<SDK_WEAPON_MAX;i++)
		{
			//Tony; ignore grenades, shotgun and the crowbar, grenades and shotgun are handled seperately because of their damage type not being DMG_BULLET.
			if (i == SDK_WEAPON_GRENADE || i == SDK_WEAPON_CROWBAR || i == SDK_WEAPON_SHOTGUN)
				continue;

			def.AddAmmoType( WeaponIDToAlias(i), DMG_BULLET, TRACER_LINE_AND_WHIZ, 0, 0, 200/*MAX carry*/, 1, 0 );
		}

		// def.AddAmmoType( BULLET_PLAYER_50AE,		DMG_BULLET, TRACER_LINE, 0, 0, "ammo_50AE_max",		2400, 0, 10, 14 );
		def.AddAmmoType( "shotgun", DMG_BUCKSHOT, TRACER_NONE, 0, 0,	200/*MAX carry*/, 1, 0 );
		def.AddAmmoType( "grenades", DMG_BLAST, TRACER_NONE, 0, 0,	4/*MAX carry*/, 1, 0 );
	}

	return &def;
}


#ifndef CLIENT_DLL

const char *CBliinkGameRules::GetChatPrefix( bool bTeamOnly, CBasePlayer *pPlayer )
{
	//Tony; no prefix for now, it isn't needed.
	return "";
}

const char *CBliinkGameRules::GetChatFormat( bool bTeamOnly, CBasePlayer *pPlayer )
{
	if ( !pPlayer )  // dedicated server output
		return NULL;

	const char *pszFormat = NULL;

	if ( bTeamOnly )
	{
		if ( pPlayer->GetTeamNumber() == TEAM_SPECTATOR )
			pszFormat = "SDK_Chat_Spec";
		else
		{
			if (pPlayer->m_lifeState != LIFE_ALIVE )
				pszFormat = "SDK_Chat_Team_Dead";
			else
				pszFormat = "SDK_Chat_Team";
		}
	}
	else
	{
		if ( pPlayer->GetTeamNumber() == TEAM_SPECTATOR)
			pszFormat = "SDK_Chat_AllSpec";
		else
		{
			if (pPlayer->m_lifeState != LIFE_ALIVE )
				pszFormat = "SDK_Chat_All_Dead";
			else
				pszFormat = "SDK_Chat_All";
		}
	}

	return pszFormat;
}
#endif

//-----------------------------------------------------------------------------
// Purpose: Find the relationship between players (teamplay vs. deathmatch)
//-----------------------------------------------------------------------------
int CBliinkGameRules::PlayerRelationship( CBaseEntity *pPlayer, CBaseEntity *pTarget )
{
#ifndef CLIENT_DLL
	// half life multiplay has a simple concept of Player Relationships.
	// you are either on another player's team, or you are not.
	if ( !pPlayer || !pTarget || !pTarget->IsPlayer() || IsTeamplay() == false )
		return GR_NOTTEAMMATE;

	if ( (*GetTeamID(pPlayer) != '\0') && (*GetTeamID(pTarget) != '\0') && !stricmp( GetTeamID(pPlayer), GetTeamID(pTarget) ) )
		return GR_TEAMMATE;

#endif

	return GR_NOTTEAMMATE;
}

float CBliinkGameRules::GetMapRemainingTime()
{
#ifdef GAME_DLL
	if ( nextlevel.GetString() && *nextlevel.GetString() && engine->IsMapValid( nextlevel.GetString() ) )
	{
		return 0;
	}
#endif

	// if timelimit is disabled, return -1
	if ( mp_timelimit.GetInt() <= 0 )
		return -1;

	// timelimit is in minutes
	float flTimeLeft =  ( m_flGameStartTime + mp_timelimit.GetInt() * 60 ) - gpGlobals->curtime;

	// never return a negative value
	if ( flTimeLeft < 0 )
		flTimeLeft = 0;

	return flTimeLeft;
}

float CBliinkGameRules::GetMapElapsedTime( void )
{
	return gpGlobals->curtime;
}