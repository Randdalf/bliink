//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Team management class. Contains all the details for a specific team
//
// $NoKeywords: $
//=============================================================================//

#ifndef SDK_TEAM_H
#define SDK_TEAM_H

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
class CSDKTeam : public CTeam
{
	DECLARE_CLASS( CSDKTeam, CTeam );
	DECLARE_SERVERCLASS();

public:

	// Initialization
	virtual void Init( const char *pName, int iNumber );
	const unsigned char *GetEncryptionKey( void ) { return g_pGameRules->GetEncryptionKey(); }

	virtual const char *GetTeamName( void ) { return "#Teamname_Spectators"; }

	void ResetScores( void );
};


extern CSDKTeam *GetGlobalSDKTeam( int iIndex );


#endif // TF_TEAM_H
