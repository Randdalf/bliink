#include "cbase.h"

#include "glow_outline_effect.h"
#include "c_bliink_player.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// C_BliinkItemPickup
// Used for adding the glow effect to item pickups when the player is looking
// at them.
//-----------------------------------------------------------------------------
class C_BliinkItemPickup : public C_BaseAnimating
{	
public:
	DECLARE_CLIENTCLASS();
	DECLARE_CLASS( C_BliinkItemPickup, C_BaseAnimating );

	C_BliinkItemPickup( );

	virtual void ClientThink();
	virtual void OnDataChanged( DataUpdateType_t updateType );

private:
	CGlowObject m_GlowObject;
};

LINK_ENTITY_TO_CLASS( bliink_item_pickup, C_BliinkItemPickup );

// This works although VS thinks it doesn't
IMPLEMENT_CLIENTCLASS_DT( C_BliinkItemPickup, DT_BliinkItemPickup ,CBliinkItemPickup )
	// ...
END_RECV_TABLE()

// Sets pickups to be useable
bool C_BliinkPlayer::IsUseableEntity( CBaseEntity *pEntity, unsigned int requiredCaps )
{
	if( pEntity && requiredCaps != FCAP_USE_IN_RADIUS )
	{
		C_BliinkItemPickup* pPickup = dynamic_cast<C_BliinkItemPickup*>( pEntity );

		if( pPickup )
			return true;
	}

	return BaseClass::IsUseableEntity( pEntity, requiredCaps );
}

C_BliinkItemPickup::C_BliinkItemPickup( ) : m_GlowObject(this)
{
	m_GlowObject.SetColor( Vector( 0.3f, 0.6f, 0.1f ) );
	m_GlowObject.SetRenderFlags( false, true );
}

void C_BliinkItemPickup::ClientThink()
{
	BaseClass::ClientThink();

	m_GlowObject.SetRenderFlags( false, false );

	// Only render the glow effect when the player is looking at us and we're
	// the first item they see.
	C_BliinkPlayer* pPlayer = ToBliinkPlayer( C_BasePlayer::GetLocalPlayer() );

	if( pPlayer && pPlayer->State_Get() == STATE_BLIINK_SURVIVOR )
	{
		/*// Finding eye position and angles.
		Vector vecStart = pPlayer->EyePosition();
		QAngle eyeAngles = pPlayer->EyeAngles();

		// Finding direction we're looking in.
		Vector vecDir;
		AngleVectors( eyeAngles, &vecDir );
		VectorNormalize( vecDir );

		// Specifiying the end of the trace.
		Vector vecEnd = vecStart + vecDir * 160;

		// Tracing vector.
		trace_t tr;
		UTIL_TraceLine( vecStart, vecEnd, MASK_SOLID|CONTENTS_DEBRIS|CONTENTS_HITBOX, pPlayer, COLLISION_GROUP_NONE, &tr );

		if ( tr.fraction == 1.0f )
			return;*/

		C_BaseEntity* pEntity = pPlayer->FindUseEntity();

		// Determining if we are visible.
		if( pEntity == this )
		{
			m_GlowObject.SetRenderFlags( false, true );
		}
	}
}

void C_BliinkItemPickup::OnDataChanged( DataUpdateType_t updateType )
{
	BaseClass::OnDataChanged( updateType );
 
	if ( updateType == DATA_UPDATE_CREATED )
	{
		SetNextClientThink( CLIENT_THINK_ALWAYS );
	}
}