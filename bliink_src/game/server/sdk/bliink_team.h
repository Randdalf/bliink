//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Team management class. Contains all the details for a specific team
//
// $NoKeywords: $
//=============================================================================//

//*****************************************************************************
// BLIINK TEAM
// Bliink doesn't use teams for anything other than designating who can damage
// who, so these classes are fairly stripped down. They are necessary for some
// base code though. - Alex
//*****************************************************************************

#ifndef BLIINK_TEAM_H
#define BLIINK_TEAM_H

#ifdef _WIN32
#pragma once
#endif


#include "utlvector.h"
#include "team.h"
#include "playerclass_info_parse.h"
#include "sdk_playerclass_info_parse.h"

//-----------------------------------------------------------------------------
// Purpose: Team Manager
//-----------------------------------------------------------------------------
class CBliinkTeam : public CTeam
{
	DECLARE_CLASS( CBliinkTeam, CTeam );
	DECLARE_SERVERCLASS();

public:

	// Initialization
	virtual void Init( const char *pName, int iNumber );
	const unsigned char *GetEncryptionKey( void ) { return g_pGameRules->GetEncryptionKey(); }

	virtual const char *GetTeamName( void ) { return "#Teamname_Spectators"; }

	void ResetScores( void );
};


extern CBliinkTeam *GetGlobalSDKTeam( int iIndex );


#endif // BLIINK_TEAM_H
