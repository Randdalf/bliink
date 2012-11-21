#ifndef BLIINK_ITEM_BASE_H
#define BLIINK_ITEM_BASE_H

#ifdef _WIN32
#pragma once
#endif

#include "weapon_sdkbase.h"

class CBliinkItemInfo;

enum
{
	ITEM_TYPE_EMPTY,
	ITEM_TYPE_LOCKED,
	ITEM_TYPE_WEAPON,
	ITEM_TYPE_AMMO,
	ITEM_TYPE_CONSUMABLE,
	ITEM_TYPE_MATERIAL
} Bliink_Item_Types;

typedef BLIINK_ITEM_INFO_HANDLE unsigned int;

//-----------------------------------------------------------------------------
// IBliinkItem
// An item that is stored inside an inventory or a pickup. To create a new type
// of item, you must implement this class.
//-----------------------------------------------------------------------------
abstract class IBliinkItem
{
public:
	virtual bool	IsConsumable() { return false; }
	virtual bool	IsAmmo() { return false; }
	virtual bool	IsWeapon() { return false; }
	virtual int		GetItemType() { return m_iType; }
	virtual int		GetItemSubType() { return m_iSubType; }

	CBliinkItemInfo &GetItemInfo() const
	/*{
		retrieve object from dictionary...
	}*/;

private:
	BLIINK_ITEM_INFO_HANDLE m_hInfoHandle;	

	int		m_iType;
	int		m_iSubType;
};

//-----------------------------------------------------------------------------
// CBliinkItemWeapon
// A test implementation of an IBliinkItem...
//-----------------------------------------------------------------------------
class CBliinkItemWeapon : IBliinkItem
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
};

#endif // BLIINK_ITEM_BASE_H