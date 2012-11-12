//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Client side C_SDKTeam class
//
// $NoKeywords: $
//=============================================================================//
#include "cbase.h"
#include "engine/IEngineSound.h"
#include "hud.h"
#include "recvproxy.h"
#include "c_sdk_team.h"
#include "c_sdk_player_resource.h"

#include <vgui/ILocalize.h>
#include <tier3/tier3.h>
// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//Tony; undefine what I did in the header so everything from this point forward functions correctly.
#undef CSDKTeam

IMPLEMENT_CLIENTCLASS_DT(C_SDKTeam, DT_SDKTeam, CSDKTeam)
END_RECV_TABLE()

//-----------------------------------------------------------------------------
// Purpose: Get a pointer to the specified TF team manager
//-----------------------------------------------------------------------------
C_SDKTeam *GetGlobalSDKTeam( int iIndex )
{
	return (C_SDKTeam*)GetGlobalTeam( iIndex );
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
C_SDKTeam::C_SDKTeam()
{
}

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
C_SDKTeam::~C_SDKTeam()
{
}
char *C_SDKTeam::Get_Name( void )
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


IMPLEMENT_CLIENTCLASS_DT(C_SDKTeam_Unassigned, DT_SDKTeam_Unassigned, CSDKTeam_Unassigned)
END_RECV_TABLE()

C_SDKTeam_Unassigned::C_SDKTeam_Unassigned()
{
}
