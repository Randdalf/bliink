#ifndef BLIINK_ITEM_SPAWNER_H
#define BLIINK_ITEM_SPAWNER_H

#include "bliink_item_parse.h"
#ifndef CLIENT_DLL
#include "bliink_item_base.h"
#endif
#define INVENTORY_MAX_SLOTS 20
#define INVENTORY_WEAPON_SLOTS 5

#ifdef CLIENT_DLL
#define CBliinkItemInventory C_BliinkItemInventory
#endif

//-----------------------------------------------------------------------------
// CBliinkItemInventory
// An inventory containing CBliinkItems. It is predicted on the client side,
// and controlled using client commands which are hooks for the drag-and-drop
// inventory UI.
//-----------------------------------------------------------------------------
class CBliinkItemInventory
{
	DECLARE_CLASS_NOBASE( CBliinkItemInventory );
	DECLARE_EMBEDDED_NETWORKVAR();
	DECLARE_PREDICTABLE();

public:
	CBliinkItemInventory();

	// Command methods
	void Command_Move(int iFromSlot, int iToSlot);
	void Command_Craft(int iFromSlot, int iToSlot);
	void Command_Drop(int iFromSlot);
	void Command_Consume(int iFromSlot);
	void Command_Meltdown(int iFromSlot);
	void Command_SetNextAmmoType(); // caller?

	// Other methods
#ifndef CLIENT_DLL
	bool AddItem( IBliinkItem* pNewItem );
	void Debug_PrintInventory( void );
#endif

private:
	// List of item definitions in each slot
	CNetworkArray( BLIINK_ITEM_INFO_HANDLE, m_iItemTypes, INVENTORY_MAX_SLOTS );

	// List of stack counts for each item
	CNetworkArray( unsigned int, m_iStackCounts, INVENTORY_MAX_SLOTS );
	
	// List of ammo stuff (TODO)
	// ...

#ifndef CLIENT_DLL
	// List of pointers to items
	IBliinkItem* m_pInventory[INVENTORY_MAX_SLOTS];

	// Player who owns this inventory, used when dealing with weapons.
	CBliinkPlayer* pOwner;

public:

	// Sets the owner of this inventory.
	void SetOwner( CBliinkPlayer* pPlayer ) { pOwner = pPlayer; }
#endif
};

#endif // BLIINK_ITEM_SPAWNER_H