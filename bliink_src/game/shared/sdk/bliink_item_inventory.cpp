#include "cbase.h"

#include "bliink_item_inventory.h"
#include "bliink_item_parse.h"
#include "ammodef.h"
#ifndef CLIENT_DLL
#include "bliink_item_base.h"
#include "bliink_player.h"
#include "bliink_item_pickup.h"
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
		if( i>1 && i<INVENTORY_WEAPON_SLOTS )
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

	// Setting all ammo slots to empty.
	for(int i=0; i<MAX_AMMO_TYPES; i++ )
	{
		m_iAmmoSlots.GetForModify(i) = -1;
		m_iAmmoCounts.GetForModify(i) = 0;
	}
}

// Attempts to move an item from one slot to another.
void CBliinkItemInventory::Command_Move(const int iFromSlot, const int iToSlot)
{
	Msg("move: %d %d\n", iFromSlot, iToSlot);

	BLIINK_ITEM_INFO_HANDLE hItemLocked = GetItemHandle( "locked_item" );
	BLIINK_ITEM_INFO_HANDLE hItemEmpty = GetItemHandle( "empty_item" );

	BLIINK_ITEM_INFO_HANDLE hFromSlot = m_iItemTypes[iFromSlot];
	BLIINK_ITEM_INFO_HANDLE hToSlot = m_iItemTypes[iToSlot];

	int iFromStack =  m_iStackCounts[iFromSlot];
	int iToStack = m_iStackCounts[iToSlot];

	// Checking slots are valid
	if( !(iFromSlot >= 0 && iFromSlot < INVENTORY_MAX_SLOTS && iToSlot >= 0 && iToSlot < INVENTORY_MAX_SLOTS) )
	{
#ifndef CLIENT_DLL
		Warning("Attempted to move items from invalid slots.\n");
#endif
		return;
	}

	// Cannot move a non-weapon into a weapon slot
	if( !(GetItemInfo(hFromSlot)->m_iType == ITEM_TYPE_WEAPON) && iToSlot < INVENTORY_WEAPON_SLOTS )
	{
#ifndef CLIENT_DLL
		Warning("Attempted to move non-weapon into a weapon slot.\n");
#endif
		return;
	}

	// If from and to are not locked, and from is not empty, then we can perform move.
	if( hFromSlot != hItemLocked && hToSlot != hItemLocked && hFromSlot != hItemEmpty )
	{
		// If the two items stack.
		// disabled for now
		if( 0 /*hFromSlot == hToSlot && GetItemInfo(hFromSlot)->m_bCanStack*/ )
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
		#ifdef CLIENT_DLL
			m_iItemTypes.GetForModify(iFromSlot) = hToSlot;
			m_iItemTypes.GetForModify(iToSlot) = hFromSlot;

			m_iStackCounts.GetForModify(iFromSlot) = iToStack;
			m_iStackCounts.GetForModify(iToSlot) = iFromStack;
		#else
			// Deal with weapon slots.
			if( iFromSlot < INVENTORY_WEAPON_SLOTS || iToSlot < INVENTORY_WEAPON_SLOTS )
			{				
				CBliinkItemWeapon* pItemWeapon = static_cast< CBliinkItemWeapon* >( m_pInventory[iFromSlot] );

				// 1. From inv -> empty/slot
				if( iFromSlot >= INVENTORY_WEAPON_SLOTS )
				{
					// Block movement if we already have that weapon.
					if( pOwner->Weapon_BliinkHasWeapon( pItemWeapon->GetWeapon() ) )
					{
						return;
					}

					// Equip weapon, replacing the one already there.
					pOwner->Weapon_BliinkReplace( iToSlot, pItemWeapon->GetWeapon() );
				}
				else
				{
					// 2. Slot -> empty/slot
					if( iFromSlot < INVENTORY_WEAPON_SLOTS && iToSlot < INVENTORY_WEAPON_SLOTS )
					{
						// Switch the weapons around
						pOwner->Weapon_BliinkSwitch( iFromSlot, iToSlot );
					}
					// 3. Slot -> inv
					else if( iToSlot >= INVENTORY_WEAPON_SLOTS )
					{
						IBliinkItem* pToItem = m_pInventory[iToSlot];

						if( pToItem && pToItem->IsWeapon() )
						{
							CBliinkItemWeapon* pToWeapon = static_cast< CBliinkItemWeapon* >( pToItem );

							// Block movement if we already have that weapon.
							if( pOwner->Weapon_BliinkHasWeapon( pToWeapon->GetWeapon() ) )
							{
								return;
							}
							// Switch in the new weapon.
							else
							{
								pOwner->Weapon_BliinkReplace( iFromSlot, pToWeapon->GetWeapon() );
							}

						}
						// Remove the weapon
						else
						{
							pOwner->Weapon_BliinkRemove( iFromSlot );
						}
					}
				}
			}

			// Swap items
			m_iItemTypes.GetForModify(iFromSlot) = hToSlot;
			m_iItemTypes.GetForModify(iToSlot) = hFromSlot;

			m_iStackCounts.GetForModify(iFromSlot) = iToStack;
			m_iStackCounts.GetForModify(iToSlot) = iFromStack;

			// Update pointers
			IBliinkItem* pTemp = m_pInventory[iFromSlot];
			m_pInventory[iFromSlot] = m_pInventory[iToSlot];
			m_pInventory[iToSlot] = pTemp;
		#endif
		}
	}
	else	
	{
#ifndef CLIENT_DLL
		Warning("Attempted to move items from locked slots or empty slots.\n");
#endif
		return;
	}

	// Updating ammo.
#ifndef CLIENT_DLL
	// Updating ammo.
	UpdateAmmoTypes();
#endif
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
	// Check slot is valid.
	if( !(iFromSlot >=0 && iFromSlot < INVENTORY_MAX_SLOTS ) )
		return;

	BLIINK_ITEM_INFO_HANDLE hItemLocked = GetItemHandle( "locked_item" );
	BLIINK_ITEM_INFO_HANDLE hItemEmpty = GetItemHandle( "empty_item" );

	BLIINK_ITEM_INFO_HANDLE hFromSlot = m_iItemTypes[iFromSlot];

	// Check we are dropping an item.
	if( hFromSlot == hItemLocked || hFromSlot == hItemEmpty )
		return;

#ifndef CLIENT_DLL	
	// Drop item(s) and deal with weapons if necessary.
	IBliinkItem* pItem = m_pInventory[iFromSlot];
	int stacks = m_iStackCounts[iFromSlot];

	// Unequipping weapon if necessary.
	if( pItem->IsWeapon() )
	{
		if( iFromSlot < INVENTORY_WEAPON_SLOTS )
			pOwner->Weapon_BliinkRemove( iFromSlot );

		Vector spawnOrigin = pOwner->GetAbsOrigin();
		CBliinkItemPickup* pPickup = (CBliinkItemPickup*) CBaseEntity::CreateNoSpawn( "bliink_item_pickup", spawnOrigin, QAngle());
		pPickup->SetItem( m_pInventory[iFromSlot] );
		DispatchSpawn( pPickup );
	}
	else
	{
		// Dropping each item in the stack.
		for(int i=0; i<stacks; i++)
		{		
			Vector spawnOrigin = pOwner->GetAbsOrigin();
			CBliinkItemPickup* pPickup = (CBliinkItemPickup*) CBaseEntity::CreateNoSpawn( "bliink_item_pickup", spawnOrigin, QAngle());

			// Creating item, dealing with ammo if we have to.
			IBliinkItem* pDropItem = CreateItemByHandle( m_iItemTypes[iFromSlot] );

			if( pDropItem->IsAmmo() )
			{
				CBliinkItemAmmo* pAmmoItem = static_cast<CBliinkItemAmmo*> ( pDropItem );				
				CBliinkItemAmmo* pInventoryAmmo = static_cast<CBliinkItemAmmo*> ( m_pInventory[iFromSlot] );
				pAmmoItem->SetAmmo( pInventoryAmmo->GetAmmo() );
				pInventoryAmmo->ResetAmmo();

				pPickup->SetItem( pAmmoItem );
			}
			else
			{
				pPickup->SetItem( pDropItem );
			}

			DispatchSpawn( pPickup );
		}

		delete m_pInventory[iFromSlot];
	}

	m_pInventory[iFromSlot] = NULL;
#endif

	// Update pointers, stack counts, etc.
	m_iItemTypes.GetForModify(iFromSlot) = hItemEmpty;
	m_iStackCounts.GetForModify(iFromSlot) = 0;

#ifndef CLIENT_DLL
	// Updating ammo.
	UpdateAmmoTypes();
#endif
}

// Attempts to consume an item from your inventory.
void CBliinkItemInventory::Command_Consume(int iFromSlot)
{
#ifndef CLIENT_DLL
	// Check slot is valid.
	if( !(iFromSlot >=0 && iFromSlot < INVENTORY_MAX_SLOTS ) )
		return;

	BLIINK_ITEM_INFO_HANDLE hItemLocked = GetItemHandle( "locked_item" );
	BLIINK_ITEM_INFO_HANDLE hItemEmpty = GetItemHandle( "empty_item" );

	BLIINK_ITEM_INFO_HANDLE hFromSlot = m_iItemTypes[iFromSlot];

	// Check we are consuming a consumable and there's a stack to consume.
	if( hFromSlot == hItemLocked || hFromSlot == hItemEmpty || !(m_pInventory[iFromSlot]->IsConsumable() && m_iStackCounts[iFromSlot] > 0) )
		return;

	// Consume.
	IBliinkItem* pItem = m_pInventory[iFromSlot];
	CBliinkItemConsumable* pConsumable = static_cast< CBliinkItemConsumable* >( pItem );

	pConsumable->Consume( pOwner );

	m_iStackCounts.GetForModify(iFromSlot) = m_iStackCounts[iFromSlot] - 1;

	// Delete if we've run out!
	if( m_iStackCounts[iFromSlot] == 0 )
	{
		Command_Delete(iFromSlot);
	}
#endif

#ifndef CLIENT_DLL
	// Updating ammo.
	UpdateAmmoTypes();
#endif
}

// Deletes an item from your inventory.
void CBliinkItemInventory::Command_Delete(int iFromSlot)
{
	// Check slot is valid.
	if( !(iFromSlot >=0 && iFromSlot < INVENTORY_MAX_SLOTS ) )
		return;

	BLIINK_ITEM_INFO_HANDLE hItemLocked = GetItemHandle( "locked_item" );
	BLIINK_ITEM_INFO_HANDLE hItemEmpty = GetItemHandle( "empty_item" );

	BLIINK_ITEM_INFO_HANDLE hFromSlot = m_iItemTypes[iFromSlot];

	// Check we are deleting an item.
	if( hFromSlot == hItemLocked || hFromSlot == hItemEmpty )
		return;

#ifndef CLIENT_DLL	
	// Drop item(s) and deal with weapons if necessary.
	IBliinkItem* pItem = m_pInventory[iFromSlot];

	// Unequipping weapon if necessary.
	if( pItem->IsWeapon() && iFromSlot < INVENTORY_WEAPON_SLOTS )
	{
		pOwner->Weapon_BliinkRemove( iFromSlot );
	}

	delete m_pInventory[iFromSlot];
	m_pInventory[iFromSlot] = NULL;
#endif

	// Update pointers, stack counts, etc.
	m_iItemTypes.GetForModify(iFromSlot) = hItemEmpty;
	m_iStackCounts.GetForModify(iFromSlot) = 0;

#ifndef CLIENT_DLL
	// Updating ammo.
	UpdateAmmoTypes();
#endif
}

// For the given ammotype, set the active ammo of that ammotype to the next
// one in the inventory.
void CBliinkItemInventory::Command_SetNextAmmoType()
{
#ifndef CLIENT_DLL
	// Getting active ammo on player.
	CBaseCombatWeapon* pWeapon = pOwner->GetActiveWeapon();

	if( !pWeapon )
		return;

	int iAmmoIndex = pWeapon->GetPrimaryAmmoType();
	
	// Check ammo index is valid.
	if( !(iAmmoIndex >=0 && iAmmoIndex < MAX_AMMO_TYPES ) )
		return;

	// Getting search slot.
	int iItemSlots = m_iAmmoSlots[iAmmoIndex];

	if( iItemSlots == - 1 )
		return;

	// Updating ammo.
	SetNextActiveAmmo( iAmmoIndex, (iItemSlots + 1)  % INVENTORY_MAX_SLOTS);
	UpdateAmmoTypes();
#endif
}

#ifndef CLIENT_DLL
// Attempts to add a new item to the inventory. Return false if we couldn't fit
// it into the inventory.
bool CBliinkItemInventory::AddItem( IBliinkItem* pNewItem )
{
	int iStartSearch = 0;
	BLIINK_ITEM_INFO_HANDLE hItemEmpty = GetItemHandle( "empty_item" );
	CBliinkItemWeapon* pItemWeapon;

	// Check if pNewItem is not NULL first
	if( !pNewItem )
		return false;

	// Don't look in weapon slots if it's not a weapon.
	if( !pNewItem->IsWeapon() )
	{
		iStartSearch = INVENTORY_WEAPON_SLOTS;
	}else{
		pItemWeapon = static_cast< CBliinkItemWeapon* >( pNewItem );
		if (pOwner->Weapon_BliinkHasWeapon( pItemWeapon->GetWeapon() )){
			return false; //already own weapon;
		}
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
				if( (int) (m_iStackCounts[i] + 1) > pNewItem->GetItemData().m_iMaxStack )
				{
					continue;
				}
				// We can stack, just increase the stack count.
				else
				{
					m_iStackCounts.GetForModify(i) =  m_iStackCounts[i] + 1;

					// Updating ammo if necessary.
					#ifndef CLIENT_DLL
					if( pNewItem->IsAmmo() )
					{
						CBliinkItemAmmo* pAmmoItem = static_cast<CBliinkItemAmmo*>( m_pInventory[i] );
						CBliinkItemAmmo* pNewAmmoItem = static_cast<CBliinkItemAmmo*>( pNewItem );

						int iNewAmmo = pAmmoItem->GetAmmo() + pNewAmmoItem->GetAmmo() - pAmmoItem->GetItemData().m_iAmmoClip;

						pAmmoItem->SetAmmo( iNewAmmo );

						UpdateAmmoTypes();
					}
					#endif

					delete pNewItem;
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
			// Creating weapon if we don't have one.
			if( pNewItem->IsWeapon() )
			{

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
						pTemp->SetAbsOrigin( Vector(0, 0, 0) );
						pTemp->AddSpawnFlags( SF_NORESPAWN );

						DispatchSpawn( pTemp );

						CWeaponSDKBase* pNewWeapon = static_cast<CWeaponSDKBase*>( pTemp );

						pItemWeapon->SetWeapon( pNewWeapon );
					}
				}
			}

			// Seeing if we can insert into weapon slots.
			if( pNewItem->IsWeapon() && i < INVENTORY_WEAPON_SLOTS )
			{
				CBliinkItemWeapon* pItemWeapon = static_cast< CBliinkItemWeapon* >( pNewItem );

				// Look for a free slot in the normal inventory if we already hold
				// a weapon of the same type as ours and we're inserting it
				// into our weapon slots.
				//EDIT 
				//return false, cant pick up weapon we already own
				if( pItemWeapon->HasWeapon() &&
					pOwner->Weapon_BliinkHasWeapon( pItemWeapon->GetWeapon() ) )
				{
					//i = INVENTORY_WEAPON_SLOTS - 1;
					//continue;
					Msg("Already Own Weapon");
					return false;
					//return false, cant pick up weapon we already own
				}
				else
				{
					// Equipping weapon
					pOwner->Weapon_BliinkReplace( i, pItemWeapon->GetWeapon() );
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

				// Updating ammo if necessary.
				#ifndef CLIENT_DLL
				if( m_pInventory[i]->IsAmmo() )
				{
					UpdateAmmoTypes();
				}
				#endif
			}

			return true;
		}
	}

	// Couldn't find a slot :(
	return false;
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

	// Ammo

	Msg("-- Ammo Slots --\n");

	for(int i=0; i<MAX_AMMO_TYPES; i++)
	{
		Msg("%d : %d : %d\n", i, m_iAmmoSlots[i], m_iAmmoCounts[i] );
	}
}

// Updates our ammo array of the active slot for each ammo type.
void CBliinkItemInventory::UpdateAmmoTypes( void )
{
	// Loop through each ammo slot, looking for incongruencies
	for(int i=0; i<MAX_AMMO_TYPES; i++)
	{
		int iItemIndex = m_iAmmoSlots[i];

		if( iItemIndex == -1 )
			continue;

		IBliinkItem* pItem = m_pInventory[ iItemIndex ];

		if( !pItem || GetAmmoDef()->Index( pItem->GetItemData().szAmmoType ) != i )
		{
			m_iAmmoSlots.GetForModify(i) = -1;
		}
	}

	// Loop through each inventory slot
	for(int i=0; i<INVENTORY_MAX_SLOTS; i++)
	{
		IBliinkItem* pItem = m_pInventory[i];

		if( pItem && pItem->IsAmmo() )
		{
			int index = GetAmmoDef()->Index( pItem->GetItemData().szAmmoType );

			// If -1 then that slot is empty and we can replace it.
			if( m_iAmmoSlots[index] == -1 )
			{
				m_iAmmoSlots.GetForModify(index) = i;
			}
		}
	}

	UpdateAmmoCounts();
}

// Sets the next active ammunition for the specified type, goes to -1 if it
// cannot find one. Can also specify a slot to start searching from (it
// will wrap around).
void CBliinkItemInventory::SetNextActiveAmmo( int iAmmoSlot, int searchStartSlot )
{
	// Check slot index is valid.
	if( !(iAmmoSlot >= 0 && iAmmoSlot < MAX_AMMO_TYPES) )
		return;

	int i = searchStartSlot;
	int count = 0;
	CBliinkItemInfo* item;

	// Do wrap around loop.
	while( count < INVENTORY_MAX_SLOTS )
	{
		item = GetItemInfo( m_iItemTypes[i] );

		if( item->m_iType == ITEM_TYPE_AMMO )
		{
			int itemIndex = GetAmmoDef()->Index( item->szAmmoType );

			// If the ammo slot matches, then set it and return.
			if( itemIndex == iAmmoSlot )
			{
				m_iAmmoSlots.GetForModify(iAmmoSlot) = i;
				return;
			}
		}

		i = (i+1) % INVENTORY_MAX_SLOTS;
		count++;
	}

	// No match, so we go to -1.
	m_iAmmoSlots.GetForModify(iAmmoSlot) = -1;
	m_iAmmoCounts.GetForModify(iAmmoSlot) = 0;
}

// Uses a clip of ammo from the specified ammo type. Returns false if we
// couldn't use a clip.
bool CBliinkItemInventory::UseAmmoClip( int iAmmoSlot, int iAmmoAmount )
{
	// Check slot index is valid.
	if( !(iAmmoSlot >= 0 && iAmmoSlot < MAX_AMMO_TYPES && iAmmoAmount > 0) )
		return false;

	// Check we have any ammo for that slot.
	const int iAmmoCount = GetAmmoClipCount( iAmmoSlot );

	if( m_iAmmoSlots[iAmmoSlot] == -1 || iAmmoCount < iAmmoAmount )
		return false;

	// Subtract ammo, removing stacks as necessary.
	const int iItemSlot = m_iAmmoSlots[iAmmoSlot];
	const int iClipSize = GetItemInfo( m_iItemTypes[iItemSlot] )->m_iAmmoClip;
	CBliinkItemAmmo* pAmmo = static_cast<CBliinkItemAmmo*>( m_pInventory[iItemSlot] );

	const int iRemainingAmmo = iAmmoCount - iAmmoAmount;
	const int iAmmoToSet = iRemainingAmmo % iClipSize;
	const int iStacksToSet = (int) ceil( ((float) iRemainingAmmo) / ((float) iClipSize) );

	Msg("iRemainingAmmo = %d - %d = %d\n", iAmmoCount, iAmmoAmount, iRemainingAmmo);
	Msg("iAmmoToSet = %d %% %d = %d\n", iRemainingAmmo, iClipSize, iAmmoToSet);
	Msg("iStacksToSet = %d\n", iStacksToSet);

	 m_iStackCounts.GetForModify(iItemSlot) = iStacksToSet;
	 pAmmo->SetAmmo( iAmmoToSet );

	// If we've run out of ammo, then deal with the consequences.
	if( m_iStackCounts[iItemSlot] == 0 )
	{
		// Delete the item
		Command_Delete(iItemSlot);

		// Attempt to find a new active ammo type.
		SetNextActiveAmmo( iAmmoSlot, (iItemSlot+1)%INVENTORY_MAX_SLOTS );
	}

	return true;
}

// Unlocks the first weapon slot available, returns false if it couldn't find
// one, so we don't waste an upgrade point.
bool CBliinkItemInventory::UnlockWeaponSlot( void )
{
	BLIINK_ITEM_INFO_HANDLE hItemLocked = GetItemHandle( "locked_item" );
	BLIINK_ITEM_INFO_HANDLE hItemEmpty = GetItemHandle( "empty_item" );

	for(int i=0; i<INVENTORY_WEAPON_SLOTS; i++)
	{
		BLIINK_ITEM_INFO_HANDLE hWeaponSlot = m_iItemTypes[i];

		if( hWeaponSlot == hItemLocked )
		{
			m_iItemTypes.GetForModify(i) = hItemEmpty;
			return true;
		}
	}

	return false;
}

// Update all the ammo counts, for the client's sake.
void CBliinkItemInventory::UpdateAmmoCounts( void )
{
	for(int i=0; i<MAX_AMMO_TYPES; i++)
	{
		if( m_iAmmoSlots[i] == -1 )
		{
			m_iAmmoCounts.GetForModify(i) = 0;
		}
		else
		{
			m_iAmmoCounts.GetForModify(i) = GetAmmoClipCount( i );
		}
		
	}
}

// Returns the subtype of the ammo of the specified type.
int CBliinkItemInventory::GetAmmoSubtype( int iAmmoSlot )
{
	// Check slot index is valid.
	if( !(iAmmoSlot >= 0 && iAmmoSlot < MAX_AMMO_TYPES) )
		return ITEM_STYPE_AMMO_NORMAL;

	// Retrieving item slot.
	int iItemSlot = m_iAmmoSlots[iAmmoSlot];

	if( iItemSlot == -1 )
		return ITEM_STYPE_AMMO_NORMAL;	

	return GetItemInfo( m_iItemTypes[iItemSlot] )->m_iSubType;
}
#endif

// Returns the amount of ammo available for a specific ammo type.
int CBliinkItemInventory::GetAmmoClipCount( int iAmmoSlot ) const
{
	// Check slot index is valid.
	if( !(iAmmoSlot >= 0 && iAmmoSlot < MAX_AMMO_TYPES) )
		return 0;

#ifdef CLIENT_DLL
	return m_iAmmoCounts[iAmmoSlot];
#else
	// Check if this slot is available.
	if( m_iAmmoSlots[iAmmoSlot] == -1 )
		return false;

	int iItemSlot = m_iAmmoSlots[iAmmoSlot];
	int iStacks = m_iStackCounts[iItemSlot];

	// Return the ammo count.
	if( iStacks > 0 )
	{
		CBliinkItemAmmo* pAmmo = static_cast<CBliinkItemAmmo*>( m_pInventory[iItemSlot] );
		return pAmmo->GetAmmo() + GetItemInfo( m_iItemTypes[iItemSlot] )->m_iAmmoClip * ( iStacks - 1);
	}
	else
		return 0;
#endif
}