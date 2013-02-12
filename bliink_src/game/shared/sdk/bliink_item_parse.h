#ifndef BLIINK_ITEM_PARSE_H
#define BLIINK_ITEM_PARSE_H

#ifdef _WIN32
#pragma once
#endif

#include "weapon_parse.h"

typedef unsigned int BLIINK_ITEM_INFO_HANDLE;

#define MAX_ITEM_STRING 80
#define MAX_ITEM_DESC_STRING 140

//-----------------------------------------------------------------------------
// Item types.
//-----------------------------------------------------------------------------
enum Bliink_Item_Types;

//-----------------------------------------------------------------------------
// Item sub-types.
//-----------------------------------------------------------------------------
enum Bliink_Item_SubTypes;

//-----------------------------------------------------------------------------
// Description of an item type.
//-----------------------------------------------------------------------------
class CBliinkItemInfo
{
public:
	CBliinkItemInfo();

	void Parse( KeyValues *pKeyValuesData, const char *szItemName );

public:
	// Name and description of the item.
	char	szItemName[MAX_ITEM_STRING];
	char	szItemDesc[MAX_ITEM_DESC_STRING];

	// Item type.
	int		m_iType;
	int		m_iSubType;

	// Item behaviors.
	bool	m_bCanStack;
	int		m_iMaxStack;

	// Weapon-specific.
	char	szWeaponClassName[MAX_WEAPON_STRING];

	// Ammo-specific
	char	szAmmoType[MAX_WEAPON_STRING];

	// Inventory icon.
	// <INSERT HERE>
};

// Allows items to access item description database.
CBliinkItemInfo *GetItemInfo( BLIINK_ITEM_INFO_HANDLE handle );

// Loads item description database from resource file.
void PrecacheBliinkItemInfo( const char *szFileName );

#endif // BLIINK_ITEM_PARSE_H