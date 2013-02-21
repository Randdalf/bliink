#include "cbase.h"
#include "bliink_player.h"
#include "sdk_shareddefs.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

#define HEALTH_SEGMENT_AMOUNT 25
#define INITIAL_SEGMENT_COUNT 3

#define BASE_EXPERIENCE 10
#define EXPERIENCE_PER_LEVEL 4
#define MAX_LEVEL 10

#define FATIGUE_UPGRADE 10
#define FATIGUE_BASE_REGEN_RATE 0.5
#define FATIGUE_INIT_REGEN_RATE 2
#define FATIGUE_REGEN_RATE_UPGRADE 0.5

#define HUNGER_HEALTH_REGEN_THRESH 30.0f
#define MAX_HEALTH_REGEN_RATE 2
#define HUNGER_DEGEN_RATE 0.7
#define STARVE_HEALTH_LOSS 0.3

void CBliinkPlayer::InitBliinkStats( void )
{
	// health bar
	m_iBliinkHealthSegments = INITIAL_SEGMENT_COUNT;
	m_fBliinkHealthMax = m_iBliinkHealthSegments * HEALTH_SEGMENT_AMOUNT;
	m_fBliinkHealth = m_fBliinkHealthMax;

	// hunger bar
	m_fBliinkHungerMax = 100.0f;
	m_fBliinkHunger = m_fBliinkHungerMax;

	// fatigue bar
	m_fBliinkFatigueMax = 100.0f;
	m_fBliinkFatigue = m_fBliinkFatigueMax;
	m_fBliinkFatigueRegenRate = FATIGUE_INIT_REGEN_RATE;

	// exp meter
	m_iBliinkLevel = 1;
	m_iBliinkExperienceMax = BASE_EXPERIENCE + EXPERIENCE_PER_LEVEL*m_iBliinkLevel;
	m_iBliinkExperience = 0;
	m_iBliinkSkillPoints = 0;
}

void CBliinkPlayer::GainExperience( int m_iExperienceAmount )
{
	m_iBliinkExperience += m_iExperienceAmount;

	// Not levelled up
	if( m_iBliinkExperience <= m_iBliinkExperienceMax )
		return;

	// Can't level up
	if( m_iBliinkLevel == MAX_LEVEL )
	{
		m_iBliinkExperience = m_iBliinkExperienceMax;
		return;
	}

	// Levelling up
	m_iBliinkExperience -= m_iExperienceAmount;
	m_iBliinkExperienceMax += EXPERIENCE_PER_LEVEL;
	m_iBliinkSkillPoints += 1;
	m_iBliinkLevel += 1;
}

void CBliinkPlayer::UseUpgradePoint( BLIINK_UPGRADE type )
{
	if( m_iBliinkSkillPoints < 1 )
		return;

	switch( type )
	{		
	case BLIINK_UPGRADE_WEAPON_SLOTS:
		// ...

		m_iBliinkSkillPoints -=1;
		break;
	case BLIINK_UPGRADE_HEALTH:
		m_iBliinkHealthSegments += 1;
		m_fBliinkHealthMax += HEALTH_SEGMENT_AMOUNT;
		m_fBliinkHealth += HEALTH_SEGMENT_AMOUNT;

		m_iBliinkSkillPoints -=1;
		break;
	case BLIINK_UPGRADE_STAMINA:
		m_fBliinkFatigueRegenRate += FATIGUE_REGEN_RATE_UPGRADE;
		m_fBliinkFatigueMax += FATIGUE_UPGRADE;
		m_fBliinkFatigue = m_fBliinkFatigueMax;

		m_iBliinkSkillPoints -=1;
		break;
	case BLIINK_UPGRADE_WEAPON_PROWESS:
		// ...

		m_iBliinkSkillPoints -=1;
		break;
	}

	return;
}

bool CBliinkPlayer::HasEnoughFatigue( float m_fRequestedFatigue )
{
	return m_fBliinkFatigue >= m_fRequestedFatigue;
}

void CBliinkPlayer::UseFatigue( float m_fFatigueAmount )
{
	if( m_fBliinkFatigue >= m_fFatigueAmount )
		m_fBliinkFatigue -= m_fFatigueAmount;
}

void CBliinkPlayer::AddHunger( float m_fHungerAmount )
{	
	m_fBliinkHunger += m_fHungerAmount;
	
	if( m_fBliinkHunger > m_fBliinkHungerMax )
		m_fBliinkHunger = m_fBliinkHungerMax;
	else if( m_fBliinkHunger < 0 )
		m_fBliinkHunger = 0;
}

void CBliinkPlayer::AddHealth( int m_iSegments )
{
	if( m_iSegments < 1 )
		return;

	m_fBliinkHealth += HEALTH_SEGMENT_AMOUNT*m_iSegments;

	if( m_fBliinkHealth > m_fBliinkHealthMax )
		m_fBliinkHealth = m_fBliinkHealthMax;
}

void CBliinkPlayer::AddHealth( float m_fHealthAmount )
{
	if( m_fHealthAmount < 0 )
	{
		m_fBliinkHealth -= m_fHealthAmount;

		if( m_fBliinkHealth < 0 )
			m_fBliinkHealth = 0;

		return;
	}

	// ...
}

void CBliinkPlayer::BliinkStatsThink( void )
{
	// Hunger degeneration
	AddHunger( -HUNGER_DEGEN_RATE ); 

	// Health regeneration
	if( m_fBliinkHunger > HUNGER_HEALTH_REGEN_THRESH )
	{
		float m_fRegenAmount = (m_fBliinkHunger - HUNGER_HEALTH_REGEN_THRESH);
		m_fRegenAmount /= HUNGER_HEALTH_REGEN_THRESH;
		m_fRegenAmount *= MAX_HEALTH_REGEN_RATE;

		AddHealth(m_fRegenAmount);
	}
	else if( m_fBliinkHunger <= 0 )
	{
		AddHealth((float)(-STARVE_HEALTH_LOSS));
	}

	// Fatigue regeneration
	float m_fRegenAmount = (m_fBliinkHunger / m_fBliinkHungerMax );
	m_fRegenAmount *= m_fBliinkFatigueRegenRate;
	m_fRegenAmount += FATIGUE_BASE_REGEN_RATE;
}