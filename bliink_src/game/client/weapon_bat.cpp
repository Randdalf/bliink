//========= Copyright © 1996-2008, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=====================================================================================//

#include "cbase.h"
#include "weapon_sdkbase.h"
#include "sdk_weapon_melee.h"

#if defined( CLIENT_DLL )

	#define CWeaponBat C_WeaponBat
	#include "c_bliink_player.h"

#else

	#include "bliink_player.h"

#endif


class CWeaponBat : public CWeaponSDKMelee
{
public:
	DECLARE_CLASS( CWeaponBat, CWeaponSDKMelee );
	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();
	DECLARE_ACTTABLE();
	
	CWeaponBat();

	virtual int GetWeaponID( void ) const		{	return SDK_WEAPON_BAT; }
	virtual float	GetRange( void )					{	return	64.0f;	}	//Tony; let the crowbar swing further.
	virtual bool CanWeaponBeDropped() const				{	return false; }

private:

	CWeaponBat( const CWeaponBat & );
};

IMPLEMENT_NETWORKCLASS_ALIASED( WeaponBat, DT_WeaponBat )

BEGIN_NETWORK_TABLE( CWeaponBat, DT_WeaponBat )
END_NETWORK_TABLE()

BEGIN_PREDICTION_DATA( CWeaponBat )
END_PREDICTION_DATA()

LINK_ENTITY_TO_CLASS( weapon_bat, CWeaponBat );
PRECACHE_WEAPON_REGISTER( weapon_bat );



CWeaponBat::CWeaponBat()
{
}

//Tony; todo; add ACT_MP_PRONE* activities, so we have them.
acttable_t CWeaponBat::m_acttable[] = 
{
	{ ACT_MP_STAND_IDLE,					ACT_DOD_STAND_AIM_SPADE,				false },
	{ ACT_MP_CROUCH_IDLE,					ACT_DOD_CROUCH_AIM_SPADE,				false },
	{ ACT_MP_PRONE_IDLE,					ACT_DOD_PRONE_AIM_SPADE,				false },

	{ ACT_MP_RUN,							ACT_DOD_RUN_AIM_SPADE,					false },
	{ ACT_MP_WALK,							ACT_DOD_WALK_AIM_SPADE,					false },
	{ ACT_MP_CROUCHWALK,					ACT_DOD_CROUCHWALK_AIM_SPADE,			false },
	{ ACT_MP_PRONE_CRAWL,					ACT_DOD_PRONEWALK_AIM_SPADE,			false },
	{ ACT_SPRINT,							ACT_DOD_SPRINT_AIM_SPADE,				false },

	{ ACT_MP_ATTACK_STAND_PRIMARYFIRE,		ACT_DOD_PRIMARYATTACK_SPADE,			false },
	{ ACT_MP_ATTACK_CROUCH_PRIMARYFIRE,		ACT_DOD_PRIMARYATTACK_SPADE,			false },
	{ ACT_MP_ATTACK_PRONE_PRIMARYFIRE,		ACT_DOD_PRIMARYATTACK_PRONE_SPADE,		false },
};

IMPLEMENT_ACTTABLE( CWeaponBat );

