//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Client side C_BliinkTeam class
//
// $NoKeywords: $
//=============================================================================//
#include "cbase.h"
#include "engine/IEngineSound.h"
#include "hud.h"
#include "recvproxy.h"
#include "c_bliink_team.h"
#include "c_sdk_player_resource.h"

#include <vgui/ILocalize.h>
#include <tier3/tier3.h>
// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//Tony; undefine what I did in the header so everything from this point forward functions correctly.
#undef CBliinkTeam

IMPLEMENT_CLIENTCLASS_DT(C_BliinkTeam, DT_SDKTeam, CBliinkTeam)
END_RECV_TABLE()

//-----------------------------------------------------------------------------
// Purpose: Get a pointer to the specified TF team manager
//-----------------------------------------------------------------------------
C_BliinkTeam *GetGlobalSDKTeam( int iIndex )
{
	return (C_BliinkTeam*)GetGlobalTeam( iIndex );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
C_BliinkTeam::C_BliinkTeam()
{
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
C_BliinkTeam::~C_BliinkTeam()
{
}
char *C_BliinkTeam::Get_Name( void )
{
	wchar_t *teamname;
	if (m_szTeamname[0] == '#')
	{
		teamname = g_pVGuiLocalize->Find(m_szTeamname);

		char ansi[128];
		g_pVGuiLocalize->ConvertUnicodeToANSI( teamname, ansi, sizeof( ansi ) );

		return strdup(ansi);
	}
	else 
		return m_szTeamname;
}

//*********************
//* BLIINK TEAMS
//*********************

// Unassigned
IMPLEMENT_CLIENTCLASS_DT(C_BliinkTeam_Unassigned, DT_SDKTeam_Unassigned, CBliinkTeam_Unassigned)
END_RECV_TABLE()

C_BliinkTeam_Unassigned::C_BliinkTeam_Unassigned()
{
}
// Survivor
IMPLEMENT_CLIENTCLASS_DT(C_BliinkTeam_Survivor, DT_SDKTeam_Survivor, CBliinkTeam_Survivor)
END_RECV_TABLE()

C_BliinkTeam_Survivor::C_BliinkTeam_Survivor()
{
}

// Stalker
IMPLEMENT_CLIENTCLASS_DT(C_BliinkTeam_Stalker, DT_SDKTeam_Stalker, CBliinkTeam_Stalker)
END_RECV_TABLE()

C_BliinkTeam_Stalker::C_BliinkTeam_Stalker()
{
}