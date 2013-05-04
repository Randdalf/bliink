#include "cbase.h"

#include "func_dust_shared.h"
#include "bliink_gamevars_shared.h"
#include "bliink_fog.h"
#include "bliink_player.h"
#include "bliink_gamerules.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

IMPLEMENT_SERVERCLASS_ST_NOBASE( CBliinkFog, DT_BliinkFog )
	// Dust stuff
	SendPropInt( SENDINFO(m_Color),	32, SPROP_UNSIGNED, SendProxy_Color32ToInt32 ),
	SendPropInt( SENDINFO(m_SpawnRate),	12, SPROP_UNSIGNED ),
	SendPropInt( SENDINFO(m_SpeedMax),	12, SPROP_UNSIGNED ),
	SendPropFloat( SENDINFO(m_flSizeMin), 0, SPROP_NOSCALE ),
	SendPropFloat( SENDINFO(m_flSizeMax), 0, SPROP_NOSCALE ),
	SendPropInt( SENDINFO(m_DistMax), 16, SPROP_UNSIGNED ),
	SendPropInt( SENDINFO(m_LifetimeMin), 4, SPROP_UNSIGNED ),
	SendPropInt( SENDINFO(m_LifetimeMax), 4, SPROP_UNSIGNED ),
	SendPropInt( SENDINFO(m_DustFlags), DUST_NUMFLAGS, SPROP_UNSIGNED ),

	// Bliink stuff
	SendPropFloat( SENDINFO(m_flMaxFogRadius), 0, SPROP_NOSCALE ),
	SendPropFloat( SENDINFO(m_flMinFogRadius), 0, SPROP_NOSCALE ),
	SendPropFloat( SENDINFO(m_flFogHeightUp), 0, SPROP_NOSCALE ),
	SendPropFloat( SENDINFO(m_flFogHeightDown), 0, SPROP_NOSCALE ),
END_SEND_TABLE()


BEGIN_DATADESC( CBliinkFog )
	// Dust stuff
	DEFINE_FIELD( m_DustFlags,FIELD_INTEGER ),

	DEFINE_KEYFIELD( m_Color,		FIELD_COLOR32,	"Color" ),
	DEFINE_KEYFIELD( m_SpawnRate,	FIELD_INTEGER,	"SpawnRate" ),
	DEFINE_KEYFIELD( m_flSizeMin,	FIELD_FLOAT,	"SizeMin" ),
	DEFINE_KEYFIELD( m_flSizeMax,	FIELD_FLOAT,	"SizeMax" ),
	DEFINE_KEYFIELD( m_SpeedMax,		FIELD_INTEGER,	"SpeedMax" ),
	DEFINE_KEYFIELD( m_LifetimeMin,	FIELD_INTEGER,	"LifetimeMin" ),
	DEFINE_KEYFIELD( m_LifetimeMax,	FIELD_INTEGER,	"LifetimeMax" ),
	DEFINE_KEYFIELD( m_DistMax,		FIELD_INTEGER,	"DistMax" ),
	DEFINE_FIELD( m_iAlpha,			FIELD_INTEGER ),
	DEFINE_KEYFIELD( m_FallSpeed,	FIELD_FLOAT,	"FallSpeed" ),

	// Bliink stuff
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

void CBliinkFog::Spawn()
{
	Precache();

	// setting colour
	color32 clr = { m_Color.m_Value.r, m_Color.m_Value.g, m_Color.m_Value.b, m_iAlpha };
	m_Color.Set( clr );

	m_flFogRadius = m_flMaxFogRadius;
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
}