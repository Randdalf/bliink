#include "cbase.h"
#include "hud.h"
#include "iclientmode.h"
#include "hud_macros.h"
#include "vgui_controls/controls.h"
#include "vgui/ISurface.h"
#include "hudelement.h"
#include <vgui_controls/Panel.h>
#include "clientmode_sdk.h"
#include "c_bliink_player.h"
#include "bliink_player_stats.h"
#include "c_bliink_player_resource.h"
#include "sdk_shareddefs.h"
 
#include "tier0/memdbgon.h"
 
using namespace vgui;
 
class CBliinkHudPlayerStates : public CHudElement, public Panel
{
   DECLARE_CLASS_SIMPLE( CBliinkHudPlayerStates, Panel );
 
   public:
	   CBliinkHudPlayerStates( const char *pElementName );

   protected:
	   virtual void Paint();

	   // Texture IDs
	   int m_nSymbolAlive;
	   int m_nSymbolDead;
};
 
DECLARE_HUDELEMENT( CBliinkHudPlayerStates );

CBliinkHudPlayerStates::CBliinkHudPlayerStates( const char *pElementName ) : CHudElement( pElementName ), BaseClass( NULL, "BliinkHudPlayerStates" )
{
	Panel *pParent = GetClientMode()->GetViewport();
	SetParent( pParent );
 
	SetVisible( true );
	SetAlpha( 255 );
	SetPaintBackgroundEnabled(false);
	SetHiddenBits( HIDEHUD_PLAYERDEAD | HIDEHUD_NEEDSUIT );

	// Creating texture IDs
	m_nSymbolAlive = surface()->CreateNewTextureID();
	m_nSymbolDead = surface()->CreateNewTextureID();

	// Loading textures
	surface()->DrawSetTextureFile( m_nSymbolAlive, "HUD/player_symbol_alive" , true, true);
	surface()->DrawSetTextureFile( m_nSymbolDead, "HUD/player_symbol_dead" , true, true);
}

void CBliinkHudPlayerStates::Paint()
{
	C_BliinkPlayer* pBliinkPlayer = ToBliinkPlayer(C_BasePlayer::GetLocalPlayer());

	if( !pBliinkPlayer )
		return;

	if( pBliinkPlayer->State_Get() != STATE_BLIINK_SURVIVOR && 
		pBliinkPlayer->State_Get() != STATE_BLIINK_STALKER )
		return;

	SetPaintBorderEnabled(false);

	// Counting players
	int iNumPlayersInGame = 0;
	int iNumSurvivors = 0;

	for ( int j = 1; j <= gpGlobals->maxClients; j++ )
	{	
		if ( BliinkGameResources()->IsConnected( j ) )
		{
			int state = BliinkGameResources()->GetPlayerState( j );

			if(
				state == STATE_BLIINK_SPECTATE_PREGAME ||
				state == STATE_BLIINK_WAITING_FOR_PLAYERS ||
				state == STATE_BLIINK_WELCOME
			  )
				continue;
			
			iNumPlayersInGame++;

			if( state == STATE_BLIINK_SURVIVOR )
				iNumSurvivors++;
		}
	}

	int iNumStalkers = iNumPlayersInGame - iNumSurvivors;

	int x=224;

	// Drawing survivor symbols.
	for(int i=0; i<iNumSurvivors; i++)
	{
		surface()->DrawSetTexture( m_nSymbolAlive );
		surface()->DrawTexturedRect( x, 0, x+32, 64 );

		x -= 32;
	}

	// Drawing stalker symbols.
	for(int i=0; i<iNumStalkers; i++)
	{
		surface()->DrawSetTexture( m_nSymbolDead );
		surface()->DrawTexturedRect( x, 0, x+32, 64 );

		x -= 32;
	}
}