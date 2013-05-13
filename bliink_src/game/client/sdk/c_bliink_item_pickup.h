#ifndef BLIINK_ITEM_PICKUP_H
#define BLIINK_ITEM_PICKUP_H

#include "cbase.h"

#include "bliink_item_parse.h"

//-----------------------------------------------------------------------------
// C_BliinkItemPickup
// Used for adding the glow effect to item pickups when the player is looking
// at them.
//-----------------------------------------------------------------------------
class C_BliinkItemPickup : public C_BaseAnimating
{	
public:
	DECLARE_CLASS( C_BliinkItemPickup, C_BaseAnimating );
	DECLARE_CLIENTCLASS();

	C_BliinkItemPickup( );

	virtual void ClientThink();
	virtual void OnDataChanged( DataUpdateType_t updateType );

	BLIINK_ITEM_INFO_HANDLE GetHandle( void ) { return m_hInfoHandle; }

private:
	CGlowObject m_GlowObject;
	BLIINK_ITEM_INFO_HANDLE m_hInfoHandle;
	
};

#endif // BLIINK_ITEM_PICKUP_H