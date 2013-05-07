//========= Copyright © 1996-2008, Valve Corporation, All rights reserved. ============//
//
// Purpose: SDK C_PlayerResource
//
// $NoKeywords: $
//=============================================================================//

#ifndef C_BLIINK_PLAYER_RESOURCE_H
#define C_BLIINK_PLAYER_RESOURCE_H
#ifdef _WIN32
#pragma once
#endif

#include "c_playerresource.h"

class C_Bliink_PlayerResource : public C_PlayerResource
{
	DECLARE_CLASS( C_Bliink_PlayerResource, C_PlayerResource );
public:
	DECLARE_CLIENTCLASS();

					C_Bliink_PlayerResource();
	virtual			~C_Bliink_PlayerResource();

	int				GetPlayerState( int i ) { return m_iPlayerState[i]; }

public:
	int m_iPlayerState[MAX_PLAYERS+1];
};
C_Bliink_PlayerResource * BliinkGameResources( void );

#endif // C_BLIINK_PLAYER_RESOURCE_H
