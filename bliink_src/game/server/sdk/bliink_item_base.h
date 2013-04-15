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

	~CBliinkItemWeapon()
	{
		if( m_hLinkedWeapon )
			UTIL_Remove( m_hLinkedWeapon );
	}

	bool				IsWeapon() { return true; }
	bool				IsStackable() { return false; } 

	// Item can't create weapon itself because it needs to know origin/angles.
	bool				HasWeapon() { return !(m_hLinkedWeapon == NULL); }
	CWeaponSDKBase*		GetWeapon() { return m_hLinkedWeapon; }
	void				SetWeapon( CWeaponSDKBase* pWeapon)
	{
		m_hLinkedWeapon = pWeapon;
	}

private:
	CWeaponSDKBase*		m_hLinkedWeapon;
};

//-----------------------------------------------------------------------------
// CBliinkItemWeapon
//-----------------------------------------------------------------------------
class CBliinkItemAmmo : public IBliinkItem
{
public:
	CBliinkItemAmmo(BLIINK_ITEM_INFO_HANDLE hItemHandle) : IBliinkItem( hItemHandle )
	{
		CBliinkItemInfo* pItemInfo = GetItemInfo( hItemHandle );

		m_iMaxAmmo = pItemInfo->m_iAmmoClip;
		m_iAmmo = m_iMaxAmmo;
	}

	bool IsAmmo() { return true; }

	// Return the ammo, for this active weapon. Set the clip size if we
	// haven't set it before.
	int GetAmmo( )
	{
		return m_iAmmo;
	}

	// Used when dropping stacks of ammo, resets this ammo count to full.
	void ResetAmmo()
	{
		m_iAmmo = m_iMaxAmmo;
	}

	// Sets our ammo.
	void SetAmmo( int iAmmoAmount )
	{
		m_iAmmo = iAmmoAmount;
	}


private:
	int		m_iAmmo;
	int		m_iMaxAmmo;
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

	virtual bool	IsConsumable() { return true; }

	void Consume( CBliinkPlayer* pConsumer );
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