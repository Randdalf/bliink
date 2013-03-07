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

// Bliink ConCommands

#ifdef CLIENT_DLL
void send_f ( const CCommand & args )
{
	engine->ServerCmd( args[ 0 ] );
}

ConCommand Bliink_WelcomePlay( "bliink_welcome_play", send_f, "Play the game, if you're at the welcome screen.", FCVAR_CLIENTCMD_CAN_EXECUTE); 
ConCommand Bliink_WelcomeSpectate( "bliink_welcome_spectate", send_f, "Spectate the game, if you're at the welcome screen.", FCVAR_CLIENTCMD_CAN_EXECUTE); 
ConCommand Bliink_SpectatePregameWelcome( "bliink_spectate_pregame_welcome", send_f, "Return to the welcome menu, if you're spectating pre-game.", FCVAR_CLIENTCMD_CAN_EXECUTE); 
ConCommand Bliink_CancelReady( "bliink_cancel_ready", send_f, "Return to the welcome screen, if you're waiting for players.", FCVAR_CLIENTCMD_CAN_EXECUTE);
#endif