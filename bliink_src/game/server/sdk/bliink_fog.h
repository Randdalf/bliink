#ifndef BLIINK_FOG_H
#define BLIINK_FOG_H

#include "cbase.h"

#include "func_dust.h"

// Radial fog.
class CBliinkFog : public CFunc_Dust
{
public:
	DECLARE_CLASS( CBliinkFog, CFunc_Dust );
	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();
	
	CBliinkFog();
	~CBliinkFog();

public:
	virtual void Precache();

public:
	// Fog will begin closing in.
	void BeginContracting();

	// What time should the fog reach min radius.
	float CalcTargetTime();

	// Used to control radius.
	virtual void Think();

	// Determines whether or not an entity is in the fog.
	bool IsInFog( CBaseEntity* pEntity );

public:
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