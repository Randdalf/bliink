#include "cbase.h"

#include "c_physicsprop.h"
#include "particle_parse.h"
#include "particles_new.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//-----------------------------------------------------------------------------
// C_BliinkExpOrb
// An experience orb which gives a pre-determined amount of experience to
// players that touch it.
//-----------------------------------------------------------------------------
class C_BliinkExpOrb : public C_PhysicsProp
{
public:
	DECLARE_CLASS( C_BliinkExpOrb, C_PhysicsProp );
	DECLARE_CLIENTCLASS();

	C_BliinkExpOrb();
	~C_BliinkExpOrb();

	virtual void Spawn( void );
	virtual void Precache( void);

private:
	CNewParticleEffect* pEffect;
};

LINK_ENTITY_TO_CLASS( bliink_exp_orb, C_BliinkExpOrb );

IMPLEMENT_CLIENTCLASS_DT( C_BliinkExpOrb, DT_BliinkExpOrb, CBliinkExpOrb )
	// ...
END_RECV_TABLE()

C_BliinkExpOrb::C_BliinkExpOrb()
{
	pEffect = NULL;
}

C_BliinkExpOrb::~C_BliinkExpOrb()
{
	if( pEffect )
		pEffect->SetRemoveFlag();
}

void C_BliinkExpOrb::Spawn( void )
{
	Precache();

	pEffect = ParticleProp()->Create( "exp_orb", PATTACH_ABSORIGIN_FOLLOW  );
}

void C_BliinkExpOrb::Precache( void )
{
	PrecacheParticleSystem( "exp_orb" );
	PrecacheModel( "models/util/empty.mdl" );
}