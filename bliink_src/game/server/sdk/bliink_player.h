//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose:		Player for SDK Game
//
// $NoKeywords: $
//=============================================================================//

#ifndef SDK_PLAYER_H
#define SDK_PLAYER_H
#pragma once

#include "basemultiplayerplayer.h"
#include "server_class.h"
#include "sdk_playeranimstate.h"
#include "bliink_player_shared.h"
#include "bliink_item_inventory.h"
#include "bliink_player_stats.h"
#include "weapon_sdkbase.h"

// Function table for each player state.
class CBliinkPlayerStateInfo
{
public:
	BliinkPlayerState m_iPlayerState;
	const char *m_pStateName;
	
	void (CBliinkPlayer::*pfnEnterState)();	// Init and deinit the state.
	void (CBliinkPlayer::*pfnLeaveState)();
	void (CBliinkPlayer::*pfnPreThink)();	// Do a PreThink() in this state.
};

//=============================================================================
// >> SDK Game player
//=============================================================================
class CBliinkPlayer : public CBaseMultiplayerPlayer
{
public:
	DECLARE_CLASS( CBliinkPlayer, CBaseMultiplayerPlayer );
	DECLARE_SERVERCLASS();
	DECLARE_PREDICTABLE();
	DECLARE_DATADESC();

	CBliinkPlayer();
	~CBliinkPlayer();

	Class_T Classify( void );

	static CBliinkPlayer *CreatePlayer( const char *className, edict_t *ed );
	static CBliinkPlayer* Instance( int iEnt );

	// This passes the event to the client's and server's CPlayerAnimState.
	void DoAnimationEvent( PlayerAnimEvent_t event, int nData = 0 );

	virtual void FlashlightTurnOn( void );
	virtual void FlashlightTurnOff( void );
	virtual int FlashlightIsOn( void );

	virtual void PreThink();
	virtual void PostThink();
	virtual void Spawn();
	virtual void InitialSpawn();

	virtual void GiveDefaultItems();

	// Animstate handles this.
	void SetAnimation( PLAYER_ANIM playerAnim ) { return; }

	virtual void Precache();
	virtual int			OnTakeDamage( const CTakeDamageInfo &inputInfo );
	virtual int			OnTakeDamage_Alive( const CTakeDamageInfo &info );
	virtual void Event_Killed( const CTakeDamageInfo &info );
	virtual void TraceAttack( const CTakeDamageInfo &inputInfo, const Vector &vecDir, trace_t *ptr );
	
	CWeaponSDKBase* GetActiveSDKWeapon() const;
	virtual void	CreateViewModel( int viewmodelindex = 0 );

	virtual void	CheatImpulseCommands( int iImpulse );
	
	virtual int		SpawnArmorValue( void ) const { return m_iSpawnArmorValue; }
	virtual void	SetSpawnArmorValue( int i ) { m_iSpawnArmorValue = i; }

	CNetworkQAngle( m_angEyeAngles );	// Copied from EyeAngles() so we can send it to the client.
	CNetworkVar( int, m_iShotsFired );	// number of shots fired recently

	// Tracks our ragdoll entity.
	CNetworkHandle( CBaseEntity, m_hRagdoll );	// networked entity handle 
	void PhysObjectSleep();
	void PhysObjectWake();

	// Player avoidance
	virtual	bool		ShouldCollide( int collisionGroup, int contentsMask ) const;
	void SDKPushawayThink(void);

// In shared code.
public:
	void FireBullet( 
		Vector vecSrc, 
		const QAngle &shootAngles, 
		float vecSpread, 
		int iDamage, 
		int iBulletType,
		CBaseEntity *pevAttacker,
		bool bDoEffects,
		float x,
		float y );

	CNetworkVarEmbedded( CBliinkPlayerShared, m_Shared );
	virtual void			PlayerDeathThink( void );
	virtual bool		ClientCommand( const CCommand &args );

	void IncreaseShotsFired() { m_iShotsFired++; if (m_iShotsFired > 16) m_iShotsFired = 16; }
	void DecreaseShotsFired() { m_iShotsFired--; if (m_iShotsFired < 0) m_iShotsFired = 0; }
	void ClearShotsFired() { m_iShotsFired = 0; }
	int GetShotsFired() { return m_iShotsFired; }

#if defined ( SDK_USE_SPRINTING )
	void SetSprinting( bool bIsSprinting );
#endif // SDK_USE_SPRINTING
	// Returns true if the player is allowed to attack.
	bool CanAttack( void );

	virtual int GetPlayerStance();

	// Called whenever this player fires a shot.
	void NoteWeaponFired();
	virtual bool WantsLagCompensationOnEntity( const CBasePlayer *pPlayer, const CUserCmd *pCmd, const CBitVec<MAX_EDICTS> *pEntityTransmitBits ) const;

// ------------------------------------------------------------------------------------------------ //
// Player state management.
// ------------------------------------------------------------------------------------------------ //
public:

	void State_Transition( BliinkPlayerState newState );
	BliinkPlayerState State_Get() const;				// Get the current state.

	virtual bool	ModeWantsSpectatorGUI( int iMode ) { return ( iMode != OBS_MODE_DEATHCAM && iMode != OBS_MODE_FREEZECAM ); }

private:
	bool SelectSpawnSpot( const char *pEntClassName, CBaseEntity* &pSpot );

	void State_Enter( BliinkPlayerState newState );	// Initialize the new state.
	void State_Leave();								// Cleanup the previous state.
	void State_PreThink();							// Update the current state.

public: //Tony; I had this private but I need it public for initial spawns.
	void MoveToNextIntroCamera();
private:

	//**************************************************************************
	//* BLIINK PLAYER STATE FUNCTIONS
	//**************************************************************************
	void State_Enter_BLIINK_WELCOME();
	void State_PreThink_BLIINK_WELCOME();

	void State_Enter_BLIINK_SPECTATE_PREGAME();
	void State_PreThink_BLIINK_SPECTATE_PREGAME();

	void State_Enter_BLIINK_WAITING_FOR_PLAYERS();
	void State_PreThink_BLIINK_WAITING_FOR_PLAYERS();

	void State_Enter_BLIINK_SPECTATE();
	void State_PreThink_BLIINK_SPECTATE();

	void State_Enter_BLIINK_SURVIVOR();
	void State_PreThink_BLIINK_SURVIVOR();

	void State_Enter_BLIINK_SURVIVOR_DEATH_ANIM();
	void State_PreThink_BLIINK_SURVIVOR_DEATH_ANIM();

	void State_Enter_BLIINK_STALKER();
	void State_PreThink_BLIINK_STALKER();

	void State_Enter_BLIINK_STALKER_DEATH_ANIM();
	void State_PreThink_BLIINK_STALKER_DEATH_ANIM();

	void State_Enter_BLIINK_STALKER_RESPAWN();
	void State_PreThink_BLIINK_STALKER_RESPAWN();

	void State_Enter_BLIINK_VIEW_RESULTS();
	void State_PreThink_BLIINK_VIEW_RESULTS();

	// Find the state info for the specified state.
	static CBliinkPlayerStateInfo* State_LookupInfo( BliinkPlayerState state );

	// This tells us which state the player is currently in (joining, observer, dying, etc).
	// Each state has a well-defined set of parameters that go with it (ie: observer is movetype_noclip, non-solid,
	// invisible, etc).
	CNetworkVar( BliinkPlayerState, m_iPlayerState );

	CBliinkPlayerStateInfo *m_pCurStateInfo;			// This can be NULL if no state info is defined for m_iPlayerState.
	bool HandleCommand_JoinTeam( int iTeam );

	bool BecomeRagdollOnClient( const Vector &force );

#if defined ( SDK_USE_SPRINTING )
	void InitSprinting( void );
	bool IsSprinting( void );
	bool CanSprint( void );
#endif // SDK_USE_SPRINTING

	void InitSpeeds( void ); //Tony; called EVERY spawn on server and client after class has been chosen (if any!)

	// from CBasePlayer
	void			SetupVisibility( CBaseEntity *pViewEntity, unsigned char *pvs, int pvssize );

	CBaseEntity*	EntSelectSpawnPoint();
	bool			CanMove( void ) const;

	virtual void	SharedSpawn();

	virtual const Vector	GetPlayerMins( void ) const; // uses local player
	virtual const Vector	GetPlayerMaxs( void ) const; // uses local player

	virtual void		CommitSuicide( bool bExplode = false, bool bForce = false );

private:
	// Last usercmd we shot a bullet on.
	int m_iLastWeaponFireUsercmd;

	virtual void Weapon_Equip( CBaseCombatWeapon *pWeapon );		//Tony; override so diethink can be cleared
	virtual void ThrowActiveWeapon( void );
	virtual void SDKThrowWeapon( CWeaponSDKBase *pWeapon, const Vector &vecForward, const QAngle &vecAngles, float flDiameter  );
	virtual void SDKThrowWeaponDir( CWeaponSDKBase *pWeapon, const Vector &vecForward, Vector *pVecThrowDir );
	// When the player joins, it cycles their view between trigger_camera entities.
	// This is the current camera, and the time that we'll switch to the next one.
	EHANDLE m_pIntroCamera;
	float m_fIntroCamTime;

	void CreateRagdollEntity();
	void DestroyRagdoll( void );


	CBliinkPlayerAnimState *m_PlayerAnimState;

	CNetworkVar( bool, m_bSpawnInterpCounter );

	int m_iSpawnArmorValue;
	IMPLEMENT_NETWORK_VAR_FOR_DERIVED( m_ArmorValue );

// Bliink stuff
private:
	// Inventory
	CNetworkVarEmbedded( CBliinkItemInventory, m_Inventory );

public:
	CBliinkItemInventory &GetBliinkInventory( void );
	
	CWeaponSDKBase*		Weapon_BliinkGet(int slot); // Weapon_GetSlot
	CWeaponSDKBase*		Weapon_BliinkReplace(int slot, CWeaponSDKBase* pReplacement);
	CWeaponSDKBase*		Weapon_BliinkRemove(int slot); // Weapon_GetSlot, then Weapon_Detach
	void				Weapon_BliinkSwitch(int slot1, int slot2);
	bool				Weapon_BliinkHasWeapon( CWeaponSDKBase* pWeapon );

	virtual void Think();

public:
	// Pre-game
	bool IsReadyToStart( void ) { return m_iPlayerState == STATE_BLIINK_WAITING_FOR_PLAYERS; }
	void StartGameTransition( void );
	void EndGameTransition( void );

private:
	// Player stats
	CNetworkVarEmbedded( CBliinkPlayerStats, m_BliinkStats );

public:
	CBliinkPlayerStats &GetBliinkPlayerStats( void );

	// Ammo
public:
	int		GetAmmoCount( int iAmmoIndex ) const;
	void	RemoveAmmo( int iCount, int iAmmoIndex );

	// Fog
private:
	CNetworkVar( bool, m_bIsInFog );
	bool blinking;

public:
	bool IsInFog() { return m_bIsInFog; }
	bool isBlinking( void ) {return blinking;}
	void setBlinking( bool blink ) {blinking = blink;}
};


inline CBliinkPlayer *ToBliinkPlayer( CBaseEntity *pEntity )
{
	if ( !pEntity || !pEntity->IsPlayer() )
		return NULL;

#ifdef _DEBUG
	Assert( dynamic_cast<CBliinkPlayer*>( pEntity ) != 0 );
#endif
	return static_cast< CBliinkPlayer* >( pEntity );
}

inline BliinkPlayerState CBliinkPlayer::State_Get() const
{
	return m_iPlayerState;
}

#endif	// SDK_PLAYER_H
