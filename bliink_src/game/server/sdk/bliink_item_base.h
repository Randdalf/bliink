#ifndef BLIINK_ITEM_BASE_H
#define BLIINK_ITEM_BASE_H

#ifdef _WIN32
#pragma once
#endif

#include "weapon_sdkbase.h"
#include "bliink_item_parse.h"

class CBliinkItemWeapon;
class CBliinkItemMaterial;
class CBliinkItemAmmo;
class CBliinkItemConsumable;

//-----------------------------------------------------------------------------
// IBliinkItem
// An item that is stored inside an inventory or a pickup. To create a new type
// of item, you must implement this interface.
//-----------------------------------------------------------------------------
class IBliinkItem
{
public:
	IBliinkItem(BLIINK_ITEM_INFO_HANDLE hItemHandle)
	{
		if( GetItemInfo(hItemHandle) )
			m_hInfoHandle = hItemHandle;
		else
			m_hInfoHandle = GetInvalidItemHandle();

		m_iStackCount = 1;
	}

	virtual bool	IsConsumable() { return false; }
	virtual bool	IsAmmo() { return false; }
	virtual bool	IsWeapon() { return false; }
	virtual bool	IsMaterial() { return false; }
	virtual bool	IsStackable() { return false; }
	virtual int		GetStackCount() { return m_iStackCount; }
	virtual bool	CanStackWith( IBliinkItem* item ) { return false; }

	CBliinkItemInfo &GetItemData() const
	{
		CBliinkItemInfo* data = GetItemInfo( m_hInfoHandle );
		
		if( data )
			return *data;
		else
			return CBliinkItemInfo();
	}

protected:
	BLIINK_ITEM_INFO_HANDLE m_hInfoHandle;

	int m_iStackCount;
};

//-----------------------------------------------------------------------------
// GetItemByName
// Allows creation of items by their handle e.g. "material_gold"
//-----------------------------------------------------------------------------
static IBliinkItem* CreateItemByHandle(BLIINK_ITEM_INFO_HANDLE hHandle)
{
	CBliinkItemInfo* info = GetItemInfo( hHandle );

	if( !info )
		return NULL;

	switch( info->m_iType )
	{
	case ITEM_TYPE_WEAPON:
		return new CBliinkItemWeapon( hHandle );
		break;
	case ITEM_TYPE_AMMO:
		return new CBliinkItemAmmo( hHandle );
		break;
	case ITEM_TYPE_CONSUMABLE:
		return new CBliinkItemConsumable( hHandle );
		break;
	case ITEM_TYPE_MATERIAL:
		return new CBliinkItemMaterial( hHandle );
		break;
	default:
		return NULL;
	}
}

//-----------------------------------------------------------------------------
// CBliinkItemWeapon
//-----------------------------------------------------------------------------
class CBliinkItemWeapon : public IBliinkItem
{
public:
	CBliinkItemWeapon(BLIINK_ITEM_INFO_HANDLE hItemHandle) : IBliinkItem( hItemHandle )
	{
		m_hLinkedWeapon = NULL;
	}

	bool	IsWeapon() { return true; }
	bool	IsStackable() { return false; }

	CWeaponSDKBase*		CreateAndLinkWeapon( void );

private:
	CWeaponSDKBase*		m_hLinkedWeapon;
	//bool				m_b
};

//-----------------------------------------------------------------------------
// CBliinkItemWeapon
//-----------------------------------------------------------------------------
class CBliinkItemAmmo : public IBliinkItem
{
public:
	CBliinkItemAmmo(BLIINK_ITEM_INFO_HANDLE hItemHandle) : IBliinkItem( hItemHandle )
	{
	}
};

//-----------------------------------------------------------------------------
// CBliinkItemConsumable
//-----------------------------------------------------------------------------
class CBliinkItemConsumable : public IBliinkItem
{
public:
	CBliinkItemConsumable(BLIINK_ITEM_INFO_HANDLE hItemHandle) : IBliinkItem( hItemHandle )
	{
	}
};

//-----------------------------------------------------------------------------
// CBliinkItemMaterial
//-----------------------------------------------------------------------------
class CBliinkItemMaterial : public IBliinkItem
{
public:
	CBliinkItemMaterial(BLIINK_ITEM_INFO_HANDLE hItemHandle) : IBliinkItem( hItemHandle )
	{
	}
};

#endif // BLIINK_ITEM_BASE_H