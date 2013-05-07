#ifndef BLIINK_EXP_ORB_H
#define BLIINK_EXP_ORB_H

#include "cbase.h"
#include "props.h"

#define EXP_ORB_RADIUS 12

//-----------------------------------------------------------------------------
// CBliinkExpOrb
// An experience orb which gives a pre-determined amount of experience to
// players that touch it.
//-----------------------------------------------------------------------------
class CBliinkExpOrb : public CPhysicsProp
{
public:
	DECLARE_CLASS( CBliinkExpOrb, CPhysicsProp );
	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();

	CBliinkExpOrb( void );
	
	virtual bool OverridePropdata() { return true; }
	bool	CreateVPhysics();
	void	OrbTouch( CBaseEntity *pOther );
	void	SetExperience( int iExperience );
	void	Precache( );
	void	Spawn();

private:
	int	m_iExperience;
};

// Spawns a random number of exp. orbs with a random amount of experience,
// randomly, inside a radius.
void spawnRandomOrbs( Vector vOrigin, float fRadius, int iMinOrbs, int iMaxOrbs, int iMinExp, int iMaxExp );


#endif // BLIINK_EXP_ORB_H