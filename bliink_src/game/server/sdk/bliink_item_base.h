#ifndef BLIINK_ITEM_BASE_H
#define BLIINK_ITEM_BASE_H

#ifdef _WIN32
#pragma once
#endif

#include "weapon_sdkbase.h"
#include "bliink_item_parse.h"

//-----------------------------------------------------------------------------
// IBliinkItem
// An item that is stored inside an inventory or a pickup. To create a new type
// of item, you must implement this interface.
//-----------------------------------------------------------------------------
class IBliinkItem
{
public:
	virtual bool	IsConsumable() { return false; }
	virtual bool	IsAmmo() { return false; }
	virtual bool	IsWeapon() { return false; }
	virtual bool	IsMaterial() { return false; }
	virtual bool	IsStackable() { return false; }
	virtual int		GetStackCount() { return m_iStackCount; }

	CBliinkItemInfo &GetItemInfo() const;

private:
	BLIINK_ITEM_INFO_HANDLE m_hInfoHandle;

	int m_iStackCount;
};

//-----------------------------------------------------------------------------
// CBliinkItemWeapon
// A test implementation of an IBliinkItem...
//-----------------------------------------------------------------------------
/*class CBliinkItemWeapon : IBliinkItem
{
public:
	CBliinkItemWeapon()
	{
		m_iType = ITEM_TYPE_WEAPON;
		m_iSubType = GetItemInfo().GetSubType();
	}

	virtual bool	IsWeapon() { return true; }		

private:
	CWeaponSDKBase*		m_hLinkedWeapon;
	//bool				m_b
};*/

#endif // BLIINK_ITEM_BASE_H