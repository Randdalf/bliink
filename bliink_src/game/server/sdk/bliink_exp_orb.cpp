#include "cbase.h"
#include "bliink_exp_orb.h"
#include "bliink_player.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

LINK_ENTITY_TO_CLASS( bliink_exp_orb, CBliinkExpOrb );

// Networking.
IMPLEMENT_SERVERCLASS_ST( CBliinkExpOrb, DT_BliinkExpOrb )
	// ...
END_SEND_TABLE()

// Data description
BEGIN_DATADESC( CBliinkExpOrb )
	
	DEFINE_ENTITYFUNC( OrbTouch ),

	DEFINE_FIELD( m_iExperience, FIELD_INTEGER ),

END_DATADESC()

CBliinkExpOrb::CBliinkExpOrb( void )
{
	Precache();

	m_iExperience = 1;
}

bool CBliinkExpOrb::CreateVPhysics()
{
	int R = EXP_ORB_RADIUS;

	// Solidity
	SetSolid( SOLID_BBOX );

	AddSolidFlags( FSOLID_TRIGGER | FSOLID_NOT_STANDABLE );

	// Collision bounds
	SetCollisionBounds( -Vector(R,R,R), Vector(R,R,R) );
	SetCollisionGroup( COLLISION_GROUP_DEBRIS );

	// VPhysics
	objectparams_t params = g_PhysDefaultObjectParams;

	params.dragCoefficient = 100.0f;
	params.rotdamping = 100.0f;
	params.pGameData = static_cast<void *>(this);

	IPhysicsObject *pPhysicsObject = physenv->CreateSphereObject( R, 0, GetAbsOrigin(), GetAbsAngles(), &params, false );

	if ( pPhysicsObject )
	{
		VPhysicsSetObject( pPhysicsObject );
		SetMoveType( MOVETYPE_VPHYSICS );
		pPhysicsObject->Wake();
	}
	
	return true;
}

void CBliinkExpOrb::OrbTouch( CBaseEntity *pOther )
{
	if( !pOther )
		return;

	CBliinkPlayer* pPlayer = ToBliinkPlayer( pOther );

	// Attempt to add experience.
	if( pOther->IsPlayer() && pPlayer && pPlayer->State_Get() == STATE_BLIINK_SURVIVOR )
	{
		pPlayer->GetBliinkPlayerStats().GainExperience( m_iExperience );
		
		Remove();			
	}
}

void CBliinkExpOrb::SetExperience( int iExperience )
{
	if( iExperience >= 0 )
		m_iExperience = iExperience;
}

void CBliinkExpOrb::Precache( )
{
	PrecacheModel( "models/util/empty.mdl" );
}

void CBliinkExpOrb::Spawn()
{
	SetTouch( &CBliinkExpOrb::OrbTouch );
	SetModel( "models/util/empty.mdl" );
	CreateVPhysics();
}

void spawnRandomOrbs( Vector vOrigin, float fRadius, int iMinOrbs, int iMaxOrbs, int iMinExp, int iMaxExp )
{
	CBliinkExpOrb* pOrb;
	int iNumOrbs = RandomInt( iMinOrbs, iMaxOrbs );

	for(int i=0; i<iNumOrbs; i++)
	{
		float dist = fRadius*RandomFloat(0, 1);
		float angle = (2*M_PI)*RandomFloat(0, 1);

		Vector rndOrigin( vOrigin.x + dist*cos(angle), vOrigin.y + dist*sin(angle), vOrigin.z );

		pOrb = (CBliinkExpOrb*) CBaseEntity::CreateNoSpawn( "bliink_exp_orb", rndOrigin, QAngle());
		pOrb->SetExperience( RandomInt(iMinExp, iMaxExp ) );
		DispatchSpawn( pOrb );
	}
}