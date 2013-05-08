//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//=============================================================================//
#ifndef HL2WARS_PLAYER_H
#define HL2WARS_PLAYER_H
#pragma once

class CHL2Wars_Player;

#include "player.h"
#include "hl2wars/rts_playerlocaldata.h"
#include "ai_basenpc.h"
#include "hl2wars/rts_shareddefs.h"
#include "hl2_player.h"

typedef struct unitgroup_t
{
	DECLARE_CLASS_NOBASE( unitgroup_t );
	DECLARE_DATADESC();

	CHandle<CAI_BaseNPC> m_Group[MAXSELECTED];
} unitgroup_t;


//=============================================================================
// >> HL2Wars_Player
//=============================================================================
class CHL2Wars_Player : public CHL2_Player
{
public:
	DECLARE_CLASS( CHL2Wars_Player, CHL2_Player );

	CHL2Wars_Player();
	~CHL2Wars_Player( void );
	
	static CHL2Wars_Player *CreatePlayer( const char *className, edict_t *ed )
	{
		CHL2Wars_Player::s_PlayerEdict = ed;
		return (CHL2Wars_Player*)CreateEntityByName( className );
	}

	DECLARE_SERVERCLASS();
	DECLARE_DATADESC();

	virtual void Precache( void );
	//virtual void InitialSpawn( void );
	virtual void Spawn( void );
	virtual void SharedSpawn(); // Shared between client and server.
	void GiveAllItems( void );
	virtual void CheatImpulseCommands( int iImpulse );
	void GiveDefaultItems( void );
	virtual void PostThink( void );
	virtual void PreThink( void );
	virtual void PlayerDeathThink( void );
	//virtual bool ClientCommand( const char *cmd );
	bool ClientCommand( const CCommand &args );
	virtual void Event_Killed( const CTakeDamageInfo &info );
	virtual void UpdateOnRemove( void );
	virtual CBaseEntity* EntSelectSpawnPoint( void );

	void State_Enter_ACTIVE();

	bool IsReady();
	void SetReady( bool bReady );

	virtual bool BumpWeapon( CBaseCombatWeapon *pWeapon );
	void SetPlayerNormalMoveType( void );
	void SetRTSMode( bool mode );
	void ToggleRTSMode( void );

	// setters for data received from client
	void SetVecPickingRay( Vector vecPickingRayMouse );

public:
	// This player's data that should only be replicated to 
	//  the player and not to other players.
	CNetworkVarEmbedded( CHLWPlayerLocalData, m_HLWLocal );

private:
	bool m_bReady;


public:
	//----------- controller prototypes
	void ProcesRTSCommands();
	void ProcesAbilityCommand( int ability_button );
	void ProcesQueueCommand( int queue_button );

	void SetBehaviorSelected( int behavior );
	void InvalidateBehaviorButtons();

	void CheckLeftMouseButton( void );
	void CheckRightMouseButton( void );

	void CheckSpaceBar( void );

	// selection
	void Selection( void );
	void SelectRay( void );

	// orders
	void Order( void );
	void MoveOrder();
	void AbilityOrder( CBaseEntity *pTarget );
	void MoveOrderNormal( CAI_BaseNPC *pNPC,Vector origin, float radius );
	void MoveOrderDefense( CAI_BaseNPC *pNPC, Vector origin, float radius );
	void AttackOrder( CAI_BaseNPC *pEnemy );
	void AttackGroundOrder( CBaseEntity *pEnt );
	bool IsValidAttackTarget( int team_id );

	void BuildOrder( );

	// unit selection management
	void		 AddUnit(  CAI_BaseNPC *pTarget );
	void		 RemoveUnit( int index );
	CAI_BaseNPC  *GetUnit( int index );
	void         ClearSelection( void );
	int          isAlreadySelected( CAI_BaseNPC *pTarget );
	int			 CountUnits() { return m_HLWLocal.m_iNumSelected; };
	void		 KillSelectedUnits();
	void		 DestroySelectedBuilding();
	void		 OrderCancelSelectedUnits();

	int GetLevelRTS( void ) { return m_HLWLocal.m_iLevelRTS; };

	void AddGroup( int group );
    void SelectGroup( int group );
	void UpdateGroup( int group );

	// getters for private data
	Vector GetMouseAim() { return m_vecPickingRayMouse; };

	// sound/voices handling when ordering/selecting
	void EmitSoundUnit( CAI_BaseNPC *pUnit, const char *soundtype );
	//void EmitSoundAbility( FileAbilityInfo_t *pFAI, const char *soundtype );

private:
	QAngle CalculateArrivalDirection( void );
	void CheckArrivalDirection( CRTSPointOrder *pTarget );

	CBaseEntity *GetEntityMouse( void ); 
	Vector RetrieveGroundPos( void ); 
	int GetAbilityType( CAI_BaseNPC *pNPC, int i );
	void UpdateSelectedUnits( void );
	
private:
	bool m_bHasSuit;		// when returning from rts mode, we might need to give the suit back.

private:
	Vector m_vecPickingRayMouse;

	Vector vecMouseRayLeftPressed;
	Vector vecMouseRayLeftReleased;
	Vector vecMouseRayRightPressed;
	Vector vecMouseRayRightReleased;

	//int m_nRTSButtonsPressed;
	//int	m_iSelectedPointer;

	unitgroup_t m_NPCGroup[10];

public:
	// controller info
	int m_nRTSButtons;
	int m_nRTSButtonsPressed;

	int m_nRTSCommands;
	int m_nRTSCommands2;

	int m_iShiftQueue;
	

	// gameroom info
private:
	CNetworkVar( int, m_iSlot );

public:
	void SetSlot( int slot ) { m_iSlot = slot; }
	int GetSlot() { return m_iSlot; }
	
};

//-----------------------------------------------------------------------------
// Purpose:
//-----------------------------------------------------------------------------
inline CAI_BaseNPC *CHL2Wars_Player::GetUnit( int index )
{
	return m_HLWLocal.m_hSelectedUnits.Get( index ).Get();
}

inline CHL2Wars_Player *ToHL2WarsPlayer( CBaseEntity *pEntity )
{
	if ( !pEntity || !pEntity->IsPlayer() )
		return NULL;

	return dynamic_cast<CHL2Wars_Player*>( pEntity );
}

#endif //HL2WARS_PLAYER_H
