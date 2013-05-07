//========= Copyright © 1996-2008, Valve Corporation, All rights reserved. ============//
//
// Purpose: SDK C_PlayerResource
//
// $NoKeywords: $
//=============================================================================//
#include "cbase.h"
#include "c_bliink_player_resource.h"
#include "c_bliink_player.h"
#include "bliink_gamerules.h"
#include <shareddefs.h>
#include "hud.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


IMPLEMENT_CLIENTCLASS_DT(C_Bliink_PlayerResource, DT_BliinkPlayerResource, CBliinkPlayerResource)
	RecvPropArray3( RECVINFO_ARRAY(m_iPlayerState), RecvPropInt( RECVINFO(m_iPlayerState[0]))),
END_RECV_TABLE()

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
C_Bliink_PlayerResource::C_Bliink_PlayerResource()
{
	m_Colors[TEAM_UNASSIGNED] = COLOR_YELLOW;
	m_Colors[TEAM_SPECTATOR] = COLOR_GREY;
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
C_Bliink_PlayerResource::~C_Bliink_PlayerResource()
{
}

C_Bliink_PlayerResource * BliinkGameResources( void )
{
	return dynamic_cast<C_Bliink_PlayerResource *>(GameResources());
}
