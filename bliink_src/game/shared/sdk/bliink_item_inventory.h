#ifndef BLIINK_ITEM_INVENTORY_H
#define BLIINK_ITEM_INVENTORY_H

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

	int GetItemStackCounts(int iFromSlot);
	char* GetItemName(int iFromSlot);
	bool IsEmpty();

	// Command methods
	void Command_Move(int iFromSlot, int iToSlot);
	void Command_Craft(int iFromSlot, int iToSlot);
	void Command_Drop(int iFromSlot);
	void Command_Consume(int iFromSlot);
	void Command_Delete(int iFromSlot);
	void Command_SetNextAmmoType();

	// Other methods
#ifndef CLIENT_DLL
	bool AddItem( IBliinkItem* pNewItem );

	// Upgrade stuff
	bool	UnlockWeaponSlot( void );

	// Ammo stuff
	void	UpdateAmmoTypes( void );
	void	SetNextActiveAmmo( int iAmmoSlot, int searchStartSlot = 0 );
	bool	UseAmmoClip( int iAmmoSlot, int iAmmoAmount );
	void	UpdateAmmoCounts( void );
	int		GetAmmoSubtype( int iAmmoSlot );

	
	// Crafting stuff
	// bool CanCraft(from, to)

	void Debug_PrintInventory( void );
#endif
	// Exposed to client
	int		GetAmmoClipCount( int iAmmoSlot ) const;

private:
	// List of item definitions in each slot
	CNetworkArray( BLIINK_ITEM_INFO_HANDLE, m_iItemTypes, INVENTORY_MAX_SLOTS );

	// List of stack counts for each item
	CNetworkArray( unsigned int, m_iStackCounts, INVENTORY_MAX_SLOTS );

	// List of active slots for different ammo types
	CNetworkArray( int, m_iAmmoSlots, MAX_AMMO_TYPES );

	// List of ammo counts for each ammo type
	CNetworkArray( int, m_iAmmoCounts, MAX_AMMO_TYPES );

#ifndef CLIENT_DLL
	// List of pointers to items
	IBliinkItem* m_pInventory[INVENTORY_MAX_SLOTS];

	// Player who owns this inventor
	CBliinkPlayer* pOwner;

public:
	// Sets the owner of this inventory.
	void SetOwner( CBliinkPlayer* pPlayer ) { pOwner = pPlayer; }
#endif
};

#endif // BLIINK_ITEM_INVENTORY_H