#include "cbase.h"

#include "bliink_item_pickup.h"
#include "bliink_item_base.h"
#include "bliink_item_parse.h"
#include "baseentity.h"
#include "bliink_player.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

LINK_ENTITY_TO_CLASS( bliink_item_pickup, CBliinkItemPickup );

// Networked so it glows on client side.
IMPLEMENT_SERVERCLASS_ST( CBliinkItemPickup, DT_BliinkItemPickup )
	// ...
END_SEND_TABLE()

CBliinkItemPickup::CBliinkItemPickup( ) : CItem()
{
	pItem = NULL;
}

void CBliinkItemPickup::Spawn( void )
{
	if( pItem )
	{
		PrecacheModel( pItem->GetItemData().szWorldModel );
		SetModel( pItem->GetItemData().szWorldModel );
	}

	BaseClass::Spawn();
}

void CBliinkItemPickup::Use( CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value )
{
	if( !pActivator )
		return;

	CBliinkPlayer* pPlayer = ToBliinkPlayer( pActivator );

	// Attempt to add to inventory
	if( pActivator->IsPlayer() && pPlayer && pPlayer->State_Get() == STATE_BLIINK_SURVIVOR )
	{
		bool bAdded = false;

		// If my item isn't NULL then add it to the 
		if( pItem )
			bAdded = pPlayer->GetBliinkInventory().AddItem( pItem );

		// Remove me from the world if I was successfully added.
		if( bAdded )
		{
			Remove();
			pPlayer->GetBliinkInventory().Debug_PrintInventory();
		} else {
			Msg("Inventory full, could not add item\n");
		}
	}
}

void CBliinkItemPickup::SetItem( BLIINK_ITEM_INFO_HANDLE hItemType )
{
	pItem = CreateItemByHandle( hItemType );
}

void CBliinkItemPickup::SetItem( IBliinkItem* pItemToSet )
{
	if( pItemToSet )
		pItem = pItemToSet;
}