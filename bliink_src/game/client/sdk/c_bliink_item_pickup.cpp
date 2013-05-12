#include "cbase.h"

#include "glow_outline_effect.h"
#include "c_bliink_player.h"
#include "c_bliink_item_pickup.h"
#include "bliink_item_parse.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

LINK_ENTITY_TO_CLASS( bliink_item_pickup, C_BliinkItemPickup );

// This works although VS thinks it doesn't
IMPLEMENT_CLIENTCLASS_DT( C_BliinkItemPickup, DT_BliinkItemPickup, CBliinkItemPickup )
	RecvPropInt( RECVINFO( m_hInfoHandle ) )
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

	m_hInfoHandle = GetItemHandle( "empty_item" );
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