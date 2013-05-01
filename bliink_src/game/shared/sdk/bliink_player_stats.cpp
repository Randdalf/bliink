#include "cbase.h"
#include "bliink_player_stats.h"
#ifndef CLIENT_DLL
#include "bliink_player.h"
#include "takedamageinfo.h"
#endif
#include "sdk_shareddefs.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

// Utility function
float getSegmentLimit(float val, float max)
{
	if( val >= max - HEALTH_PER_SEGMENT )
		return max;

	int iValSegment = (int) floor(val / HEALTH_PER_SEGMENT);
	return ((float) (iValSegment+1)) * HEALTH_PER_SEGMENT - 0.01;
}

CBliinkPlayerStats::CBliinkPlayerStats()
{
	m_fHealth = BASE_HEALTH;
	m_fFatigue = BASE_FATIGUE;
	m_fHunger = BASE_HUNGER;
	m_iExperience = BASE_EXPERIENCE;
	m_iLevel = BASE_LEVEL;
	m_iUpgradePoints = BASE_UPGRADE_POINTS;
	m_fMaxHealth = BASE_HEALTH;
	m_fMaxFatigue = BASE_FATIGUE;
	m_fFatigueRegenRate = BASE_FATIGUE_REGEN_RATE_PER_SECOND;
	m_iMaxExperience = BASE_MAX_EXPERIENCE;
	m_iStatusEffect = BLIINK_STATUS_NORMAL;
	m_fStatusEndTime = gpGlobals->curtime;

#ifndef CLIENT_DLL
	m_fLastDamageTime = 0;
#endif
}

bool CBliinkPlayerStats::UseFatigue(float fFatigueAmount, bool limit)
{
	if( fFatigueAmount < 0 || (limit && fFatigueAmount > m_fFatigue) )
		return false;

	m_fFatigue -= fFatigueAmount;

	if( m_fFatigue < 0.0f )
		m_fFatigue = 0.0f;

	return true;
}

void CBliinkPlayerStats::GainFatigue(float fFatigueAmount)
{
	if( fFatigueAmount < 0 )
		return;

	m_fFatigue += fFatigueAmount;

	if( m_fFatigue >= m_fMaxFatigue )
		m_fFatigue = m_fMaxFatigue;

	return;
}

bool CBliinkPlayerStats::UseUpgrade(BLIINK_UPGRADE type)
{
	if( m_iUpgradePoints <= 0 )
		return false;

#ifndef CLIENT_DLL
	float flRatio;
	float flNewHealth;
#endif

	// fatigue is also handled on client
	switch(type)
	{
#ifndef CLIENT_DLL
	case BLIINK_UPGRADE_WEAPON_SLOTS:
		// Check if slot has been unlocked, so we don't waste points.
		if( !m_pOwner->GetBliinkInventory().UnlockWeaponSlot() )
			return false;

		break;
	case BLIINK_UPGRADE_HEALTH:
		// Increasing maximum health by one segment
		flRatio = m_fHealth/m_fMaxHealth;
		m_fMaxHealth += HEALTH_PER_SEGMENT;
		UpdateMaxHealth();

		// Keeping same health ratio as before, rounded up to the size of a segment.
		flNewHealth = m_fMaxHealth * flRatio;
		m_fHealth = flNewHealth;
		UpdateHealth();

		break;
#endif
	case BLIINK_UPGRADE_STAMINA:
		// Increase the fatigue regen rate.
		m_fFatigueRegenRate += UPGRADE_FATIGUE_REGEN_RATE;

		// Increase the max fatigue.
		m_fMaxFatigue += UPGRADE_MAX_FATIGUE;

		break;
	}

	m_iUpgradePoints--;

	return true;
}

#ifndef CLIENT_DLL
void CBliinkPlayerStats::Reset()
{
	m_fHealth = BASE_HEALTH;
	m_fFatigue = BASE_FATIGUE;
	m_fHunger = BASE_HUNGER;
	m_iExperience = BASE_EXPERIENCE;
	m_iLevel = BASE_LEVEL;
	m_iUpgradePoints = BASE_UPGRADE_POINTS;
	m_fMaxHealth = BASE_HEALTH;
	m_fMaxFatigue = BASE_FATIGUE;
	m_fFatigueRegenRate = BASE_FATIGUE_REGEN_RATE_PER_SECOND;
	m_iMaxExperience = BASE_MAX_EXPERIENCE;

	UpdateMaxHealth();
	UpdateHealth();
}

bool CBliinkPlayerStats::Think()
{
	float fTimePassed = gpGlobals->frametime;

	// Hunger (lost up to twice as fast with less stamina) 
	float flHungerDegen = (2.0f - (m_fFatigue/m_fMaxFatigue)) * BASE_HUNGER_DEGEN_RATE_PER_SECOND;

	m_fHunger -= fTimePassed * flHungerDegen;

	if( m_fHunger < 0.0f )
		m_fHunger = 0.0f;

	// Hunger-health regen
	if( m_fHunger >= HUNGER_REGEN_THRESHOLD*BASE_HUNGER &&
		gpGlobals->curtime - m_fLastDamageTime > HEALTH_REGEN_DAMAGE_COOLDOWN &&
		m_iStatusEffect == BLIINK_STATUS_NORMAL )
	{
		float flSegmentLimit = getSegmentLimit(m_fHealth, m_fMaxHealth);
		float flHealthLimit = MIN(m_fMaxHealth,flSegmentLimit);

		m_fHealth += fTimePassed * BASE_HEATH_REGEN_RATE_PER_SECOND;

		if( m_fHealth > flHealthLimit )
			m_fHealth = flHealthLimit;
	}

	// Hunger-health degen
	if( m_fHunger <= HUNGER_DEGEN_THRESHOLD*BASE_HUNGER )
	{
		m_fHealth -= fTimePassed * BASE_HEATH_DEGEN_RATE_PER_SECOND;

		if( m_fHealth <= 0.0f )
		{
			m_fHealth = 0.0f;
			return true;
		}
	}

	// Status
	StatusThink();

	return false;
}

void CBliinkPlayerStats::GainExperience(int iExpGain)
{
	// Can't gain experience if we're already at the max level.
	// Can't gain negative experience.
	if( m_iLevel == MAX_LEVEL || iExpGain <= 0 )
		return;

	// Gaining level(s)
	while( m_iExperience + iExpGain >= m_iMaxExperience )
	{
		m_iLevel++;
		if(m_iLevel % 2 == 0) m_iUpgradePoints++;

		// If we're max level just set our exp bar to full.
		if( m_iLevel == MAX_LEVEL )
		{
			m_iExperience = m_iMaxExperience;
			return;
		}
		// Reduce experience gain by the different to go up a level
		else
		if( m_iExperience + iExpGain >= m_iMaxExperience )
		{
			iExpGain -= (m_iMaxExperience - m_iExperience);
		}
		
		m_iExperience = 0.0f;
		m_iMaxExperience += MAX_EXP_PER_LEVEL;
	}
		
	// Only leftovers now
	m_iExperience += iExpGain;
}

void CBliinkPlayerStats::GainHealth(float fHealthGain)
{
	if( fHealthGain < 0.0f )
		return;

	m_fHealth += fHealthGain;

	if( m_fHealth > m_fMaxHealth )
		m_fHealth = m_fMaxHealth;

	UpdateHealth();
}

bool CBliinkPlayerStats::TakeDamage(float fDamage)
{
	if( fDamage < 0.0f )
		return false;

	m_fHealth -= fDamage;

	m_fLastDamageTime = gpGlobals->curtime;

	if( m_fHealth < 0.0f )
	{
		m_fHealth = 0.0f;
		return true;
	}
	else
	{
		return false;
	}
}

void CBliinkPlayerStats::GainHunger(float fHungerGain)
{
	if( fHungerGain < 0.0f )
		return;

	m_fHunger += fHungerGain;

	if( m_fHunger > BASE_HUNGER )
		m_fHunger = BASE_HUNGER;
}

void CBliinkPlayerStats::UpdateMaxHealth( void )
{
	if( !m_pOwner )
		return;

	m_pOwner->SetMaxHealth( (int) m_fMaxHealth );
}

void CBliinkPlayerStats::UpdateHealth( void )
{
	if( !m_pOwner )
		return;

	int iMyHealth = (int) floor(m_fHealth);
	int iCurrHealth = m_pOwner->GetHealth();

	// If our value is greater, than set it to that value.
	if( iMyHealth > iCurrHealth )
	{
		m_pOwner->SetHealth( iMyHealth);
	}
	// Otherwise, damage the player so they are at the requisite amount.
	else
	if( iMyHealth < iCurrHealth )
	{
		int iDiff = iCurrHealth - iMyHealth;

		CTakeDamageInfo info;
		info.Set(m_pOwner, m_pOwner, (float) iDiff, DMG_BLIINKSELF);

		m_pOwner->OnTakeDamage(info);
	}
}

void CBliinkPlayerStats::AfflictStatus(int iEffect, float fDuration)
{
	if( iEffect == BLIINK_STATUS_NORMAL )
		return;

	// Set status and end time
	switch(iEffect)
	{
	case BLIINK_STATUS_POISONED:
	case BLIINK_STATUS_BURNING:
	case BLIINK_STATUS_FOGGED:
		if( m_iStatusEffect != BLIINK_STATUS_NORMAL )
			return;
		else
		{
			m_iStatusEffect  = iEffect;
			m_fStatusEndTime = gpGlobals->curtime + fDuration;
		}

		break;
	case BLIINK_STATUS_SLOWED:
		if( m_iStatusEffect == BLIINK_STATUS_SLOWED )
		{
			m_fStatusEndTime += fDuration;
		}
		else
		if(  m_iStatusEffect == BLIINK_STATUS_NORMAL )
		{
			m_iStatusEffect  = BLIINK_STATUS_SLOWED;
			m_fStatusEndTime = gpGlobals->curtime + fDuration;
			
			m_pOwner->m_Shared.m_flRunSpeed = SDK_DEFAULT_PLAYER_RUNSPEED * STATUS_SLOW_PERCENT;
			m_pOwner->m_Shared.m_flSprintSpeed = SDK_DEFAULT_PLAYER_SPRINTSPEED * STATUS_SLOW_PERCENT;
		}

		break;
	}

}

void CBliinkPlayerStats::StatusThink()
{
	if( m_iStatusEffect == BLIINK_STATUS_NORMAL )
		return;

	// If our time is over...
	if( gpGlobals->curtime > m_fStatusEndTime )
	{
		switch(m_iStatusEffect)
		{
		case BLIINK_STATUS_SLOWED:
			m_pOwner->m_Shared.m_flRunSpeed = SDK_DEFAULT_PLAYER_RUNSPEED;
			m_pOwner->m_Shared.m_flSprintSpeed = SDK_DEFAULT_PLAYER_SPRINTSPEED;

			break;
		}

		m_iStatusEffect = BLIINK_STATUS_NORMAL;
	}
	// If our time is yet to come
	else
	{		
		float fTimePassed = gpGlobals->frametime;

		switch(m_iStatusEffect)
		{
			case BLIINK_STATUS_POISONED:
				m_fHealth -= fTimePassed * STATUS_POISON_DAMAGE_PER_SECOND;
				m_fLastDamageTime = gpGlobals->curtime;
				break;
			case BLIINK_STATUS_BURNING:
				m_fHealth -= fTimePassed * STATUS_BURN_DAMAGE_PER_SECOND;
				m_fLastDamageTime = gpGlobals->curtime;
				break;
			case BLIINK_STATUS_FOGGED:
				m_fHealth -= fTimePassed * STATUS_FOGGED_DAMAGE_PER_SECOND;
				break;
		}
	}
}

#endif