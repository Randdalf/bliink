#include "cbase.h"

#include "bliink_item_spawner.h"
#include "bliink_item_parse.h"
#include "bliink_item_pickup.h"

class CBliinkRoamingSpawner: public CLogicalEntity
{
public:
	DECLARE_CLASS( CBliinkRoamingSpawner, CLogicalEntity );
	DECLARE_DATADESC();

	CBliinkRoamingSpawner( void );

	virtual void	Think( void );
	virtual void	Spawn( void );
	bool			CanSpawnNPC( void );
	void			SpawnNPC( void );
	void			BeginSpawning( inputdata_t &inputdata );
	void			NPCDied( void );

private:
	bool						m_bNPCAlive;
	bool						m_bIsCamp;
	bool						m_bHasLegs;

	// Fixed variables
	const char*					m_szNPCname;
};

class CBliinkBliinker;
class CBliinkWalker;
class CBliinkCrawler;