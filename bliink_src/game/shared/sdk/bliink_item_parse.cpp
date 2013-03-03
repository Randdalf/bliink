#include "cbase.h"
#include <KeyValues.h>
#include <tier0/mem.h>
#include "filesystem.h"
#include "utldict.h"
#include "bliink_item_parse.h"
#include "weapon_parse.h"

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
#define ITEM_TYPE_COUNT 5

stringEnum_t g_typeStrings[ITEM_TYPE_COUNT] =
{
	{"ITEM_TYPE_NONE", ITEM_TYPE_NONE},
	{"ITEM_TYPE_WEAPON", ITEM_TYPE_WEAPON},
	{"ITEM_TYPE_AMMO", ITEM_TYPE_AMMO},
	{"ITEM_TYPE_CONSUMABLE", ITEM_TYPE_CONSUMABLE},
	{"ITEM_TYPE_MATERIAL", ITEM_TYPE_MATERIAL},
};

//-----------------------------------------------------------------------------
// Item sub-types.
//-----------------------------------------------------------------------------
#define ITEM_STYPE_COUNT 1

stringEnum_t g_subTypeStrings[ITEM_STYPE_COUNT] =
{
	{"ITEM_STYPE_EMPTY", ITEM_STYPE_EMPTY},
};

//-----------------------------------------------------------------------------
// Database storing item description information.
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
	m_iType = ITEM_TYPE_NONE;
	m_iSubType = ITEM_STYPE_EMPTY;

	// Item behaviors.
	m_bCanStack = false;
	m_iMaxStack = 1;

	// Weapon-specific.
	szWeaponClassName[0] = 0;

	// Ammo-specific.
	szAmmoType[0] = 0;

	// World model.
	szWorldModel[0] = 0;
}

// Parses item data from a KeyValues structure.
void CBliinkItemInfo::Parse( KeyValues *pKeyValuesData, const char *szItemName )
{
	// Name and description of the item.
	Q_strncpy( this->szItemName, szItemName, MAX_ITEM_STRING );
	Q_strncpy( szItemDesc, pKeyValuesData->GetString( "description", ""), MAX_ITEM_DESC_STRING);

	// Item type.
	m_iType = stringToEnum( pKeyValuesData->GetString( "item_type", "ITEM_TYPE_EMPTY" ), g_typeStrings, ITEM_TYPE_COUNT );
	m_iSubType = stringToEnum( pKeyValuesData->GetString( "item_subtype", "ITEM_STYPE_BLANK" ), g_subTypeStrings, ITEM_STYPE_COUNT );

	// Item behaviors.
	m_bCanStack = pKeyValuesData->GetBool( "can_stack", false );
	m_iMaxStack =  pKeyValuesData->GetInt( "max_stack", false );

	// Weapon-specific.
	Q_strncpy( szWeaponClassName, pKeyValuesData->GetString( "weapon_name", "none"), MAX_WEAPON_STRING );

	// Ammo-specific
	Q_strncpy( szAmmoType, pKeyValuesData->GetString( "ammo_type", "none"), MAX_WEAPON_STRING );

	// Ammo-specific
	Q_strncpy( szWorldModel, pKeyValuesData->GetString( "world_model", "models/weapons/w_smg_mp5.mdl"), 128 );
}

// Allows items to access item description database.
CBliinkItemInfo *GetItemInfo( BLIINK_ITEM_INFO_HANDLE handle )
{	
	if( m_ItemInfoDatabase.IsValidIndex( handle ) )
		return m_ItemInfoDatabase[ handle ];
	else
		return NULL;
}

// Returns the handle into the database for an item of a specified name.
BLIINK_ITEM_INFO_HANDLE GetItemHandle( const char* szItemName )
{	
	return m_ItemInfoDatabase.Find( szItemName );
}

// Returns the invalid index into the database for use in comparison.
BLIINK_ITEM_INFO_HANDLE GetInvalidItemHandle( void )
{
	return (BLIINK_ITEM_INFO_HANDLE)m_ItemInfoDatabase.InvalidIndex();
}

// Loads item description database from resource file.
void PrecacheBliinkItemInfo( const char *szFileName )
{
	// If the database isn't empty, don't precache.
	if( m_ItemInfoDatabase.Count() )
		return;

	// Load KeyValues file.
	KeyValues *pKV = new KeyValues( "BliinkItemListfile" );
	pKV->UsesEscapeSequences( true );

	// Create BliinkItemInfo for each item description, parse the KeyValues, and
	// then insert into the database.
	pKV->LoadFromFile( filesystem, "scripts/bliink_item_list.txt", "GAME" );
	
	Msg("--LOADING BLIINK ITEMS FILE--\n");
	
	CBliinkItemInfo* insert;

	for( KeyValues *sub = pKV->GetFirstSubKey(); sub; sub = sub->GetNextKey() )
	{
		const char* szItemName = sub->GetName();

		// Parsing data.
		insert = new CBliinkItemInfo;
		insert->Parse(sub, szItemName);

		Msg( "adding item: '%s'...\n", szItemName );

		// Precache models/textures here...
		CBaseEntity::PrecacheModel( insert->szWorldModel );

		// Inserting into database.
		m_ItemInfoDatabase.Insert(szItemName, insert);
	}

	pKV->deleteThis();
}

//-----------------------------------------------------------------------------
// Pre-caching item info list.
//-----------------------------------------------------------------------------
PRECACHE_REGISTER_BEGIN( GLOBAL, CBliinkItemInfo )
	PRECACHE( BLIINK_ITEM_LIST, "bliink_item_list" )
PRECACHE_REGISTER_END()