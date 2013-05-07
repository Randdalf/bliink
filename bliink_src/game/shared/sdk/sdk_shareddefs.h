//========= Copyright © 1996-2008, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#ifndef SDK_SHAREDDEFS_H
#define SDK_SHAREDDEFS_H
#ifdef _WIN32
#pragma once
#endif

//=========================
// GAMEPLAY RELATED OPTIONS
//=========================

// Do your players have stamina? - this is a pre-requisite for sprinting, if you define sprinting, and don't uncomment this, it will be included anyway.
#define SDK_USE_STAMINA

// Are your players able to sprint?
#define SDK_USE_SPRINTING

#define SDK_SHOOT_WHILE_JUMPING

#define SDK_GAME_DESCRIPTION	"Project Bliink"

//================================================================================
// Most elements below here are specific to the options above.
//================================================================================

#if defined ( SDK_USE_SPRINTING )

	#define INITIAL_SPRINT_STAMINA_PENALTY 15
	#define LOW_STAMINA_THRESHOLD	35

#endif // SDK_USE_SPRINTING

#define SDK_PLAYER_MODEL "models/player/bliink_player.mdl"
#define BLIINK_SURVIVOR_MODEL "models/player/bliink_player.mdl"
#define BLIINK_STALKER_MODEL "models/player/bliink_player.mdl"

//Tony; We need to precache all possible player models that we're going to use
extern const char *pszPossiblePlayerModels[];

extern const char *pszTeamNames[];

//Tony; these defines handle the default speeds for all of these - all are listed regardless of which option is enabled.
#define SDK_DEFAULT_PLAYER_RUNSPEED			220
#define SDK_DEFAULT_PLAYER_SPRINTSPEED		330
#define SDK_DEFAULT_PLAYER_PRONESPEED		100

#define BLIINK_DEFAULT_STALKER_SPEED		400

//--------------------------------------------------------------------------------------------------------
//
// Weapon IDs for all SDK Game weapons
//
typedef enum
{
	WEAPON_NONE = 0,

	SDK_WEAPON_NONE = WEAPON_NONE,
	SDK_WEAPON_MP5,
	SDK_WEAPON_SHOTGUN,
	SDK_WEAPON_GRENADE,
	SDK_WEAPON_PISTOL,
	SDK_WEAPON_CROWBAR,

	SDK_WEAPON_MAX,		// number of weapons weapon index
} SDKWeaponID;

#if defined(TF_DLL) || defined(TF_CLIENT_DLL)
	#define TIME_TO_DUCK		0.2
	#define TIME_TO_DUCK_MS		200.0f
#else
	#define TIME_TO_DUCK		0.4
	#define TIME_TO_DUCK_MS		400.0f
#endif 
#define TIME_TO_UNDUCK		0.2
#define TIME_TO_UNDUCK_MS	200.0f


typedef enum
{
	FM_AUTOMATIC = 0,
	FM_SEMIAUTOMATIC,
	FM_BURST,

} SDK_Weapon_Firemodes;

const char *WeaponIDToAlias( int id );
int AliasToWeaponID( const char *alias );


// The various states the player can be in during the join game process.
enum BliinkPlayerState
{
	// Happily running around in the game.
	// You can't move though if CSGameRules()->IsFreezePeriod() returns true.
	// This state can jump to a bunch of other states like STATE_PICKINGCLASS or STATE_DEATH_ANIM.
	//STATE_ACTIVE=0,
	
	// This is the state you're in when you first enter the server.
	// It's switching between intro cameras every few seconds, and there's a level info 
	// screen up.
	//STATE_WELCOME,			// Show the level intro screen.
	
	// During these states, you can either be a new player waiting to join, or
	// you can be a live player in the game who wants to change teams.
	// Either way, you can't move while choosing team or class (or while any menu is up).
	
	//STATE_DEATH_ANIM,			// Playing death anim, waiting for that to finish.
	//STATE_OBSERVER_MODE,		// Noclipping around, watching players, etc.

	// BLIINK STATES
	// Pre-game stuff

	// Puts you on the welcome screen, asks you whether you want to play or
	// spectate, puts you next to an intro camera.
	STATE_BLIINK_WELCOME=0,
	STATE_BLIINK_SPECTATE_PREGAME,
	STATE_BLIINK_WAITING_FOR_PLAYERS,

	// Game-time stuff
	STATE_BLIINK_SPECTATE,
	STATE_BLIINK_SURVIVOR,
	STATE_BLIINK_SURVIVOR_DEATH_ANIM,
	STATE_BLIINK_STALKER,
	STATE_BLIINK_STALKER_DEATH_ANIM,
	STATE_BLIINK_STALKER_RESPAWN,

	// Post-game stuff
	STATE_BLIINK_VIEW_RESULTS,

	NUM_PLAYER_STATES
};
#define SDK_PLAYER_DEATH_TIME	3.0f	//Minimum Time before respawning

#define BLIINK_STALKER_RESPAWN_TIME (10.0f+SDK_PLAYER_DEATH_TIME)

// Special Damage types
enum
{
	SDK_DMG_CUSTOM_NONE = 0,
	SDK_DMG_CUSTOM_SUICIDE,
};

// Player avoidance
#define PUSHAWAY_THINK_INTERVAL		(1.0f / 20.0f)

// Bliink teams
#define BLIINK_TEAM_SURVIVOR 2
#define BLIINK_TEAM_STALKER 3

// Bliink upgrades
typedef enum
{
	BLIINK_UPGRADE_WEAPON_SLOTS,
	BLIINK_UPGRADE_HEALTH,
	BLIINK_UPGRADE_STAMINA
} BLIINK_UPGRADE;

#endif // SDK_SHAREDDEFS_H
