#include "cbase.h"
#include "weapon_sdkbase.h"
#include "sdk_weapon_melee.h"

#if defined( CLIENT_DLL )

	#define CWeaponClaw C_WeaponClaw
	#include "c_bliink_player.h"

#else

	#include "bliink_player.h"

#endif


class CWeaponClaw : public CWeaponSDKMelee
{
public:
	DECLARE_CLASS( CWeaponClaw, CWeaponSDKMelee );
	DECLARE_NETWORKCLASS(); 
	DECLARE_PREDICTABLE();
	DECLARE_ACTTABLE();
	
	CWeaponClaw();

	virtual int GetWeaponID( void ) const		{	return SDK_WEAPON_CLAW; }
	virtual float	GetRange( void )					{	return	64.0f;	}	//Tony; let the crowbar swing further.
	virtual bool CanWeaponBeDropped() const				{	return false; }

private:

	CWeaponClaw( const CWeaponClaw & );
};

IMPLEMENT_NETWORKCLASS_ALIASED( WeaponClaw, DT_WeaponClaw )

BEGIN_NETWORK_TABLE( CWeaponClaw, DT_WeaponClaw )
END_NETWORK_TABLE()

BEGIN_PREDICTION_DATA( CWeaponClaw )
END_PREDICTION_DATA()

LINK_ENTITY_TO_CLASS( weapon_claw, CWeaponClaw );
PRECACHE_WEAPON_REGISTER( weapon_claw );



CWeaponClaw::CWeaponClaw()
{
}

//Tony; todo; add ACT_MP_PRONE* activities, so we have them.
acttable_t CWeaponClaw::m_acttable[] = 
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

IMPLEMENT_ACTTABLE( CWeaponClaw );

