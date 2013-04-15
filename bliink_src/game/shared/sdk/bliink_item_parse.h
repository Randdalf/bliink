#ifndef BLIINK_ITEM_PARSE_H
#define BLIINK_ITEM_PARSE_H

#ifdef _WIN32
#pragma once
#endif

#include "weapon_parse.h"

typedef unsigned short BLIINK_ITEM_INFO_HANDLE;

#define MAX_ITEM_STRING 80
#define MAX_ITEM_DESC_STRING 140

//-----------------------------------------------------------------------------
// Item types.
//-----------------------------------------------------------------------------
typedef enum
{
	ITEM_TYPE_NONE=0,
	ITEM_TYPE_WEAPON,
	ITEM_TYPE_AMMO,
	ITEM_TYPE_CONSUMABLE,
	ITEM_TYPE_MATERIAL
} Bliink_Item_Types;

//-----------------------------------------------------------------------------
// Item sub-types.
//-----------------------------------------------------------------------------
typedef enum
{
	ITEM_STYPE_EMPTY=0,
	ITEM_STYPE_LOCKED,

	ITEM_STYPE_WEAPONS_BEGIN,
	// ...
	ITEM_STYPE_WEAPONS_END,

	ITEM_STYPE_AMMO_BEGIN,
	ITEM_STYPE_AMMO_NORMAL,
	ITEM_STYPE_AMMO_POISON,
	ITEM_STYPE_AMMO_FOGGED,
	ITEM_STYPE_AMMO_FIRE,
	ITEM_STYPE_AMMO_SLOW,
	ITEM_STYPE_AMMO_END,

	ITEM_STYPE_CONSUMABLES_BEGIN,
	ITEM_STYPE_CONSUMABLE_HEALTH,
	ITEM_STYPE_CONSUMABLE_FOOD,
	ITEM_STYPE_CONSUMABLE_BOOSTER,
	ITEM_STYPE_CONSUMABLES_END,

	ITEM_STYPE_MATERIALS_BEGIN,
	// ...
	ITEM_STYPE_MATERIALS_END
} Bliink_Item_SubTypes;

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
	int		m_iAmmoClip;

	// Consumable-specific
	int		m_iConsumeValue;

	// World model
	char	szWorldModel[128];

	// Inventory icon.
	// <INSERT HERE>
};

// Allows items to access item description database.
CBliinkItemInfo *GetItemInfo( BLIINK_ITEM_INFO_HANDLE handle );

// Returns the handle into the database for an item of a specified name.
BLIINK_ITEM_INFO_HANDLE GetItemHandle( const char* szItemName );

// Returns the invalid index into the database for use in comparison.
WEAPON_FILE_INFO_HANDLE GetInvalidItemHandle( void );

// Loads item description database from resource file.
void PrecacheBliinkItemInfo( const char *szFileName );

#endif // BLIINK_ITEM_PARSE_H