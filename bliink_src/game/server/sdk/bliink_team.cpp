//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Team management class. Contains all the details for a specific team
//
// $NoKeywords: $
//=============================================================================//
#include "cbase.h"
#include "bliink_team.h"
#include "entitylist.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"


// Datatable
IMPLEMENT_SERVERCLASS_ST(CBliinkTeam, DT_SDKTeam)
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS( bliink_team_manager, CBliinkTeam );

//-----------------------------------------------------------------------------
// Purpose: Get a pointer to the specified TF team manager
//-----------------------------------------------------------------------------
CBliinkTeam *GetGlobalSDKTeam( int iIndex )
{
	return (CBliinkTeam*)GetGlobalTeam( iIndex );
}


//-----------------------------------------------------------------------------
// Purpose: Needed because this is an entity, but should never be used
//-----------------------------------------------------------------------------
void CBliinkTeam::Init( const char *pName, int iNumber )
{
	BaseClass::Init( pName, iNumber );

	// Only detect changes every half-second.
	NetworkProp()->SetUpdateInterval( 0.75f );
}

void CBliinkTeam::ResetScores( void )
{
	SetRoundsWon(0);
	SetScore(0);
}

//*********************
//* BLIINK TEAMS
//*********************

// Unassigned
class CBliinkTeam_Unassigned : public CBliinkTeam
{
	DECLARE_CLASS( CBliinkTeam_Unassigned, CBliinkTeam );
	DECLARE_SERVERCLASS();

	virtual void Init( const char *pName, int iNumber )
	{
		BaseClass::Init( pName, iNumber );
	}

	virtual const char *GetTeamName( void ) { return "#Teamname_Unassigned"; }
};

IMPLEMENT_SERVERCLASS_ST(CBliinkTeam_Unassigned, DT_SDKTeam_Unassigned)
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS( bliink_team_unassigned, CBliinkTeam_Unassigned );

// Survivor
class CBliinkTeam_Survivor : public CBliinkTeam
{
	DECLARE_CLASS( CBliinkTeam_Survivor, CBliinkTeam );
	DECLARE_SERVERCLASS();

	virtual void Init( const char *pName, int iNumber )
	{
		BaseClass::Init( pName, iNumber );
	}

	virtual const char *GetTeamName( void ) { return "#Teamname_Survivor"; }
};

IMPLEMENT_SERVERCLASS_ST(CBliinkTeam_Survivor, DT_SDKTeam_Survivor)
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS( bliink_team_survivor, CBliinkTeam_Survivor );

// Stalker
class CBliinkTeam_Stalker : public CBliinkTeam
{
	DECLARE_CLASS( CBliinkTeam_Stalker, CBliinkTeam );
	DECLARE_SERVERCLASS();

	virtual void Init( const char *pName, int iNumber )
	{
		BaseClass::Init( pName, iNumber );
	}

	virtual const char *GetTeamName( void ) { return "#Teamname_Stalker"; }
};

IMPLEMENT_SERVERCLASS_ST(CBliinkTeam_Stalker, DT_SDKTeam_Stalker)
END_SEND_TABLE()

LINK_ENTITY_TO_CLASS( bliink_team_stalker, CBliinkTeam_Stalker );

