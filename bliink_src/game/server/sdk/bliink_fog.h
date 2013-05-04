#ifndef BLIINK_FOG_H
#define BLIINK_FOG_H

#include "cbase.h"

// Radial fog.
class CBliinkFog : public CPointEntity
{
public:
	DECLARE_CLASS( CBliinkFog, CPointEntity );
	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();
	
	CBliinkFog();
	~CBliinkFog();

public:
	virtual void Spawn();
	virtual void Precache();

public:
	// Fog will begin closing in.
	void BeginContracting();

	// What time should the fog reach min radius.
	float CalcTargetTime();

	// Used to control radius.
	void Think();

public:
	// Func dust stuff for particles.
	CNetworkVar( color32, m_Color );
	CNetworkVar( int, m_SpawnRate );	
	CNetworkVar( float, m_flSizeMin );
	CNetworkVar( float, m_flSizeMax );
	CNetworkVar( int, m_SpeedMax );
	CNetworkVar( int, m_LifetimeMin );
	CNetworkVar( int, m_LifetimeMax );
	CNetworkVar( int, m_DistMax );
	CNetworkVar( float, m_FallSpeed );
	CNetworkVar( int, m_DustFlags );
	int m_iAlpha;

	// Bliink specific.
	CNetworkVar( float, m_flMaxFogRadius );
	CNetworkVar( float, m_flMinFogRadius );
	CNetworkVar( float, m_flFogHeightUp );
	CNetworkVar( float, m_flFogHeightDown );
	CNetworkVar( float, m_flFogRadius );

private:
	float m_flStartTime;
	float m_flTargetTime;
	bool m_bIsContracting;
};

#endif // BLIINK_FOG_H