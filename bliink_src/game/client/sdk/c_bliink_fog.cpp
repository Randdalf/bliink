#include "cbase.h"

#include "c_func_dust.h"
#include "math.h"
#include "c_func_dust.h"
#include "func_dust_shared.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

// Adaption of C_Func_Dust for Bliink.
class C_BliinkFog : public C_Func_Dust
{
public:	
	DECLARE_CLIENTCLASS();
	DECLARE_CLASS( C_BliinkFog, C_Func_Dust );

	C_BliinkFog();
	~C_BliinkFog();

private:
	virtual void AttemptSpawnNewParticle();
	virtual void ClientThink();

public:
	float m_flMaxFogRadius; 
	float m_flMinFogRadius; 
	float m_flFogHeightUp;
	float m_flFogHeightDown; 
	float m_flFogRadius;
};

LINK_ENTITY_TO_CLASS( func_bliink_fog, C_BliinkFog );

IMPLEMENT_CLIENTCLASS_DT( C_BliinkFog, DT_BliinkFog, CBliinkFog )
	RecvPropFloat( RECVINFO(m_flFogRadius) ),
	RecvPropFloat( RECVINFO(m_flMaxFogRadius) ),
	RecvPropFloat( RECVINFO(m_flMinFogRadius) ),
	RecvPropFloat( RECVINFO(m_flFogHeightUp) ),
	RecvPropFloat( RECVINFO(m_flFogHeightDown) ),
END_RECV_TABLE()

C_BliinkFog::C_BliinkFog()
{
	Msg("yo!\n");
}

C_BliinkFog::~C_BliinkFog()
{

}

void C_BliinkFog::AttemptSpawnNewParticle()
{
	// Find a random spot inside our bmodel.
	static int nTests=10;

	if( m_flFogRadius >= m_flMaxFogRadius || m_flFogRadius == 0.0f )
		return;

	for( int iTest=0; iTest < nTests; iTest++ )
	{
		// Calculating point to spawn at around player.
		Vector pOrigin = CBasePlayer::GetLocalPlayer()->GetAbsOrigin();
		Vector fOrigin = GetAbsOrigin();
		float x = pOrigin.x;
		float y = pOrigin.y;
		float range = 1.5f * ((float) this->m_DistMax);
		float rPercent = RandomFloat( 0, 1 );
		float aPercent = RandomFloat( 0, 1 );

		float height =  RandomFloat( fOrigin.z - m_flFogHeightDown, fOrigin.z + m_flFogHeightUp );
		float dist = rPercent * range;
		float angle = 2*M_PI*aPercent;

		Vector vTest = Vector( x + dist*cos(angle), y + dist*sin(angle), height );

		float xOffset = vTest.x - fOrigin.x;
		float yOffset = vTest.y - fOrigin.y;
		float fromCentre = sqrt(xOffset*xOffset + yOffset*yOffset);

		if( fromCentre > m_flFogRadius )
		{
			int contents = enginetrace->GetPointContents_Collideable( GetCollideable(), vTest );
			if( contents & CONTENTS_SOLID )
			{
				PMaterialHandle my_hMaterial = m_Effect.GetPMaterial( "particle/particle_smokegrenade1" );;
				CFuncDustParticle *pParticle = (CFuncDustParticle*)m_Effect.AddParticle( 10, my_hMaterial, vTest );
				if( pParticle )
				{
					pParticle->m_vVelocity = RandomVector( -m_SpeedMax, m_SpeedMax );
					pParticle->m_vVelocity.z -= m_FallSpeed;

					pParticle->m_flLifetime = 0;
					pParticle->m_flDieTime = RemapVal( rand(), 0, RAND_MAX, m_LifetimeMin, m_LifetimeMax );

					if( m_DustFlags & DUSTFLAGS_SCALEMOTES )
						pParticle->m_flSize = RemapVal( rand(), 0, RAND_MAX, m_flSizeMin/10000.0f, m_flSizeMax/10000.0f );
					else
						pParticle->m_flSize = RemapVal( rand(), 0, RAND_MAX, m_flSizeMin, m_flSizeMax );
			
					pParticle->m_Color = m_Color;
				}

				break;
			}
		}
	}
}

void C_BliinkFog::ClientThink()
{
	BaseClass::ClientThink();

	// Do bbox based on fog radius.
	Vector o = GetAbsOrigin();
	Vector vWorldMins, vWorldMaxs;

	vWorldMins = o - Vector( m_flMaxFogRadius, m_flMaxFogRadius, m_flFogHeightDown );
	vWorldMaxs = o + Vector( m_flMaxFogRadius, m_flMaxFogRadius, m_flFogHeightDown );

	m_Effect.GetBinding().SetBBox( vWorldMins, vWorldMaxs );
}