//============ Copyright © 1996-2008, Valve Corporation, All rights reserved. ===============//
//
// Purpose: Shared Player Variables / Functions and variables that may or may not be networked
//
//===========================================================================================//

#ifndef SDK_PLAYER_SHARED_H
#define SDK_PLAYER_SHARED_H
#ifdef _WIN32
#pragma once
#endif

#include "networkvar.h"
#include "weapon_sdkbase.h"

#ifdef CLIENT_DLL
class C_BliinkPlayer;
#else
class CBliinkPlayer;
#endif

class CBliinkPlayerShared
{
public:

#ifdef CLIENT_DLL
	friend class C_BliinkPlayer;
	typedef C_BliinkPlayer OuterClass;
	DECLARE_PREDICTABLE();
#else
	friend class CBliinkPlayer;
	typedef CBliinkPlayer OuterClass;
#endif

	DECLARE_EMBEDDED_NETWORKVAR()
	DECLARE_CLASS_NOBASE( CBliinkPlayerShared );

	CBliinkPlayerShared();
	~CBliinkPlayerShared();

#if defined ( SDK_USE_STAMINA ) || defined ( SDK_USE_SPRINTING )
	void	SetStamina( float stamina );
#endif // SDK_USE_STAMINA || SDK_USE_SPRINTING

	void	Init( OuterClass *pOuter );

	bool	IsSniperZoomed( void ) const;
	bool	IsDucking( void ) const; 

	CWeaponSDKBase* GetActiveSDKWeapon() const;

	bool	IsJumping( void ) { return m_bJumping; }
	void	SetJumping( bool bJumping );

	void	ForceUnzoom( void );

#ifdef SDK_USE_SPRINTING
	bool	IsSprinting( void ) { return m_bIsSprinting; }

	void	SetSprinting( bool bSprinting );
	void	StartSprinting( void );
	void	StopSprinting( void );

	void	SetSprintPenalty( bool pPenalty );
	bool	GaveSprintPenalty( void ) {return m_bGaveSprintPenalty;}
#endif

	void ComputeWorldSpaceSurroundingBox( Vector *pVecWorldMins, Vector *pVecWorldMaxs );

private:

#if defined ( SDK_USE_SPRINTING )
	CNetworkVar( bool, m_bIsSprinting );
	bool m_bGaveSprintPenalty;
#endif

#if defined ( SDK_USE_STAMINA ) || defined ( SDK_USE_SPRINTING )
	CNetworkVar( float, m_flStamina );
#endif // SDK_USE_STAMINA || SDK_USE_SPRINTING

public:
	bool m_bJumping;

	float m_flLastViewAnimationTime;

	//Tony; player speeds; at spawn server and client update both of these based on class (if any)
	float m_flRunSpeed;
	float m_flSprintSpeed;
	float m_flProneSpeed;

private:
	OuterClass *m_pOuter;

	// Bliink inventory
public:

};			   




#endif //SDK_PLAYER_SHARED_H