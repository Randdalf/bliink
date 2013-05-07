//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose:		Player for HL2W. Contains mainly code for managing, selecting and
//				ordering units.
//
//=============================================================================//

//#include "weapon_hl2mpbasehlmpcombatweapon.h"

#include "cbase.h"
#include "hl2wars/hl2wars_player.h"
#include "hl2wars/in_buttons_rts.h"
#include "hl2wars/rts_tracefilter.h"
#include "in_buttons.h"
#include "hl2wars/rts_point_order.h"
#include "hl2wars/rts_globalresource.h"
#include "hl2wars/rts_mouse_brush.h"
#include "hl2wars/rts_buildings.h"
#include "hl2wars/util_hl2wars.h"
#include "hl2wars/rts_parsedata.h"
#include "hl2wars/rts_mouse_model.h"
#include "hl2wars/util_hl2wars_shared.h"
#include "collisionutils.h"
#include "hl2wars/hl2wars_gamerules.h"

//#ifdef HL2MP 
//	#include "hl2wars/mp/hl2wmp_gamerules.h"
//#endif

#define PI 3.14159265359

extern CBaseEntity				*g_pLastSpawn;

// --------- player spawn 
class CBaseRTSStart : public CPointEntity
{
public:
	DECLARE_CLASS( CBaseRTSStart, CPointEntity );

	DECLARE_DATADESC();

	string_t m_Master;
	int m_iTeamID;

private:
};

BEGIN_DATADESC( CBaseRTSStart )
	DEFINE_KEYFIELD( m_Master, FIELD_STRING, "master" ),
	DEFINE_KEYFIELD( m_iTeamID, FIELD_INTEGER, "teamid" ),
END_DATADESC()


// These are the new entry points to entities. 
LINK_ENTITY_TO_CLASS(info_player_rts,CBaseRTSStart);

// --- end player spawn entity

void ClientKill( edict_t *pEdict );

LINK_ENTITY_TO_CLASS( player, CHL2Wars_Player );
PRECACHE_REGISTER(player);


IMPLEMENT_SERVERCLASS_ST(CHL2Wars_Player, DT_HL2Wars_Player)
	SendPropDataTable(SENDINFO_DT(m_HLWLocal), &REFERENCE_SEND_TABLE(DT_HLWLocal), SendProxy_SendLocalDataTable),

	SendPropInt		(SENDINFO(m_iSlot), 4, SPROP_UNSIGNED ),	// gameroom specific

	// exclude all animation info, we don't care
	SendPropExclude( "DT_BaseAnimating", "m_flPoseParameter" ),	
	SendPropExclude( "DT_BaseFlex", "m_viewtarget" ),			
	SendPropExclude( "DT_BaseAnimating", "m_flPlaybackRate" ),	
	SendPropExclude( "DT_BaseAnimating", "m_nSequence" ),	
	SendPropExclude( "DT_BaseEntity", "m_angRotation" ),
	SendPropExclude( "DT_BaseAnimatingOverlay", "overlay_vars" ),					
	SendPropExclude( "DT_ServerAnimationData" , "m_flCycle" ),
	SendPropExclude( "DT_AnimTimeMustBeFirst" , "m_flAnimTime" ),	
END_SEND_TABLE()

// unit group info
BEGIN_DATADESC_NO_BASE( unitgroup_t )
	DEFINE_ARRAY( m_Group,			FIELD_EHANDLE, MAXSELECTED ),
END_DATADESC()

BEGIN_DATADESC( CHL2Wars_Player ) 
	DEFINE_EMBEDDED( m_HLWLocal ),
	DEFINE_EMBEDDED_ARRAY( m_NPCGroup, 10 ),

	DEFINE_FIELD( m_nRTSButtons,			FIELD_INTEGER ),
	DEFINE_FIELD( m_nRTSButtonsPressed,		FIELD_INTEGER ),
	DEFINE_FIELD( m_vecPickingRayMouse,		FIELD_VECTOR ),
	DEFINE_FIELD( m_nRTSCommands,			FIELD_INTEGER ),
	DEFINE_FIELD( m_nRTSCommands2,			FIELD_INTEGER ),

	DEFINE_FIELD( m_iShiftQueue,			FIELD_INTEGER ),
	DEFINE_FIELD( m_HLWLocal.m_iNumSelected,			FIELD_INTEGER ),
END_DATADESC()

#pragma warning( disable : 4355 )

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
CHL2Wars_Player::CHL2Wars_Player()
{
	SetTeamRTSID(3);		// The player must have a player teamid (and not neutral, like or hate)

	m_iShiftQueue = 0;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
CHL2Wars_Player::~CHL2Wars_Player( void )
{

}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CHL2Wars_Player::UpdateOnRemove( void )
{
	BaseClass::UpdateOnRemove();
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CHL2Wars_Player::Precache( void )
{
	BaseClass::Precache();
}

//-----------------------------------------------------------------------------
// Purpose: Sets HL2 specific defaults.
//-----------------------------------------------------------------------------
void CHL2Wars_Player::Spawn(void)
{
	// request teamid before selecting a spawn point
	if ( HL2WarsRules()->IsGameRoom() == true )	// used to create game, only on the map "room"
	{
		//Msg("Player spawning in game room map, so we can't move \n");
		AddFlag( FL_FROZEN );
	}
	else 
	{
		g_pRTSResource->RequestTeamRTSID( this );
	}

	BaseClass::Spawn();
	m_Local.m_iHideHUD = 0;

	if ( HL2WarsRules()->IsGameRoom() == true )	// used to create game, only on the map "room"
	{
		SetRTSMode( false );
	}
	else 
	{
		SetRTSMode( true );	// true by default
	}

	m_nRTSCommands = 0;
	m_nRTSCommands2 = 0;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CHL2Wars_Player::SharedSpawn()
{
	BaseClass::SharedSpawn();
	SetPlayerNormalMoveType();
}

void CHL2Wars_Player::GiveAllItems( void )
{
	EquipSuit();

	CBasePlayer::GiveAmmo( 255,	"Pistol");
	CBasePlayer::GiveAmmo( 255,	"AR2" );
	CBasePlayer::GiveAmmo( 5,	"AR2AltFire" );
	CBasePlayer::GiveAmmo( 255,	"SMG1");
	CBasePlayer::GiveAmmo( 1,	"smg1_grenade");
	CBasePlayer::GiveAmmo( 255,	"Buckshot");
	CBasePlayer::GiveAmmo( 32,	"357" );
	CBasePlayer::GiveAmmo( 3,	"rpg_round");

	CBasePlayer::GiveAmmo( 1,	"grenade" );
	//CBasePlayer::GiveAmmo( 2,	"slam" );

	CBasePlayer::GiveAmmo( 30,	"SniperRound");

	GiveNamedItem( "weapon_crowbar" );
	GiveNamedItem( "weapon_stunstick" );
	GiveNamedItem( "weapon_pistol" );
	GiveNamedItem( "weapon_357" );

	GiveNamedItem( "weapon_smg1" );
	GiveNamedItem( "weapon_ar2" );
	
	GiveNamedItem( "weapon_shotgun" );
	GiveNamedItem( "weapon_frag" );
	
	GiveNamedItem( "weapon_crossbow" );
	
	GiveNamedItem( "weapon_rpg" );

	//GiveNamedItem( "weapon_slam" );

	GiveNamedItem( "weapon_physcannon" );

	GiveNamedItem( "weapon_sniperrifle" );
	
}

//=========================================================
//=========================================================
extern int gEvilImpulse101;
void CHL2Wars_Player::CheatImpulseCommands( int iImpulse )
{
	switch ( iImpulse )
	{
		case 101:
			{
				gEvilImpulse101		= true;
				GiveNamedItem( "weapon_sniperrifle" );
				gEvilImpulse101		= false;
				break;
			}
	}

	BaseClass::CheatImpulseCommands(iImpulse);
}

void CHL2Wars_Player::GiveDefaultItems( void )
{

}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CHL2Wars_Player::PreThink( void )
{
	BaseClass::PreThink();

	if( !g_pRTSResource|| !g_pRTSResource->IsAlive() )
		return;

	// let the controller do it's stuff
	m_HLWLocal.m_iResources = g_pRTSResource->GetResources( GetTeamRTSID() ); // update resources
	ProcesRTSCommands();
	InvalidateBehaviorButtons();
	UpdateSelectedUnits();

	// When frozen, don't react to mouse buttons
	//if( pPlayer->GetFlags() & FL_FROZEN )
	//	return;

	CheckLeftMouseButton();
	CheckRightMouseButton();
	CheckSpaceBar();

	//Msg("Server picking ray: %f %f %f\n", m_vecPickingRayMouse.x, m_vecPickingRayMouse.y, m_vecPickingRayMouse.z );
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CHL2Wars_Player::PostThink( void )
{
	BaseClass::PostThink();
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CHL2Wars_Player::PlayerDeathThink()
{
	BaseClass::PlayerDeathThink();
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
bool CHL2Wars_Player::ClientCommand( const CCommand &args )
{
	if( !Q_stricmp( args[0], "hl2wars_commands" ) )
	{
		m_nRTSCommands |= atoi( args[1] );
		m_nRTSCommands2 |= atoi( args[2] );

		return true;
	}
	else if( !Q_stricmp( args[0], "hl2wars_clearselection" ) )
	{
		ClearSelection();
		return true;
	}
	else if( !Q_stricmp( args[0], "hl2wars_addunit" ) )
	{
		// because of the lag in multiplayer, the npc might have died and the entity index might have changed.
		// make sure this is an npc.
		CAI_BaseNPC *pNPC = dynamic_cast<CAI_BaseNPC *>(UTIL_EntityByIndex( atoi( args[ 1 ] ) ) ); 
		if( !pNPC )
			return false;

		EmitSoundUnit( pNPC, "select" );
		AddUnit( pNPC );
		return true;
	}
	else if( !Q_stricmp( args[0], "hl2wars_newposition" ) )
	{
		if( args.ArgC() < 4 )
		{
			Warning("CHL2Wars_Player::ClientCommand: Receiving new position from rts player without enough arguments!?\n");
			return true;
		}

		SetAbsOrigin( Vector(atof(args[ 1 ]), atof(args[ 2 ]), atof(args[ 3 ])));
		return true;
	}
	else if( !Q_stricmp( args[0], "hl2wars_killselected" ) )
	{
		switch( m_HLWLocal.m_iSelectionType ) 
		{
			case SELECTION_UNIT:
				{
					KillSelectedUnits();
					break;
				}
			case SELECTION_BUILDING:
				{
					DestroySelectedBuilding();
					break;
				}
			default:
				break;
		}
		
		return true;
	}
	else if( !Q_stricmp( args[0], "hl2wars_orderstop" ) )
	{
		OrderCancelSelectedUnits();
		return true;
	}

	// none? check for hl2wars_us%d and hl2wars_uds%d
	char szbuf[144];
	for(int i = 0; i < MAXUNITSLOTS; i++)
	{
		Q_snprintf( szbuf, sizeof(szbuf), "hl2wars_us%d", i+1 );
		if (!Q_stricmp(args[0], szbuf)) 
		{ 
			m_HLWLocal.m_iHighLightedUnit = i+1;
			return true;
		} 
	}

	for(int i = 0; i < MAXUNITSLOTS; i++)
	{
		Q_snprintf( szbuf, sizeof(szbuf), "hl2wars_uds%d", i+1 );
		if (!Q_stricmp(args[0], szbuf)) 
		{ 
			CAI_BaseNPC *pNPC = GetUnit(i+1);
			ClearSelection();
			AddUnit(pNPC);	
			return true;
		} 
	}

	return BaseClass::ClientCommand( args );
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CHL2Wars_Player::Event_Killed( const CTakeDamageInfo &info )
{
	BaseClass::Event_Killed( info );
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
CBaseEntity* CHL2Wars_Player::EntSelectSpawnPoint( void )
{
	edict_t		*player;

	player = edict();

	CBaseRTSStart *pFirstSpot = dynamic_cast<CBaseRTSStart *>(gEntList.FindEntityByClassname( NULL, "info_player_rts" ));
	CBaseRTSStart *pCurrentSpot = pFirstSpot;

	do 
	{
		if ( pCurrentSpot )
		{
			// check if this is our spot
			if ( pCurrentSpot->m_iTeamID == GetTeamRTSID() )
			{
				// if so, go to pSpot
				g_pLastSpawn = pCurrentSpot;
				return pCurrentSpot;	
			}
		}
		// increment pSpot
		pCurrentSpot = dynamic_cast<CBaseRTSStart *>(gEntList.FindEntityByClassname( pCurrentSpot, "info_player_rts" ));
	} while ( pCurrentSpot != pFirstSpot ); // loop if we're not back to the start

	return BaseClass::EntSelectSpawnPoint();
} 

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CHL2Wars_Player::State_Enter_ACTIVE()
{
	SetPlayerNormalMoveType();
	RemoveSolidFlags( FSOLID_NOT_SOLID );
	m_Local.m_iHideHUD = 0;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CHL2Wars_Player::SetPlayerNormalMoveType()
{
	if( m_Local.m_bRTSMode ) 
		SetMoveType( MOVETYPE_RTS );
	else
		SetMoveType( MOVETYPE_WALK );
}

//-----------------------------------------------------------------------------
// Purpose: Player reacts to bumping a weapon. 
// Input  : pWeapon - the weapon that the player bumped into.
// Output : Returns true if player picked up the weapon
//-----------------------------------------------------------------------------
bool CHL2Wars_Player::BumpWeapon( CBaseCombatWeapon *pWeapon )
{
	if( m_Local.m_bRTSMode )	// don't pick up weapons in rts mode
		return false;

	return BaseClass::BumpWeapon( pWeapon );
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CHL2Wars_Player::SetRTSMode( bool mode )
{
	m_Local.m_bRTSMode = mode;
	if( m_Local.m_bRTSMode )
	{		
		//m_afPhysicsFlags |= PFLAG_OBSERVER;
		//AddEFlags( EFL_NOCLIP_ACTIVE );
		m_Local.m_iHideHUD &= ~HIDEHUD_RTS;
		SetMoveType( MOVETYPE_RTS );	// move like a rts player
		m_Local.m_iHideHUD |= HIDEHUD_CROSSHAIR;	// hide the crosshair
		m_bHasSuit = IsSuitEquipped();	// remove normal suit, remember if the player had the suit
		RemoveSuit();
		//SetCollisionGroup( COLLISION_GROUP_HL2WARSPLAYER );	// set the collision group: the player should collide only with the world.
		SetGroundEntity( (CBaseEntity *)NULL );
		AddFlag( FL_FLY );
		m_takedamage = DAMAGE_NO;	// take no damage
		AddEffects( EF_NODRAW );	// become invisible

		// holster weapon
		if ( GetActiveWeapon() )
			GetActiveWeapon()->Holster();

		m_afPhysicsFlags |= PFLAG_OBSERVER;
		RemoveFlag( FL_DUCKING );
		AddSolidFlags( FSOLID_NOT_SOLID );
		//m_iHealth = 1;
		//m_lifeState = LIFE_DEAD; // Can't be dead, otherwise movement doesn't work right.
		//pl.deadflag = true;
	}
	else
	{ 
		ClearSelection();	// clear any selected units
		//RemoveEFlags( EFL_NOCLIP_ACTIVE );
		//m_afPhysicsFlags &= ~PFLAG_OBSERVER;
		m_Local.m_iHideHUD |= HIDEHUD_RTS;	// hide all rts hud elements
		SetMoveType( MOVETYPE_WALK );	// we will need to walk again :(
		RemoveFlag( FL_FLY );			// nope, we don't fly. No idea what this flag exactly does.
		m_takedamage = DAMAGE_YES;		// become a mortal person again.	
		m_Local.m_iHideHUD &= ~HIDEHUD_CROSSHAIR;	// unhide the crosshair
		SetCollisionGroup( COLLISION_GROUP_PLAYER );	// normal collision for player

		// did we had the suit?
		if( m_bHasSuit )
			EquipSuit();

		RemoveEffects( EF_NODRAW );	// become visible again.

		m_afPhysicsFlags &= ~PFLAG_OBSERVER;
	}
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CHL2Wars_Player::SetVecPickingRay( Vector vecPickingRayMouse )
{
	m_vecPickingRayMouse = vecPickingRayMouse;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
bool CHL2Wars_Player::IsReady()
{
	return m_bReady;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CHL2Wars_Player::SetReady( bool bReady )
{
	m_bReady = bReady;
}


// ##################################################################################
//	>> Control stuff follows here
// ##################################################################################
//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CHL2Wars_Player::ProcesRTSCommands()
{
	// ability commands
	if( m_nRTSCommands & IN_ABILITY_1 ) {
		ProcesAbilityCommand( 1 );
	}
	else if( m_nRTSCommands & IN_ABILITY_2 ) {
		ProcesAbilityCommand( 2 );
	}
	else if( m_nRTSCommands & IN_ABILITY_3 ) {
		ProcesAbilityCommand( 3 );
	}
	else if( m_nRTSCommands & IN_ABILITY_4 ) {
		ProcesAbilityCommand( 4 );
	}
	else if( m_nRTSCommands & IN_ABILITY_5 ) {
		ProcesAbilityCommand( 5 );
	}
	else if( m_nRTSCommands & IN_ABILITY_6 ) {
		ProcesAbilityCommand( 6 );
	}
	else if( m_nRTSCommands & IN_ABILITY_7 ) {
		ProcesAbilityCommand( 7 );
	}
	else if( m_nRTSCommands & IN_ABILITY_8 ) {
		ProcesAbilityCommand( 8 );
	}
	else if( m_nRTSCommands & IN_ABILITY_9 ) {
		ProcesAbilityCommand( 9 );
	}
	else if( m_nRTSCommands & IN_ABILITY_10 ) {
		ProcesAbilityCommand( 10 );
	}
	else if( m_nRTSCommands & IN_ABILITY_11 ) {
		ProcesAbilityCommand( 11 );
	}
	else if( m_nRTSCommands & IN_ABILITY_12 ) {
		ProcesAbilityCommand( 12 );
	}

	// level up, and level down commands
	if( m_nRTSCommands2 & IN_LEVELUP ) {
		m_HLWLocal.m_iLevelRTS += 1;
	}
	else if( m_nRTSCommands2 & IN_LEVELDOWN ) {
		m_HLWLocal.m_iLevelRTS -= 1;
	}	

	//  select a group
	if( m_nRTSCommands & IN_SELECTGROUP_1 ) {
		if( m_nButtons & IN_DUCK )
			AddGroup( 1 );
		else 
            SelectGroup( 1 );
	}
	else if( m_nRTSCommands & IN_SELECTGROUP_2 ) {
		if( m_nButtons & IN_DUCK )
			AddGroup( 2 );
		else 
            SelectGroup( 2 );
	}
	else if( m_nRTSCommands & IN_SELECTGROUP_3 ) {
		if( m_nButtons & IN_DUCK )
			AddGroup( 3 );
		else 
            SelectGroup( 3 );
	}
	else if( m_nRTSCommands & IN_SELECTGROUP_4 ) {
		if( m_nButtons & IN_DUCK )
			AddGroup( 4 );
		else 
            SelectGroup( 4 );
	}
	else if( m_nRTSCommands & IN_SELECTGROUP_5 ) {
		if( m_nButtons & IN_DUCK )
			AddGroup( 5 );
		else 
            SelectGroup( 5 );
	}
	else if( m_nRTSCommands & IN_SELECTGROUP_6 ) {
		if( m_nButtons & IN_DUCK )
			AddGroup( 6 );
		else 
            SelectGroup( 6 );
	}
	else if( m_nRTSCommands & IN_SELECTGROUP_7 ) {
		if( m_nButtons & IN_DUCK )
			AddGroup( 7 );
		else 
            SelectGroup( 7 );
	}
	else if( m_nRTSCommands & IN_SELECTGROUP_8 ) {
		if( m_nButtons & IN_DUCK )
			AddGroup( 8 );
		else 
            SelectGroup( 8 );
	}
	else if( m_nRTSCommands & IN_SELECTGROUP_9 ) {
		if( m_nButtons & IN_DUCK )
			AddGroup( 9 );
		else 
            SelectGroup( 9 );
	}
	else if( m_nRTSCommands & IN_SELECTGROUP_10 ) {
		if( m_nButtons & IN_DUCK )
			AddGroup( 10 );
		else 
            SelectGroup( 10 );
	}

	// change behavior of selected units
	if( m_nRTSCommands2 & IN_BEHAVIOR_NORM )
	{
		SetBehaviorSelected( BEHAVIOR_NORMAL );
	}
	else if( m_nRTSCommands2 & IN_BEHAVIOR_AGG )
	{	
		SetBehaviorSelected( BEHAVIOR_AGGRESSIVE );
	}

	// building queue buttons
	if( m_nRTSCommands2 & IN_QUEUE_1 ) {
		ProcesQueueCommand( 0 );
	}
	else if( m_nRTSCommands2 & IN_QUEUE_2 ) {
		ProcesQueueCommand( 1 );
	}	
	else if( m_nRTSCommands2 & IN_QUEUE_3 ) {
		ProcesQueueCommand( 2 );
	}	
	else if( m_nRTSCommands2 & IN_QUEUE_4 ) {
		ProcesQueueCommand( 3 );
	}	
	else if( m_nRTSCommands2 & IN_QUEUE_5 ) {
		ProcesQueueCommand( 4 );
	}	
	else if( m_nRTSCommands2 & IN_CYCLEQUEUE_1 ) {
		if( m_HLWLocal.m_hSelected->IsRTSBrush() )
		{
			CBuildingBrush *pBuilding = (CBuildingBrush *)m_HLWLocal.m_hSelected.Get();
			if( pBuilding )
			{
				if( m_iShiftQueue + QUEUE_MAX < pBuilding->CountQueue()  )
				{
					m_iShiftQueue++;
					m_HLWLocal.m_bShowProgressQueue = false;
				}
			}
		}
		else if(m_HLWLocal.m_hSelected->IsRTSModel())
		{
			CBaseBuildingModel *pBuildingM = (CBaseBuildingModel *)m_HLWLocal.m_hSelected.Get();
			if( pBuildingM && pBuildingM->IsAlive() )
			{
				if( m_iShiftQueue + QUEUE_MAX < pBuildingM->CountQueue()  )
				{
					m_iShiftQueue++;
					m_HLWLocal.m_bShowProgressQueue = false;
				}
			}
		}
	}	
	else if( m_nRTSCommands2 & IN_CYCLEQUEUE_2 ) {
		if( m_iShiftQueue > 0 )
			m_iShiftQueue--;

		if( m_iShiftQueue == 0 )
			m_HLWLocal.m_bShowProgressQueue = true;
	}	

	// clear all commands, we processed them
	m_nRTSCommands = 0;
	m_nRTSCommands2 = 0;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHL2Wars_Player::ProcesAbilityCommand( int ability_button )
{
	switch( m_HLWLocal.m_iSelectionType ) 
	{
		case SELECTION_UNIT:
			{
				m_HLWLocal.m_iSelectedAbility = ability_button;
				break;
			}
		case SELECTION_BUILDING:
			{
				if( m_HLWLocal.m_hSelected.Get() )
				{
					if( m_HLWLocal.m_hSelected.Get()->IsRTSBrush() )
					{
						CBuildingBrush *pBuilding = (CBuildingBrush *)m_HLWLocal.m_hSelected.Get();
						if( pBuilding && ability_button > 0 )
						{
							if( m_afButtonPressed & IN_SPEED )
							{
								for( int i = 0; i < 5; i++ )
									pBuilding->AddToQueue( ability_button, -1 );
							}
							else
							{
								pBuilding->AddToQueue( ability_button, -1 );
							}
						}
					}
					else if( m_HLWLocal.m_hSelected.Get()->IsRTSModel() )
					{
						CBaseBuildingModel *pBuildingM = (CBaseBuildingModel *)m_HLWLocal.m_hSelected.Get();
						if( pBuildingM && pBuildingM->IsAlive() && ability_button > 0 )
						{
							if( m_afButtonPressed & IN_SPEED )
							{
								for( int i = 0; i < 5; i++ )
									pBuildingM->AddToQueue( ability_button, -1 );
							}
							else
							{
								pBuildingM->AddToQueue( ability_button, -1 );
							}
						}
					}
				}
				break;
			}
		default:
			m_HLWLocal.m_iSelectedAbility = ability_button;
			break;
	}
}

//-----------------------------------------------------------------------------
// Purpose: Remove a unit from the queue
//-----------------------------------------------------------------------------
void CHL2Wars_Player::ProcesQueueCommand( int queue_button )
{
	if( !m_HLWLocal.m_hSelected.Get() )
		return;

	if( m_HLWLocal.m_hSelected.Get()->IsRTSBrush() )
	{
		CBuildingBrush *pBuilding = (CBuildingBrush *)m_HLWLocal.m_hSelected.Get();
		if( pBuilding )
		{
			pBuilding->RemoveFromQueue( queue_button );
		}
	}
	else if( m_HLWLocal.m_hSelected.Get()->IsRTSModel() )
	{
		CBaseBuildingModel *pBuildingM = (CBaseBuildingModel *)m_HLWLocal.m_hSelected.Get();
		if( pBuildingM&& pBuildingM->IsAlive() )
		{
			pBuildingM->RemoveFromQueue( queue_button );
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHL2Wars_Player::SetBehaviorSelected( int behavior )
{
	for( int i = 0; i < m_HLWLocal.m_iNumSelected; i++ )
	{
		GetUnit( i )->SetBehavior( behavior );

		// make the units searc a cover spot when we are in defense mode
		if( behavior == BEHAVIOR_NORMAL  && ( !GetUnit( i )->GetCurrentOrder() || 
			GetUnit( i )->GetCurrentOrder()->GetOrderType() == ORDER_MOVE ) )
		{
			// first create the target	
			CRTSPointOrder *pTarget = (CRTSPointOrder *)CreateEntityByName( "rts_point_order" );	
			if( pTarget ) {
				// let the order float a little above the ground
				pTarget->SetAbsOrigin( GetUnit( i )->GetAbsOrigin() );   
				pTarget->Spawn(); 
				pTarget->SetNPC( GetUnit( i ) );
				pTarget->SetOrderType( ORDER_MOVE, true );	
				pTarget->Start();
				GetUnit(i)->ClearAllOrders();
				GetUnit(i)->QueueNewOrder(pTarget);
			}	  		
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CHL2Wars_Player::InvalidateBehaviorButtons()
{
	m_HLWLocal.m_nBehaviorButtonsState = 0;	// clear old
	for( int i = 0; i < m_HLWLocal.m_iNumSelected; i++ )
	{
		if( GetUnit(i) && GetUnit(i)->IsAlive() )
		{
			if( GetUnit( i )->GetBehavior() == BEHAVIOR_NORMAL )
				m_HLWLocal.m_nBehaviorButtonsState |= IN_BUTTON_NORMAL;
			else if( GetUnit( i )->GetBehavior() == BEHAVIOR_AGGRESSIVE )
				m_HLWLocal.m_nBehaviorButtonsState |= IN_BUTTON_AGGRESSIVE;
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose: Proces the mouse inputs, like select a unit, move, etc
//			FIXME: double click doesn't works
//-----------------------------------------------------------------------------
void CHL2Wars_Player::CheckLeftMouseButton() 
{
	// handles mouse button left pressed and released
	if(( ( m_nRTSButtons & IN_MOUSELEFT) || (m_nRTSButtons & IN_MOUSELEFTDOUBLE) ) && !( m_nRTSButtonsPressed & IN_MOUSELEFT ) ) {
		m_nRTSButtonsPressed |= IN_MOUSELEFT;
		if( m_nRTSButtons & IN_MOUSELEFTDOUBLE )
			m_nRTSButtonsPressed |= IN_MOUSELEFTDOUBLE;

		// copy vector to trace the movement of the mouse on release of the mouse button
		VectorCopy(RetrieveGroundPos(), vecMouseRayLeftPressed);
	}
	else if( !(m_nRTSButtons & IN_MOUSELEFT) && ( m_nRTSButtonsPressed & IN_MOUSELEFT ) ) {	
		VectorCopy(RetrieveGroundPos(), vecMouseRayLeftReleased );

        Selection();

		m_nRTSButtonsPressed &= ~IN_MOUSELEFT;
		m_nRTSButtonsPressed &= ~IN_MOUSELEFTDOUBLE;
	}
}

//-----------------------------------------------------------------------------
// Purpose: Proces the mouse inputs, like select a unit, move, etc
//-----------------------------------------------------------------------------
void CHL2Wars_Player::CheckRightMouseButton() 
{
	// handles mouse button right pressed and released
	if( ( (m_nRTSButtons & IN_MOUSERIGHT) || (m_nRTSButtons & IN_MOUSERIGHTDOUBLE) ) && !(m_nRTSButtonsPressed & IN_MOUSERIGHT)) {
		m_nRTSButtonsPressed |= IN_MOUSERIGHT;
		if( m_nRTSButtons & IN_MOUSERIGHTDOUBLE )
			m_nRTSButtonsPressed |= IN_MOUSERIGHTDOUBLE;

		// copy vector to trace the movement of the mouse on release of the mouse button
		VectorCopy(RetrieveGroundPos(), vecMouseRayRightPressed);
	}
	else if( !(m_nRTSButtons & IN_MOUSERIGHT) && (m_nRTSButtonsPressed & IN_MOUSERIGHT) ) {
		VectorCopy(RetrieveGroundPos(), vecMouseRayRightReleased );

		// determine the kind of order we give. For buildings we set a rally point, but for units where the move to.
		switch( m_HLWLocal.m_iSelectionType ) {
			case SELECTION_UNIT:
				Order();
				break;
			case SELECTION_BUILDING:
				BuildOrder();
				break;
			default:
				Order();
				break;
		}

		m_nRTSButtonsPressed &= ~IN_MOUSERIGHT;
		m_nRTSButtonsPressed &= ~IN_MOUSERIGHTDOUBLE;
	}
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CHL2Wars_Player::CheckSpaceBar( void )
{
	// when having space pressed, we need to go to the units of our selection
	if (m_nButtons & IN_JUMP)
	{
		Vector origin = Vector();
		// determine the kind of order we give. For buildings we set a rally point, but for units where the move to.
		switch( m_HLWLocal.m_iSelectionType ) {
			case SELECTION_UNIT:
				{
					if( m_HLWLocal.m_iNumSelected <= 0 || m_HLWLocal.m_iNumSelected >= MAXSELECTED )
						return; 

					for(int i = 0; i < m_HLWLocal.m_iNumSelected; i++) 
					{		
						origin.x += GetUnit(i)->GetAbsOrigin().x;
						origin.y += GetUnit(i)->GetAbsOrigin().y;
						origin.z += GetUnit(i)->GetAbsOrigin().z;
					}
					origin.x /= m_HLWLocal.m_iNumSelected;
					origin.y /= m_HLWLocal.m_iNumSelected;
					origin.z /= m_HLWLocal.m_iNumSelected;
					break;
				}
			case SELECTION_BUILDING:
				{
					Vector origin = m_HLWLocal.m_hSelected.Get()->GetAbsOrigin();
					break;
				}
			default:
				return;
				break;
		}		

		// calculate an intersection (I assume there is a better way then this?)
		Ray_t ray1, ray2;
		float s, t;
		QAngle angle, angle2;
		Vector vDir;
		VectorAngles((origin-GetAbsOrigin()), angle2);
		angle = GetAbsAngles();
		angle[YAW] = angle2[YAW];
		AngleVectors(angle, &vDir);
		vDir.Negate();
		ray1.Init(Vector(origin.x, origin.y, GetAbsOrigin().z), GetAbsOrigin());
		ray2.Init(origin, origin + vDir * MAX_TRACE_LENGTH);

		//debugoverlay->AddLineOverlay( Vector(origin.x, origin.y, GetAbsOrigin().z), GetAbsOrigin(), 100, 55, 255, false, 5 ); 
		//debugoverlay->AddLineOverlay( origin, origin + vDir * 8000, 100, 255, 255, false, 5 ); 

		IntersectRayWithRay(ray1, ray2, s, t);
		//Msg("1. s: %f, t: %f\n", s, t);
		//t = clamp( t, 0, 1 );
		//s = clamp( s, 0, 1 );
		s = s / ray1.m_Delta.Length();
		t = t / ray2.m_Delta.Length();
		//Msg("2. s: %f, t: %f\n", s, t);
		if(t > 0)
			//Msg("CHL2Wars_Player::CheckSpaceBar: %f %f %f\n", (ray1.m_Start+ray1.m_Delta*s).x,
			//	(ray1.m_Start+ray1.m_Delta*s).y, (ray1.m_Start+ray1.m_Delta*s).z);
			SetAbsOrigin(ray1.m_Start+ray1.m_Delta*s);
		else
		{
			DevMsg(2, "CHL2Wars_Player::CheckSpaceBar: Intersection failed\n");
			SetAbsOrigin(Vector(origin.x, origin.y, GetAbsOrigin().z));
		}

	}
}

//-----------------------------------------------------------------------------
// Purpose: Handles selection on left mouse button release
//-----------------------------------------------------------------------------
void CHL2Wars_Player::Selection( void ) {	
	// when the box points are to small for a selectionpoint, we use a ray
	if( abs(vecMouseRayLeftReleased.x - vecMouseRayLeftPressed.x) < 10 &&
		abs(vecMouseRayLeftReleased.y - vecMouseRayLeftPressed.y) < 10) {
		  SelectRay();
	}
}

//-----------------------------------------------------------------------------
// Purpose: Uses a ray to select a npc or activate a rts brush
//-----------------------------------------------------------------------------
void CHL2Wars_Player::SelectRay( void )
{
	// if we have a selected ability, cancel it on this button.
	if( m_HLWLocal.m_iSelectedAbility != 0 )
	{
		m_HLWLocal.m_iSelectedAbility = 0;
		return;
	}

	// Check what we catch
	CAI_BaseNPC	*pTarget;	
	CBaseEntity *pEnt = GetEntityMouse();
	if( !pEnt )
		return;

	// npc
	if( ( pTarget = pEnt->MyNPCPointer() ) != NULL ) {
		// Does the player owns the npc?
		if( GetTeamRTSID() != pTarget->GetTeamRTSID() ) {
			return;
		}
		// do we have the duck button pressed?
		else if( m_nButtons & IN_DUCK) {
			int index;

			// if already selected, deselect
			if( (index = isAlreadySelected( pTarget )) >= 0 ) {
				RemoveUnit( index );
			}
			// else find a new place for the unit
			else {
				AddUnit( pTarget );
			}
		}	
		// in this case, we might be selecting all units of the same type
		else if( m_nRTSButtons & IN_MOUSELEFTDOUBLE ) 
		{
			// do nothing
			return;
		}
		// duck button not pressed, clear selection, add unit
		else {        
			ClearSelection();		      
			AddUnit( pTarget );
			EmitSoundUnit( pTarget, "select" );
		}	    
	}
	// rts brush
	else if( pEnt->IsRTSBrush() ) {
        CMouseRTSBrush *pRTSBrush = assert_cast<CMouseRTSBrush *>( pEnt );
		// make the brush sends it output stuff first
		if( m_nRTSButtons & IN_MOUSELEFTDOUBLE ) {			
		    pRTSBrush->OnClickLeftDouble( this );
		}		
		else {			 				
			pRTSBrush->OnClickLeft( this );
		}
	}
	else if( pEnt->IsRTSModel() ) {
        CMouseRTSModel *pRTSModel = assert_cast<CMouseRTSModel *>( pEnt );
		// make the brush sends it output stuff first
		if( m_nRTSButtons & IN_MOUSELEFTDOUBLE ) {			
		    pRTSModel->OnClickLeftDouble( this );
		}		
		else {			 				
			pRTSModel->OnClickLeft( this );
		}
	}
	else {
		ClearSelection();
	}
}

//-----------------------------------------------------------------------------
// Purpose: Clear selected units with start point 'start' in the selected array
//-----------------------------------------------------------------------------
void CHL2Wars_Player::ClearSelection() 
{
	if( m_HLWLocal.m_iSelectionType == SELECTION_BUILDING ) {
		m_HLWLocal.m_hSelected = NULL;
		m_HLWLocal.m_iSelectionType = SELECTION_UNIT;
	}
	else {
		// because we clear everything, we don't need to worry about resorting the array :)
		int selected = m_HLWLocal.m_iNumSelected;
		for(int i = 0; i < selected; i++) {
			if( GetUnit(i) ) {
				m_HLWLocal.m_hSelectedUnits.Set( i, NULL); // remove from selection array
				m_HLWLocal.m_iNumSelected--;
			}
		}

		m_HLWLocal.m_iHighLightedUnit = -1;
	}
}

//-----------------------------------------------------------------------------
// Purpose: Orders
//-----------------------------------------------------------------------------
void CHL2Wars_Player::Order()
{
	// first we check what kind of order we give. In the functions we will check what behavior the npc has
	// for the order.
	CAI_BaseNPC	*pTarget = NULL;	
	CBaseEntity *pEnt = GetEntityMouse();
	if( !pEnt )
		return;

	// npc
	else if( ( pTarget = pEnt->MyNPCPointer() ) != NULL ) {
		if( m_HLWLocal.m_iSelectedAbility == 0 ) {
			if( m_nButtons & IN_DUCK )	// control pressed, attack no matter what
				AttackOrder( pTarget );
			else if( pTarget && pTarget->IsAlive() && IsValidAttackTarget( pTarget->GetTeamRTSID() ) )
				AttackOrder( pTarget );
			else 
				MoveOrder();
			}
		else {
			AbilityOrder( pTarget );
		}
	}
	// rts brush
	else if( pEnt->IsRTSBrush() ) {
        CMouseRTSBrush *pRTSBrush = assert_cast<CMouseRTSBrush *>( pEnt );

		if( m_nRTSButtons & IN_MOUSERIGHTDOUBLE ) {			
		    pRTSBrush->OnClickRightDouble( this );
		}		
		else {			 				
			pRTSBrush->OnClickRight( this );
		}		
	}
	else if( pEnt->IsRTSModel() ) {
        CMouseRTSModel *pRTSModel = assert_cast<CMouseRTSModel *>( pEnt );

		if( m_nRTSButtons & IN_MOUSERIGHTDOUBLE ) {			
		    pRTSModel->OnClickRightDouble( this );
		}		
		else {			 				
			pRTSModel->OnClickRight( this );
		}	

		// if the brush type is a building, we can select it
		if( pRTSModel->GetBrushType() == MOUSEBRUSH_BUILDING ) {
			CBaseBuildingModel *pBuildingM = dynamic_cast<CBaseBuildingModel *>(pRTSModel); 
			if( pBuildingM&& pBuildingM->IsAlive() )
			{
				if( IsValidAttackTarget( pBuildingM->GetOwnerShip() ) )
					AttackGroundOrder( pEnt );
				else if( m_nButtons & IN_DUCK )
					AttackGroundOrder( pEnt );
				else if( m_HLWLocal.m_iSelectedAbility != 0 )
					AbilityOrder( pEnt );
			}
		}
		else
		{
			if( m_HLWLocal.m_iSelectedAbility != 0 )
				AbilityOrder( pEnt );
		}
	}
	else if( m_nButtons & IN_DUCK  ) {
		AttackGroundOrder( pEnt );
	}
	// default to move order
	else {
		if( m_HLWLocal.m_iSelectedAbility == 0 )
			MoveOrder();
		else
		{
			AbilityOrder( pEnt );
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
bool CHL2Wars_Player::IsValidAttackTarget( int team_id )
{
	if( GetTeamRTSID() == team_id )
		return false;
	else if( team_id == TEAMRTS_NEUTRAL )
		return false;
	else if( g_RelationshipsRTS[GetTeamRTSID()][team_id] != D_HT )
		return false;
	else
		return true;

}

//-----------------------------------------------------------------------------
// Purpose: Move Order
//-----------------------------------------------------------------------------
void CHL2Wars_Player::MoveOrder()
{    
	float radius = 32.0f;
	for(int i = 0; i < m_HLWLocal.m_iNumSelected; i++) 
	{		
		EmitSoundUnit( GetUnit(i), "move" );

		radius += 32.0f;
		MoveOrderNormal( GetUnit(i), vecMouseRayRightPressed, radius );
	}	
}

//-----------------------------------------------------------------------------
// Purpose: Create a move order.
//-----------------------------------------------------------------------------
void CHL2Wars_Player::MoveOrderNormal( CAI_BaseNPC *pNPC, Vector origin, float radius )
{    
	// first create the target	
	CRTSPointOrder *pTarget = (CRTSPointOrder *)CreateEntityByName( "rts_point_order" );	
	if( pTarget ) {
		// find a spot
		origin[2] += 24.0f;
		Vector result;
		if( UTIL_CheckForOrderInSphere( origin, 16.0f ) )	
		    UTIL_FindSpotForOrderInRadius( &result, origin, radius );
		else
			VectorCopy( origin, result );

		// let the order float a little above the ground
		//result[2] += 16.0f;  

		pTarget->SetAbsOrigin( result );   
		pTarget->Spawn(); 
		pTarget->SetNPC( pNPC );
		CheckArrivalDirection( pTarget );
		pTarget->SetOrderType( ORDER_MOVE, true );	
		pTarget->Start();

		if( !(m_nButtons & IN_SPEED) )
			pNPC->ClearAllOrders();

		pNPC->QueueNewOrder(pTarget);
	}	  
}

//-----------------------------------------------------------------------------
// Purpose: AttackOrder
//-----------------------------------------------------------------------------
void CHL2Wars_Player::AttackOrder( CAI_BaseNPC *pEnemy )
{		
	for(int i = 0; i < m_HLWLocal.m_iNumSelected; i++) {		
		// create a new order
		CRTSPointOrder *pTarget = (CRTSPointOrder *)CreateEntityByName( "rts_point_order" );	
		if( !pTarget ) {
			return;
		}

		pTarget->SetAbsOrigin( pEnemy->GetAbsOrigin() );   
		pTarget->Spawn(); 
		pTarget->SetNPC( GetUnit(i) );
		pTarget->SetTarget( pEnemy );				
		pTarget->SetOrderType( ORDER_ATTACK, true );	
		pTarget->Start();

		if( !(m_nButtons & IN_SPEED) )
			GetUnit(i)->ClearAllOrders();

		GetUnit(i)->QueueNewOrder(pTarget);

		EmitSoundUnit( GetUnit(i), "attack" );
	}
}

//-----------------------------------------------------------------------------
// Purpose: Let the units attack the ground.
//-----------------------------------------------------------------------------
void CHL2Wars_Player::AttackGroundOrder( CBaseEntity *pEnt ) 
{
	for(int i = 0; i < m_HLWLocal.m_iNumSelected; i++) {		
		// create a new order
		CRTSPointOrder *pTarget = (CRTSPointOrder *)CreateEntityByName( "rts_point_order" );	
		if( !pTarget )
			return;

		pTarget->SetAbsOrigin( vecMouseRayRightPressed + Vector(0, 0, 16.0f ) );   
		pTarget->Spawn(); 
		pTarget->SetNPC( GetUnit(i) );
		if( !pEnt->IsWorld() )
			pTarget->SetTarget( pEnt );	

		pTarget->SetOrderType( ORDER_GROUNDATTACK, true );
		pTarget->Start();

		if( !(m_nButtons & IN_SPEED) )
			GetUnit(i)->ClearAllOrders();

		GetUnit(i)->QueueNewOrder(pTarget);

		EmitSoundUnit( GetUnit(i), "attack" );
	}
}

//-----------------------------------------------------------------------------
// Purpose: Ability order
//-----------------------------------------------------------------------------
void CHL2Wars_Player::AbilityOrder( CBaseEntity *pTarget ) 
{
	Vector mins, maxs;
	int selected_ability = m_HLWLocal.m_iSelectedAbility;
	m_HLWLocal.m_iSelectedAbility = 0;

	// check if the unit is valid
	if( m_HLWLocal.m_iHighLightedUnit >= m_HLWLocal.m_iNumSelected || m_HLWLocal.m_iHighLightedUnit < 0 )
		return;

	CAI_BaseNPC *pNPC = GetUnit(m_HLWLocal.m_iHighLightedUnit);
	if( !pNPC )
		return;

	// can we do this ability? ( ain't it recharging?)
	if( !pNPC->CanDoAbility( selected_ability ) )
		return;

	FileUnitInfo_t *pFUI = GetFileUnitInfoFromHandle( LookupUnitInfoSlot( STRING(pNPC->GetUnitType() ) ) );
	if( !pFUI )
		return;

	FileAbilityInfo_t *pFAI = GetFileAbilityInfoFromHandle( pFUI->m_iAbilities[selected_ability-1] );
	if( !pFAI )
		return;

	if( !g_pRTSResource->IsAbilityAvailable( GetTeamRTSID(), pFUI->m_iAbilities[selected_ability-1] ) )
	{
		Msg("We are sorry, we can't do this ability!\n");
		return;
	}

	// can we place it?
	if( pFAI->m_iVisualHelper == 1 )
	{
		QAngle angle;
		int iModelIndex = modelinfo->GetModelIndex(pFAI->m_szModel);
		if( !iModelIndex )
			return;

		if( (vecMouseRayRightPressed - vecMouseRayRightReleased).Length2D() > 20 )
			angle = CalculateArrivalDirection();
		else
			angle = QAngle(0, 0, 0);

		modelinfo->GetModelRenderBounds( modelinfo->GetModel(iModelIndex), mins, maxs );
		if( !UTIL_ValidBuildingPosition( vecMouseRayRightPressed + pFAI->m_vOffSet, angle, mins, maxs, pFAI->m_fTolerance, false, GetTeamRTSID() ) )
			return;
	}

	// can we pay it?
	if( pFAI->m_iCost > g_pRTSResource->GetResources( GetTeamRTSID() ) )
	{
		UTIL_HudStrategyText( (CBasePlayer *)this, "#HLW_NOTENOUGHRESOURCES", S_RED );
		return;
	}

	char ability_data[MAX_PATH];
	Q_snprintf( ability_data, sizeof( ability_data ), "ability_%d", selected_ability );
	EmitSoundUnit( pNPC, ability_data );
	//EmitSoundAbility( pFAI, "activate" );

	// create a new order
	CRTSPointOrder *pOrder = (CRTSPointOrder *)CreateEntityByName( "rts_point_order" );	
	if( !pOrder )
		return;

	pOrder->SetAbilityRange( pFAI->m_iMinRange, pFAI->m_iMaxRange);

	if( pFAI->m_iVisualHelper == 1 )
		pOrder->SetAbilityModelMinMax( mins, maxs );	

	pOrder->SetAbsOrigin( vecMouseRayRightPressed );   
	pOrder->Spawn(); 
	pOrder->SetNPC( pNPC );

	if( pFAI->m_bRotate )
		CheckArrivalDirection( pOrder );

	if( pTarget )
	{
		if( !pTarget->IsWorld() )
			pOrder->SetTarget( pTarget );
	}

	if( pFAI->m_iAbilityType == ABILITY_BUILDING )
	{
		pOrder->SetTarget( UTIL_PlaceBuilding( pFUI->m_iAbilities[selected_ability-1], pOrder->GetAbsOrigin(),
			pOrder->GetArrivalDirection(), GetTeamRTSID(), false ) );
	}
								
	pOrder->SetOrderType( ORDER_DO_ABILITY, true );

	pOrder->SetAbility( pFAI->m_iAbilityType );
	pOrder->SetAbilityButton( selected_ability );
	pOrder->Start();

	if( !(m_nButtons & IN_SPEED) )
		pNPC->ClearAllOrders();

	pNPC->QueueNewOrder(pOrder);
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CHL2Wars_Player::BuildOrder( )
{
	if( m_HLWLocal.m_hSelected.Get() )
	{
		if( m_HLWLocal.m_hSelected.Get()->IsRTSBrush() )
		{
			CBuildingBrush *pBuilding = dynamic_cast<CBuildingBrush *>(m_HLWLocal.m_hSelected.Get());
			if( pBuilding )
				pBuilding->SetRallyPoint( vecMouseRayRightPressed );
		}
		else if( m_HLWLocal.m_hSelected.Get()->IsRTSModel() )
		{
			CBaseBuildingModel *pBuildingM = (CBaseBuildingModel *)m_HLWLocal.m_hSelected.Get();
			if( pBuildingM&& pBuildingM->IsAlive() )
				pBuildingM->OnSelectedRightClick( vecMouseRayRightPressed );
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
int CHL2Wars_Player::GetAbilityType( CAI_BaseNPC *pNPC, int i )
{
	FileUnitInfo_t *pFUI = GetFileUnitInfoFromHandle( LookupUnitInfoSlot( STRING(pNPC->GetUnitType() ) ) );
	if( !pFUI ) {
		DevMsg("Missing unit entry for %s!\n", STRING( pNPC->GetUnitType() ) );
		return 0;
	}

	return GetFileAbilityInfoFromHandle( pFUI->m_iAbilities[i-1] )->m_iAbilityType;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CHL2Wars_Player::AddGroup( int group )
{
	// clear old group
	for(int i = 0; i < MAXSELECTED; i++) {
		if( m_NPCGroup[group].m_Group[i] ) {
            m_NPCGroup[group].m_Group[i] = NULL;  // remove from selection array
		}
		else
			break;
    }

	// check if we got units selected
	if( m_HLWLocal.m_iNumSelected == 0 )
		return;

	// add the units to the new group
	int j = 0;
	for( int i = 0; i < m_HLWLocal.m_iNumSelected; i++ ) {
		if( GetUnit(i) )
			m_NPCGroup[group].m_Group[j++] = GetUnit(i);
	}
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CHL2Wars_Player::SelectGroup( int group )
{
	ClearSelection( );
	UpdateGroup( group );	// update the group, so dead or removed npc's are cleaned up

	for( int i = 0; i < MAXSELECTED; i++ ) {
		// copy the group to the selected array
		if( m_NPCGroup[group].m_Group[i] ) {
			AddUnit( m_NPCGroup[group].m_Group[i] );
		}
		else
			break;
	}	
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void CHL2Wars_Player::UpdateGroup( int group )
{
	for( int i = 0; i < MAXSELECTED; i++ ) {
		// copy the group to the selected array
		if( !m_NPCGroup[group].m_Group[i] || !m_NPCGroup[group].m_Group[i]->IsAlive() ) {
			m_NPCGroup[group].m_Group[i] = NULL;
			for( int j = i; j < MAXSELECTED - 1; j++ ) {
				m_NPCGroup[group].m_Group[i] = m_NPCGroup[group].m_Group[i + 1];
			}
		}
	}	
}

//-----------------------------------------------------------------------------
// Purpose: Check if the unit ain't selected already
//-----------------------------------------------------------------------------
int CHL2Wars_Player::isAlreadySelected( CAI_BaseNPC *pTarget ) 
{
	for(int i = 0; i < m_HLWLocal.m_iNumSelected; i++) {
      if( GetUnit(i) == pTarget )
		  return i;
	}
	return -1;
}

//-----------------------------------------------------------------------------
// Purpose: Adds a unit
//-----------------------------------------------------------------------------
void CHL2Wars_Player::AddUnit(  CAI_BaseNPC *pTarget )
{
	if( !pTarget )
		return;

	if( m_HLWLocal.m_iNumSelected == 0 && m_HLWLocal.m_iHighLightedUnit == -1 )
		m_HLWLocal.m_iHighLightedUnit = 0;

	if( m_HLWLocal.m_iSelectionType == SELECTION_BUILDING ) {
		m_HLWLocal.m_hSelected = NULL;
		m_HLWLocal.m_iSelectionType = SELECTION_UNIT;
	}

	if( m_HLWLocal.m_iNumSelected != MAXSELECTED ) {
		// add to unit map for client
		m_HLWLocal.m_hSelectedUnits.Set( m_HLWLocal.m_iNumSelected, pTarget );

		m_HLWLocal.m_iNumSelected++;
	}
}

//-----------------------------------------------------------------------------
// Purpose: Removes a unit
//-----------------------------------------------------------------------------
void CHL2Wars_Player::RemoveUnit( int index )
{
	// remove
	if( GetUnit( index ) ) {
		m_HLWLocal.m_hSelectedUnits.Set( index, NULL );
	}

	// if the highlighted unit is this unit, reset to -1.
	if( index == m_HLWLocal.m_iHighLightedUnit )
		m_HLWLocal.m_iHighLightedUnit = -1;

	//resort array
	for( int i = index; i < m_HLWLocal.m_iNumSelected; i++ ) {
		m_HLWLocal.m_hSelectedUnits.Set( i, m_HLWLocal.m_hSelectedUnits.Get( i + 1 ) );

		// if the highlighted unit is the next one, we move it with us.
		if( i + 1 == m_HLWLocal.m_iHighLightedUnit )
			m_HLWLocal.m_iHighLightedUnit = i;
	}

	m_HLWLocal.m_iNumSelected--;
}

//-----------------------------------------------------------------------------
// Purpose: Kills the selected units
//-----------------------------------------------------------------------------
void CHL2Wars_Player::KillSelectedUnits()
{
	for( int i = 0; i < m_HLWLocal.m_iNumSelected; i++ ) 
	{
		if( !GetUnit( i ) || !GetUnit( i )->IsAlive() )
			continue;

		// some units can have a lot of damage reduction. Apply a good amount of damage.
		int killdamage = GetUnit( i )->GetHealth() * 2 + 10;
		GetUnit( i )->TakeDamage( CTakeDamageInfo( GetUnit( i ), GetUnit( i ), killdamage, DMG_GENERIC ) );
	}
}

//-----------------------------------------------------------------------------
// Purpose: Destroy the selected building
//-----------------------------------------------------------------------------
void CHL2Wars_Player::DestroySelectedBuilding()
{
	if( m_HLWLocal.m_hSelected.Get() )
	{
		if( m_HLWLocal.m_hSelected.Get()->IsRTSModel() )
		{
			CBaseBuildingModel *pBuildingM = (CBaseBuildingModel *)m_HLWLocal.m_hSelected.Get();
			if( pBuildingM&& pBuildingM->IsAlive() )
			{
				int killdamage = pBuildingM->GetHealth() + 10;
				pBuildingM->TakeDamage( CTakeDamageInfo( this, this, killdamage, DMG_GENERIC ) );

				m_HLWLocal.m_iSelectionType = SELECTION_UNIT;
				m_HLWLocal.m_hSelected = NULL;
			}
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose: Cancel the orders of the current units
//-----------------------------------------------------------------------------
void CHL2Wars_Player::OrderCancelSelectedUnits()
{
	for( int i = 0; i < m_HLWLocal.m_iNumSelected; i++ ) 
	{
		if( GetUnit( i ) && GetUnit( i )->GetCurrentOrder() )
		{
			GetUnit( i )->GetCurrentOrder()->SetOrderType( ORDER_IDLE, false );
			GetUnit( i )->ClearSchedule(NULL);
		}
	}
}

//-----------------------------------------------------------------------------
// Hits triggers with raycasts
//-----------------------------------------------------------------------------
/*class CTriggerTraceEnum2 : public IEntityEnumerator
{
public:
	CTriggerTraceEnum2( Ray_t *pRay, const Vector& dir, int contentsMask ) :
		m_VecDir(dir), m_ContentsMask(contentsMask), m_pRay(pRay)
	{
		m_pEnt = NULL;
		m_fDistance = 9999999.0f;
	}

	virtual bool EnumEntity( IHandleEntity *pHandleEntity )
	{
		if( m_pEnt )
			return false;

		CBaseEntity *pEnt = gEntList.GetBaseEntity( pHandleEntity->GetRefEHandle() );
		Msg("Filtering entity in enum %s\n", pEnt->GetClassname() );

		// Done to avoid hitting an entity that's both solid & a trigger.
		if ( pEnt->IsRTSBrush() )
		{
			m_pEnt = pEnt;
			m_fDistance = (m_pRay->m_Start - pEnt->GetAbsOrigin() ).Length();
			Msg("rts brush, distance %f\n", m_fDistance );
		}

		return true;
	}

	CBaseEntity *GetHitEnt() { return m_pEnt; }
	float GetDistance() { return m_fDistance; }

private:
	Vector m_VecDir;
	int m_ContentsMask;
	Ray_t *m_pRay;
	CBaseEntity *m_pEnt;
	float m_fDistance;
};*/

//-----------------------------------------------------------------------------
// Purpose: Get the first entity in the mouse ray
//-----------------------------------------------------------------------------
CBaseEntity *CHL2Wars_Player::GetEntityMouse( void ) 
{
	// Check if the mouse points to a npc, if so, return the npc
    trace_t tr;

	CTraceFilterRTS TraceFiler( this );
	CTraceFilterRTS *pTraceFiler = &TraceFiler;

	// first try with mask_solid
	UTIL_TraceHull( Weapon_ShootPosition(), Weapon_ShootPosition() + (m_vecPickingRayMouse *  8192), -Vector(16,16,16), Vector(16,16,16), MASK_SOLID, pTraceFiler, &tr ); 
	//UTIL_TraceHull( Weapon_ShootPosition(), Weapon_ShootPosition() + (m_vecPickingRayMouse *  8192), -Vector(16,16,16), Vector(16,16,16), MASK_ALL, pTraceFiler, &tr ); 

	// oh, this looks hacky! Stupid bitches at valve don't give us the possibility to traceline a none solid?
	/*Ray_t ray;
	ray.Init( Weapon_ShootPosition(), Weapon_ShootPosition() + (m_vecPickingRayMouse *  8192), -Vector(16,16,16), Vector(16,16,16) );

	CTriggerTraceEnum2 triggerTraceEnum( &ray, m_vecPickingRayMouse, MASK_SHOT );
	enginetrace->EnumerateEntities( ray, true, &triggerTraceEnum );

	// check entity
    if (tr.m_pEnt ) 
    {
		Msg("Distance: %f\n", (Weapon_ShootPosition() - tr.m_pEnt->GetAbsOrigin()).Length() );
		if( triggerTraceEnum.GetHitEnt() )
		{
			float distance = (Weapon_ShootPosition() - tr.m_pEnt->GetAbsOrigin()).Length();
			Msg("Distance 1: %f %s, distance 2: %f %s\n", distance, tr.m_pEnt->GetClassname(), 
				triggerTraceEnum.GetDistance(), triggerTraceEnum.GetHitEnt()->GetClassname() );
			if( distance > triggerTraceEnum.GetDistance() )
			{
				Msg("Returning hit ent\n");
				return triggerTraceEnum.GetHitEnt();
			}
		}

  	    return tr.m_pEnt;
    }
	else if( triggerTraceEnum.GetHitEnt() )
	{
		Msg("Distance: %f\n", triggerTraceEnum.GetDistance() );
		return triggerTraceEnum.GetHitEnt();
	}*/

    if (tr.m_pEnt ) 
    {
		//Msg("Server entity is %s\n", tr.m_pEnt->GetClassname() );
  	    return tr.m_pEnt;
    }

	return NULL;
}

//-----------------------------------------------------------------------------
// Purpose: Find the first ground spot to spawn something from the mouse pointer
//-----------------------------------------------------------------------------
Vector CHL2Wars_Player::RetrieveGroundPos( void ) 
{
	// Check if the mouse points to a npc, if so, return the npc
    trace_t tr;
    //Vector forward;
    //AngleVectors(EyeAngles(),&forward);	//Get the forward vector frow our own eye angles.
    
	CTraceFilterRTS TraceFiler( this );
	CTraceFilterRTS *pTraceFiler = &TraceFiler;

    UTIL_TraceLine(Weapon_ShootPosition(),Weapon_ShootPosition() + (m_vecPickingRayMouse *  8192), MASK_SOLID, pTraceFiler,&tr);

	// traceline for debugging
	//debugoverlay->AddLineOverlay( pPlayer->Weapon_ShootPosition(),pPlayer->Weapon_ShootPosition() + (pPlayer->m_Local.m_vecPickingRayMouse *  8192), 100, 55, 255, false, 5 ); 

	// hit ground?
    if ( tr.DidHitWorld() || tr.IsDispSurface())//If we hit the ground, return the position
    {
  	  return tr.endpos;
    }
	else if( tr.m_pEnt && UTIL_IsRTSClientBrush( tr.m_pEnt ) ) {
  	    return tr.endpos;	
	}
	else if( tr.m_pEnt ) {
		return tr.m_pEnt->GetAbsOrigin();
	}

	return Vector(0, 0, 0);
}

//-----------------------------------------------------------------------------
// Purpose: Calculate arrival direction of a unit, based on the position of the 
//			mouse pressed and release vector.
// Output : 
//-----------------------------------------------------------------------------
QAngle CHL2Wars_Player::CalculateArrivalDirection( void )
{
	float diff_x = vecMouseRayRightPressed.x - vecMouseRayRightReleased.x;
	float diff_y = vecMouseRayRightPressed.y - vecMouseRayRightReleased.y;
	//float schuine_hoek = sqrt( pow( diff_x, 2 ) + pow( diff_y, 2 ) );
	float angle = atan( diff_y / diff_x ) * ( 180 / PI );

	// fix up angle if needed
	if( diff_x > 0 && diff_y > 0 )
		angle += 180.0f;
	else if( diff_x > 0 )
		angle += 180.0f;
	
	QAngle temp;
	temp[0] = temp[2] = 0.0f;
	temp[YAW] = angle;
	return temp;
}

void CHL2Wars_Player::CheckArrivalDirection( CRTSPointOrder *pTarget )
{
	if( (vecMouseRayRightPressed - vecMouseRayRightReleased).Length2D() > 64.0f )
		pTarget->SetArrivalDirection( CalculateArrivalDirection() ); 
}

//-----------------------------------------------------------------------------
// Purpose: Check if everybody is still alive
// Output : 
//-----------------------------------------------------------------------------
void CHL2Wars_Player::UpdateSelectedUnits( )
{
	for(int i = 0; i < m_HLWLocal.m_iNumSelected; i++) {
		if( !GetUnit(i) || !GetUnit(i)->IsAlive() ) {
			RemoveUnit( i );
		}
	}
}

//-----------------------------------------------------------------------------
// Purpose: Plays the specified sound of a unit
// Output : 
//-----------------------------------------------------------------------------
void CHL2Wars_Player::EmitSoundUnit( CAI_BaseNPC *pUnit, const char *soundtype )
{
	FileUnitInfo_t *pFUI = GetFileUnitInfoFromHandle( LookupUnitInfoSlot( STRING(pUnit->GetUnitType() ) ) );
	if( !pFUI )
		return;	

	if( !pFUI->m_pSoundData )
		return;

	CSingleUserRecipientFilter filter( this );
	//if ( IsPredicted() )
	//{
	//	filter.UsePredictionRules();
	//}
	EmitSound( filter, pUnit->entindex(), pFUI->m_pSoundData->GetString(soundtype) );
}

//-----------------------------------------------------------------------------
// Purpose: Plays the specified sound of a unit
// Output : 
//-----------------------------------------------------------------------------
/*void CHL2Wars_Player::EmitSoundAbility( FileAbilityInfo_t *pFAI, const char *soundtype )
{
	if( !pFAI )
		return;

	if( !pFAI->m_pSoundData )
		return;

	CSingleUserRecipientFilter filter( this );
	//if ( IsPredicted() )
	//{
	//	filter.UsePredictionRules();
	//}
	EmitSound( filter, entindex(), pFAI->m_pSoundData->GetString(soundtype) );
}*/