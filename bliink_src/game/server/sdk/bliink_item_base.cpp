#include "cbase.h"

#include "bliink_item_base.h"
#include "bliink_item_parse.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

bool CanStack( BLIINK_ITEM_INFO_HANDLE hItemHandle1, BLIINK_ITEM_INFO_HANDLE hItemHandle2 )
{	
	if( hItemHandle1 == hItemHandle2 && GetItemInfo(hItemHandle1)->m_bCanStack )
		return true;
	else
		return false;
}

IBliinkItem* CreateItemByHandle(BLIINK_ITEM_INFO_HANDLE hHandle)
{
	CBliinkItemInfo* info = GetItemInfo( hHandle );

	if( !info )
		return NULL;

	switch( info->m_iType )
	{
	case ITEM_TYPE_WEAPON:
		return new CBliinkItemWeapon( hHandle );
	case ITEM_TYPE_AMMO:
		return new CBliinkItemAmmo( hHandle );
	case ITEM_TYPE_CONSUMABLE:
		return new CBliinkItemConsumable( hHandle );
	case ITEM_TYPE_MATERIAL:
		return new CBliinkItemMaterial( hHandle );
	default:
		return NULL;
	}
}