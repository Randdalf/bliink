//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef C_SDK_PLAYER_H
#define C_SDK_PLAYER_H
#ifdef _WIN32
#pragma once
#endif


#include "sdk_playeranimstate.h"
#include "c_baseplayer.h"
#include "baseparticleentity.h"
#include "bliink_player_shared.h"
#include "sdk_shareddefs.h"
#include "bliink_item_inventory.h"
#include "bliink_player_stats.h"

class C_BliinkPlayer : public C_BasePlayer
{
public:
	DECLARE_CLASS( C_BliinkPlayer, C_BasePlayer );
	DECLARE_CLIENTCLASS();
	DECLARE_PREDICTABLE();
	DECLARE_INTERPOLATION();

	C_BliinkPlayer();
	~C_BliinkPlayer();

	static C_BliinkPlayer* GetLocalSDKPlayer();

	virtual const QAngle& GetRenderAngles();
	virtual void UpdateClientSideAnimation();
	virtual void PostDataUpdate( DataUpdateType_t updateType );
	virtual void OnDataChanged( DataUpdateType_t updateType );

	virtual void CalcVehicleView(IClientVehicle *pVehicle, Vector& eyeOrigin, QAngle& eyeAngles, float& zNear, float& zFar, float& fov );

	// Player avoidance
	bool ShouldCollide( int collisionGroup, int contentsMask ) const;
	void AvoidPlayers( CUserCmd *pCmd );
	float m_fNextThinkPushAway;
	virtual bool CreateMove( float flInputSampleTime, CUserCmd *pCmd );
	virtual void ClientThink();
	virtual const QAngle& EyeAngles( void );

	// Have this player play the sounds from his view model's reload animation.
	void PlayReloadEffect();

// Called by shared code.
public:
	BliinkPlayerState State_Get() const;
	
	void DoAnimationEvent( PlayerAnimEvent_t event, int nData = 0 );
	virtual bool ShouldDraw();

	CWeaponSDKBase *GetActiveSDKWeapon() const;

	virtual C_BaseAnimating * BecomeRagdollOnClient();
	virtual IRagdoll* GetRepresentativeRagdoll() const;

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

	void IncreaseShotsFired() { m_iShotsFired++; if (m_iShotsFired > 16) m_iShotsFired = 16; }
	void DecreaseShotsFired() { m_iShotsFired--; if (m_iShotsFired < 0) m_iShotsFired = 0; }
	void ClearShotsFired() { m_iShotsFired = 0; }
	int GetShotsFired() { return m_iShotsFired; }

	virtual void SharedSpawn();
	
	void InitSpeeds( void ); //Tony; called EVERY spawn on server and client after class has been chosen (if any!)

//Tony; pronetodo!
//	void CheckProneMoveSound( int groundspeed, bool onground );

	// Returns true if the player is allowed to move.
	bool CanMove() const;

	// Returns true if the player is allowed to attack.
	bool CanAttack( void );

#if defined ( SDK_USE_SPRINTING )
	void SetSprinting( bool bIsSprinting );
	bool IsSprinting( void );
#endif

	CBliinkPlayerShared m_Shared;

	virtual const Vector	GetPlayerMins( void ) const; // uses local player
	virtual const Vector	GetPlayerMaxs( void ) const; // uses local player

// Not Shared, but public.
public:
	void LocalPlayerRespawn( void );

	//Tony; update lookat, if our model has moving eyes setup, they need to be updated.
	void			UpdateLookAt( void );
	bool			playerInFog( void );
	int				GetIDTarget() const;
	void			UpdateIDTarget( void );

	//Tony; when model is changed, need to init some stuff.
	virtual CStudioHdr *OnNewModel( void );
	void InitializePoseParams( void );

public: // Public Variables
	CBliinkPlayerAnimState *m_PlayerAnimState;

	QAngle	m_angEyeAngles;
	CInterpolatedVar< QAngle >	m_iv_angEyeAngles;

	CNetworkVar( int, m_iShotsFired );	// number of shots fired recently

	EHANDLE	m_hRagdoll;

	int	m_headYawPoseParam;
	int	m_headPitchPoseParam;
	float m_headYawMin;
	float m_headYawMax;
	float m_headPitchMin;
	float m_headPitchMax;

	Vector m_vLookAtTarget;

	float m_flLastBodyYaw;
	float m_flCurrentHeadYaw;
	float m_flCurrentHeadPitch;

	int	  m_iIDEntIndex;
	int GetArmorValue() { return m_ArmorValue; }
private:
	void UpdateSoundEvents();

	CNetworkVar( bool, m_bSpawnInterpCounter );
	bool m_bSpawnInterpCounterCache;

	CNetworkVar( BliinkPlayerState, m_iPlayerState );

	C_BliinkPlayer( const C_BliinkPlayer & );

	int m_ArmorValue;

	class CSDKSoundEvent
	{
	public:
		string_t m_SoundName;
		float m_flEventTime;	// Play the event when gpGlobals->curtime goes past this.
	};
	CUtlLinkedList<CSDKSoundEvent,int> m_SoundEvents;

// Bliink stuff
	CBliinkItemInventory m_Inventory;
	CBliinkPlayerStats m_BliinkStats;
public:

	CBliinkItemInventory &GetBliinkInventory( void );
	CBliinkPlayerStats &GetBliinkPlayerStats( void );

	// defined in c_bliink_item_pickup.cpp
	bool IsUseableEntity( CBaseEntity *pEntity, unsigned int requiredCaps );

	// Ammo
public:
	virtual int GetAmmoCount( int iAmmoIndex ) const;
	virtual void RemoveAmmo( int iCount, int iAmmoIndex ) {}
	virtual int	GetMaxHealth();
};


inline C_BliinkPlayer* ToBliinkPlayer( CBaseEntity *pPlayer )
{
	if ( !pPlayer || !pPlayer->IsPlayer() )
		return NULL;

	return static_cast< C_BliinkPlayer* >( pPlayer );
}

inline BliinkPlayerState C_BliinkPlayer::State_Get() const
{
	return m_iPlayerState;
}

#endif // C_SDK_PLAYER_H
