//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose:		Player for HL1.
//
// $NoKeywords: $
//=============================================================================//

#include "cbase.h"
#include "bliink_player.h"
#include "bliink_team.h"
#include "bliink_gamerules.h"
#include "weapon_sdkbase.h"
#include "predicted_viewmodel.h"
#include "iservervehicle.h"
#include "viewport_panel_names.h"
#include "info_camera_link.h"
#include "GameStats.h"
#include "obstacle_pushaway.h"
#include "in_buttons.h"
#include "physics_prop_ragdoll.h"
#include "particle_parse.h"
#include "bliink_item_inventory.h"
#include "bliink_player_stats.h"
#include "basecombatweapon_shared.h"
#include "weapon_sdkbase.h"
#include "engine/ienginesound.h"
// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

extern int gEvilImpulse101;


ConVar SDK_ShowStateTransitions( "sdk_ShowStateTransitions", "-2", FCVAR_CHEAT, "sdk_ShowStateTransitions <ent index or -1 for all>. Show player state transitions." );

EHANDLE g_pLastDMSpawn;
// -------------------------------------------------------------------------------- //
// Player animation event. Sent to the client when a player fires, jumps, reloads, etc..
// -------------------------------------------------------------------------------- //

class CTEPlayerAnimEvent : public CBaseTempEntity
{
public:
	DECLARE_CLASS( CTEPlayerAnimEvent, CBaseTempEntity );
	DECLARE_SERVERCLASS();

					CTEPlayerAnimEvent( const char *name ) : CBaseTempEntity( name )
					{
					}

	CNetworkHandle( CBasePlayer, m_hPlayer );
	CNetworkVar( int, m_iEvent );
	CNetworkVar( int, m_nData );
};

IMPLEMENT_SERVERCLASS_ST_NOBASE( CTEPlayerAnimEvent, DT_TEPlayerAnimEvent )
	SendPropEHandle( SENDINFO( m_hPlayer ) ),
	SendPropInt( SENDINFO( m_iEvent ), Q_log2( PLAYERANIMEVENT_COUNT ) + 1, SPROP_UNSIGNED ),
	SendPropInt( SENDINFO( m_nData ), 32 )
END_SEND_TABLE()

static CTEPlayerAnimEvent g_TEPlayerAnimEvent( "PlayerAnimEvent" );

void TE_PlayerAnimEvent( CBasePlayer *pPlayer, PlayerAnimEvent_t event, int nData )
{
	CPVSFilter filter( (const Vector&)pPlayer->EyePosition() );

	//Tony; pull the player who is doing it out of the recipientlist, this is predicted!!
	filter.RemoveRecipient( pPlayer );

	g_TEPlayerAnimEvent.m_hPlayer = pPlayer;
	g_TEPlayerAnimEvent.m_iEvent = event;
	g_TEPlayerAnimEvent.m_nData = nData;
	g_TEPlayerAnimEvent.Create( filter, 0 );
}

// -------------------------------------------------------------------------------- //
// Tables.
// -------------------------------------------------------------------------------- //
BEGIN_DATADESC( CBliinkPlayer )
DEFINE_THINKFUNC( SDKPushawayThink ),
END_DATADESC()

LINK_ENTITY_TO_CLASS( player, CBliinkPlayer );
PRECACHE_REGISTER(player);

// CBliinkPlayerShared Data Tables
//=============================

// specific to the local player
BEGIN_SEND_TABLE_NOBASE( CBliinkPlayerShared, DT_SDKSharedLocalPlayerExclusive )
END_SEND_TABLE()

BEGIN_SEND_TABLE_NOBASE( CBliinkPlayerShared, DT_SDKPlayerShared )
#if defined ( SDK_USE_SPRINTING )
	SendPropBool( SENDINFO( m_bIsSprinting ) ),
#endif
	SendPropDataTable( "sdksharedlocaldata", 0, &REFERENCE_SEND_TABLE(DT_SDKSharedLocalPlayerExclusive), SendProxy_SendLocalDataTable ),
END_SEND_TABLE()
extern void SendProxy_Origin( const SendProp *pProp, const void *pStruct, const void *pData, DVariant *pOut, int iElement, int objectID );

BEGIN_SEND_TABLE_NOBASE( CBliinkPlayer, DT_SDKLocalPlayerExclusive )
	SendPropInt( SENDINFO( m_iShotsFired ), 8, SPROP_UNSIGNED ),
	// send a hi-res origin to the local player for use in prediction
	SendPropVector	(SENDINFO(m_vecOrigin), -1,  SPROP_NOSCALE|SPROP_CHANGES_OFTEN, 0.0f, HIGH_DEFAULT, SendProxy_Origin ),

	SendPropFloat( SENDINFO_VECTORELEM(m_angEyeAngles, 0), 8, SPROP_CHANGES_OFTEN, -90.0f, 90.0f ),
//	SendPropAngle( SENDINFO_VECTORELEM(m_angEyeAngles, 1), 10, SPROP_CHANGES_OFTEN ),

	SendPropInt( SENDINFO( m_ArmorValue ), 8, SPROP_UNSIGNED ),
END_SEND_TABLE()

BEGIN_SEND_TABLE_NOBASE( CBliinkPlayer, DT_SDKNonLocalPlayerExclusive )
	// send a lo-res origin to other players
	SendPropVector	(SENDINFO(m_vecOrigin), -1,  SPROP_COORD_MP_LOWPRECISION|SPROP_CHANGES_OFTEN, 0.0f, HIGH_DEFAULT, SendProxy_Origin ),

	SendPropFloat( SENDINFO_VECTORELEM(m_angEyeAngles, 0), 8, SPROP_CHANGES_OFTEN, -90.0f, 90.0f ),
	SendPropAngle( SENDINFO_VECTORELEM(m_angEyeAngles, 1), 10, SPROP_CHANGES_OFTEN ),
END_SEND_TABLE()

// Inventory table
BEGIN_NETWORK_TABLE_NOBASE( CBliinkItemInventory, DT_BliinkItemInventory )
		SendPropArray3( SENDINFO_ARRAY3(m_iItemTypes), SendPropInt( SENDINFO_ARRAY(m_iItemTypes), INVENTORY_MAX_SLOTS, SPROP_UNSIGNED ) ),
		SendPropArray3( SENDINFO_ARRAY3(m_iStackCounts), SendPropInt( SENDINFO_ARRAY(m_iStackCounts), INVENTORY_MAX_SLOTS, SPROP_UNSIGNED ) ),
		SendPropArray3( SENDINFO_ARRAY3(m_iAmmoSlots), SendPropInt( SENDINFO_ARRAY(m_iAmmoSlots), MAX_AMMO_TYPES, SPROP_NOSCALE ) ),
		SendPropArray3( SENDINFO_ARRAY3(m_iAmmoCounts), SendPropInt( SENDINFO_ARRAY(m_iAmmoCounts), MAX_AMMO_TYPES, SPROP_NOSCALE ) ),
END_NETWORK_TABLE()

// Stats table
BEGIN_NETWORK_TABLE_NOBASE( CBliinkPlayerStats, DT_BliinkPlayerStats )
	SendPropFloat( SENDINFO(m_fHealth), -1, SPROP_NOSCALE | SPROP_CHANGES_OFTEN),
	SendPropFloat( SENDINFO(m_fFatigue), -1, SPROP_NOSCALE | SPROP_CHANGES_OFTEN),
	SendPropFloat( SENDINFO(m_fHunger), -1, SPROP_NOSCALE | SPROP_CHANGES_OFTEN),
	SendPropFloat( SENDINFO(m_fMaxHealth), -1, SPROP_NOSCALE),
	SendPropFloat( SENDINFO(m_fMaxFatigue), -1, SPROP_NOSCALE),
	SendPropFloat( SENDINFO(m_fFatigueRegenRate), -1, SPROP_NOSCALE),
	SendPropInt( SENDINFO(m_iExperience), -1, SPROP_UNSIGNED),
	SendPropInt( SENDINFO(m_iLevel), -1, SPROP_UNSIGNED),
	SendPropInt( SENDINFO(m_iUpgradePoints), -1, SPROP_UNSIGNED),
	SendPropInt( SENDINFO(m_iMaxExperience), -1, SPROP_UNSIGNED),
	SendPropInt( SENDINFO(m_iStatusEffect), -1, SPROP_UNSIGNED),
	SendPropFloat( SENDINFO(m_fStatusEndTime), -1, SPROP_NOSCALE),
END_NETWORK_TABLE()

// main table
IMPLEMENT_SERVERCLASS_ST( CBliinkPlayer, DT_SDKPlayer )
	SendPropExclude( "DT_BaseAnimating", "m_flPoseParameter" ),
	SendPropExclude( "DT_BaseAnimating", "m_flPlaybackRate" ),	
	SendPropExclude( "DT_BaseAnimating", "m_nSequence" ),
	SendPropExclude( "DT_BaseAnimating", "m_nNewSequenceParity" ),
	SendPropExclude( "DT_BaseAnimating", "m_nResetEventsParity" ),
	SendPropExclude( "DT_BaseEntity", "m_angRotation" ),
	SendPropExclude( "DT_BaseAnimatingOverlay", "overlay_vars" ),
	SendPropExclude( "DT_BaseEntity", "m_vecOrigin" ),
	
	// playeranimstate and clientside animation takes care of these on the client
	SendPropExclude( "DT_ServerAnimationData" , "m_flCycle" ),	
	SendPropExclude( "DT_AnimTimeMustBeFirst" , "m_flAnimTime" ),

	// Data that only gets sent to the local player.
	SendPropDataTable( SENDINFO_DT( m_Shared ), &REFERENCE_SEND_TABLE( DT_SDKPlayerShared ) ),

	// Data that only gets sent to the local player.
	SendPropDataTable( "sdklocaldata", 0, &REFERENCE_SEND_TABLE(DT_SDKLocalPlayerExclusive), SendProxy_SendLocalDataTable ),
	// Data that gets sent to all other players
	SendPropDataTable( "sdknonlocaldata", 0, &REFERENCE_SEND_TABLE(DT_SDKNonLocalPlayerExclusive), SendProxy_SendNonLocalDataTable ),

	SendPropEHandle( SENDINFO( m_hRagdoll ) ),

	SendPropInt( SENDINFO( m_iPlayerState ), Q_log2( NUM_PLAYER_STATES )+1, SPROP_UNSIGNED ),

	SendPropBool( SENDINFO( m_bSpawnInterpCounter ) ),

	// Send table for inventory
	SendPropDataTable( SENDINFO_DT(m_Inventory), &REFERENCE_SEND_TABLE( DT_BliinkItemInventory ) ),

	// Send table for Bliink stats
	SendPropDataTable( SENDINFO_DT(m_BliinkStats), &REFERENCE_SEND_TABLE( DT_BliinkPlayerStats ) ),

END_SEND_TABLE()

class CSDKRagdoll : public CBaseAnimatingOverlay
{
public:
	DECLARE_CLASS( CSDKRagdoll, CBaseAnimatingOverlay );
	DECLARE_SERVERCLASS();

	// Transmit ragdolls to everyone.
	virtual int UpdateTransmitState()
	{
		return SetTransmitState( FL_EDICT_ALWAYS );
	}

public:
	// In case the client has the player entity, we transmit the player index.
	// In case the client doesn't have it, we transmit the player's model index, origin, and angles
	// so they can create a ragdoll in the right place.
	CNetworkHandle( CBaseEntity, m_hPlayer );	// networked entity handle 
	CNetworkVector( m_vecRagdollVelocity );
	CNetworkVector( m_vecRagdollOrigin );
};

LINK_ENTITY_TO_CLASS( sdk_ragdoll, CSDKRagdoll );

IMPLEMENT_SERVERCLASS_ST_NOBASE( CSDKRagdoll, DT_SDKRagdoll )
	SendPropVector( SENDINFO(m_vecRagdollOrigin), -1,  SPROP_COORD ),
	SendPropEHandle( SENDINFO( m_hPlayer ) ),
	SendPropModelIndex( SENDINFO( m_nModelIndex ) ),
	SendPropInt		( SENDINFO(m_nForceBone), 8, 0 ),
	SendPropVector	( SENDINFO(m_vecForce), -1, SPROP_NOSCALE ),
	SendPropVector( SENDINFO( m_vecRagdollVelocity ) )
END_SEND_TABLE()


// -------------------------------------------------------------------------------- //

void cc_CreatePredictionError_f()
{
	CBaseEntity *pEnt = CBaseEntity::Instance( 1 );
	pEnt->SetAbsOrigin( pEnt->GetAbsOrigin() + Vector( 63, 0, 0 ) );
}

ConCommand cc_CreatePredictionError( "CreatePredictionError", cc_CreatePredictionError_f, "Create a prediction error", FCVAR_CHEAT );

void CBliinkPlayer::SetupVisibility( CBaseEntity *pViewEntity, unsigned char *pvs, int pvssize )
{
	BaseClass::SetupVisibility( pViewEntity, pvs, pvssize );

	int area = pViewEntity ? pViewEntity->NetworkProp()->AreaNum() : NetworkProp()->AreaNum();
	PointCameraSetupVisibility( this, area, pvs, pvssize );
}

CBliinkPlayer::CBliinkPlayer()
{
	//Tony; create our player animation state.
	m_PlayerAnimState = CreateSDKPlayerAnimState( this );
	m_iLastWeaponFireUsercmd = 0;
	
	m_Shared.Init( this );

	UseClientSideAnimation();

	m_angEyeAngles.Init();

	m_pCurStateInfo = NULL;	// no state yet
}


CBliinkPlayer::~CBliinkPlayer()
{
	DestroyRagdoll();
	m_PlayerAnimState->Release();
}


CBliinkPlayer *CBliinkPlayer::CreatePlayer( const char *className, edict_t *ed )
{
	CBliinkPlayer::s_PlayerEdict = ed;
	return (CBliinkPlayer*)CreateEntityByName( className );
}

void CBliinkPlayer::PreThink(void)
{
	State_PreThink();

	// Riding a vehicle?
	if ( IsInAVehicle() )	
	{
		// make sure we update the client, check for timed damage and update suit even if we are in a vehicle
		UpdateClientData();		
		CheckTimeBasedDamage();

		// Allow the suit to recharge when in the vehicle.
		CheckSuitUpdate();
		
		WaterMove();	
		return;
	}

	BaseClass::PreThink();
}


void CBliinkPlayer::PostThink()
{
	BaseClass::PostThink();

	QAngle angles = GetLocalAngles();
	angles[PITCH] = 0;
	SetLocalAngles( angles );
	
	// Store the eye angles pitch so the client can compute its animation state correctly.
	m_angEyeAngles = EyeAngles();

    m_PlayerAnimState->Update( m_angEyeAngles[YAW], m_angEyeAngles[PITCH] );
}


void CBliinkPlayer::Precache()
{

	//Tony; go through our list of player models that we may be using and cache them
	int i = 0;
	while( pszPossiblePlayerModels[i] != NULL )
	{
		PrecacheModel( pszPossiblePlayerModels[i] );
		i++;
	}	

	BaseClass::Precache();
}

//Tony; this is where default items go when not using playerclasses!
void CBliinkPlayer::GiveDefaultItems()
{
	if ( State_Get() == STATE_BLIINK_SURVIVOR )
	{
		// give me survivory stuff...

		/*CBasePlayer::GiveAmmo( 30,	"pistol");
		CBasePlayer::GiveAmmo( 30,	"mp5");
		CBasePlayer::GiveAmmo( 12,	"shotgun");
		CBasePlayer::GiveAmmo( 5,	"grenades" );

		GiveNamedItem( "weapon_pistol" );
		GiveNamedItem( "weapon_mp5" );
		GiveNamedItem( "weapon_shotgun" );
		GiveNamedItem( "weapon_crowbar" );
		GiveNamedItem( "weapon_grenade" );*/
	}
	else if ( State_Get() == STATE_BLIINK_STALKER )
	{
		// give me stalker stuff
	}
}
#define SDK_PUSHAWAY_THINK_CONTEXT	"SDKPushawayThink"
void CBliinkPlayer::SDKPushawayThink(void)
{
	// Push physics props out of our way.
	PerformObstaclePushaway( this );
	SetNextThink( gpGlobals->curtime + PUSHAWAY_THINK_INTERVAL, SDK_PUSHAWAY_THINK_CONTEXT );
}

void CBliinkPlayer::Spawn()
{
	SetModel( SDK_PLAYER_MODEL );	//Tony; basically, leave this alone ;) unless you're not using classes or teams, then you can change it to whatever.
	
	SetBloodColor( BLOOD_COLOR_RED );
	
	SetMoveType( MOVETYPE_WALK );
	RemoveSolidFlags( FSOLID_NOT_SOLID );

	//Tony; if we're spawning in active state, equip the suit so the hud works. -- Gotta love base code !
	if ( State_Get() == STATE_BLIINK_SURVIVOR || State_Get() == STATE_BLIINK_STALKER )
	{
		EquipSuit( false );
	}

	m_hRagdoll = NULL;
	
	BaseClass::Spawn();

#if defined ( SDK_USE_SPRINTING )
	InitSprinting();
#endif

	// update this counter, used to not interp players when they spawn
	m_bSpawnInterpCounter = !m_bSpawnInterpCounter;

	InitSpeeds(); //Tony; initialize player speeds.

	SetContextThink( &CBliinkPlayer::SDKPushawayThink, gpGlobals->curtime + PUSHAWAY_THINK_INTERVAL, SDK_PUSHAWAY_THINK_CONTEXT );
	pl.deadflag = false;

	// Setting us as owner of Bliink inventory
	m_Inventory.SetOwner( this );

	// Initialising the player stats and setting us as owner.
	m_BliinkStats.SetOwner( this );
	m_BliinkStats.Reset();

	// Thinking
	SetThink(&CBliinkPlayer::Think);
	SetNextThink(gpGlobals->curtime);
}

bool CBliinkPlayer::SelectSpawnSpot( const char *pEntClassName, CBaseEntity* &pSpot )
{
	// Find the next spawn spot.
	pSpot = gEntList.FindEntityByClassname( pSpot, pEntClassName );

	if ( pSpot == NULL ) // skip over the null point
		pSpot = gEntList.FindEntityByClassname( pSpot, pEntClassName );

	CBaseEntity *pFirstSpot = pSpot;
	do 
	{
		if ( pSpot )
		{
			// check if pSpot is valid
			if ( g_pGameRules->IsSpawnPointValid( pSpot, this ) )
			{
				if ( pSpot->GetAbsOrigin() == Vector( 0, 0, 0 ) )
				{
					pSpot = gEntList.FindEntityByClassname( pSpot, pEntClassName );
					continue;
				}

				// if so, go to pSpot
				return true;
			}
		}
		// increment pSpot
		pSpot = gEntList.FindEntityByClassname( pSpot, pEntClassName );
	} while ( pSpot != pFirstSpot ); // loop if we're not back to the start

	DevMsg("CBliinkPlayer::SelectSpawnSpot: couldn't find valid spawn point.\n");

	return true;
}


CBaseEntity* CBliinkPlayer::EntSelectSpawnPoint()
{
	CBaseEntity *pSpot = NULL;

	const char *pSpawnPointName = "";

	switch( GetTeamNumber() )
	{
	case TEAM_UNASSIGNED:
		{
			pSpawnPointName = "info_player_spawn";
			pSpot = g_pLastDMSpawn;
			if ( SelectSpawnSpot( pSpawnPointName, pSpot ) )
			{
				g_pLastDMSpawn = pSpot;
			}
		}		
		break;
	case TEAM_SPECTATOR:
	default:
		{
			pSpot = CBaseEntity::Instance( INDEXENT(0) );
		}
		break;		
	}

	if ( !pSpot )
	{
		Warning( "PutClientInServer: no %s on level\n", pSpawnPointName );
		return CBaseEntity::Instance( INDEXENT(0) );
	}

	return pSpot;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CBliinkPlayer::CommitSuicide( bool bExplode /* = false */, bool bForce /*= false*/ )
{
	// Don't suicide if we haven't picked a class for the first time, or we're not in active state
	if (
		State_Get() != STATE_BLIINK_STALKER || State_Get() != STATE_BLIINK_SURVIVOR
		)
		return;
	
	m_iSuicideCustomKillFlags = SDK_DMG_CUSTOM_SUICIDE;

	BaseClass::CommitSuicide( bExplode, bForce );
}

// Puts the player in the WELCOME state when they join the server, however, if
// they join when the game is active, then we put them in spectate mode.
void CBliinkPlayer::InitialSpawn( void )
{
	BaseClass::InitialSpawn();
	
	if( BliinkGameRules()->IsGameActive() )
		State_Enter( STATE_BLIINK_SPECTATE );
	else
		State_Enter( STATE_BLIINK_WELCOME );

}
void CBliinkPlayer::TraceAttack( const CTakeDamageInfo &inputInfo, const Vector &vecDir, trace_t *ptr )
{
	//Tony; disable prediction filtering, and call the baseclass.
	CDisablePredictionFiltering disabler;
	BaseClass::TraceAttack( inputInfo, vecDir, ptr );
}
int CBliinkPlayer::OnTakeDamage( const CTakeDamageInfo &inputInfo )
{
	CTakeDamageInfo info = inputInfo;

	CBaseEntity *pInflictor = info.GetInflictor();

	if ( !pInflictor )
		return 0;

	if ( GetMoveType() == MOVETYPE_NOCLIP || GetMoveType() == MOVETYPE_OBSERVER )
		return 0;

	float flDamage = info.GetDamage();

	Msg("Taking damage %f!\n", flDamage);

	if ( 0 /*pInflictor == this ||	info.GetAttacker() == this*/ )
	{
		// keep track of amount of damage last sustained
		m_lastDamageAmount = flDamage;

		// round damage to integer
		info.SetDamage( (int)flDamage );

		if ( info.GetDamage() <= 0 )
			return 0;

		CSingleUserRecipientFilter user( this );
		user.MakeReliable();
		UserMessageBegin( user, "Damage" );
			WRITE_BYTE( (int)info.GetDamage() );
			WRITE_VEC3COORD( info.GetInflictor()->WorldSpaceCenter() );
		MessageEnd();

		// Do special explosion damage effect
		if ( info.GetDamageType() & DMG_BLAST )
		{
			OnDamagedByExplosion( info );
		}

		gamestats->Event_PlayerDamage( this, info );

		return CBaseCombatCharacter::OnTakeDamage( info );
	}
	else
	{
		return CBaseCombatCharacter::OnTakeDamage( info );
	}
}

int CBliinkPlayer::OnTakeDamage_Alive( const CTakeDamageInfo &info )
{
	// set damage type sustained
	m_bitsDamageType |= info.GetDamageType();
	
	// Updating health.
	if( !(info.GetDamageType() & DMG_BLIINKSELF) )
	{
		m_BliinkStats.TakeDamage(info.GetDamage());
	}

	if ( !CBaseCombatCharacter::OnTakeDamage_Alive( info ) )
		return 0;

	// Doing status effects.
	float fRandomFloat = RandomFloat();

	if( (info.GetDamageType() & DMG_BURN) && fRandomFloat <= STATUS_BURN_CHANCE )
		m_BliinkStats.AfflictStatus( BLIINK_STATUS_BURNING, 5.0f );
	else
	if( (info.GetDamageType() & DMG_NERVEGAS) && fRandomFloat <= STATUS_FOG_CHANCE )
		m_BliinkStats.AfflictStatus( BLIINK_STATUS_FOGGED, 20.0f );
	else
	if( (info.GetDamageType() & DMG_POISON) && fRandomFloat <= STATUS_POISON_CHANCE )
		m_BliinkStats.AfflictStatus( BLIINK_STATUS_POISONED, 20.0f );
	else
	if( (info.GetDamageType() & DMG_PARALYZE) && fRandomFloat <= STATUS_SLOW_CHANCE )
		m_BliinkStats.AfflictStatus( BLIINK_STATUS_SLOWED, 0.5f );

	// fire global game event

	IGameEvent * event = gameeventmanager->CreateEvent( "player_hurt" );

	if ( event )
	{
		event->SetInt("userid", GetUserID() );
		event->SetInt("health", MAX(0, m_iHealth) );
		event->SetInt("armor", MAX(0, ArmorValue()) );

		if ( info.GetDamageType() & DMG_BLAST )
		{
			event->SetInt( "hitgroup", HITGROUP_GENERIC );
		}
		else
		{
			event->SetInt( "hitgroup", LastHitGroup() );
		}

		CBaseEntity * attacker = info.GetAttacker();
		const char *weaponName = "";

		if ( attacker->IsPlayer() )
		{
			CBasePlayer *player = ToBasePlayer( attacker );
			event->SetInt("attacker", player->GetUserID() ); // hurt by other player

			CBaseEntity *pInflictor = info.GetInflictor();
			if ( pInflictor )
			{
				if ( pInflictor == player )
				{
					// If the inflictor is the killer,  then it must be their current weapon doing the damage
					if ( player->GetActiveWeapon() )
					{
						weaponName = player->GetActiveWeapon()->GetClassname();
					}
				}
				else
				{
					weaponName = STRING( pInflictor->m_iClassname );  // it's just that easy
				}
			}
		}
		else
		{
			event->SetInt("attacker", 0 ); // hurt by "world"
		}

		if ( strncmp( weaponName, "weapon_", 7 ) == 0 )
		{
			weaponName += 7;
		}
		else if( strncmp( weaponName, "grenade", 9 ) == 0 )	//"grenade_projectile"	
		{
			weaponName = "grenade";
		}

		event->SetString( "weapon", weaponName );
		event->SetInt( "priority", 5 );

		gameeventmanager->FireEvent( event );
	}
	
	return 1;
}

ConVar c_server_ragdoll("c_server_ragdoll", "0", FCVAR_CHEAT, "If set, players will have server ragdolls instead of clientside ones.");

bool CBliinkPlayer::BecomeRagdollOnClient( const Vector &force )
{
	if ( !CanBecomeRagdoll() ) 
		return false;

	// Become server-side ragdoll if we're flagged to do it
	//if ( m_spawnflags & SF_ANTLIONGUARD_SERVERSIDE_RAGDOLL )
	if (c_server_ragdoll.GetBool())
	{
		CTakeDamageInfo	info;

		// Fake the info
		info.SetDamageType( DMG_GENERIC );
		info.SetDamageForce( force );
		info.SetDamagePosition( WorldSpaceCenter() );		
		IPhysicsObject *pPhysics = VPhysicsGetObject();
		if ( pPhysics )
		{
			VPhysicsDestroyObject();
		}
		CBaseEntity *pRagdoll = CreateServerRagdoll( this, m_nForceBone, info, COLLISION_GROUP_INTERACTIVE_DEBRIS, true );
		FixupBurningServerRagdoll( pRagdoll );
		PhysSetEntityGameFlags( pRagdoll, FVPHYSICS_NO_SELF_COLLISIONS );

		//CBaseEntity *pRagdoll = CreateServerRagdoll( this, 0, info, COLLISION_GROUP_NONE );

		// Transfer our name to the new ragdoll
		pRagdoll->SetName( GetEntityName() );
		//pRagdoll->SetCollisionGroup( COLLISION_GROUP_DEBRIS );
		
		// Get rid of our old body
		//UTIL_Remove(this);
		RemoveDeferred();

		return true;
	}

	return BaseClass::BecomeRagdollOnClient( force );
}

void CBliinkPlayer::Event_Killed( const CTakeDamageInfo &info )
{
	ThrowActiveWeapon();

	// show killer in death cam mode
	// chopped down version of SetObserverTarget without the team check
	if( info.GetAttacker() && info.GetAttacker()->IsPlayer() )
	{
		// set new target
		m_hObserverTarget.Set( info.GetAttacker() ); 

		// reset fov to default
		SetFOV( this, 0 );
	}
	else
		m_hObserverTarget.Set( NULL );

	// Note: since we're dead, it won't draw us on the client, but we don't set EF_NODRAW
	// because we still want to transmit to the clients in our PVS.
	//CreateRagdollEntity();

	if(m_iPlayerState == STATE_BLIINK_SURVIVOR)
	{
		State_Transition( STATE_BLIINK_SURVIVOR_DEATH_ANIM );
	}
	else if(m_iPlayerState == STATE_BLIINK_STALKER)
	{
		State_Transition( STATE_BLIINK_STALKER_DEATH_ANIM );
	}


	//Tony; after transition, remove remaining items
	RemoveAllItems( true );

	BaseClass::Event_Killed( info );

}
void CBliinkPlayer::ThrowActiveWeapon( void )
{
	CWeaponSDKBase *pWeapon = (CWeaponSDKBase *)GetActiveWeapon();

	if( pWeapon && pWeapon->CanWeaponBeDropped() )
	{
		QAngle gunAngles;
		VectorAngles( BodyDirection2D(), gunAngles );

		Vector vecForward;
		AngleVectors( gunAngles, &vecForward, NULL, NULL );

		float flDiameter = sqrt( CollisionProp()->OBBSize().x * CollisionProp()->OBBSize().x + CollisionProp()->OBBSize().y * CollisionProp()->OBBSize().y );

		pWeapon->Holster(NULL);
		SwitchToNextBestWeapon( pWeapon );
		SDKThrowWeapon( pWeapon, vecForward, gunAngles, flDiameter );
	}
}
void CBliinkPlayer::Weapon_Equip( CBaseCombatWeapon *pWeapon )
{
	BaseClass::Weapon_Equip( pWeapon );
	dynamic_cast<CWeaponSDKBase*>(pWeapon)->SetDieThink( false );	//Make sure the context think for removing is gone!!

}
void CBliinkPlayer::SDKThrowWeapon( CWeaponSDKBase *pWeapon, const Vector &vecForward, const QAngle &vecAngles, float flDiameter  )
{
	Vector vecOrigin;
	CollisionProp()->RandomPointInBounds( Vector( 0.5f, 0.5f, 0.5f ), Vector( 0.5f, 0.5f, 1.0f ), &vecOrigin );

	// Nowhere in particular; just drop it.
	Vector vecThrow;
	SDKThrowWeaponDir( pWeapon, vecForward, &vecThrow );

	Vector vecOffsetOrigin;
	VectorMA( vecOrigin, flDiameter, vecThrow, vecOffsetOrigin );

	trace_t	tr;
	UTIL_TraceLine( vecOrigin, vecOffsetOrigin, MASK_SOLID_BRUSHONLY, this, COLLISION_GROUP_NONE, &tr );
		
	if ( tr.startsolid || tr.allsolid || ( tr.fraction < 1.0f && tr.m_pEnt != pWeapon ) )
	{
		//FIXME: Throw towards a known safe spot?
		vecThrow.Negate();
		VectorMA( vecOrigin, flDiameter, vecThrow, vecOffsetOrigin );
	}

	vecThrow *= random->RandomFloat( 150.0f, 240.0f );

	pWeapon->SetAbsOrigin( vecOrigin );
	pWeapon->SetAbsAngles( vecAngles );
	pWeapon->Drop( vecThrow );
	pWeapon->SetRemoveable( false );
	Weapon_Detach( pWeapon );

	pWeapon->SetDieThink( true );
}

void CBliinkPlayer::SDKThrowWeaponDir( CWeaponSDKBase *pWeapon, const Vector &vecForward, Vector *pVecThrowDir )
{
	VMatrix zRot;
	MatrixBuildRotateZ( zRot, random->RandomFloat( -60.0f, 60.0f ) );

	Vector vecThrow;
	Vector3DMultiply( zRot, vecForward, *pVecThrowDir );

	pVecThrowDir->z = random->RandomFloat( -0.5f, 0.5f );
	VectorNormalize( *pVecThrowDir );
}

void CBliinkPlayer::PlayerDeathThink()
{
	//overridden, do nothing - our states handle this now
}
void CBliinkPlayer::CreateRagdollEntity()
{
	// If we already have a ragdoll, don't make another one.
	CSDKRagdoll *pRagdoll = dynamic_cast< CSDKRagdoll* >( m_hRagdoll.Get() );

	if( pRagdoll )
	{
		UTIL_Remove( pRagdoll );
		pRagdoll = NULL;
	}
	Assert( pRagdoll == NULL );

	if ( !pRagdoll )
	{
		// create a new one
		pRagdoll = dynamic_cast< CSDKRagdoll* >( CreateEntityByName( "sdk_ragdoll" ) );
	}

	if ( pRagdoll )
	{
		pRagdoll->m_hPlayer = this;
		pRagdoll->m_vecRagdollOrigin = GetAbsOrigin();
		pRagdoll->m_vecRagdollVelocity = GetAbsVelocity();
		pRagdoll->m_nModelIndex = m_nModelIndex;
		pRagdoll->m_nForceBone = m_nForceBone;
		pRagdoll->m_vecForce = Vector(0,0,0);
	}

	// ragdolls will be removed on round restart automatically
	m_hRagdoll = pRagdoll;
}
//-----------------------------------------------------------------------------
// Purpose: Destroy's a ragdoll, called when a player is disconnecting.
//-----------------------------------------------------------------------------
void CBliinkPlayer::DestroyRagdoll( void )
{
	CSDKRagdoll *pRagdoll = dynamic_cast<CSDKRagdoll*>( m_hRagdoll.Get() );	
	if( pRagdoll )
	{
		UTIL_Remove( pRagdoll );
	}
}

void CBliinkPlayer::DoAnimationEvent( PlayerAnimEvent_t event, int nData )
{
	m_PlayerAnimState->DoAnimationEvent( event, nData );
	TE_PlayerAnimEvent( this, event, nData );	// Send to any clients who can see this guy.
}

CWeaponSDKBase* CBliinkPlayer::GetActiveSDKWeapon() const
{
	return static_cast< CWeaponSDKBase* >( GetActiveWeapon() );
}

void CBliinkPlayer::CreateViewModel( int index /*=0*/ )
{
	Assert( index >= 0 && index < MAX_VIEWMODELS );

	if ( GetViewModel( index ) )
		return;

	CPredictedViewModel *vm = ( CPredictedViewModel * )CreateEntityByName( "predicted_viewmodel" );
	if ( vm )
	{
		vm->SetAbsOrigin( GetAbsOrigin() );
		vm->SetOwner( this );
		vm->SetIndex( index );
		DispatchSpawn( vm );
		vm->FollowEntity( this, false );
		m_hViewModel.Set( index, vm );
	}
}

void CBliinkPlayer::CheatImpulseCommands( int iImpulse )
{
	if ( !sv_cheats->GetBool() )
	{
		return;
	}

	if ( iImpulse != 101 )
	{
		BaseClass::CheatImpulseCommands( iImpulse );
		return ;
	}
	gEvilImpulse101 = true;

	EquipSuit();
	
	if ( GetHealth() < 100 )
	{
		TakeHealth( 25, DMG_GENERIC );
	}

	gEvilImpulse101		= false;
}


void CBliinkPlayer::FlashlightTurnOn( void )
{
	AddEffects( EF_DIMLIGHT );
}

void CBliinkPlayer::FlashlightTurnOff( void )
{
	RemoveEffects( EF_DIMLIGHT );
}

int CBliinkPlayer::FlashlightIsOn( void )
{
	return IsEffectActive( EF_DIMLIGHT );
}

bool CBliinkPlayer::ClientCommand( const CCommand &args )
{
	const char *pcmd = args[0];
	if( !Q_strncmp( pcmd, "cls_", 4 ) )
	{
		return true;
	}
	else if ( FStrEq( pcmd, "spectate" ) )
	{
		// instantly join spectators
		return true;
	}
	else if ( FStrEq( pcmd, "menuopen" ) )
	{
		return true;
	}
	else if ( FStrEq( pcmd, "menuclosed" ) )
	{
		return true;
	}
	else if ( FStrEq( pcmd, "drop" ) )
	{
		ThrowActiveWeapon();
		return true;
	}
	// State transitions
	else if( FStrEq( pcmd, "bliink_welcome_spectate" ) )
	{
		// If we are at the welcome menu
		if( m_iPlayerState == STATE_BLIINK_WELCOME)
		{
			State_Transition( STATE_BLIINK_SPECTATE_PREGAME );
		}
	}
	else if( FStrEq( pcmd, "bliink_welcome_play" ) )
	{
		if( m_iPlayerState == STATE_BLIINK_WELCOME)
		{
			State_Transition( STATE_BLIINK_WAITING_FOR_PLAYERS );
		}
	}
	else if( FStrEq( pcmd, "bliink_spectate_pregame_welcome" ) )
	{
		if( m_iPlayerState == STATE_BLIINK_SPECTATE_PREGAME )
		{
			State_Transition( STATE_BLIINK_WELCOME );
		}
	}
	else if( FStrEq( pcmd, "bliink_cancel_ready" ) )
	{
		if( m_iPlayerState == STATE_BLIINK_WAITING_FOR_PLAYERS )
		{
			State_Transition( STATE_BLIINK_WELCOME );
		}
	}
	
	if( m_iPlayerState == STATE_BLIINK_SURVIVOR )
	{
		// Upgrades
		if( FStrEq( pcmd, "bliink_upgrade_slots" ) )
		{
			m_BliinkStats.UseUpgrade( BLIINK_UPGRADE_WEAPON_SLOTS );
		}
		else if( FStrEq( pcmd, "bliink_upgrade_health" ) )
		{
			m_BliinkStats.UseUpgrade( BLIINK_UPGRADE_HEALTH );
		}
		else if( FStrEq( pcmd, "bliink_upgrade_fatigue" ) )
		{
			m_BliinkStats.UseUpgrade( BLIINK_UPGRADE_STAMINA );
		}

		// Cheats
		else if( FStrEq( pcmd, "bliink_debug_exp" ) )
		{
			m_BliinkStats.GainExperience( 17 );
		}
		else if( FStrEq( pcmd, "bliink_debug_slow" ) )
		{
			m_BliinkStats.AfflictStatus( BLIINK_STATUS_SLOWED, 5.0f );
		}
		else if( FStrEq( pcmd, "bliink_debug_burn" ) )
		{
			m_BliinkStats.AfflictStatus( BLIINK_STATUS_BURNING, 5.0f );
		}

		// Inventory	
		else if( FStrEq( pcmd, "bliink_inventory_move" ) )
		{
			int from = atoi( args.Arg(1) ); 
			int to = atoi( args.Arg(2) );

			m_Inventory.Command_Move(from, to);
		}	
		else if( FStrEq( pcmd, "bliink_inventory_craft" ) )
		{
			int from = atoi( args.Arg(1) ); 
			int to = atoi( args.Arg(2) );

			m_Inventory.Command_Craft(from, to);
		}	
		else if( FStrEq( pcmd, "bliink_inventory_drop") )
		{
			int from = atoi( args.Arg(1) ); 

			m_Inventory.Command_Drop(from);
		}	
		else if( FStrEq( pcmd, "bliink_inventory_consume" ) )
		{
			int from = atoi( args.Arg(1) ); 

			m_Inventory.Command_Consume(from);
		}	
		else if( FStrEq( pcmd, "bliink_inventory_delete" ) )
		{
			int from = atoi( args.Arg(1) ); 

			m_Inventory.Command_Delete(from);
		}	
		else if( FStrEq( pcmd, "bliink_inventory_nextammo" ) )
		{
			m_Inventory.Command_SetNextAmmoType();
		}
		else if( FStrEq( pcmd, "bliink_inventory_print" ) )
		{
			m_Inventory.Debug_PrintInventory();
		}
	}

	return BaseClass::ClientCommand( args );
}

#if defined ( SDK_USE_SPRINTING )
void CBliinkPlayer::InitSprinting( void )
{
	m_Shared.SetSprinting( false );
}

//-----------------------------------------------------------------------------
// Purpose: Returns whether or not we are allowed to sprint now.
//-----------------------------------------------------------------------------
bool CBliinkPlayer::CanSprint()
{
	return ( 
		//!IsWalking() &&									// Not if we're walking
		!( m_Local.m_bDucked && !m_Local.m_bDucking ) &&	// Nor if we're ducking
		(GetWaterLevel() != 3) );							// Certainly not underwater
}
#endif // SDK_USE_SPRINTING
// ------------------------------------------------------------------------------------------------ //
// Player state management.
// ------------------------------------------------------------------------------------------------ //

void CBliinkPlayer::State_Transition( BliinkPlayerState newState )
{
	State_Leave();
	State_Enter( newState );
}


void CBliinkPlayer::State_Enter( BliinkPlayerState newState )
{
	m_iPlayerState = newState;
	m_pCurStateInfo = State_LookupInfo( newState );

	if ( SDK_ShowStateTransitions.GetInt() == -1 || SDK_ShowStateTransitions.GetInt() == entindex() )
	{
		if ( m_pCurStateInfo )
			Msg( "ShowStateTransitions: entering '%s'\n", m_pCurStateInfo->m_pStateName );
		else
			Msg( "ShowStateTransitions: entering #%d\n", newState );
	}
	
	// Initialize the new state.
	if ( m_pCurStateInfo && m_pCurStateInfo->pfnEnterState )
		(this->*m_pCurStateInfo->pfnEnterState)();
}


void CBliinkPlayer::State_Leave()
{
	if ( m_pCurStateInfo && m_pCurStateInfo->pfnLeaveState )
	{
		(this->*m_pCurStateInfo->pfnLeaveState)();
	}
}


void CBliinkPlayer::State_PreThink()
{
	if ( m_pCurStateInfo && m_pCurStateInfo->pfnPreThink )
	{
		(this->*m_pCurStateInfo->pfnPreThink)();
	}
}


CBliinkPlayerStateInfo* CBliinkPlayer::State_LookupInfo( BliinkPlayerState state )
{
	// This table MUST match the 
	static CBliinkPlayerStateInfo playerStateInfos[] =
	{
		{ STATE_BLIINK_WELCOME,					"STATE_BLIINK_WELCOME",	&CBliinkPlayer::State_Enter_BLIINK_WELCOME,	NULL, &CBliinkPlayer::State_PreThink_BLIINK_WELCOME },
		{ STATE_BLIINK_SPECTATE_PREGAME,		"STATE_BLIINK_SPECTATE_PREGAME",	&CBliinkPlayer::State_Enter_BLIINK_SPECTATE_PREGAME,	NULL, &CBliinkPlayer::State_PreThink_BLIINK_SPECTATE_PREGAME },
		{ STATE_BLIINK_WAITING_FOR_PLAYERS,		"STATE_BLIINK_WAITING_FOR_PLAYERS",	&CBliinkPlayer::State_Enter_BLIINK_WAITING_FOR_PLAYERS,	NULL, &CBliinkPlayer::State_PreThink_BLIINK_WAITING_FOR_PLAYERS },
		{ STATE_BLIINK_SPECTATE,				"STATE_BLIINK_SPECTATE",			&CBliinkPlayer::State_Enter_BLIINK_SPECTATE,	NULL, &CBliinkPlayer::State_PreThink_BLIINK_SPECTATE },
		{ STATE_BLIINK_SURVIVOR,				"STATE_BLIINK_SURVIVOR",			&CBliinkPlayer::State_Enter_BLIINK_SURVIVOR,	NULL, &CBliinkPlayer::State_PreThink_BLIINK_SURVIVOR },
		{ STATE_BLIINK_SURVIVOR_DEATH_ANIM,		"STATE_BLIINK_SURVIVOR_DEATH_ANIM",	&CBliinkPlayer::State_Enter_BLIINK_SURVIVOR_DEATH_ANIM,	NULL, &CBliinkPlayer::State_PreThink_BLIINK_SURVIVOR_DEATH_ANIM },
		{ STATE_BLIINK_STALKER,					"STATE_BLIINK_STALKER",				&CBliinkPlayer::State_Enter_BLIINK_STALKER,	NULL, &CBliinkPlayer::State_PreThink_BLIINK_STALKER },
		{ STATE_BLIINK_STALKER_DEATH_ANIM,		"STATE_BLIINK_STALKER_DEATH_ANIM",	&CBliinkPlayer::State_Enter_BLIINK_STALKER_DEATH_ANIM,	NULL, &CBliinkPlayer::State_PreThink_BLIINK_STALKER_DEATH_ANIM },
		{ STATE_BLIINK_STALKER_RESPAWN,			"STATE_BLIINK_STALKER_RESPAWN",		&CBliinkPlayer::State_Enter_BLIINK_STALKER_RESPAWN,	NULL, &CBliinkPlayer::State_PreThink_BLIINK_STALKER_RESPAWN },
		{ STATE_BLIINK_VIEW_RESULTS,			"STATE_BLIINK_VIEW_RESULTS",		&CBliinkPlayer::State_Enter_BLIINK_VIEW_RESULTS,	NULL, &CBliinkPlayer::State_PreThink_BLIINK_VIEW_RESULTS }
	};

	for ( int i=0; i < ARRAYSIZE( playerStateInfos ); i++ )
	{
		if ( playerStateInfos[i].m_iPlayerState == state )
			return &playerStateInfos[i];
	}

	return NULL;
}
void CBliinkPlayer::PhysObjectSleep()
{
	IPhysicsObject *pObj = VPhysicsGetObject();
	if ( pObj )
		pObj->Sleep();
}


void CBliinkPlayer::PhysObjectWake()
{
	IPhysicsObject *pObj = VPhysicsGetObject();
	if ( pObj )
		pObj->Wake();
}

void CBliinkPlayer::MoveToNextIntroCamera()
{
	m_pIntroCamera = gEntList.FindEntityByClassname( m_pIntroCamera, "point_viewcontrol" );

	// if m_pIntroCamera is NULL we just were at end of list, start searching from start again
	if(!m_pIntroCamera)
		m_pIntroCamera = gEntList.FindEntityByClassname(m_pIntroCamera, "point_viewcontrol");

	// find the target
	CBaseEntity *Target = NULL;
	
	if( m_pIntroCamera )
	{
		Target = gEntList.FindEntityByName( NULL, STRING(m_pIntroCamera->m_target) );
	}

	SetViewOffset( vec3_origin );	// no view offset
	UTIL_SetSize( this, vec3_origin, vec3_origin ); // no bbox

	if( !Target ) //if there are no cameras(or the camera has no target, find a spawn point and black out the screen
	{
		if ( m_pIntroCamera.IsValid() ){

			SetAbsOrigin( m_pIntroCamera->GetAbsOrigin() + VEC_VIEW );
			SetAbsAngles( m_pIntroCamera->GetAbsAngles() );
		}

		//SetAbsAngles( QAngle( 0, 0, 0 ) );
		
		m_pIntroCamera = NULL;  // never update again
		return;
	}
	

	Vector vCamera = Target->GetAbsOrigin() - m_pIntroCamera->GetAbsOrigin();
	Vector vIntroCamera = m_pIntroCamera->GetAbsOrigin();
	
	VectorNormalize( vCamera );
		
	QAngle CamAngles;
	VectorAngles( vCamera, CamAngles );

	SetAbsOrigin( vIntroCamera );
	SetAbsAngles( m_pIntroCamera->GetAbsAngles() );
	SnapEyeAngles( m_pIntroCamera->GetAbsAngles() );
	m_fIntroCamTime = gpGlobals->curtime + 6;
}

//**************************************************************************
//* BLIINK PLAYER STATE FUNCTIONS
//**************************************************************************
void CBliinkPlayer::State_Enter_BLIINK_WELCOME()
{	
	// Movement and physics
	SetMoveType( MOVETYPE_NONE );
	AddSolidFlags( FSOLID_NOT_SOLID );
	PhysObjectSleep();

	// Show welcome menu

	// TEMPORARY, REPLACE THIS WITH READY BUTTON!!!!!!!!!
	State_Transition(STATE_BLIINK_WAITING_FOR_PLAYERS);
}

void CBliinkPlayer::State_PreThink_BLIINK_WELCOME()
{	
	// Update whatever intro camera it's at.
	if( m_pIntroCamera && (gpGlobals->curtime >= m_fIntroCamTime) )
	{
		MoveToNextIntroCamera();
	}
}

void CBliinkPlayer::State_Enter_BLIINK_SPECTATE_PREGAME()
{	
	// Movement and physics
	SetMoveType( MOVETYPE_OBSERVER );

	// Always start a spectator session in roaming mode
	m_iObserverLastMode = OBS_MODE_ROAMING;

	if( m_hObserverTarget == NULL )
	{
		// find a new observer target
		CheckObserverSettings();
	}

	// Change our observer target to the nearest teammate
	CTeam *pTeam = GetGlobalTeam( GetTeamNumber() );

	CBasePlayer *pPlayer;
	Vector localOrigin = GetAbsOrigin();
	Vector targetOrigin;
	float flMinDist = FLT_MAX;
	float flDist;

	for ( int i=0;i<pTeam->GetNumPlayers();i++ )
	{
		pPlayer = pTeam->GetPlayer(i);

		if ( !pPlayer )
			continue;

		if ( !IsValidObserverTarget(pPlayer) )
			continue;

		targetOrigin = pPlayer->GetAbsOrigin();

		flDist = ( targetOrigin - localOrigin ).Length();

		if ( flDist < flMinDist )
		{
			m_hObserverTarget.Set( pPlayer );
			flMinDist = flDist;
		}
	}

	StartObserverMode( m_iObserverLastMode );
	PhysObjectSleep();
}

void CBliinkPlayer::State_PreThink_BLIINK_SPECTATE_PREGAME()
{	
	//Tony; if we're in eye, or chase, validate the target - if it's invalid, find a new one, or go back to roaming
	if (  m_iObserverMode == OBS_MODE_IN_EYE || m_iObserverMode == OBS_MODE_CHASE )
	{
		//Tony; if they're not on a spectating team use the cbaseplayer validation method.
		if ( GetTeamNumber() != TEAM_SPECTATOR )
			ValidateCurrentObserverTarget();
		else
		{
			if ( !IsValidObserverTarget( m_hObserverTarget.Get() ) )
			{
				// our target is not valid, try to find new target
				CBaseEntity * target = FindNextObserverTarget( false );
				if ( target )
				{
					// switch to new valid target
					SetObserverTarget( target );	
				}
				else
				{
					// let player roam around
					ForceObserverMode( OBS_MODE_ROAMING );
				}
			}
		}
	}
}

void CBliinkPlayer::State_Enter_BLIINK_WAITING_FOR_PLAYERS()
{
	// Movement and physics
	SetMoveType( MOVETYPE_NONE );
	AddSolidFlags( FSOLID_NOT_SOLID );
	PhysObjectSleep();
}

void CBliinkPlayer::State_PreThink_BLIINK_WAITING_FOR_PLAYERS()
{		
	// Update whatever intro camera it's at.
	if( m_pIntroCamera && (gpGlobals->curtime >= m_fIntroCamTime) )
	{
		MoveToNextIntroCamera();
	}
}

void CBliinkPlayer::State_Enter_BLIINK_SPECTATE()
{		
	// Movement and physics
	SetMoveType( MOVETYPE_OBSERVER );

	// Always start a spectator session in roaming mode
	m_iObserverLastMode = OBS_MODE_ROAMING;

	if( m_hObserverTarget == NULL )
	{
		// find a new observer target
		CheckObserverSettings();
	}

	// Change our observer target to the nearest teammate
	CTeam *pTeam = GetGlobalTeam( GetTeamNumber() );

	CBasePlayer *pPlayer;
	Vector localOrigin = GetAbsOrigin();
	Vector targetOrigin;
	float flMinDist = FLT_MAX;
	float flDist;

	for ( int i=0;i<pTeam->GetNumPlayers();i++ )
	{
		pPlayer = pTeam->GetPlayer(i);

		if ( !pPlayer )
			continue;

		if ( !IsValidObserverTarget(pPlayer) )
			continue;

		targetOrigin = pPlayer->GetAbsOrigin();

		flDist = ( targetOrigin - localOrigin ).Length();

		if ( flDist < flMinDist )
		{
			m_hObserverTarget.Set( pPlayer );
			flMinDist = flDist;
		}
	}

	StartObserverMode( m_iObserverLastMode );
	PhysObjectSleep();
}

void CBliinkPlayer::State_PreThink_BLIINK_SPECTATE()
{	
	//Tony; if we're in eye, or chase, validate the target - if it's invalid, find a new one, or go back to roaming
	if (  m_iObserverMode == OBS_MODE_IN_EYE || m_iObserverMode == OBS_MODE_CHASE )
	{
		//Tony; if they're not on a spectating team use the cbaseplayer validation method.
		if ( GetTeamNumber() != TEAM_SPECTATOR )
			ValidateCurrentObserverTarget();
		else
		{
			if ( !IsValidObserverTarget( m_hObserverTarget.Get() ) )
			{
				// our target is not valid, try to find new target
				CBaseEntity * target = FindNextObserverTarget( false );
				if ( target )
				{
					// switch to new valid target
					SetObserverTarget( target );	
				}
				else
				{
					// let player roam around
					ForceObserverMode( OBS_MODE_ROAMING );
				}
			}
		}
	}
}

void CBliinkPlayer::State_Enter_BLIINK_SURVIVOR()
{	
	SetMoveType( MOVETYPE_WALK );
	RemoveSolidFlags( FSOLID_NOT_SOLID );
    m_Local.m_iHideHUD = 0;
	PhysObjectWake();

	Spawn();
}

void CBliinkPlayer::State_PreThink_BLIINK_SURVIVOR()
{
}

void CBliinkPlayer::State_Enter_BLIINK_SURVIVOR_DEATH_ANIM()
{	
	if ( HasWeapons() )
	{
		// we drop the guns here because weapons that have an area effect and can kill their user
		// will sometimes crash coming back from CBasePlayer::Killed() if they kill their owner because the
		// player class sometimes is freed. It's safer to manipulate the weapons once we know
		// we aren't calling into any of their code anymore through the player pointer.
		PackDeadPlayerItems();
	}

	// Used for a timer.
	m_flDeathTime = gpGlobals->curtime;

	StartObserverMode( OBS_MODE_DEATHCAM );	// go to observer mode

	RemoveEffects( EF_NODRAW );	// still draw player body
}

void CBliinkPlayer::State_PreThink_BLIINK_SURVIVOR_DEATH_ANIM()
{
	
	// If the anim is done playing, go to the next state (waiting for a keypress to 
	// either respawn the guy or put him into observer mode).
	if ( GetFlags() & FL_ONGROUND )
	{
		float flForward = GetAbsVelocity().Length() - 20;
		if (flForward <= 0)
		{
			SetAbsVelocity( vec3_origin );
		}
		else
		{
			Vector vAbsVel = GetAbsVelocity();
			VectorNormalize( vAbsVel );
			vAbsVel *= flForward;
			SetAbsVelocity( vAbsVel );
		}
	}

	if ( gpGlobals->curtime >= (m_flDeathTime + SDK_PLAYER_DEATH_TIME ) )	// let the death cam stay going up to min spawn time.
	{
		m_lifeState = LIFE_DEAD;

		StopAnimation();

		AddEffects( EF_NOINTERP );

		if ( GetMoveType() != MOVETYPE_NONE && (GetFlags() & FL_ONGROUND) )
			SetMoveType( MOVETYPE_NONE );
	}

	//Tony; if we're now dead, and not changing classes, spawn
	if ( m_lifeState == LIFE_DEAD )
	{
		State_Transition( STATE_BLIINK_STALKER_RESPAWN );
	}
}

void CBliinkPlayer::State_Enter_BLIINK_STALKER()
{		
	SetMoveType( MOVETYPE_WALK );
	RemoveSolidFlags( FSOLID_NOT_SOLID );
    m_Local.m_iHideHUD = 0;
	PhysObjectWake();

	Spawn();
}

void CBliinkPlayer::State_PreThink_BLIINK_STALKER()
{	
}

void CBliinkPlayer::State_Enter_BLIINK_STALKER_DEATH_ANIM()
{	
	if ( HasWeapons() )
	{
		// we drop the guns here because weapons that have an area effect and can kill their user
		// will sometimes crash coming back from CBasePlayer::Killed() if they kill their owner because the
		// player class sometimes is freed. It's safer to manipulate the weapons once we know
		// we aren't calling into any of their code anymore through the player pointer.
		PackDeadPlayerItems();
	}

	// Used for a timer.
	m_flDeathTime = gpGlobals->curtime;

	StartObserverMode( OBS_MODE_DEATHCAM );	// go to observer mode

	RemoveEffects( EF_NODRAW );	// still draw player body
}

void CBliinkPlayer::State_PreThink_BLIINK_STALKER_DEATH_ANIM()
{	
	// If the anim is done playing, go to the next state (waiting for a keypress to 
	// either respawn the guy or put him into observer mode).
	if ( GetFlags() & FL_ONGROUND )
	{
		float flForward = GetAbsVelocity().Length() - 20;
		if (flForward <= 0)
		{
			SetAbsVelocity( vec3_origin );
		}
		else
		{
			Vector vAbsVel = GetAbsVelocity();
			VectorNormalize( vAbsVel );
			vAbsVel *= flForward;
			SetAbsVelocity( vAbsVel );
		}
	}

	if ( gpGlobals->curtime >= (m_flDeathTime + SDK_PLAYER_DEATH_TIME ) )	// let the death cam stay going up to min spawn time.
	{
		m_lifeState = LIFE_DEAD;

		StopAnimation();

		AddEffects( EF_NOINTERP );

		if ( GetMoveType() != MOVETYPE_NONE && (GetFlags() & FL_ONGROUND) )
			SetMoveType( MOVETYPE_NONE );
	}

	//Tony; if we're now dead, and not changing classes, spawn
	if ( m_lifeState == LIFE_DEAD )
	{
		State_Transition( STATE_BLIINK_STALKER_RESPAWN );
	}
}

void CBliinkPlayer::State_Enter_BLIINK_STALKER_RESPAWN()
{	
	SetMoveType( MOVETYPE_OBSERVER );
	StartObserverMode( OBS_MODE_ROAMING );
	PhysObjectSleep();
}

void CBliinkPlayer::State_PreThink_BLIINK_STALKER_RESPAWN()
{
	if ( gpGlobals->curtime >= (m_flDeathTime + BLIINK_STALKER_RESPAWN_TIME ) )
	{
		State_Transition( STATE_BLIINK_STALKER );
	}
}

void CBliinkPlayer::State_Enter_BLIINK_VIEW_RESULTS()
{
}

void CBliinkPlayer::State_PreThink_BLIINK_VIEW_RESULTS()
{
}

// --BLIINK STATE FUNCTIONS END--

int CBliinkPlayer::GetPlayerStance()
{

#if defined ( SDK_USE_SPRINTING )
	if (IsSprinting())
		return PINFO_STANCE_SPRINTING;
#endif
	if (m_Local.m_bDucking)
		return PINFO_STANCE_DUCKING;
	else
		return PINFO_STANCE_STANDING;
}

void CBliinkPlayer::NoteWeaponFired( void )
{
	Assert( m_pCurrentCommand );
	if( m_pCurrentCommand )
	{
		m_iLastWeaponFireUsercmd = m_pCurrentCommand->command_number;
	}
}

bool CBliinkPlayer::WantsLagCompensationOnEntity( const CBasePlayer *pPlayer, const CUserCmd *pCmd, const CBitVec<MAX_EDICTS> *pEntityTransmitBits ) const
{
	// No need to lag compensate at all if we're not attacking in this command and
	// we haven't attacked recently.
	if ( !( pCmd->buttons & IN_ATTACK ) && (pCmd->command_number - m_iLastWeaponFireUsercmd > 5) )
		return false;

	return BaseClass::WantsLagCompensationOnEntity( pPlayer, pCmd, pEntityTransmitBits );
}

// Bliink player methods
void CBliinkPlayer::StartGameTransition( void )
{
	if( m_iPlayerState == STATE_BLIINK_WAITING_FOR_PLAYERS )
		State_Transition( STATE_BLIINK_SURVIVOR );
	else
		State_Transition( STATE_BLIINK_SPECTATE );
}

void CBliinkPlayer::EndGameTransition( void )
{
	State_Transition( STATE_BLIINK_VIEW_RESULTS );
}

// Handles team joining
bool CBliinkPlayer::HandleCommand_JoinTeam( int team )
{
	CBliinkGameRules *rules = BliinkGameRules();
	int iOldTeam = GetTeamNumber();

	if( !GetGlobalTeam( team ) )
	{
		Warning("HandleCommand_JoinTeam( %d ) - invalid team.\n", team);
		return false;
	}

	if( team == TEAM_UNASSIGNED )
	{
		team = rules->SelectDefaultTeam();

		if( team == TEAM_UNASSIGNED)
		{
			ClientPrint( this, HUD_PRINTTALK, "#All_Teams_Full" );
			team = TEAM_SPECTATOR;
		}
	}

	if( team == iOldTeam )
		return true;

	if( team == TEAM_SPECTATOR )
	{
		ChangeTeam( TEAM_SPECTATOR );

		return true;
	}

	if( team == BLIINK_TEAM_SURVIVOR )
	{
		ChangeTeam( BLIINK_TEAM_SURVIVOR);

		return true;
	}

	if( team == BLIINK_TEAM_STALKER )
	{
		ChangeTeam( BLIINK_TEAM_STALKER);

		return true;
	}

	return false;
}

// Gives access to the player's inventory.
CBliinkItemInventory &CBliinkPlayer::GetBliinkInventory( void )
{
	return m_Inventory.GetForModify();
}

// Gives access to the player's stats.
CBliinkPlayerStats &CBliinkPlayer::GetBliinkPlayerStats( void )
{
	return m_BliinkStats;
}

// API for adapting current weapon system into system suited for the weapon
// inventory slots.

// Returns the weapon at the specified slot;
CWeaponSDKBase* CBliinkPlayer::Weapon_BliinkGet(int slot)
{
	CBaseCombatWeapon* pWeapon = Weapon_GetSlot( slot );

	return pWeapon ? ToWeaponSDKBase( pWeapon ) : NULL;
}

// Replaces and returns the weapon at the specified slot.
CWeaponSDKBase* CBliinkPlayer::Weapon_BliinkReplace(int slot, CWeaponSDKBase* pReplacement)
{
	pReplacement->SetSlot( slot );

	CBaseCombatWeapon* pWeapon = Weapon_BliinkRemove( slot );

	if( pReplacement )
		Weapon_Equip( pReplacement );

	return pWeapon ? ToWeaponSDKBase( pWeapon ) : NULL;
}

// Removes and returns the weapon at the specified slot.
CWeaponSDKBase* CBliinkPlayer::Weapon_BliinkRemove(int slot)
{
	CBaseCombatWeapon* pWeapon = Weapon_GetSlot(slot);

	if( pWeapon )
	{
		// Dropping + detaching weapon
		Weapon_Drop( pWeapon, NULL, NULL );
	}

	Msg("%d %d\n", GetActiveSDKWeapon(), pWeapon);

	if( GetActiveWeapon() == pWeapon )
		SetActiveWeapon( NULL );

	return pWeapon ? ToWeaponSDKBase( pWeapon ) : NULL;
}

// Swaps the two weapons in the specified slots.
void CBliinkPlayer::Weapon_BliinkSwitch(int slot1, int slot2)
{
	CWeaponSDKBase* pWeapon1 = Weapon_BliinkRemove( slot1 );
	CWeaponSDKBase* pWeapon2 = Weapon_BliinkRemove( slot2 );

	if( pWeapon1 )
	{
		pWeapon1->SetSlot( slot2 );
		Weapon_Equip( pWeapon1 );

		if( GetActiveWeapon() == pWeapon1 )
			SetActiveWeapon( pWeapon1 );
	}

	if( pWeapon2 )
	{
		pWeapon2->SetSlot( slot1 );
		Weapon_Equip( pWeapon2 );

		if( GetActiveWeapon() == pWeapon2 )
			SetActiveWeapon( pWeapon2 );
	}
}

// Checks if the player has the specified weapon.
bool CBliinkPlayer::Weapon_BliinkHasWeapon( CWeaponSDKBase* pWeapon )
{
	if( !pWeapon )
		return false;

	for (int i=0; i < MAX_WEAPONS; i++)
	{
		if ( m_hMyWeapons[i] && m_hMyWeapons[i]->GetWeaponID() == pWeapon->GetWeaponID() )
		{
			return true;
		}
	}

	return false;
}

// Thinking
void CBliinkPlayer::Think()
{
	// If we're a survivor than do our stats thinking
	if( State_Get() == STATE_BLIINK_SURVIVOR )
	{
		m_BliinkStats.Think();
		m_BliinkStats.UpdateHealth();
		m_Inventory.UpdateAmmoCounts();
	}

	SetNextThink(gpGlobals->frametime);
}

// Getting ammo in inventory
int	CBliinkPlayer::GetAmmoCount( int iAmmoIndex ) const
{
	return m_Inventory.GetAmmoClipCount( iAmmoIndex );
}

// Using ammo in inventory
void CBliinkPlayer::RemoveAmmo( int iCount, int iAmmoIndex )
{
	m_Inventory.UseAmmoClip( iAmmoIndex, iCount );
}