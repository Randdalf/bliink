#include "cbase.h"

#include "func_dust.h"
#include "func_dust_shared.h"
#include "bliink_gamevars_shared.h"
#include "bliink_fog.h"
#include "bliink_player.h"
#include "bliink_gamerules.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

IMPLEMENT_SERVERCLASS_ST( CBliinkFog, DT_BliinkFog )
	SendPropFloat( SENDINFO(m_flFogRadius), 0, SPROP_NOSCALE ),
	SendPropFloat( SENDINFO(m_flMaxFogRadius), 0, SPROP_NOSCALE ),
	SendPropFloat( SENDINFO(m_flMinFogRadius), 0, SPROP_NOSCALE ),
	SendPropFloat( SENDINFO(m_flFogHeightUp), 0, SPROP_NOSCALE ),
	SendPropFloat( SENDINFO(m_flFogHeightDown), 0, SPROP_NOSCALE ),
END_SEND_TABLE()


BEGIN_DATADESC( CBliinkFog )
	DEFINE_KEYFIELD ( m_flMaxFogRadius, FIELD_FLOAT, "MaxFogRadius" ),
	DEFINE_KEYFIELD ( m_flMinFogRadius, FIELD_FLOAT, "MinFogRadius" ),
	DEFINE_KEYFIELD ( m_flFogHeightUp, FIELD_FLOAT, "FogHeightUp" ),
	DEFINE_KEYFIELD ( m_flFogHeightDown, FIELD_FLOAT, "FogHeightDown" ),
END_DATADESC()

LINK_ENTITY_TO_CLASS( func_bliink_fog, CBliinkFog );
	
CBliinkFog::CBliinkFog()
{
	m_bIsContracting = false;
}

CBliinkFog::~CBliinkFog()
{
}

void CBliinkFog::Precache()
{
	PrecacheMaterial( "particle/sparkles" );
}

int GetNumSurvivors()
{
	int survivors = 0;

	for(int i=1; i<=gpGlobals->maxClients; i++)
	{
		CBliinkPlayer* pPlayer = ToBliinkPlayer(UTIL_PlayerByIndex(i));

		if( !pPlayer || !pPlayer->IsPlayer() )
			continue;

		if( pPlayer->State_Get() == STATE_BLIINK_SURVIVOR )
			survivors++;		
	}

	survivors++;

	return survivors;
}

float CBliinkFog::CalcTargetTime()
{
	float fBaseTime = Bliink_FogBaseTime.GetFloat();
	float fPlayerTime = Bliink_FogPlayerTime.GetFloat();
	float fSurvivors = (float) GetNumSurvivors();

	return m_flStartTime + fBaseTime + (fPlayerTime*fSurvivors);
}

void CBliinkFog::BeginContracting()
{
	m_bIsContracting = true;

	m_flStartTime = gpGlobals->curtime;
	m_flTargetTime = CalcTargetTime();
	m_flFogRadius = m_flMaxFogRadius;

	SetNextThink( gpGlobals->curtime + 0.1f );
}

void CBliinkFog::Think()
{
	m_flTargetTime = CalcTargetTime();

	if( m_bIsContracting && gpGlobals->curtime < m_flTargetTime && m_flFogRadius >= m_flMinFogRadius )
	{
		float fRadiusPerSec = (m_flFogRadius - m_flMinFogRadius)/(m_flTargetTime - gpGlobals->curtime);

		m_flFogRadius -= fRadiusPerSec*0.1f;
	}

	SetNextThink( gpGlobals->curtime + 0.1f );
}

bool CBliinkFog::IsInFog( CBaseEntity* pEntity )
{
	if( !pEntity )
		return false;

	Vector pOrigin = pEntity->GetAbsOrigin();
	Vector fOrigin = GetAbsOrigin();

	float xOffset = pOrigin.x - fOrigin.x;
	float yOffset = pOrigin.y - fOrigin.y;
	float fromCentre = sqrt(xOffset*xOffset + yOffset*yOffset);

	if( fromCentre > m_flFogRadius )
		return true;
	else
		return false;
}