//========= Copyright © 1996-2008, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=====================================================================================//

#include "cbase.h"
#include "weapon_sdkbase.h"
#include "sdk_weapon_melee.h"

#if defined( CLIENT_DLL )

	#define CWeaponMachete C_WeaponMachete
	#include "c_bliink_player.h"

#else

	#include "bliink_player.h"

#endif


class CWeaponMachete : public CWeaponSDKMelee
{
public:
	DECLARE_CLASS( CWeaponMachete, CWeaponSDKMelee );
	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();
	DECLARE_ACTTABLE();
	
	CWeaponMachete();

	virtual int GetWeaponID( void ) const		{	return SDK_WEAPON_MACHETE; }
	virtual float	GetRange( void )					{	return	64.0f;	}	//Tony; let the crowbar swing further.
	virtual bool CanWeaponBeDropped() const				{	return false; }

private:

	CWeaponMachete( const CWeaponMachete & );
};

IMPLEMENT_NETWORKCLASS_ALIASED( WeaponMachete, DT_WeaponMachete )

BEGIN_NETWORK_TABLE( CWeaponMachete, DT_WeaponMachete )
END_NETWORK_TABLE()

BEGIN_PREDICTION_DATA( CWeaponMachete )
END_PREDICTION_DATA()

LINK_ENTITY_TO_CLASS( weapon_machete, CWeaponMachete );
PRECACHE_WEAPON_REGISTER( weapon_machete );



CWeaponMachete::CWeaponMachete()
{
}

//Tony; todo; add ACT_MP_PRONE* activities, so we have them.
acttable_t CWeaponMachete::m_acttable[] = 
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

IMPLEMENT_ACTTABLE( CWeaponMachete );

