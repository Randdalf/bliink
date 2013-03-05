#include "cbase.h"

#include "bliink_item_inventory.h"
#include "bliink_item_parse.h"
#ifndef CLIENT_DLL
#include "bliink_item_base.h"
#include "bliink_player.h"
#include "baseentity.h"
#endif

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

CBliinkItemInventory::CBliinkItemInventory()
{
	BLIINK_ITEM_INFO_HANDLE hItemLocked = GetItemHandle( "locked_item" );
	BLIINK_ITEM_INFO_HANDLE hItemEmpty = GetItemHandle( "empty_item" );

	// Setting up inventory, only first weapon slot is unlocked initially.
	for(int i=0; i<INVENTORY_MAX_SLOTS; i++ )
	{
		// Setting up networked slots
		if( i>0 && i<INVENTORY_WEAPON_SLOTS )
		{
			m_iItemTypes.GetForModify(i) = hItemLocked;
		}
		else
		{
			m_iItemTypes.GetForModify(i) = hItemEmpty;
		}

		m_iStackCounts.GetForModify(i) = 0;

		// Setting up server inventory
#ifndef CLIENT_DLL
		m_pInventory[i] = NULL;
#endif
	}

#ifndef CLIENT_DLL
	pOwner = NULL;
#endif
}

// Attempts to move an item from one slot to another.
void CBliinkItemInventory::Command_Move(int iFromSlot, int iToSlot)
{
	BLIINK_ITEM_INFO_HANDLE hItemLocked = GetItemHandle( "locked_item" );
	BLIINK_ITEM_INFO_HANDLE hItemEmpty = GetItemHandle( "empty_item" );

	BLIINK_ITEM_INFO_HANDLE hFromSlot = m_iItemTypes[iFromSlot];
	BLIINK_ITEM_INFO_HANDLE hToSlot = m_iItemTypes[iToSlot];

	int iFromStack =  m_iStackCounts[iFromSlot];
	int iToStack = m_iStackCounts[iToSlot];

	// Checking slots are valid
	if( iFromSlot >= 0 && iFromSlot < INVENTORY_MAX_SLOTS && iToSlot >= 0 && iToSlot < INVENTORY_MAX_SLOTS )
	{
#ifdef CLIENT_DLL
		Warning("Attempted to move items from invalid slots.\n");
#endif
		return;
	}

	// Cannot move a non-weapon into a weapon slot
	if( !GetItemInfo(hFromSlot)->m_iType == ITEM_TYPE_WEAPON && iToSlot < INVENTORY_WEAPON_SLOTS )
	{
#ifdef CLIENT_DLL
		Warning("Attempted to move non-weapon into a weapon slot.\n");
#endif
		return;
	}

	// If from and to are not locked, and from is not empty, then we can perform move.
	if( hFromSlot != hItemLocked && hToSlot != hItemLocked && hFromSlot != hItemEmpty )
	{
		// If the two items stack.
		if( hFromSlot == hToSlot && GetItemInfo(hFromSlot)->m_bCanStack )
		{
			int iMaxStack = GetItemInfo( hFromSlot )->m_iMaxStack;

			// If we can safely merge into a bigger stack.
			if( iFromStack + iToStack > iMaxStack )
			{
				m_iItemTypes.GetForModify(iFromSlot) = hItemEmpty;

				m_iStackCounts.GetForModify(iFromSlot) = 0;
				m_iStackCounts.GetForModify(iToSlot) = iFromStack + iToStack;

			#ifndef CLIENT_DLL
				m_pInventory[iFromSlot] = NULL;
			#endif
			}
			// If we can't fully merge.
			else
			{
				m_iStackCounts.GetForModify(iFromSlot) = iFromStack + iToStack - iMaxStack;
				m_iStackCounts.GetForModify(iToSlot) = iMaxStack;
			}
		}
		// Swap the two entries.
		else
		{
			m_iItemTypes.GetForModify(iFromSlot) = hToSlot;
			m_iItemTypes.GetForModify(iToSlot) = hFromSlot;

			m_iStackCounts.GetForModify(iFromSlot) = iToStack;
			m_iStackCounts.GetForModify(iToSlot) = iFromStack;

		#ifndef CLIENT_DLL
			IBliinkItem* pTemp = m_pInventory[iFromSlot];
			m_pInventory[iFromSlot] = m_pInventory[iToSlot];
			m_pInventory[iToSlot] = pTemp;
		#endif
		}
	}
	else	
	{
#ifdef CLIENT_DLL
		Warning("Attempted to move items from locked slots.\n");
#endif
		return;
	}
}

// Attempts to craft an item in one slot with another.
void CBliinkItemInventory::Command_Craft(int iFromSlot, int iToSlot)
{

#ifndef CLIENT_DLL

#endif
}

// Attempts to drop an item from your inventory.
void CBliinkItemInventory::Command_Drop(int iFromSlot)
{

#ifndef CLIENT_DLL

#endif
}

// Attempts to consume an item from your inventory.
void CBliinkItemInventory::Command_Consume(int iFromSlot)
{

#ifndef CLIENT_DLL

#endif
}

// Attempts to meltdown an item from your inventory.
void CBliinkItemInventory::Command_Meltdown(int iFromSlot)
{

#ifndef CLIENT_DLL

#endif
}

// For the given ammotype, set the active ammo of that ammotype to the next
// one in the inventory.
void CBliinkItemInventory::Command_SetNextAmmoType()
{

#ifndef CLIENT_DLL

#endif
}

#ifndef CLIENT_DLL
// Attempts to add a new item to the inventory. Return false if we couldn't fit
// it into the inventory.
bool CBliinkItemInventory::AddItem( IBliinkItem* pNewItem )
{
	int iStartSearch = 0;
	BLIINK_ITEM_INFO_HANDLE hItemEmpty = GetItemHandle( "empty_item" );

	// Check if pNewItem is not NULL first
	if( !pNewItem )
		return false;

	// Don't look in weapon slots if it's not a weapon.
	if( !pNewItem->IsWeapon() )
	{
		iStartSearch = INVENTORY_WEAPON_SLOTS;
	}

	// If we can stack our item. Weapons don't stack so no need to worry about them here.
	if( pNewItem->IsStackable() )
	{
		// Looking for an item to stack with.
		for(int i=iStartSearch; i<INVENTORY_MAX_SLOTS; i++)
		{
			if( m_pInventory[i] && m_pInventory[i]->CanStackWith( pNewItem ) )
			{
				// We can stack but we would go over our limit, so look for a
				// free slot instead.
				if( (int) (m_iStackCounts[i] + 1) == pNewItem->GetItemData().m_iMaxStack )
				{
					break;
				}
				// We can stack, just increase the stack count.
				else
				{
					m_iStackCounts.GetForModify(i) =  m_iStackCounts[i] + 1;
					return true;
				}
			}
		}
	}
	
	// Look for a free slot.
	for(int i=iStartSearch; i<INVENTORY_MAX_SLOTS; i++)
	{
		if( m_iItemTypes[i] == hItemEmpty )
		{
			// We've found a free slot and we're a weapon, so have to insert
			// into the player's weapon slots.
			if( pNewItem->IsWeapon() && i<INVENTORY_WEAPON_SLOTS)
			{
				CBliinkItemWeapon* pItemWeapon = static_cast< CBliinkItemWeapon* >( pNewItem );

				// Creating weapon for item if it doesn't have one.
				if( !pItemWeapon->HasWeapon() )
				{
					CBaseEntity* pTemp = CreateEntityByName( pItemWeapon->GetItemData().szWeaponClassName );
					

					if( pTemp == NULL )
					{
						Warning("Couldn't create weapon entity\n");
					}
					else
					{
						pTemp->SetLocalOrigin( pOwner->GetLocalOrigin() );
						pTemp->AddSpawnFlags( SF_NORESPAWN );

						DispatchSpawn( pTemp );

						CWeaponSDKBase* pNewWeapon = static_cast<CWeaponSDKBase*>( pTemp );

						pItemWeapon->SetWeapon( pNewWeapon );
					}
				}

				// Look for a free slot in the normal inventory if we already hold
				// a weapon of the same type as ours.
				if( pItemWeapon->HasWeapon() && pOwner->Weapon_BliinkHasWeapon( pItemWeapon->GetWeapon() ) )
				{
					i = INVENTORY_WEAPON_SLOTS - 1;
					continue;
				}
				else
				{
					// Equipping weapon
					pOwner->Weapon_BliinkReplace( i+1, pItemWeapon->GetWeapon() );
					pOwner->SetActiveWeapon( pItemWeapon->GetWeapon() );

					// Adding to inventory
					m_pInventory[i] = pNewItem;
					m_iStackCounts.GetForModify(i) = 1;
					m_iItemTypes.GetForModify(i) = pNewItem->GetInfoHandle();

					return true;
				}
			}
			else
			{
				m_pInventory[i] = pNewItem;
				m_iStackCounts.GetForModify(i) = 1;
				m_iItemTypes.GetForModify(i) = pNewItem->GetInfoHandle();
			}
			return true;
		}
	}

	// Couldn't find a slot :(
	return false;

	// DEALING WITH WEAPONS
	// Insertion
	// 1. Weapon slots are full -> add weapon + ammo to inventory
	//    (if only 1 slot is available, insert only weapon)
	// 2. Weapon slot is available
	//    a) We don't have that weapon -> add to inventory/player weapons and switch to weapon
	//    b) We do have that weapon -> don't add to weapon slots, we can't have
	//		 more than one weapon of the same type in the slots.

	// Moving
	// 1. From inv -> empty
	// 2. From slot -> slot
	// 3. From slot-> empty

	// override weapon get slot and add set slot
	// keep track of owner

	// Removal/Crafting/Meltdown
	// 1. We are holding that weapon -> switch to hands + remove from player weapons
	// 2. We aren't holding that weapon -> just act normally

}

// Print the contents of the inventory to console.
void CBliinkItemInventory::Debug_PrintInventory( void )
{
	Msg("-- Inventory --\n");

	// Weapon slots
	for(int i=0; i<INVENTORY_WEAPON_SLOTS; i++)
	{
		Msg("%d : %s : %d\n", i+1, GetItemInfo( m_iItemTypes[i] )->szItemName, m_iStackCounts[i] );
	}

	Msg("---------------\n");

	// Item slots
	for(int i=INVENTORY_WEAPON_SLOTS; i<INVENTORY_MAX_SLOTS; i++)
	{
		Msg("%d : %s : %d\n", i+1, GetItemInfo( m_iItemTypes[i] )->szItemName, m_iStackCounts[i] );
	}
}
#endif