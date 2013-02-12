#include "cbase.h"
#include <KeyValues.h>
#include <tier0/mem.h>
#include "filesystem.h"
#include "utldict.h"
#include "bliink_item_parse.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// Name -> enum conversion.
//-----------------------------------------------------------------------------
struct stringEnum_t
{
	char *szString;
	int szValue;
};

// Conversion function.
int stringToEnum( const char *szString, stringEnum_t *table, int tableSize )
{
	for(int i=0; i<tableSize; i++)
	{
		if( Q_strcmp(szString, table[i].szString) == 0 )
			return table[i].szValue;
	}

	return 0;
}

//-----------------------------------------------------------------------------
// Item types.
//-----------------------------------------------------------------------------
enum
{
	ITEM_TYPE_EMPTY=0,
	ITEM_TYPE_LOCKED,
	ITEM_TYPE_WEAPON,
	ITEM_TYPE_AMMO,
	ITEM_TYPE_CONSUMABLE,
	ITEM_TYPE_MATERIAL
} Bliink_Item_Types;

#define ITEM_TYPE_COUNT 6

stringEnum_t g_typeStrings[ITEM_TYPE_COUNT] =
{
	{"ITEM_TYPE_EMPTY", ITEM_TYPE_EMPTY},
	{"ITEM_TYPE_LOCKED", ITEM_TYPE_LOCKED},
	{"ITEM_TYPE_WEAPON", ITEM_TYPE_WEAPON},
	{"ITEM_TYPE_AMMO", ITEM_TYPE_AMMO},
	{"ITEM_TYPE_CONSUMABLE", ITEM_TYPE_CONSUMABLE},
	{"ITEM_TYPE_MATERIAL", ITEM_TYPE_MATERIAL},
};

//-----------------------------------------------------------------------------
// Item sub-types.
//-----------------------------------------------------------------------------
enum
{
	ITEM_STYPE_BLANK=0,
	ITEM_STYPE_WEAPONS_BEGIN,
	// ...
	ITEM_STYPE_WEAPONS_END,
	ITEM_STYPE_AMMO_BEGIN,
	// ...
	ITEM_STYPE_AMMO_END,
	ITEM_STYPE_CONSUMABLES_BEGIN,
	// ...
	ITEM_STYPE_CONSUMABLES_END,
	ITEM_STYPE_MATERIALS_BEGIN,
	// ...
	ITEM_STYPE_MATERIALS_END
} Bliink_Item_SubTypes;

#define ITEM_STYPE_COUNT 1

stringEnum_t g_subTypeStrings[ITEM_STYPE_COUNT] =
{
	{"ITEM_STYPE_BLANK", ITEM_STYPE_BLANK},
};

//-----------------------------------------------------------------------------
// Database storing item description information. Accessed using item subtype.
//-----------------------------------------------------------------------------
static CUtlDict< CBliinkItemInfo*, BLIINK_ITEM_INFO_HANDLE > m_ItemInfoDatabase;

//-----------------------------------------------------------------------------
// CBliinkItemInfo definition.
//-----------------------------------------------------------------------------
CBliinkItemInfo::CBliinkItemInfo()
{
	// Name and description of the item.
	szItemName[0] = 0;
	szItemDesc[0] = 0;

	// Item type.
	m_iType = ITEM_TYPE_EMPTY;
	m_iSubType = ITEM_STYPE_BLANK;

	// Item behaviors.
	m_bCanStack = false;
	m_iMaxStack = 1;

	// Weapon-specific.
	szWeaponClassName[0] = 0;

	// Ammo-specific
	szAmmoType[0] = 0;
}

// Parses item data from a KeyValues structure.
void CBliinkItemInfo::Parse( KeyValues *pKeyValuesData, const char *szItemName )
{
	// Name and description of the item.
	Q_strncpy( this->szItemName, szItemName, MAX_ITEM_STRING );
	Q_strncpy( szItemDesc, pKeyValuesData->GetString( "description", ""), MAX_ITEM_DESC_STRING);

	// Item type.
	m_iType = stringToEnum( pKeyValuesData->GetString( "item_type", "ITEM_TYPE_EMPTY" ), g_typeStrings, ITEM_TYPE_COUNT );
	m_iSubType = stringToEnum( pKeyValuesData->GetString( "item_subtype", "ITEM_STYPE_BLANK" ), g_subTypeStrings, ITEM_STYPE_COUNT);

	// Item behaviors.
	m_bCanStack = pKeyValuesData->GetBool( "can_stack", false );
	m_iMaxStack =  pKeyValuesData->GetInt( "max_stack", false );

	// Weapon-specific.
	Q_strncpy( szWeaponClassName, pKeyValuesData->GetString( "weapon_name", "none"), MAX_WEAPON_STRING );

	// Ammo-specific
	Q_strncpy( szAmmoType, pKeyValuesData->GetString( "ammo_type", "none"), MAX_WEAPON_STRING );
}

// Allows items to access item description database.
CBliinkItemInfo *GetItemInfo( BLIINK_ITEM_INFO_HANDLE handle )
{
	// Making sure we can't access stuff we're not meant to.
	Assert(
		handle != ITEM_STYPE_WEAPONS_BEGIN &&
		handle != ITEM_STYPE_WEAPONS_END &&
		handle != ITEM_STYPE_AMMO_BEGIN &&
		handle != ITEM_STYPE_AMMO_END &&
		handle != ITEM_STYPE_CONSUMABLES_BEGIN &&
		handle != ITEM_STYPE_CONSUMABLES_END &&
		handle != ITEM_STYPE_MATERIALS_BEGIN &&
		handle != ITEM_STYPE_MATERIALS_END
	);
	
	if( m_ItemInfoDatabase.IsValidIndex( handle ) )
		return m_ItemInfoDatabase[ handle ];
	else
		return NULL;
}

// Loads item description database from resource file.
void PrecacheBliinkItemInfo( const char *szFileName )
{
	// Load KeyValues file.
	KeyValues *pKV = new KeyValues( "BliinkItemList" );

	// Create BliinkItemInfo for each item description, parse the KeyValues, and
	// then insert into the database.
}

//-----------------------------------------------------------------------------
// Pre-caching item info list.
//-----------------------------------------------------------------------------
PRECACHE_REGISTER_BEGIN( GLOBAL, CBliinkItemInfo )
	PRECACHE( BLIINK_ITEM_LIST, "bliink_item_list" )
PRECACHE_REGISTER_END()