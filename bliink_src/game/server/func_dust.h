#ifndef FUNC_DUST_H
#define FUNC_DUST_H

#include "cbase.h"

class CFunc_Dust : public CBaseEntity
{
public:
	DECLARE_CLASS( CFunc_Dust, CBaseEntity );
	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();

					CFunc_Dust();
	virtual 		~CFunc_Dust();


// CBaseEntity overrides.
public:

	virtual void	Spawn();
	virtual void	Activate();
	virtual void	Precache();
	virtual bool	KeyValue( const char *szKeyName, const char *szValue );


// Input handles.
public:
	
	void InputTurnOn( inputdata_t &inputdata );
	void InputTurnOff( inputdata_t &inputdata );


// FGD properties.
public:

	CNetworkVar( color32, m_Color );
	CNetworkVar( int, m_SpawnRate );
	
	CNetworkVar( float, m_flSizeMin );
	CNetworkVar( float, m_flSizeMax );

	CNetworkVar( int, m_SpeedMax );

	CNetworkVar( int, m_LifetimeMin );
	CNetworkVar( int, m_LifetimeMax );

	CNetworkVar( int, m_DistMax );

	CNetworkVar( float, m_FallSpeed )

public:

	CNetworkVar( int, m_DustFlags );	// Combination of DUSTFLAGS_

private:	
	int			m_iAlpha;

};


class CFunc_DustMotes : public CFunc_Dust
{
	DECLARE_CLASS( CFunc_DustMotes, CFunc_Dust );
public:
					CFunc_DustMotes();
};


class CFunc_DustCloud : public CFunc_Dust
{
	DECLARE_CLASS( CFunc_DustCloud, CFunc_Dust );
public:
};

#endif