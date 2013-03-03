#include "cbase.h"

#include "bliink_item_spawner.h"
#include "bliink_item_parse.h"
#include "bliink_item_pickup.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

LINK_ENTITY_TO_CLASS( bliink_item_spawner, CBliinkItemSpawner  );

// Start of our data description for the class
BEGIN_DATADESC( CBliinkItemSpawner  )
	
	// Hammer variables
	DEFINE_KEYFIELD( m_iSpawnerChance[0], FIELD_INTEGER, "item_spawn_chance_1"),
	DEFINE_KEYFIELD( m_iSpawnerChance[1], FIELD_INTEGER, "item_spawn_chance_2"),
	DEFINE_KEYFIELD( m_iSpawnerChance[2], FIELD_INTEGER, "item_spawn_chance_3"),
	DEFINE_KEYFIELD( m_iSpawnerChance[3], FIELD_INTEGER, "item_spawn_chance_4"),
	DEFINE_KEYFIELD( m_iSpawnerChance[4], FIELD_INTEGER, "item_spawn_chance_5"),
	DEFINE_KEYFIELD( m_iSpawnerChance[5], FIELD_INTEGER, "item_spawn_chance_6"),
	DEFINE_KEYFIELD( m_iSpawnerChance[6], FIELD_INTEGER, "item_spawn_chance_7"),
	DEFINE_KEYFIELD( m_iSpawnerChance[7], FIELD_INTEGER, "item_spawn_chance_8"),

	DEFINE_KEYFIELD( m_szItemNames[0], FIELD_STRING, "item_type_1"),
	DEFINE_KEYFIELD( m_szItemNames[1], FIELD_STRING, "item_type_2"),
	DEFINE_KEYFIELD( m_szItemNames[2], FIELD_STRING, "item_type_3"),
	DEFINE_KEYFIELD( m_szItemNames[3], FIELD_STRING, "item_type_4"),
	DEFINE_KEYFIELD( m_szItemNames[4], FIELD_STRING, "item_type_5"),
	DEFINE_KEYFIELD( m_szItemNames[5], FIELD_STRING, "item_type_6"),
	DEFINE_KEYFIELD( m_szItemNames[6], FIELD_STRING, "item_type_7"),
	DEFINE_KEYFIELD( m_szItemNames[7], FIELD_STRING, "item_type_8"),

	DEFINE_KEYFIELD( m_iItemMinQuantity, FIELD_INTEGER, "item_min_quantity"),
	DEFINE_KEYFIELD( m_iItemMaxQuantity, FIELD_INTEGER, "item_max_quantity"),
	DEFINE_KEYFIELD( m_fSpawnMinInterval, FIELD_FLOAT, "spawner_min_interval"),
	DEFINE_KEYFIELD( m_fSpawnMaxInterval, FIELD_FLOAT, "spawner_max_interval"),
	DEFINE_KEYFIELD( m_bSpawnOnlyOnce, FIELD_BOOLEAN, "spawner_only_once"),
	DEFINE_KEYFIELD( m_fSpawnDistanceX, FIELD_FLOAT, "spawner_distance_x"),
	DEFINE_KEYFIELD( m_fSpawnDistanceY, FIELD_FLOAT, "spawner_distance_y"),
	DEFINE_KEYFIELD( m_fSpawnDistanceZ, FIELD_FLOAT, "spawner_distance_z"),

	DEFINE_INPUTFUNC( FIELD_VOID, "BeginSpawning", BeginSpawning ),

END_DATADESC()

CBliinkItemSpawner::CBliinkItemSpawner( void )
{
	m_bHasSpawnedItems = false;
}

// Attempts to perform a spawning.
void CBliinkItemSpawner::Think( void )
{
	RandomSeed( gpGlobals->curtime );
	float fNextSpawnInterval = RandomFloat(m_fSpawnMinInterval, m_fSpawnMaxInterval);

	if( CanSpawnItem() )
		SpawnItems();
	
	SetNextThink( gpGlobals->curtime + fNextSpawnInterval );
}


// Sets up the item types to be used when spawning.
void CBliinkItemSpawner::Spawn( void )
{
	for(int i=0; i<MAX_SPAWNER_ITEMS; i++)
	{
		m_iItemInfoType[i] = GetItemHandle( m_szItemNames[i] );
	}
}

// An input functions which tells us to begin spawning.
void CBliinkItemSpawner::BeginSpawning( inputdata_t &inputdata )
{
	SetNextThink( gpGlobals->curtime );
}

// Checks whether or not we can spawn an item:
// 1. If we're only spawning once or not, and
// 2. If there are no pickups nearby, and
// 3. If there are no players nearby, and
// 4. If we are not in the PVS of a player (disabled for now)
bool CBliinkItemSpawner::CanSpawnItem( void )
{
	if( m_bSpawnOnlyOnce && m_bHasSpawnedItems )
	{
		Msg("Couldn't spawn because I can only spawn once!\n");
		return false;
	}


	if( gEntList.FindEntityByClassnameNearest("bliink_item_pickup", GetAbsOrigin(), SPAWNER_PICKUP_SEARCH_RADIUS) )
	{
		Msg("Couldn't spawn because there's already some pickups near me.\n");
		return false;
	}

	if( gEntList.FindEntityByClassnameNearest("player", GetAbsOrigin(), SPAWNER_PLAYER_SEARCH_RADIUS) )
	{
		Msg("Couldn't spawn because player is near me.\n");
		return false;
	}

	/*CBaseEntity* pEnt = pEnt = UTIL_EntitiesInPVS( this, NULL );

	while( pEnt )
	{
		if( pEnt->IsPlayer() )
		{
			Msg("Couldn't spawn because player could see me.\n");
			return false;
		}

		pEnt = UTIL_EntitiesInPVS( this, pEnt );
	}*/
	
	Msg("OMG I can spawn!\n");

	return true;
}

// Spawns item(s).
void CBliinkItemSpawner::SpawnItems( void )
{
	CBliinkItemPickup* pPickup = NULL;
	int iTotalChance = 0;
	int iChanceAccumulator = 0;
	int iSelectedItem = 0;
	int iSelectedChance = 0;
	int iItemQuantity = RandomInt(m_iItemMinQuantity, m_iItemMaxQuantity);

	for( int k=0; k<iItemQuantity; k++ )
	{
		// Selecting item type to spawn
		for( int i=0; i<MAX_SPAWNER_ITEMS; i++ )
		{
			iTotalChance += m_iSpawnerChance[i];
		}

		iSelectedChance = RandomInt(0, iTotalChance);

		for( int i=0; i<MAX_SPAWNER_ITEMS; i++ )
		{
			iChanceAccumulator += m_iSpawnerChance[i];

			if( iChanceAccumulator >= iSelectedChance )
			{
				iSelectedItem = i;
				break;
			}
		}

		// Item creation
		float dist_x = RandomFloat()*m_fSpawnDistanceX;
		float dist_y = RandomFloat()*m_fSpawnDistanceY;
		float dist_z = RandomFloat()*m_fSpawnDistanceZ;

		Vector spawnOrigin = GetAbsOrigin() + Vector(dist_x,dist_y,dist_z);
		QAngle spawnAngles = GetAbsAngles() + QAngle(0, 0, RandomFloat()*360.0f);

		pPickup = (CBliinkItemPickup*) CBaseEntity::CreateNoSpawn( "bliink_item_pickup", spawnOrigin, spawnAngles);
		pPickup->SetItem( m_iItemInfoType[iSelectedItem] );
		DispatchSpawn( pPickup );
	}
	
	m_bHasSpawnedItems = true;
}