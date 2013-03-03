#ifndef BLIINK_ITEM_SPAWNER_H
#define BLIINK_ITEM_SPAWNER_H

#include "cbase.h"

#include "bliink_item_parse.h"

class CBliinkItemPickup;

#define MAX_SPAWNER_ITEMS 8
#define SPAWNER_PICKUP_SEARCH_RADIUS 96
#define SPAWNER_PLAYER_SEARCH_RADIUS 256

//-----------------------------------------------------------------------------
// CBliinkItemSpawner
// An item spawner, will randomly spawn items from its list of items at the
// given time interval and 
//-----------------------------------------------------------------------------
class CBliinkItemSpawner : public CLogicalEntity
{
public:
	DECLARE_CLASS( CBliinkItemSpawner, CLogicalEntity );
	DECLARE_DATADESC();

	CBliinkItemSpawner( void );

	virtual void	Think( void );
	virtual void	Spawn( void );
	bool			CanSpawnItem( void );
	void			SpawnItems( void );
	void			BeginSpawning( inputdata_t &inputdata );

private:
	BLIINK_ITEM_INFO_HANDLE		m_iItemInfoType[MAX_SPAWNER_ITEMS];
	bool						m_bHasSpawnedItems;

	// Fixed variables
	unsigned int				m_iSpawnerChance[MAX_SPAWNER_ITEMS];
	const char*					m_szItemNames[MAX_SPAWNER_ITEMS];
	unsigned int				m_iItemMinQuantity;
	unsigned int				m_iItemMaxQuantity;
	float						m_fSpawnMinInterval;
	float						m_fSpawnMaxInterval;
	bool						m_bSpawnOnlyOnce;
	float						m_fSpawnDistanceX;
	float						m_fSpawnDistanceY;
	float						m_fSpawnDistanceZ;
};

#endif // BLIINK_ITEM_SPAWNER_H