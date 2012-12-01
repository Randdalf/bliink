//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: Client side CTFTeam class
//
// $NoKeywords: $
//=============================================================================//

#ifndef C_BLIINK_TEAM_H
#define C_BLIINK_TEAM_H
#ifdef _WIN32
#pragma once
#endif

#include "c_team.h"
#include "shareddefs.h"
#include "sdk_playerclass_info_parse.h"

class C_BaseEntity;
class C_BaseObject;
class CBaseTechnology;

//Tony; so we can call this from shared code!
#define CBliinkTeam C_BliinkTeam

//-----------------------------------------------------------------------------
// Purpose: TF's Team manager
//-----------------------------------------------------------------------------
class C_BliinkTeam : public C_Team
{
	DECLARE_CLASS( C_BliinkTeam, C_Team );
	DECLARE_CLIENTCLASS();

public:

					C_BliinkTeam();
	virtual			~C_BliinkTeam();

	virtual char	*Get_Name( void );
};

//*********************
//* BLIINK TEAMS
//*********************

// Unassigned
class C_BliinkTeam_Unassigned : public C_BliinkTeam
{
	DECLARE_CLASS( C_BliinkTeam_Unassigned, C_BliinkTeam );
public:
	DECLARE_CLIENTCLASS();

				     C_BliinkTeam_Unassigned();
	 virtual		~C_BliinkTeam_Unassigned() {}
};

// Survivor
class C_BliinkTeam_Survivor : public C_BliinkTeam
{
	DECLARE_CLASS( C_BliinkTeam_Survivor, C_BliinkTeam );
public:
	DECLARE_CLIENTCLASS();

				     C_BliinkTeam_Survivor();
	 virtual		~C_BliinkTeam_Survivor() {}
};

// Stalker
class C_BliinkTeam_Stalker : public C_BliinkTeam
{
	DECLARE_CLASS( C_BliinkTeam_Stalker, C_BliinkTeam );
public:
	DECLARE_CLIENTCLASS();

				     C_BliinkTeam_Stalker();
	 virtual		~C_BliinkTeam_Stalker() {}
};

extern C_BliinkTeam *GetGlobalSDKTeam( int iIndex );

#endif // C_BLIINK_TEAM_H
