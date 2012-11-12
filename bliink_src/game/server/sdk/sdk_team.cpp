//========= Copyright � 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Team management class. Contains all the details for a specific team
//
// $NoKeywords: $
//=============================================================================//
#include "cbase.h"
#include "sdk_team.h"
#include "entitylist.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


// Datatable
IMPLEMENT_SERVERCLASS_ST(CSDKTeam, DT_SDKTeam)
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS( sdk_team_manager, CSDKTeam );

//-----------------------------------------------------------------------------
// Purpose: Get a pointer to the specified TF team manager
//-----------------------------------------------------------------------------
CSDKTeam *GetGlobalSDKTeam( int iIndex )
{
	return (CSDKTeam*)GetGlobalTeam( iIndex );
}


//-----------------------------------------------------------------------------
// Purpose: Needed because this is an entity, but should never be used
//-----------------------------------------------------------------------------
void CSDKTeam::Init( const char *pName, int iNumber )
{
	BaseClass::Init( pName, iNumber );

	// Only detect changes every half-second.
	NetworkProp()->SetUpdateInterval( 0.75f );
}

void CSDKTeam::ResetScores( void )
{
	SetRoundsWon(0);
	SetScore(0);
}

//
// TEAMS
//

// UNASSIGNED
//==================

class CSDKTeam_Unassigned : public CSDKTeam
{
	DECLARE_CLASS( CSDKTeam_Unassigned, CSDKTeam );
	DECLARE_SERVERCLASS();

	virtual void Init( const char *pName, int iNumber )
	{
		BaseClass::Init( pName, iNumber );
	}

	virtual const char *GetTeamName( void ) { return "#Teamname_Unassigned"; }
};

IMPLEMENT_SERVERCLASS_ST(CSDKTeam_Unassigned, DT_SDKTeam_Unassigned)
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS( sdk_team_unassigned, CSDKTeam_Unassigned );

