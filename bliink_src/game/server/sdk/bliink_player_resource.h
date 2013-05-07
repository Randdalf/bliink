//========= Copyright © 1996-2008, Valve Corporation, All rights reserved. ============//
//
// Purpose: SDK CPlayerResource
//
// $NoKeywords: $
//=============================================================================//

#ifndef BLIINK_PLAYER_RESOURCE_H
#define BLIINK_PLAYER_RESOURCE_H
#ifdef _WIN32
#pragma once
#endif

class CBliinkPlayerResource : public CPlayerResource
{
	DECLARE_CLASS( CBliinkPlayerResource, CPlayerResource );
	
public:
	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();

	CBliinkPlayerResource();

	virtual void UpdatePlayerData( void );
	virtual void Spawn( void );

protected:
//	CNetworkArray( int, m_iObjScore, MAX_PLAYERS+1 );
	CNetworkArray( int, m_iPlayerState, MAX_PLAYERS+1 );
};

#endif // BLIINK_PLAYER_RESOURCE_H
