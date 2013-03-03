#ifndef BLIINK_ITEM_PICKUP_H
#define BLIINK_ITEM_PICKUP_H

#include "cbase.h"
#include "bliink_item_parse.h"
#include "bliink_item_base.h"
#include "items.h"

//-----------------------------------------------------------------------------
// CBliinkItemPickup
// An item resident in the game world which can be picked up by players and
// added to their inventory. They can also be created by bliink_item_spawners.
//-----------------------------------------------------------------------------
class CBliinkItemPickup : public CItem
{
public:
	DECLARE_SERVERCLASS();
	DECLARE_CLASS( CBliinkItemPickup, CItem );

	CBliinkItemPickup(  );

	virtual void Spawn( void );

	void ItemTouch( CBaseEntity *pOther ) { };
	virtual void Use( CBaseEntity *pActivator, CBaseEntity *pCaller, USE_TYPE useType, float value );
	void SetItem( BLIINK_ITEM_INFO_HANDLE hItemType );
	void SetItem( IBliinkItem* pItemToSet );

private:
	IBliinkItem*	pItem;
};

#endif // BLIINK_ITEM_PICKUP_H