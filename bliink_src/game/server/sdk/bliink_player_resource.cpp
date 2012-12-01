//========= Copyright © 1996-2008, Valve Corporation, All rights reserved. ============//
//
// Purpose: Bliink CPlayerResource
//
// $NoKeywords: $
//=============================================================================//
#include "cbase.h"
#include "bliink_player.h"
#include "player_resource.h"
#include "sdk_player_resource.h"
#include <coordsize.h>

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

// Datatable
IMPLEMENT_SERVERCLASS_ST(CBliinkPlayerResource, DT_SDKPlayerResource)
END_SEND_TABLE()

BEGIN_DATADESC( CBliinkPlayerResource )
END_DATADESC()

LINK_ENTITY_TO_CLASS( sdk_player_manager, CBliinkPlayerResource );

CBliinkPlayerResource::CBliinkPlayerResource( void )
{
	
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
void CBliinkPlayerResource::UpdatePlayerData( void )
{
	int i;

	for ( i = 1; i <= gpGlobals->maxClients; i++ )
	{
		CBliinkPlayer *pPlayer = (CBliinkPlayer*)UTIL_PlayerByIndex( i );
		
		if ( pPlayer && pPlayer->IsConnected() )
		{
		}
	}

	BaseClass::UpdatePlayerData();
}

void CBliinkPlayerResource::Spawn( void )
{
	int i;

	for ( i=0; i < MAX_PLAYERS+1; i++ )
	{
	}

	BaseClass::Spawn();
}
