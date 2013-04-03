#ifndef BLIINK_PLAYER_STATS_H
#define BLIINK_PLAYER_STATS_H

#ifdef CLIENT_DLL
#define CBliinkPlayerStats C_BliinkPlayerStats
#endif

#include "sdk_shareddefs.h"

#define BASE_HEALTH 100.0f
#define BASE_FATIGUE 100.0f
#define BASE_HUNGER 100.0f
#define BASE_EXPERIENCE 43
#define BASE_LEVEL 1
#define BASE_UPGRADE_POINTS 0
#define BASE_FATIGUE_REGEN_RATE_PER_SECOND 10.0f
#define BASE_MAX_EXPERIENCE 100
#define BASE_HUNGER_DEGEN_RATE_PER_SECOND 0.05f
#define BASE_HEATH_REGEN_RATE_PER_SECOND 5.0f
#define BASE_HEATH_DEGEN_RATE_PER_SECOND 0.5f

#define FATIGUE_SPRINT_LOSS 20.0f
#define FATIGUE_INIT_SPRINT_LOSS 10.0f
#define FATIGUE_JUMP_LOSS 15.0f
#define FATIGUE_STANDING_REGEN_MUL 5.0f
#define FATIGUE_WEAPON_MELEE_LOSS 25.0f
#define FATIGUE_WEAPON_LOSS 7.5f

#define UPGRADE_FATIGUE_REGEN_RATE 1.7f
#define UPGRADE_MAX_FATIGUE 10.0f

#define HEALTH_REGEN_DAMAGE_COOLDOWN 5.0f
#define HEALTH_PER_SEGMENT 20.0f
#define MAX_LEVEL 10
#define MAX_EXP_PER_LEVEL 20
#define HUNGER_REGEN_THRESHOLD 0.7f
#define HUNGER_DEGEN_THRESHOLD 0.0f

class CBliinkPlayer;

//-----------------------------------------------------------------------------
// CBliinkPlayerStats
// A class controlling the stats of the player including health, hunger,
// experience and fatigue, as well as other elements such as a player's level.
//-----------------------------------------------------------------------------
class CBliinkPlayerStats
{
	DECLARE_CLASS_NOBASE( CBliinkPlayerStats );
	DECLARE_EMBEDDED_NETWORKVAR();
	DECLARE_PREDICTABLE();

public:
	CBliinkPlayerStats();

	// Initialise values.
#ifndef CLIENT_DLL
	void Reset();

	// Runs every frame, for stuff like health regen etc.
	bool Think();  // true if dead
#endif

	// Getter functions.
	float GetHealth() { return m_fHealth; }
	float GetMaxHealth() { return m_fMaxHealth; }
	float GetFatigue() { return m_fFatigue; }
	float GetMaxFatigue() { return m_fMaxFatigue; }
	float GetFatigueRegenRate() { return m_fFatigueRegenRate; }
	float GetHunger() { return m_fHunger; }
	int GetExperience() { return m_iExperience; }
	int GetMaxExperience() { return m_iMaxExperience; }
	int GetLevel() { return m_iLevel; }
	int GetUpgradePoints() { return m_iUpgradePoints; }

	// Interface functions
	bool UseFatigue(float fFatigueAmount, bool limit = false);
	void GainFatigue(float fFatigueAmount);
	bool UseUpgrade(BLIINK_UPGRADE type);

#ifndef CLIENT_DLL
	void GainExperience(int iExpGain);
	void GainHealth(float fHealthGain);
	bool TakeDamage(float fHealthLoss); // true if dead
	void GainHunger(float fHungerGain);
#endif
	
private:
#ifdef CLIENT_DLL
	// Stat values
	float m_fHealth;
	float m_fFatigue;
	float m_fHunger;
	int m_iExperience;
	int m_iLevel;
	int m_iUpgradePoints;

	// Other values
	float m_fMaxHealth;
	float m_fMaxFatigue;
	int m_iMaxExperience;
	float m_fFatigueRegenRate;
#else
	// Stat values
	CNetworkVar( float, m_fHealth );
	CNetworkVar( float, m_fFatigue );
	CNetworkVar( float, m_fHunger );
	CNetworkVar( int, m_iExperience );
	CNetworkVar( int, m_iLevel );
	CNetworkVar( int, m_iUpgradePoints );

	// Other values
	CNetworkVar( float, m_fMaxHealth );
	CNetworkVar( float, m_fMaxFatigue );
	CNetworkVar( int, m_iMaxExperience );
	CNetworkVar( float, m_fFatigueRegenRate );

	float m_fLastDamageTime;

	// Player whose stats these are.
	CBliinkPlayer* m_pOwner;

public:
	// Sets the owner of these stats.
	void SetOwner( CBliinkPlayer* pPlayer ) { m_pOwner = pPlayer; }

	// Updates the maximum health of the owner with our max health.
	void UpdateMaxHealth( void );

	// Updates the health of the owner with our health.
	void UpdateHealth( void );
#endif
};

#endif //BLIINK_PLAYER_STATS_H