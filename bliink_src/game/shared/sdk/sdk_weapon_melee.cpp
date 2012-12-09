//========= Copyright � 1996-2008, Valve Corporation, All rights reserved. ============//
//
// Purpose: Base code for any melee based weapon
//
//=====================================================================================//

#include "cbase.h"

#include "weapon_sdkbase.h"
#include "sdk_weapon_melee.h"

#include "bliink_gamerules.h"
#include "ammodef.h"
#include "mathlib/mathlib.h"
#include "in_buttons.h"
#include "animation.h"

#if defined( CLIENT_DLL )
	#include "c_bliink_player.h"
#else
	#include "bliink_player.h"
	#include "ndebugoverlay.h"
	#include "te_effect_dispatch.h"
	#include "ilagcompensationmanager.h"
#endif

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

IMPLEMENT_NETWORKCLASS_ALIASED( WeaponSDKMelee, DT_WeaponSDKMelee )

BEGIN_NETWORK_TABLE( CWeaponSDKMelee, DT_WeaponSDKMelee )
END_NETWORK_TABLE()

BEGIN_PREDICTION_DATA( CWeaponSDKMelee )
END_PREDICTION_DATA()

#define MELEE_HULL_DIM		16

static const Vector g_meleeMins(-MELEE_HULL_DIM,-MELEE_HULL_DIM,-MELEE_HULL_DIM);
static const Vector g_meleeMaxs(MELEE_HULL_DIM,MELEE_HULL_DIM,MELEE_HULL_DIM);

//-----------------------------------------------------------------------------
// Constructor
//-----------------------------------------------------------------------------
CWeaponSDKMelee::CWeaponSDKMelee()
{
	m_bFiresUnderwater = true;
}

//-----------------------------------------------------------------------------
// Purpose: Spawn the weapon
//-----------------------------------------------------------------------------
void CWeaponSDKMelee::Spawn( void )
{
	m_fMinRange1	= 0;
	m_fMinRange2	= 0;
	m_fMaxRange1	= 64;
	m_fMaxRange2	= 64;
	//Call base class first
	BaseClass::Spawn();
}

//-----------------------------------------------------------------------------
// Purpose: Precache the weapon
//-----------------------------------------------------------------------------
void CWeaponSDKMelee::Precache( void )
{
	//Call base class first
	BaseClass::Precache();
}

//------------------------------------------------------------------------------
// Purpose : Update weapon
//------------------------------------------------------------------------------
void CWeaponSDKMelee::ItemPostFrame( void )
{
	CBliinkPlayer *pPlayer = GetPlayerOwner();
	if ( pPlayer == NULL )
		return;

	if ( (pPlayer->m_nButtons & IN_ATTACK) && (m_flNextPrimaryAttack <= gpGlobals->curtime) && pPlayer->CanAttack() )
	{
		PrimaryAttack();
	} 
	else if ( (pPlayer->m_nButtons & IN_ATTACK2) && (m_flNextSecondaryAttack <= gpGlobals->curtime) && pPlayer->CanAttack() )
	{
		SecondaryAttack();
	}
	else 
	{
		WeaponIdle();
	}
}

//------------------------------------------------------------------------------
// Purpose :
// Input   :
// Output  :
//------------------------------------------------------------------------------
void CWeaponSDKMelee::PrimaryAttack()
{
	
#ifndef CLIENT_DLL
	CBliinkPlayer *pPlayer = ToSDKPlayer( GetPlayerOwner() );
	pPlayer->NoteWeaponFired();
	// Move other players back to history positions based on local player's lag
	lagcompensation->StartLagCompensation( pPlayer, LAG_COMPENSATE_BOUNDS );
#endif
	Swing( false );

#ifndef CLIENT_DLL
	// Move other players back to history positions based on local player's lag
	lagcompensation->FinishLagCompensation( pPlayer );
#endif

}

//------------------------------------------------------------------------------
// Purpose :
// Input   :
// Output  :
//------------------------------------------------------------------------------
void CWeaponSDKMelee::SecondaryAttack()
{
	Swing( true );
}


//------------------------------------------------------------------------------
// Purpose: Implement impact function
//------------------------------------------------------------------------------
void CWeaponSDKMelee::Hit( trace_t &traceHit, Activity nHitActivity )
{
	CBliinkPlayer *pPlayer = ToSDKPlayer( GetOwner() );
	
	//Do view kick
//	AddViewKick();

	CBaseEntity	*pHitEntity = traceHit.m_pEnt;

	//Apply damage to a hit target
	if ( pHitEntity != NULL )
	{
		Vector hitDirection;
		pPlayer->EyeVectors( &hitDirection, NULL, NULL );
		VectorNormalize( hitDirection );

#ifndef CLIENT_DLL
		CTakeDamageInfo info( GetOwner(), GetOwner(), GetDamageForActivity( nHitActivity ), DMG_CLUB );

		if( pPlayer && pHitEntity->IsNPC() )
		{
			// If bonking an NPC, adjust damage.
			info.AdjustPlayerDamageInflictedForSkillLevel();
		}

		CalculateMeleeDamageForce( &info, hitDirection, traceHit.endpos );

		pHitEntity->DispatchTraceAttack( info, hitDirection, &traceHit ); 
		ApplyMultiDamage();

		// Now hit all triggers along the ray that... 
		TraceAttackToTriggers( info, traceHit.startpos, traceHit.endpos, hitDirection );
#endif
		WeaponSound( MELEE_HIT );
	}

	// Apply an impact effect
	ImpactEffect( traceHit );
}

Activity CWeaponSDKMelee::ChooseIntersectionPointAndActivity( trace_t &hitTrace, const Vector &mins, const Vector &maxs, CBliinkPlayer *pOwner )
{
	int			i, j, k;
	float		distance;
	const float	*minmaxs[2] = {mins.Base(), maxs.Base()};
	trace_t		tmpTrace;
	Vector		vecHullEnd = hitTrace.endpos;
	Vector		vecEnd;

	distance = 1e6f;
	Vector vecSrc = hitTrace.startpos;

	vecHullEnd = vecSrc + ((vecHullEnd - vecSrc)*2);
	UTIL_TraceLine( vecSrc, vecHullEnd, MASK_SHOT_HULL, pOwner, COLLISION_GROUP_NONE, &tmpTrace );
	if ( tmpTrace.fraction == 1.0 )
	{
		for ( i = 0; i < 2; i++ )
		{
			for ( j = 0; j < 2; j++ )
			{
				for ( k = 0; k < 2; k++ )
				{
					vecEnd.x = vecHullEnd.x + minmaxs[i][0];
					vecEnd.y = vecHullEnd.y + minmaxs[j][1];
					vecEnd.z = vecHullEnd.z + minmaxs[k][2];

					UTIL_TraceLine( vecSrc, vecEnd, MASK_SHOT_HULL, pOwner, COLLISION_GROUP_NONE, &tmpTrace );
					if ( tmpTrace.fraction < 1.0 )
					{
						float thisDistance = (tmpTrace.endpos - vecSrc).Length();
						if ( thisDistance < distance )
						{
							hitTrace = tmpTrace;
							distance = thisDistance;
						}
					}
				}
			}
		}
	}
	else
	{
		hitTrace = tmpTrace;
	}


	return ACT_VM_HITCENTER;
}

//-----------------------------------------------------------------------------
// Purpose: 
// Input  : &traceHit - 
//-----------------------------------------------------------------------------
bool CWeaponSDKMelee::ImpactWater( const Vector &start, const Vector &end )
{
	//FIXME: This doesn't handle the case of trying to splash while being underwater, but that's not going to look good
	//		 right now anyway...
	
	// We must start outside the water
	//if ( UTIL_PointContents( start ) & (CONTENTS_WATER|CONTENTS_SLIME))
	//	return false;

	//// We must end inside of water
	//if ( !(UTIL_PointContents( end ) & (CONTENTS_WATER|CONTENTS_SLIME)))
	//	return false;

	trace_t	waterTrace;

	UTIL_TraceLine( start, end, (CONTENTS_WATER|CONTENTS_SLIME), GetOwner(), COLLISION_GROUP_NONE, &waterTrace );

	if ( waterTrace.fraction < 1.0f )
	{
#ifndef CLIENT_DLL
		CEffectData	data;

		data.m_fFlags  = 0;
		data.m_vOrigin = waterTrace.endpos;
		data.m_vNormal = waterTrace.plane.normal;
		data.m_flScale = 8.0f;

		// See if we hit slime
		if ( waterTrace.contents & CONTENTS_SLIME )
		{
			data.m_fFlags |= FX_WATER_IN_SLIME;
		}

		DispatchEffect( "watersplash", data );			
#endif
	}

	return true;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CWeaponSDKMelee::ImpactEffect( trace_t &traceHit )
{
	// See if we hit water (we don't do the other impact effects in this case)
	if ( ImpactWater( traceHit.startpos, traceHit.endpos ) )
		return;

	//FIXME: need new decals
	UTIL_ImpactTrace( &traceHit, DMG_CLUB );
}


//------------------------------------------------------------------------------
// Purpose : Starts the swing of the weapon and determines the animation
// Input   : bIsSecondary - is this a secondary attack?
//------------------------------------------------------------------------------
void CWeaponSDKMelee::Swing( int bIsSecondary )
{
	trace_t traceHit;

	// Try a ray
	CBliinkPlayer *pOwner = ToSDKPlayer( GetOwner() );
	if ( !pOwner )
		return;

	Vector swingStart = pOwner->Weapon_ShootPosition( );
	Vector forward;

	pOwner->EyeVectors( &forward, NULL, NULL );

	Vector swingEnd = swingStart + forward * GetRange();
	UTIL_TraceLine( swingStart, swingEnd, MASK_SHOT_HULL, pOwner, COLLISION_GROUP_NONE, &traceHit );
	Activity nHitActivity = ACT_VM_HITCENTER;

#ifndef CLIENT_DLL
	// Like bullets, melee traces have to trace against triggers.
	CTakeDamageInfo triggerInfo( GetOwner(), GetOwner(), GetDamageForActivity( nHitActivity ), DMG_CLUB );
	TraceAttackToTriggers( triggerInfo, traceHit.startpos, traceHit.endpos, vec3_origin );
#endif

	if ( traceHit.fraction == 1.0 )
	{
		float meleeHullRadius = 1.732f * MELEE_HULL_DIM;  // hull is +/- 16, so use cuberoot of 2 to determine how big the hull is from center to the corner point

		// Back off by hull "radius"
		swingEnd -= forward * meleeHullRadius;

		UTIL_TraceHull( swingStart, swingEnd, g_meleeMins, g_meleeMaxs, MASK_SHOT_HULL, pOwner, COLLISION_GROUP_NONE, &traceHit );
		if ( traceHit.fraction < 1.0 && traceHit.m_pEnt )
		{
			Vector vecToTarget = traceHit.m_pEnt->GetAbsOrigin() - swingStart;
			VectorNormalize( vecToTarget );

			float dot = vecToTarget.Dot( forward );

			// YWB:  Make sure they are sort of facing the guy at least...
			if ( dot < 0.70721f )
			{
				// Force amiss
				traceHit.fraction = 1.0f;
			}
			else
			{
				nHitActivity = ChooseIntersectionPointAndActivity( traceHit, g_meleeMins, g_meleeMaxs, pOwner );
			}
		}
	}

	WeaponSound( SINGLE );

	// -------------------------
	//	Miss
	// -------------------------
	if ( traceHit.fraction == 1.0f )
	{
		nHitActivity = bIsSecondary ? ACT_VM_MISSCENTER2 : ACT_VM_MISSCENTER;

		// We want to test the first swing again
		Vector testEnd = swingStart + forward * GetRange();
		
		// See if we happened to hit water
		ImpactWater( swingStart, testEnd );
	}
	else
	{
		Hit( traceHit, nHitActivity );
	}

	// Send the anim
	SendWeaponAnim( nHitActivity );

	pOwner->DoAnimationEvent( PLAYERANIMEVENT_ATTACK_PRIMARY );

	//Setup our next attack times
	m_flNextPrimaryAttack = gpGlobals->curtime + GetFireRate();
	m_flNextSecondaryAttack = gpGlobals->curtime + SequenceDuration();
}

