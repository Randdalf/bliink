//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#include "cbase.h"
#include "c_bliink_player.h"
#include "c_user_message_register.h"
#include "weapon_sdkbase.h"
#include "c_basetempentity.h"
#include "iclientvehicle.h"
#include "prediction.h"
#include "view.h"
#include "iviewrender.h"
#include "ivieweffects.h"
#include "view_scene.h"
#include "fx.h"
#include "collisionutils.h"
#include "c_bliink_team.h"
#include "obstacle_pushaway.h"
#include "bone_setup.h"
#include "cl_animevent.h"
#include "bliink_player_stats.h"
#include "bliink_item_inventory.h"
#include "engine/ienginesound.h"
#include "glow_outline_effect.h"

// memdbgon must be the last include file in a .cpp file!!!
ConVar cl_ragdoll_physics_enable( "cl_ragdoll_physics_enable", "1", 0, "Enable/disable ragdoll physics." );
#include "tier0/memdbgon.h"

#if defined( CBliinkPlayer )
	#undef CBliinkPlayer
#endif

bool inFog = false;
bool soundPlaying = false;
int mainThemeID = NULL;
int cagesThemeID = NULL;
int fogThemeID = NULL;
bool fadeToSmoke = false;
bool fadeToNorm = false;
float smokeVol;
float normVol;
int state = -1;
bool surviver = false;
bool cagesPlaying = false;


// -------------------------------------------------------------------------------- //
// Player animation event. Sent to the client when a player fires, jumps, reloads, etc..
// -------------------------------------------------------------------------------- //

class C_TEPlayerAnimEvent : public C_BaseTempEntity
{
public:
	DECLARE_CLASS( C_TEPlayerAnimEvent, C_BaseTempEntity );
	DECLARE_CLIENTCLASS();

	virtual void PostDataUpdate( DataUpdateType_t updateType )
	{
		// Create the effect.
		C_BliinkPlayer *pPlayer = dynamic_cast< C_BliinkPlayer* >( m_hPlayer.Get() );
		if ( pPlayer && !pPlayer->IsDormant() )
		{
			pPlayer->DoAnimationEvent( (PlayerAnimEvent_t)m_iEvent.Get(), m_nData );
		}	
	}

public:
	CNetworkHandle( CBasePlayer, m_hPlayer );
	CNetworkVar( int, m_iEvent );
	CNetworkVar( int, m_nData );
};

IMPLEMENT_CLIENTCLASS_EVENT( C_TEPlayerAnimEvent, DT_TEPlayerAnimEvent, CTEPlayerAnimEvent );

BEGIN_RECV_TABLE_NOBASE( C_TEPlayerAnimEvent, DT_TEPlayerAnimEvent )
	RecvPropEHandle( RECVINFO( m_hPlayer ) ),
	RecvPropInt( RECVINFO( m_iEvent ) ),
	RecvPropInt( RECVINFO( m_nData ) )
END_RECV_TABLE()

void __MsgFunc_ReloadEffect( bf_read &msg )
{
	int iPlayer = msg.ReadShort();
	C_BliinkPlayer *pPlayer = dynamic_cast< C_BliinkPlayer* >( C_BaseEntity::Instance( iPlayer ) );
	if ( pPlayer )
		pPlayer->PlayReloadEffect();

}
USER_MESSAGE_REGISTER( ReloadEffect );

// CBliinkPlayerShared Data Tables
//=============================

// specific to the local player ( ideally should not be in CBliinkPlayerShared! )
BEGIN_RECV_TABLE_NOBASE( CBliinkPlayerShared, DT_SDKSharedLocalPlayerExclusive )
#if defined ( SDK_USE_PLAYERCLASSES )
	RecvPropInt( RECVINFO( m_iPlayerClass ) ),
	RecvPropInt( RECVINFO( m_iDesiredPlayerClass ) ),
#endif
END_RECV_TABLE()

BEGIN_RECV_TABLE_NOBASE( CBliinkPlayerShared, DT_SDKPlayerShared )

#if defined ( SDK_USE_PRONE )
	RecvPropBool( RECVINFO( m_bProne ) ),
	RecvPropTime( RECVINFO( m_flGoProneTime ) ),
	RecvPropTime( RECVINFO( m_flUnProneTime ) ),
#endif
#if defined( SDK_USE_SPRINTING )
	RecvPropBool( RECVINFO( m_bIsSprinting ) ),
#endif
	RecvPropDataTable( "sdksharedlocaldata", 0, 0, &REFERENCE_RECV_TABLE(DT_SDKSharedLocalPlayerExclusive) ),
END_RECV_TABLE()

BEGIN_RECV_TABLE_NOBASE( C_BliinkPlayer, DT_SDKLocalPlayerExclusive )
	RecvPropInt( RECVINFO( m_iShotsFired ) ),
	RecvPropVector( RECVINFO_NAME( m_vecNetworkOrigin, m_vecOrigin ) ),

	RecvPropFloat( RECVINFO( m_angEyeAngles[0] ) ),
//	RecvPropFloat( RECVINFO( m_angEyeAngles[1] ) ),
	RecvPropInt( RECVINFO( m_ArmorValue ) ),
END_RECV_TABLE()

BEGIN_RECV_TABLE_NOBASE( C_BliinkPlayer, DT_SDKNonLocalPlayerExclusive )
	RecvPropVector( RECVINFO_NAME( m_vecNetworkOrigin, m_vecOrigin ) ),

	RecvPropFloat( RECVINFO( m_angEyeAngles[0] ) ),
	RecvPropFloat( RECVINFO( m_angEyeAngles[1] ) ),
END_RECV_TABLE()

// Inventory table
BEGIN_NETWORK_TABLE_NOBASE( CBliinkItemInventory, DT_BliinkItemInventory )
		RecvPropArray3( RECVINFO_ARRAY( m_iItemTypes ), RecvPropInt( RECVINFO( m_iItemTypes[0] ) ) ),
		RecvPropArray3( RECVINFO_ARRAY( m_iStackCounts ), RecvPropInt( RECVINFO( m_iStackCounts[0] ) ) ),
		RecvPropArray3( RECVINFO_ARRAY( m_iAmmoSlots ), RecvPropInt( RECVINFO( m_iAmmoSlots[0] ) ) ),
		RecvPropArray3( RECVINFO_ARRAY( m_iAmmoCounts ), RecvPropInt( RECVINFO( m_iAmmoCounts[0] ) ) ),
END_NETWORK_TABLE()

// Stats table
BEGIN_NETWORK_TABLE_NOBASE( CBliinkPlayerStats, DT_BliinkPlayerStats )		
	RecvPropFloat( RECVINFO(m_fHealth) ),
	RecvPropFloat( RECVINFO(m_fFatigue) ),
	RecvPropFloat( RECVINFO(m_fHunger) ),
	RecvPropFloat( RECVINFO(m_fMaxHealth) ),
	RecvPropFloat( RECVINFO(m_fMaxFatigue) ),
	RecvPropFloat( RECVINFO(m_fFatigueRegenRate) ),
	RecvPropInt( RECVINFO(m_iExperience) ),
	RecvPropInt( RECVINFO(m_iLevel) ),
	RecvPropInt( RECVINFO(m_iUpgradePoints) ),
	RecvPropInt( RECVINFO(m_iMaxExperience) ),
	RecvPropInt( RECVINFO(m_iStatusEffect) ),
	RecvPropFloat( RECVINFO(m_fStatusEndTime) ),
END_NETWORK_TABLE()

// main table
IMPLEMENT_CLIENTCLASS_DT( C_BliinkPlayer, DT_SDKPlayer, CBliinkPlayer )
	RecvPropDataTable( RECVINFO_DT( m_Shared ), 0, &REFERENCE_RECV_TABLE( DT_SDKPlayerShared ) ),

	RecvPropDataTable( "sdklocaldata", 0, 0, &REFERENCE_RECV_TABLE(DT_SDKLocalPlayerExclusive) ),
	RecvPropDataTable( "sdknonlocaldata", 0, 0, &REFERENCE_RECV_TABLE(DT_SDKNonLocalPlayerExclusive) ),

	RecvPropEHandle( RECVINFO( m_hRagdoll ) ),

	RecvPropInt( RECVINFO( m_iPlayerState ) ),

	RecvPropBool( RECVINFO( m_bSpawnInterpCounter ) ),

	// Inventory
	RecvPropDataTable( RECVINFO_DT( m_Inventory), 0, &REFERENCE_RECV_TABLE( DT_BliinkItemInventory ) ),

	// Bliink stats
	RecvPropDataTable( RECVINFO_DT( m_BliinkStats), 0, &REFERENCE_RECV_TABLE( DT_BliinkPlayerStats ) ),

	// Fog status.
	RecvPropBool( RECVINFO( m_bIsInFog ) )
END_RECV_TABLE()

// ------------------------------------------------------------------------------------------ //
// Prediction tables.
// ------------------------------------------------------------------------------------------ //
BEGIN_PREDICTION_DATA_NO_BASE( CBliinkPlayerShared )
#if defined( SDK_USE_PRONE )
	DEFINE_PRED_FIELD( m_bProne, FIELD_BOOLEAN, FTYPEDESC_INSENDTABLE ),
	DEFINE_PRED_FIELD( m_flGoProneTime, FIELD_FLOAT, FTYPEDESC_INSENDTABLE ),
	DEFINE_PRED_FIELD( m_flUnProneTime, FIELD_FLOAT, FTYPEDESC_INSENDTABLE ),
#endif
#if defined( SDK_USE_SPRINTING )
	DEFINE_PRED_FIELD( m_bIsSprinting, FIELD_BOOLEAN, FTYPEDESC_INSENDTABLE ),
#endif
END_PREDICTION_DATA()

BEGIN_PREDICTION_DATA( C_BliinkPlayer )
	DEFINE_PRED_FIELD( m_flCycle, FIELD_FLOAT, FTYPEDESC_OVERRIDE | FTYPEDESC_PRIVATE | FTYPEDESC_NOERRORCHECK ),
	DEFINE_PRED_FIELD( m_iShotsFired, FIELD_INTEGER, FTYPEDESC_INSENDTABLE ),   
END_PREDICTION_DATA()

// Inventory prediction
BEGIN_PREDICTION_DATA_NO_BASE( CBliinkItemInventory )
	DEFINE_PRED_ARRAY( m_iItemTypes, FIELD_INTEGER, INVENTORY_MAX_SLOTS, FTYPEDESC_INSENDTABLE ),
	DEFINE_PRED_ARRAY( m_iStackCounts, FIELD_INTEGER, INVENTORY_MAX_SLOTS, FTYPEDESC_INSENDTABLE ),
END_PREDICTION_DATA()

// Stats prediction
BEGIN_PREDICTION_DATA_NO_BASE( CBliinkPlayerStats )
	DEFINE_PRED_FIELD( m_fFatigue, FIELD_FLOAT, FTYPEDESC_INSENDTABLE ),
	DEFINE_PRED_FIELD( m_fMaxFatigue, FIELD_FLOAT, FTYPEDESC_INSENDTABLE ),
	DEFINE_PRED_FIELD( m_fFatigueRegenRate, FIELD_FLOAT, FTYPEDESC_INSENDTABLE ),
END_PREDICTION_DATA()

LINK_ENTITY_TO_CLASS( player, C_BliinkPlayer );

ConVar cl_ragdoll_fade_time( "cl_ragdoll_fade_time", "15", FCVAR_CLIENTDLL );
ConVar cl_ragdoll_pronecheck_distance( "cl_ragdoll_pronecheck_distance", "64", FCVAR_GAMEDLL );

class C_SDKRagdoll : public C_BaseAnimatingOverlay
{
public:
	DECLARE_CLASS( C_SDKRagdoll, C_BaseAnimatingOverlay );
	DECLARE_CLIENTCLASS();

	C_SDKRagdoll();
	~C_SDKRagdoll();

	virtual void OnDataChanged( DataUpdateType_t type );

	int GetPlayerEntIndex() const;
	IRagdoll* GetIRagdoll() const;

	virtual void ImpactTrace( trace_t *pTrace, int iDamageType, char *pCustomImpactName );

	void ClientThink( void );
	void StartFadeOut( float fDelay );
	
	bool IsRagdollVisible();
	int BloodColor()
	{
		return BLOOD_COLOR_RED; 
	}
private:

	C_SDKRagdoll( const C_SDKRagdoll & ) {}

	void Interp_Copy( C_BaseAnimatingOverlay *pSourceEntity );

	void CreateRagdoll();


private:

	EHANDLE	m_hPlayer;
	CNetworkVector( m_vecRagdollVelocity );
	CNetworkVector( m_vecRagdollOrigin );
	float m_fDeathTime;
	bool  m_bFadingOut;
};


IMPLEMENT_CLIENTCLASS_DT_NOBASE( C_SDKRagdoll, DT_SDKRagdoll, CSDKRagdoll )
	RecvPropVector( RECVINFO(m_vecRagdollOrigin) ),
	RecvPropEHandle( RECVINFO( m_hPlayer ) ),
	RecvPropInt( RECVINFO( m_nModelIndex ) ),
	RecvPropInt( RECVINFO(m_nForceBone) ),
	RecvPropVector( RECVINFO(m_vecForce) ),
	RecvPropVector( RECVINFO( m_vecRagdollVelocity ) )
END_RECV_TABLE()


C_SDKRagdoll::C_SDKRagdoll()
{
	m_fDeathTime = -1;
	m_bFadingOut = false;
}

C_SDKRagdoll::~C_SDKRagdoll()
{
	PhysCleanupFrictionSounds( this );
}

void C_SDKRagdoll::Interp_Copy( C_BaseAnimatingOverlay *pSourceEntity )
{
	if ( !pSourceEntity )
		return;
	
	VarMapping_t *pSrc = pSourceEntity->GetVarMapping();
	VarMapping_t *pDest = GetVarMapping();
    	
	// Find all the VarMapEntry_t's that represent the same variable.
	for ( int i = 0; i < pDest->m_Entries.Count(); i++ )
	{
		VarMapEntry_t *pDestEntry = &pDest->m_Entries[i];
		for ( int j=0; j < pSrc->m_Entries.Count(); j++ )
		{
			VarMapEntry_t *pSrcEntry = &pSrc->m_Entries[j];
			if ( !Q_strcmp( pSrcEntry->watcher->GetDebugName(),
				pDestEntry->watcher->GetDebugName() ) )
			{
				pDestEntry->watcher->Copy( pSrcEntry->watcher );
				break;
			}
		}
	}
}
void FX_BloodSpray( const Vector &origin, const Vector &normal, float scale, unsigned char r, unsigned char g, unsigned char b, int flags );
void C_SDKRagdoll::ImpactTrace( trace_t *pTrace, int iDamageType, char *pCustomImpactName )
{
//	DevMsg("C_SDKRagDoll::ImpactTrace: %i\n", iDamageType);
	IPhysicsObject *pPhysicsObject = VPhysicsGetObject();

	if( !pPhysicsObject )
		return;

	Vector dir = pTrace->endpos - pTrace->startpos;

	if ( iDamageType == DMG_BLAST )
	{
		dir *= 4000;  // adjust impact strength
				
		// apply force at object mass center
		pPhysicsObject->ApplyForceCenter( dir );
	}
	else
	{
		Vector hitpos;  

		VectorMA( pTrace->startpos, pTrace->fraction, dir, hitpos );
		VectorNormalize( dir );

		// Blood spray!
		FX_BloodSpray( hitpos, dir, 3, 72, 0, 0, FX_BLOODSPRAY_ALL  );

		dir *= 4000;  // adjust impact strenght

		// apply force where we hit it
		pPhysicsObject->ApplyForceOffset( dir, hitpos );	
		//Tony; throw in some bleeds! - just use a generic value for damage.
		TraceBleed( 40, dir, pTrace, iDamageType );

	}

	m_pRagdoll->ResetRagdollSleepAfterTime();
}


void C_SDKRagdoll::CreateRagdoll()
{
	// First, initialize all our data. If we have the player's entity on our client,
	// then we can make ourselves start out exactly where the player is.
	C_BliinkPlayer *pPlayer = dynamic_cast< C_BliinkPlayer* >( m_hPlayer.Get() );

	if ( pPlayer && !pPlayer->IsDormant() )
	{
		// move my current model instance to the ragdoll's so decals are preserved.
		pPlayer->SnatchModelInstance( this );

		VarMapping_t *varMap = GetVarMapping();

		// Copy all the interpolated vars from the player entity.
		// The entity uses the interpolated history to get bone velocity.
		if ( !pPlayer->IsLocalPlayer() && pPlayer->IsInterpolationEnabled() )
		{
			Interp_Copy( pPlayer );

			SetAbsAngles( pPlayer->GetRenderAngles() );
			GetRotationInterpolator().Reset(0.0f);

			m_flAnimTime = pPlayer->m_flAnimTime;
			SetSequence( pPlayer->GetSequence() );
			m_flPlaybackRate = pPlayer->GetPlaybackRate();
		}
		else
		{
			// This is the local player, so set them in a default
			// pose and slam their velocity, angles and origin
			SetAbsOrigin( m_vecRagdollOrigin );

			SetAbsAngles( pPlayer->GetRenderAngles() );

			SetAbsVelocity( m_vecRagdollVelocity );

			int iSeq = LookupSequence( "RagdollSpawn" );	// hax, find a neutral standing pose
			if ( iSeq == -1 )
			{
				Assert( false );	// missing look_idle?
				iSeq = 0;
			}
			
			SetSequence( iSeq );	// look_idle, basic pose
			SetCycle( 0.0 );

			Interp_Reset( varMap );
		}		

		m_nBody = pPlayer->GetBody();
	}
	else
	{
		// overwrite network origin so later interpolation will
		// use this position
		SetNetworkOrigin( m_vecRagdollOrigin );

		SetAbsOrigin( m_vecRagdollOrigin );
		SetAbsVelocity( m_vecRagdollVelocity );

		Interp_Reset( GetVarMapping() );

	}

	SetModelIndex( m_nModelIndex );
	
	// Turn it into a ragdoll.
	if ( cl_ragdoll_physics_enable.GetInt() )
	{
		// Make us a ragdoll..
		//m_nRenderFX = kRenderFxRagdoll;
		//SetRenderMode(kRenderFxRagdoll);

		matrix3x4a_t boneDelta0[MAXSTUDIOBONES];
		matrix3x4a_t boneDelta1[MAXSTUDIOBONES];
		matrix3x4a_t currentBones[MAXSTUDIOBONES];
		const float boneDt = 0.05f;

		if ( pPlayer && pPlayer == C_BasePlayer::GetLocalPlayer() )
		{
			pPlayer->GetRagdollInitBoneArrays( boneDelta0, boneDelta1, currentBones, boneDt );
		}
		else
		{
			GetRagdollInitBoneArrays( boneDelta0, boneDelta1, currentBones, boneDt );
		}

		InitAsClientRagdoll( boneDelta0, boneDelta1, currentBones, boneDt );
	}
	else
	{
		//ClientLeafSystem()->SetRenderGroup( GetRenderHandle(), RENDER_GROUP_TRANSLUCENT_ENTITY );
	}		

	// Fade out the ragdoll in a while
	StartFadeOut( cl_ragdoll_fade_time.GetFloat() );
	SetNextClientThink( gpGlobals->curtime + 5.0f );
}

void C_SDKRagdoll::OnDataChanged( DataUpdateType_t type )
{
	BaseClass::OnDataChanged( type );

	if ( type == DATA_UPDATE_CREATED )
	{
		CreateRagdoll();
	}
	else 
	{
		if ( !cl_ragdoll_physics_enable.GetInt() )
		{
			// Don't let it set us back to a ragdoll with data from the server.
			//m_nRenderFX = kRenderFxNone;
			SetRenderFX(kRenderFxNone);
		}
	}
}
bool C_SDKRagdoll::IsRagdollVisible()
{
	Vector vMins = Vector(-1,-1,-1);	//WorldAlignMins();
	Vector vMaxs = Vector(1,1,1);	//WorldAlignMaxs();
		
	Vector origin = GetAbsOrigin();
	
	if( !engine->IsBoxInViewCluster( vMins + origin, vMaxs + origin) )
	{
		return false;
	}
	else if( engine->CullBox( vMins + origin, vMaxs + origin ) )
	{
		return false;
	}

	return true;
}

void C_SDKRagdoll::ClientThink( void )
{
	SetNextClientThink( CLIENT_THINK_ALWAYS );

	if ( m_bFadingOut == true )
	{
		int iAlpha = GetRenderAlpha();
		int iFadeSpeed = 600.0f;

		iAlpha = MAX( iAlpha - ( iFadeSpeed * gpGlobals->frametime ), 0 );

		SetRenderMode( kRenderTransAlpha );
		//SetRenderColorA( iAlpha );
		SetRenderAlpha( iAlpha );

		if ( iAlpha == 0 )
		{
			Release();
		}

		return;
	}

	for( int iClient = 1; iClient <= gpGlobals->maxClients; ++iClient )
	{
		C_BliinkPlayer *pEnt = static_cast< C_BliinkPlayer *> ( UTIL_PlayerByIndex( iClient ) );

		if(!pEnt || !pEnt->IsPlayer())
			continue;

		if ( m_hPlayer == NULL )
			continue;

		if ( pEnt->entindex() == m_hPlayer->entindex() )
			continue;
		
		if ( pEnt->GetHealth() <= 0 )
			continue;
#if defined ( SDK_USE_PRONE )
		if ( pEnt->m_Shared.IsProne() == false )
			continue;
#endif
		Vector vTargetOrigin = pEnt->GetAbsOrigin();
		Vector vMyOrigin =  GetAbsOrigin();

		Vector vDir = vTargetOrigin - vMyOrigin;

		if ( vDir.Length() > cl_ragdoll_pronecheck_distance.GetInt() ) 
			continue;

		SetNextClientThink( CLIENT_THINK_ALWAYS );
		m_bFadingOut = true;
		return;
	}

	//Tony; this is kind of silly, because.. whats the point of fading out?
	// if the player is looking at us, delay the fade
	if ( IsRagdollVisible() )
	{
		StartFadeOut( 5.0 );
		return;
	}

	if ( m_fDeathTime > gpGlobals->curtime )
		return;

	Release(); // Die
}

void C_SDKRagdoll::StartFadeOut( float fDelay )
{
	m_fDeathTime = gpGlobals->curtime + fDelay;
	SetNextClientThink( CLIENT_THINK_ALWAYS );
}
IRagdoll* C_SDKRagdoll::GetIRagdoll() const
{
	return m_pRagdoll;
}

C_BaseAnimating * C_BliinkPlayer::BecomeRagdollOnClient()
{
	return BaseClass::BecomeRagdollOnClient();
}


IRagdoll* C_BliinkPlayer::GetRepresentativeRagdoll() const
{
	if ( m_hRagdoll.Get() )
	{
		C_SDKRagdoll *pRagdoll = (C_SDKRagdoll*)m_hRagdoll.Get();

		return pRagdoll->GetIRagdoll();
	}
	else
	{
		return NULL;
	}
}



C_BliinkPlayer::C_BliinkPlayer() : 
	m_iv_angEyeAngles( "C_BliinkPlayer::m_iv_angEyeAngles" ),
	m_GlowObject(this)
{
	// Setting up glow state
	m_GlowObject.SetColor( Vector( 0.3f, 0.1f, 0.6f ) );
	m_GlowObject.SetRenderFlags( false, false );

	m_PlayerAnimState = CreateSDKPlayerAnimState( this );
	m_Shared.Init(this);

	m_angEyeAngles.Init();
	AddVar( &m_angEyeAngles, &m_iv_angEyeAngles, LATCH_SIMULATION_VAR );

	m_fNextThinkPushAway = 0.0f;

}


C_BliinkPlayer::~C_BliinkPlayer()
{
	m_PlayerAnimState->Release();
}


C_BliinkPlayer* C_BliinkPlayer::GetLocalSDKPlayer()
{
	return ToBliinkPlayer( C_BasePlayer::GetLocalPlayer() );
}

const QAngle &C_BliinkPlayer::EyeAngles()
{
	if( IsLocalPlayer() )
	{
		return BaseClass::EyeAngles();
	}
	else
	{
		return m_angEyeAngles;
	}
}
const QAngle& C_BliinkPlayer::GetRenderAngles()
{
	if ( IsRagdoll() )
	{
		return vec3_angle;
	}
	else
	{
		return m_PlayerAnimState->GetRenderAngles();
	}
}


void C_BliinkPlayer::UpdateClientSideAnimation()
{
	m_PlayerAnimState->Update( EyeAngles()[YAW], EyeAngles()[PITCH] );
	BaseClass::UpdateClientSideAnimation();
}
//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
CStudioHdr *C_BliinkPlayer::OnNewModel( void )
{
	CStudioHdr *hdr = BaseClass::OnNewModel();

	InitializePoseParams();

	// Reset the players animation states, gestures
	if ( m_PlayerAnimState )
	{
		m_PlayerAnimState->OnNewModel();
	}

	return hdr;
}
//-----------------------------------------------------------------------------
// Purpose: Clear all pose parameters
//-----------------------------------------------------------------------------
void C_BliinkPlayer::InitializePoseParams( void )
{
	CStudioHdr *hdr = GetModelPtr();
	Assert( hdr );
	if ( !hdr )
		return;

	m_headYawPoseParam = LookupPoseParameter( "head_yaw" );
	GetPoseParameterRange( m_headYawPoseParam, m_headYawMin, m_headYawMax );

	m_headPitchPoseParam = LookupPoseParameter( "head_pitch" );
	GetPoseParameterRange( m_headPitchPoseParam, m_headPitchMin, m_headPitchMax );

	for ( int i = 0; i < hdr->GetNumPoseParameters() ; i++ )
	{
		SetPoseParameter( hdr, i, 0.0 );
	}

}
//Tony; TODO!
//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
/*void C_BliinkPlayer::OnPlayerClassChange( void )
{
	// Init the anim movement vars
	m_PlayerAnimState->SetRunSpeed( GetPlayerClass()->GetMaxSpeed() );
	m_PlayerAnimState->SetWalkSpeed( GetPlayerClass()->GetMaxSpeed() * 0.5 );
}
*/
void C_BliinkPlayer::PostDataUpdate( DataUpdateType_t updateType )
{
	// C_BaseEntity assumes we're networking the entity's angles, so pretend that it
	// networked the same value we already have.
	SetNetworkAngles( GetLocalAngles() );
	
	BaseClass::PostDataUpdate( updateType );

	bool bIsLocalPlayer = IsLocalPlayer();

	if( m_bSpawnInterpCounter != m_bSpawnInterpCounterCache )
	{
		MoveToLastReceivedPosition( true );
		ResetLatched();

		if ( bIsLocalPlayer )
		{
			LocalPlayerRespawn();
		}
		m_bSpawnInterpCounterCache = m_bSpawnInterpCounter.m_Value;
	}

}
// Called every time the player respawns
void C_BliinkPlayer::LocalPlayerRespawn( void )
{
	ResetToneMapping(1.0);
#if defined ( SDK_USE_PRONE )
	m_Shared.m_bForceProneChange = true;
	m_bUnProneToDuck = false;
#endif

	InitSpeeds(); //Tony; initialize player speeds.
}

void C_BliinkPlayer::OnDataChanged( DataUpdateType_t type )
{
	BaseClass::OnDataChanged( type );

	if ( type == DATA_UPDATE_CREATED )
	{
		SetNextClientThink( CLIENT_THINK_ALWAYS );
	}

	UpdateVisibility();
}

void C_BliinkPlayer::PlayReloadEffect()
{
	// Only play the effect for other players.
	if ( this == C_BliinkPlayer::GetLocalSDKPlayer() )
	{
		Assert( false ); // We shouldn't have been sent this message.
		return;
	}

	// Get the view model for our current gun.
	CWeaponSDKBase *pWeapon = GetActiveSDKWeapon();
	if ( !pWeapon )
		return;

	// The weapon needs two models, world and view, but can only cache one. Synthesize the other.
	const CSDKWeaponInfo &info = pWeapon->GetSDKWpnData();
	const model_t *pModel = modelinfo->GetModel( modelinfo->GetModelIndex( info.szViewModel ) );
	if ( !pModel )
		return;
	CStudioHdr studioHdr( modelinfo->GetStudiomodel( pModel ), mdlcache );
	if ( !studioHdr.IsValid() )
		return;

	// Find the reload animation.
	for ( int iSeq=0; iSeq < studioHdr.GetNumSeq(); iSeq++ )
	{
		mstudioseqdesc_t *pSeq = &studioHdr.pSeqdesc( iSeq );

		if ( pSeq->activity == ACT_VM_RELOAD )
		{
			float poseParameters[MAXSTUDIOPOSEPARAM];
			memset( poseParameters, 0, sizeof( poseParameters ) );
			float cyclesPerSecond = Studio_CPS( &studioHdr, *pSeq, iSeq, poseParameters );

			// Now read out all the sound events with their timing
			for ( int iEvent=0; iEvent < pSeq->numevents; iEvent++ )
			{
				//mstudioevent_t *pevent = (mstudioevent_for_client_server_t*)pSeq.pEvent(iEvent );
				mstudioevent_t *pEvent = (mstudioevent_for_client_server_t*)pSeq->pEvent( iEvent );

				if ( pEvent->Event() == CL_EVENT_SOUND )
				{
					CSDKSoundEvent event;
					event.m_SoundName = pEvent->options;
					event.m_flEventTime = gpGlobals->curtime + pEvent->cycle / cyclesPerSecond;
					m_SoundEvents.AddToTail( event );
				}
			}

			break;
		}
	}	
}

void C_BliinkPlayer::DoAnimationEvent( PlayerAnimEvent_t event, int nData )
{
	if ( IsLocalPlayer() )
	{
		if ( ( prediction->InPrediction() && !prediction->IsFirstTimePredicted() ) )
			return;
	}

	MDLCACHE_CRITICAL_SECTION();
	m_PlayerAnimState->DoAnimationEvent( event, nData );
}

bool C_BliinkPlayer::ShouldDraw( void )
{
	// If we're dead, our ragdoll will be drawn for us instead.
	if ( !IsAlive() )
		return false;

	if( GetTeamNumber() == TEAM_SPECTATOR )
		return false;

	if ( State_Get() == STATE_BLIINK_WELCOME
		|| State_Get() == STATE_BLIINK_WAITING_FOR_PLAYERS)
		return false;

	if( IsLocalPlayer() && IsRagdoll() )
		return true;

	return BaseClass::ShouldDraw();
}

CWeaponSDKBase* C_BliinkPlayer::GetActiveSDKWeapon() const
{
	return dynamic_cast< CWeaponSDKBase* >( GetActiveWeapon() );
}

//-----------------------------------------------------------------------------
// Purpose: Non-Caching CalcVehicleView for Scratch SDK + Multiplayer
// TODO: fix the normal CalcVehicleView so that Caching can work in multiplayer.
//-----------------------------------------------------------------------------
void C_BliinkPlayer::CalcVehicleView(IClientVehicle *pVehicle,	Vector& eyeOrigin, QAngle& eyeAngles,	float& zNear, float& zFar, float& fov )
{
	Assert( pVehicle );

	// Start with our base origin and angles
	int nRole = pVehicle->GetPassengerRole( this );

	// Get our view for this frame
	pVehicle->GetVehicleViewPosition( nRole, &eyeOrigin, &eyeAngles, &fov );

	// Allows the vehicle to change the clip planes
	pVehicle->GetVehicleClipPlanes( zNear, zFar );

	// Snack off the origin before bob + water offset are applied
	Vector vecBaseEyePosition = eyeOrigin;

	CalcViewRoll( eyeAngles );

	// Apply punch angle
	VectorAdd( eyeAngles, m_Local.m_vecPunchAngle, eyeAngles );

	if ( !prediction->InPrediction() )
	{
		// Shake it up baby!
		GetViewEffects()->CalcShake();
		GetViewEffects()->ApplyShake( eyeOrigin, eyeAngles, 1.0 );
	}
}

void C_BliinkPlayer::ClientThink()
{
	UpdateSoundEvents();

	// Pass on through to the base class.
	BaseClass::ClientThink();

	bool bFoundViewTarget = false;
	
	Vector vForward;
	AngleVectors( GetLocalAngles(), &vForward );

	C_BliinkPlayer* pPlayer = ToBliinkPlayer( C_BasePlayer::GetLocalPlayer() );

	state = pPlayer->State_Get();

	if(!enginesound->IsSoundStillPlaying(mainThemeID) && !soundPlaying){
		CLocalPlayerFilter filter;
		enginesound->SetRoomType( filter, 1 );
		normVol = 1.0f;
		enginesound->EmitAmbientSound( "common/ambient_1a.wav", normVol );
		mainThemeID = enginesound->GetGuidForLastSoundEmitted();
		Msg( "Starting bliink_main_theme %d\n",enginesound->IsLoopingSound("common/ambient_1a.wav"));
		soundPlaying = true;
	}

	if(!surviver && state == STATE_BLIINK_SURVIVOR){
		normVol = 0.1f;
		enginesound->StopSoundByGuid(mainThemeID);
		enginesound->EmitAmbientSound( "common/ambient_1b.wav", normVol );
		mainThemeID = enginesound->GetGuidForLastSoundEmitted();
		CLocalPlayerFilter filter;
		filter.AddRecipientsByPVS( GetAbsOrigin() );	// Clients within the entity's PVS will be added.
		filter.MakeReliable();
		enginesound->EmitSound(filter,-1,1,"common/Cage_Opening.wav",1.0f,75);
		cagesThemeID = enginesound->GetGuidForLastSoundEmitted();
		cagesPlaying = true;
		surviver = true;
	}

	if(!enginesound->IsSoundStillPlaying(cagesThemeID) && cagesPlaying){
		normVol += 0.01f;
		enginesound->SetVolumeByGuid(mainThemeID, normVol);
		Msg( "normVol - %g\n",normVol);
		if(normVol >= 1.0f) cagesPlaying = false;
	}

	bool inFogNow = GetBliinkPlayerStats().GetStatus() == BLIINK_STATUS_FOGGED;

	if(inFogNow){
		if(!inFog){
			inFog = true;
			fadeToNorm = false;
			fadeToSmoke = true;
			//switch from normal to smoke theme
			//enginesound->SetVolumeByGuid(mainThemeID, 0.0f);
			//enginesound->SetVolumeByGuid(fogThemeID, 1.0f);
			smokeVol = 0.0f;
			enginesound->SetVolumeByGuid(fogThemeID, smokeVol);
			enginesound->StopSoundByGuid(fogThemeID);
			enginesound->EmitAmbientSound( "common/Fog.wav", smokeVol );
			fogThemeID = enginesound->GetGuidForLastSoundEmitted();
			Msg( "Swiching from bliink_main_theme to bliink_fog_theme\n");
		}
	}else{
		if(inFog){
			inFog = false;
			fadeToNorm = true;
			fadeToSmoke = false;
			//switch from smoke to normal theme
			//enginesound->SetVolumeByGuid(fogThemeID, 0.0f);
			//enginesound->SetVolumeByGuid(mainThemeID, 1.0f);
			Msg( "Switching from bliink_fog_theme to bliink_main_theme\n");
		}
	}

	if(fadeToNorm){
		normVol += 0.01f;
		smokeVol -= 0.01f;
		Msg( "normVol - %g , smokeVol - %g\n",normVol,smokeVol);
		enginesound->SetVolumeByGuid(mainThemeID, normVol);
		enginesound->SetVolumeByGuid(fogThemeID, smokeVol);
		if(normVol >= 1.0f) fadeToNorm = false;
	}

	if(fadeToSmoke){
		normVol -= 0.01f;
		smokeVol += 0.01f;
		Msg( "normVol - %g , smokeVol - %g\n",normVol,smokeVol);
		enginesound->SetVolumeByGuid(mainThemeID, normVol);
		enginesound->SetVolumeByGuid(fogThemeID, smokeVol);
		if(smokeVol >= 1.0f) fadeToSmoke = false;
	}
	for( int iClient = 1; iClient <= gpGlobals->maxClients; ++iClient )
	{
		CBaseEntity *pEnt = UTIL_PlayerByIndex( iClient );
		if(!pEnt || !pEnt->IsPlayer())
			continue;

		if ( pEnt->entindex() == entindex() )
			continue;

		Vector vTargetOrigin = pEnt->GetAbsOrigin();
		Vector vMyOrigin =  GetAbsOrigin();

		Vector vDir = vTargetOrigin - vMyOrigin;
		
		if ( vDir.Length() > 128 ) 
			continue;

		VectorNormalize( vDir );

		if ( DotProduct( vForward, vDir ) < 0.0f )
			 continue;

		m_vLookAtTarget = pEnt->EyePosition();
		bFoundViewTarget = true;
		break;
	}

	if ( bFoundViewTarget == false )
	{
		m_vLookAtTarget = GetAbsOrigin() + vForward * 512;
	}

	UpdateIDTarget();

	// Avoidance
	if ( gpGlobals->curtime >= m_fNextThinkPushAway )
	{
		PerformObstaclePushaway( this );
		m_fNextThinkPushAway =  gpGlobals->curtime + PUSHAWAY_THINK_INTERVAL;
	}

	// Glowing
	m_GlowObject.SetRenderFlags( false, false );

	if( pPlayer->State_Get() == STATE_BLIINK_STALKER ||
		pPlayer->State_Get() == STATE_BLIINK_STALKER_RESPAWN ||
		pPlayer->State_Get() == STATE_BLIINK_STALKER_DEATH_ANIM
		)
	{
		// Only render when player is fogged.
		if( State_Get() == STATE_BLIINK_SURVIVOR &&
			m_BliinkStats.GetStatus() == BLIINK_STATUS_FOGGED )
		{
			m_GlowObject.SetRenderFlags( true, true );
		}
	}
}

bool C_BliinkPlayer::playerInFog(void)
{
	Vector vMyOrigin =  GetAbsOrigin();
	double distance = sqrt((vMyOrigin.x*vMyOrigin.x) + (vMyOrigin.y*vMyOrigin.y));

	if(distance >= 1000) return true;

	return false;
}

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
void C_BliinkPlayer::UpdateLookAt( void )
{
	// head yaw
	if (m_headYawPoseParam < 0 || m_headPitchPoseParam < 0)
		return;

	// orient eyes
	m_viewtarget = m_vLookAtTarget;

	// Figure out where we want to look in world space.
	QAngle desiredAngles;
	Vector to = m_vLookAtTarget - EyePosition();
	VectorAngles( to, desiredAngles );

	// Figure out where our body is facing in world space.
	QAngle bodyAngles( 0, 0, 0 );
	bodyAngles[YAW] = GetLocalAngles()[YAW];


	float flBodyYawDiff = bodyAngles[YAW] - m_flLastBodyYaw;
	m_flLastBodyYaw = bodyAngles[YAW];
	

	// Set the head's yaw.
	float desired = AngleNormalize( desiredAngles[YAW] - bodyAngles[YAW] );
	desired = clamp( desired, m_headYawMin, m_headYawMax );
	m_flCurrentHeadYaw = ApproachAngle( desired, m_flCurrentHeadYaw, 130 * gpGlobals->frametime );

	// Counterrotate the head from the body rotation so it doesn't rotate past its target.
	m_flCurrentHeadYaw = AngleNormalize( m_flCurrentHeadYaw - flBodyYawDiff );
	desired = clamp( desired, m_headYawMin, m_headYawMax );
	
	SetPoseParameter( m_headYawPoseParam, m_flCurrentHeadYaw );

	
	// Set the head's yaw.
	desired = AngleNormalize( desiredAngles[PITCH] );
	desired = clamp( desired, m_headPitchMin, m_headPitchMax );
	
	m_flCurrentHeadPitch = ApproachAngle( desired, m_flCurrentHeadPitch, 130 * gpGlobals->frametime );
	m_flCurrentHeadPitch = AngleNormalize( m_flCurrentHeadPitch );
	SetPoseParameter( m_headPitchPoseParam, m_flCurrentHeadPitch );
}



int C_BliinkPlayer::GetIDTarget() const
{
	return m_iIDEntIndex;
}

//-----------------------------------------------------------------------------
// Purpose: Update this client's target entity
//-----------------------------------------------------------------------------
void C_BliinkPlayer::UpdateIDTarget()
{
	if ( !IsLocalPlayer() )
		return;

	// Clear old target and find a new one
	m_iIDEntIndex = 0;

	// don't show id's in any state but active.
	if ( State_Get() != STATE_BLIINK_SURVIVOR && State_Get() != STATE_BLIINK_STALKER )
		return;

	//trace_t tr;
	//Vector vecStart, vecEnd;
	//VectorMA( MainViewOrigin(), 1500, MainViewForward(), vecEnd );
	//VectorMA( MainViewOrigin(), 10,   MainViewForward(), vecStart );
	//UTIL_TraceLine( vecStart, vecEnd, MASK_SOLID, this, COLLISION_GROUP_NONE, &tr );

	//if ( !tr.startsolid && tr.DidHitNonWorldEntity() )
	//{
	//	C_BaseEntity *pEntity = tr.m_pEnt;

	//	if ( pEntity && (pEntity != this) )
	//	{
	//		m_iIDEntIndex = pEntity->entindex();
	//	}
	//}
}

//-----------------------------------------------------------------------------
// Purpose: Try to steer away from any players and objects we might interpenetrate
//-----------------------------------------------------------------------------
#define SDK_AVOID_MAX_RADIUS_SQR		5184.0f			// Based on player extents and MAX buildable extents.
#define SDK_OO_AVOID_MAX_RADIUS_SQR		0.00029f

ConVar sdk_max_separation_force ( "sdk_max_separation_force", "256", FCVAR_CHEAT|FCVAR_HIDDEN );

extern ConVar cl_forwardspeed;
extern ConVar cl_backspeed;
extern ConVar cl_sidespeed;

void C_BliinkPlayer::AvoidPlayers( CUserCmd *pCmd )
{
}

bool C_BliinkPlayer::CreateMove( float flInputSampleTime, CUserCmd *pCmd )
{	
	static QAngle angMoveAngle( 0.0f, 0.0f, 0.0f );

	VectorCopy( pCmd->viewangles, angMoveAngle );

	BaseClass::CreateMove( flInputSampleTime, pCmd );

	AvoidPlayers( pCmd );

	return true;
}

void C_BliinkPlayer::UpdateSoundEvents()
{
	int iNext;
	for ( int i=m_SoundEvents.Head(); i != m_SoundEvents.InvalidIndex(); i = iNext )
	{
		iNext = m_SoundEvents.Next( i );

		CSDKSoundEvent *pEvent = &m_SoundEvents[i];
		if ( gpGlobals->curtime >= pEvent->m_flEventTime )
		{
			CLocalPlayerFilter filter;
			EmitSound( filter, GetSoundSourceIndex(), STRING( pEvent->m_SoundName ) );

			m_SoundEvents.Remove( i );
		}
	}
}

// Gives access to the player's inventory.
CBliinkItemInventory &C_BliinkPlayer::GetBliinkInventory( void )
{
	return m_Inventory;
}

// Gives access to the player's stats.
CBliinkPlayerStats &C_BliinkPlayer::GetBliinkPlayerStats( void )
{
	return m_BliinkStats;
}

// Getting ammo in inventory
int	C_BliinkPlayer::GetAmmoCount( int iAmmoIndex ) const
{
	return m_Inventory.GetAmmoClipCount( iAmmoIndex );
}

int	C_BliinkPlayer::GetMaxHealth()
{
	if( State_Get() == STATE_BLIINK_SURVIVOR )
		return (int) floor(m_BliinkStats.GetMaxHealth());
	else
		return 100;
}