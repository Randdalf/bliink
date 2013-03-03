#ifndef BLIINK_ITEM_BASE_H
#define BLIINK_ITEM_BASE_H

#ifdef _WIN32
#pragma once
#endif

#include "weapon_sdkbase.h"
#include "bliink_item_parse.h"

// Whether two items can stack together or not.
bool CanStack( BLIINK_ITEM_INFO_HANDLE hItemHandle1, BLIINK_ITEM_INFO_HANDLE hItemHandle2 );

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
	}

	virtual bool	IsConsumable() { return false; }
	virtual bool	IsAmmo() { return false; }
	virtual bool	IsWeapon() { return false; }
	virtual bool	IsMaterial() { return false; }
	virtual bool	IsStackable() { return GetItemData().m_bCanStack; }

	virtual bool	CanStackWith( IBliinkItem* pItem )
	{
		return CanStack(m_hInfoHandle, pItem->GetInfoHandle());
	}

	CBliinkItemInfo &GetItemData() const
	{
		return *GetItemInfo( m_hInfoHandle );
	}

	BLIINK_ITEM_INFO_HANDLE GetInfoHandle() const
	{
		return m_hInfoHandle;
	}

protected:
	BLIINK_ITEM_INFO_HANDLE m_hInfoHandle;
};

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

//-----------------------------------------------------------------------------
// GetItemByName
// Allows creation of items by their handle e.g. "material_gold"
//-----------------------------------------------------------------------------
IBliinkItem* CreateItemByHandle(BLIINK_ITEM_INFO_HANDLE hHandle);

#endif // BLIINK_ITEM_BASE_H