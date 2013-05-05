#include "cbase.h"
#include "gamevars_shared.h"

#ifdef CLIENT_DLL
#include "c_bliink_player.h"
#endif

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

// Bliink ConVars
ConVar Bliink_CountdownToLive( "bliink_countdown_to_live", "5.0", FCVAR_REPLICATED );
ConVar Bliink_ResultsTime( "bliink_results_time", "5.0", FCVAR_REPLICATED );
ConVar Bliink_MinPlayers( "bliink_min_players", "2", FCVAR_REPLICATED );
ConVar Bliink_MinSurvivors( "bliink_min_survivors", "1", FCVAR_REPLICATED );
ConVar Bliink_FogBaseTime( "bliink_fog_basetime", "300.0f", FCVAR_REPLICATED );
ConVar Bliink_FogPlayerTime( "bliink_fog_playertime", "90.0f", FCVAR_REPLICATED );

// Bliink ConCommands
#ifdef CLIENT_DLL
void send_f ( const CCommand & args )
{
	engine->ServerCmd( args[ 0 ] );
}

void send_upgrade_f ( const CCommand & args )
{
	C_BliinkPlayer* pPlayer = ToBliinkPlayer( CBasePlayer::GetLocalPlayer() );

	if( !pPlayer || pPlayer->GetBliinkPlayerStats().GetUpgradePoints() <= 0 )
		return;

	engine->ServerCmd( args[ 0 ] );
}

bool send_inv_arg1 ( const CCommand & args )
{
	if ( args.ArgC() != 2 )
	{
		return false;
	}

	engine->ServerCmd( args.GetCommandString() );

	return true;
}

bool send_inv_arg2 ( const CCommand & args )
{
	if ( args.ArgC() != 3 )
	{
		return false;
	}

	engine->ServerCmd( args.GetCommandString() );

	return true;
}

ConCommand Bliink_WelcomePlay( "bliink_welcome_play", send_f, "Play the game, if you're at the welcome screen.", FCVAR_CLIENTCMD_CAN_EXECUTE); 
ConCommand Bliink_WelcomeSpectate( "bliink_welcome_spectate", send_f, "Spectate the game, if you're at the welcome screen.", FCVAR_CLIENTCMD_CAN_EXECUTE); 
ConCommand Bliink_SpectatePregameWelcome( "bliink_spectate_pregame_welcome", send_f, "Return to the welcome menu, if you're spectating pre-game.", FCVAR_CLIENTCMD_CAN_EXECUTE); 
ConCommand Bliink_CancelReady( "bliink_cancel_ready", send_f, "Return to the welcome screen, if you're waiting for players.", FCVAR_CLIENTCMD_CAN_EXECUTE);

ConCommand Bliink_UpgradeWeaponSlots( "bliink_upgrade_slots", send_upgrade_f, "Spend an upgrade point to unlock a weapon slot in your inventory.", FCVAR_CLIENTCMD_CAN_EXECUTE);
ConCommand Bliink_UpgradeHealth( "bliink_upgrade_health", send_upgrade_f, "Spend an upgrade point to increase your maximum health.", FCVAR_CLIENTCMD_CAN_EXECUTE);
ConCommand Bliink_UpgradeFatigue( "bliink_upgrade_fatigue", send_upgrade_f, "Spend an upgrade point to increase your maximum fatigue and fatigue regeneration.", FCVAR_CLIENTCMD_CAN_EXECUTE);

ConCommand Bliink_DevAddExp( "bliink_debug_exp", send_f, "", FCVAR_CLIENTCMD_CAN_EXECUTE | FCVAR_CHEAT );
ConCommand Bliink_DevGiveSlow( "bliink_debug_slow", send_f, "", FCVAR_CLIENTCMD_CAN_EXECUTE | FCVAR_CHEAT );
ConCommand Bliink_DevGiveBurn( "bliink_debug_burn", send_f, "", FCVAR_CLIENTCMD_CAN_EXECUTE | FCVAR_CHEAT );

// INVENTORY COMMANDS
ConCommand Bliink_InventoryPrint( "bliink_inventory_print", send_f, "", FCVAR_CLIENTCMD_CAN_EXECUTE);

// Move <from> <to>
void inv_move_cmd ( const CCommand & args )
{
	CBliinkPlayer* pPlayer = ToBliinkPlayer( CBasePlayer::GetLocalPlayer() );

	if( pPlayer )
	{
		if( !send_inv_arg2( args ) )
		{
			return;
		}

		int from = atoi( args.Arg(1) ); 
		int to = atoi( args.Arg(2) );

		pPlayer->GetBliinkInventory().Command_Move(from, to);
	}
}
ConCommand Bliink_InventoryMove( "bliink_inventory_move", inv_move_cmd, "Move <from> <to>", FCVAR_CLIENTCMD_CAN_EXECUTE);

// Craft <from> <to>
void inv_craft_cmd ( const CCommand & args )
{
	CBliinkPlayer* pPlayer = ToBliinkPlayer( CBasePlayer::GetLocalPlayer() );

	if( pPlayer )
	{
		if( !send_inv_arg2( args ) )
			return;

		int from = atoi( args.Arg(1) );
		int to = atoi( args.Arg(2) );

		pPlayer->GetBliinkInventory().Command_Craft(from, to);		
	}
}
ConCommand Bliink_InventoryCraft( "bliink_inventory_craft", inv_craft_cmd, "Craft <from> <to>", FCVAR_CLIENTCMD_CAN_EXECUTE);

// Drop <from>
void inv_drop_cmd ( const CCommand & args )
{
	CBliinkPlayer* pPlayer = ToBliinkPlayer( CBasePlayer::GetLocalPlayer() );

	if( pPlayer )
	{
		if( !send_inv_arg1( args ) )
			return;

		int from = atoi( args.Arg(1) );

		pPlayer->GetBliinkInventory().Command_Drop(from);			
	}
}
ConCommand Bliink_InventoryDrop( "bliink_inventory_drop", inv_drop_cmd, "Drop <from>", FCVAR_CLIENTCMD_CAN_EXECUTE);

// Consume <from>
void inv_consume_cmd ( const CCommand & args )
{
	CBliinkPlayer* pPlayer = ToBliinkPlayer( CBasePlayer::GetLocalPlayer() );

	if( pPlayer )
	{
		if( !send_inv_arg1( args ) )
			return;

		int from = atoi( args.Arg(1) );

		pPlayer->GetBliinkInventory().Command_Consume(from);
	}
}
ConCommand Bliink_InventoryConsume( "bliink_inventory_consume", inv_consume_cmd, "Consume <from>", FCVAR_CLIENTCMD_CAN_EXECUTE);

// Delete <from>
void inv_delete_cmd ( const CCommand & args )
{
	CBliinkPlayer* pPlayer = ToBliinkPlayer( CBasePlayer::GetLocalPlayer() );

	if( pPlayer )
	{
		if( !send_inv_arg1( args ) )
			return;

		int from = atoi( args.Arg(1) );

		pPlayer->GetBliinkInventory().Command_Delete(from);
	}
}
ConCommand Bliink_InventoryDelete( "bliink_inventory_delete", inv_delete_cmd, "Delete <from>", FCVAR_CLIENTCMD_CAN_EXECUTE);

// SetNextAmmoType
void inv_ammo_cmd ( const CCommand & args )
{
	CBliinkPlayer* pPlayer = ToBliinkPlayer( CBasePlayer::GetLocalPlayer() );

	if( pPlayer )
	{
		engine->ServerCmd( args[ 0 ] );

		pPlayer->GetBliinkInventory().Command_SetNextAmmoType();
	}
}
ConCommand Bliink_InventorySetNextAmmoType( "bliink_inventory_nextammo", inv_ammo_cmd, "SetNextAmmoType", FCVAR_CLIENTCMD_CAN_EXECUTE);
#endif