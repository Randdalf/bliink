//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef SDK_PLAYERANIMSTATE_H
#define SDK_PLAYERANIMSTATE_H
#ifdef _WIN32
#pragma once
#endif


#include "convar.h"
#include "multiplayer_animstate.h"

#if defined( CLIENT_DLL )
class C_BliinkPlayer;
#define CBliinkPlayer C_BliinkPlayer
#else
class CBliinkPlayer;
#endif

// ------------------------------------------------------------------------------------------------ //
// CPlayerAnimState declaration.
// ------------------------------------------------------------------------------------------------ //
class CBliinkPlayerAnimState : public CMultiPlayerAnimState
{
public:
	
	DECLARE_CLASS( CBliinkPlayerAnimState, CMultiPlayerAnimState );

	CBliinkPlayerAnimState();
	CBliinkPlayerAnimState( CBasePlayer *pPlayer, MultiPlayerMovementData_t &movementData );
	~CBliinkPlayerAnimState();

	void InitSDKAnimState( CBliinkPlayer *pPlayer );
	CBliinkPlayer *GetSDKPlayer( void )							{ return m_pSDKPlayer; }

	virtual void ClearAnimationState();
	virtual Activity TranslateActivity( Activity actDesired );
	virtual void Update( float eyeYaw, float eyePitch );

	void	DoAnimationEvent( PlayerAnimEvent_t event, int nData = 0 );

	bool	HandleMoving( Activity &idealActivity );
	bool	HandleJumping( Activity &idealActivity );
	bool	HandleDucking( Activity &idealActivity );
	bool	HandleSwimming( Activity &idealActivity );

//#if defined ( SDK_USE_SPRINTING )
	bool	HandleSprinting( Activity &idealActivity );
//#endif

	//Tony; overriding because the SDK Player models pose parameter is flipped the opposite direction
	virtual void		ComputePoseParam_MoveYaw( CStudioHdr *pStudioHdr );

	virtual Activity CalcMainActivity();	

private:
	
	CBliinkPlayer   *m_pSDKPlayer;
	bool		m_bInAirWalk;

	float		m_flHoldDeployedPoseUntilTime;
};

CBliinkPlayerAnimState *CreateSDKPlayerAnimState( CBliinkPlayer *pPlayer );



#endif // SDK_PLAYERANIMSTATE_H
