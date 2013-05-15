#include "cbase.h"
#include "hud.h"
#include "iclientmode.h"
#include "hud_macros.h"
#include "vgui_controls/controls.h"
#include "vgui/ISurface.h"
#include "hudelement.h"
#include <vgui_controls/Panel.h>
#include <vgui_controls/AnimationController.h>
#include "vgui_bindpanel.h"
#include "clientmode_sdk.h"
#include "c_bliink_player.h"
#include "bliink_player_stats.h"
#include "sdk_shareddefs.h"
#include "c_bliink_item_pickup.h"
#include "bliink_item_parse.h"
#include "c_bliink_player_resource.h"
#include "bliink_gamevars_shared.h"
#include "bliink_gamerules.h"
 
#include "tier0/memdbgon.h"
 
using namespace vgui;
 
 
class CBliinkHudGameState : public CHudElement, public Panel
{
   DECLARE_CLASS_SIMPLE( CBliinkHudGameState, Panel );
 
   public:
	   CBliinkHudGameState( const char *pElementName );

   protected:
		virtual void Paint();
};
 
DECLARE_HUDELEMENT( CBliinkHudGameState );

CBliinkHudGameState::CBliinkHudGameState( const char *pElementName ) : CHudElement( pElementName ), BaseClass( NULL, "BliinkHudGameState" )
{
	Panel *pParent = GetClientMode()->GetViewport();
	SetParent( pParent );
 
	SetVisible( true );
	SetAlpha( 255 );
	SetPaintBackgroundEnabled(false);
}

void CBliinkHudGameState::Paint()
{
	C_BliinkPlayer* pBliinkPlayer = ToBliinkPlayer(C_BasePlayer::GetLocalPlayer());

	if( !pBliinkPlayer )
		return;

	vgui::IScheme* pScheme = vgui::scheme()->GetIScheme(GetScheme());
	int wide, tall;
	wchar_t pTextUpper[128];
	wchar_t pTextLower[128];

	// Tell the other players who won.
	if( pBliinkPlayer->State_Get() == STATE_BLIINK_VIEW_RESULTS )
	{
		for ( int j = 1; j <= gpGlobals->maxClients; j++ )
		{	
			if ( BliinkGameResources()->IsConnected( j ) )
			{
				int state = BliinkGameResources()->GetPlayerState( j );

				if(	state == STATE_BLIINK_VIEW_RESULTS )
				{
					V_UTF8ToUnicode( BliinkGameResources()->GetPlayerName( j ), pTextLower, sizeof(wchar_t)*128 );
					break;
				}
			}
		}

		V_snwprintf( pTextUpper, ARRAYSIZE(pTextUpper), L"Congratulations to the winner!" );
	}
	// Tell the player that they won.
	else
	if( pBliinkPlayer->State_Get() == STATE_BLIINK_VIEW_RESULTS_WINNER )
	{
		V_snwprintf( pTextUpper, ARRAYSIZE(pTextUpper), L"Congratulations, you won!" );
		V_snwprintf( pTextLower, ARRAYSIZE(pTextLower), L"" );
	}
	// Printing out waiting info...
	else
	if( pBliinkPlayer->State_Get() == STATE_BLIINK_WAITING_FOR_PLAYERS ||
		pBliinkPlayer->State_Get() == STATE_BLIINK_WELCOME )
	{
		int iNumPlayersRequired = Bliink_MinPlayers.GetInt();
		int iPlayersReady = 0;

		for ( int j = 1; j <= gpGlobals->maxClients; j++ )
		{	
			if ( BliinkGameResources()->IsConnected( j ) )
			{
				int state = BliinkGameResources()->GetPlayerState( j );

				if(	state == STATE_BLIINK_WAITING_FOR_PLAYERS )
				{
					iPlayersReady++;
				}
			}
		}

		if( BliinkGameRules()->GetCountingDown() )
		{
			float fLiveTime = BliinkGameRules()->GetLiveTime();
			int iTimeLeft = (int) floor( fLiveTime - gpGlobals->curtime );

			if( pBliinkPlayer->State_Get() == STATE_BLIINK_WELCOME )
				V_snwprintf( pTextUpper, ARRAYSIZE(pTextUpper), L"%d/%d players ready... press F4 to join", iPlayersReady, iNumPlayersRequired );
			else
				V_snwprintf( pTextUpper, ARRAYSIZE(pTextUpper), L"%d/%d players ready...", iPlayersReady, iNumPlayersRequired );

			V_snwprintf( pTextLower, ARRAYSIZE(pTextLower), L"%d seconds until game starts", iTimeLeft );
		}
		else
		{
			V_snwprintf( pTextUpper, ARRAYSIZE(pTextUpper), L"%d/%d players ready...", iPlayersReady, iNumPlayersRequired );

			if( pBliinkPlayer->State_Get() == STATE_BLIINK_WELCOME )
				V_snwprintf( pTextLower, ARRAYSIZE(pTextLower), L"press F4 to join" );
			else
				V_snwprintf( pTextLower, ARRAYSIZE(pTextLower), L"" );
		}
	}
	else
	{
		return;
	}

	//
	vgui::HFont hItemFont = pScheme->GetFont( "BliinkHUDRespawnTimer" );
	
	// DRAWING UPPER
	surface()->GetTextSize(hItemFont, pTextUpper, wide, tall);
	
	int xpos = (int) floor(240.0f - ((float) wide)/2.0f);
	int ypos = 0;
	
	surface()->DrawSetTextFont( hItemFont );
	surface()->DrawSetTextColor( 255, 255, 255, 255 );
	surface()->DrawSetTextPos( xpos, ypos );
	surface()->DrawPrintText( pTextUpper, wcslen(pTextUpper) );

	// DRAWING LOWER
	hItemFont = pScheme->GetFont( "BliinkHUDRespawnTimer" );
	surface()->GetTextSize(hItemFont, pTextLower, wide, tall);
	
	xpos = (int) floor(240.0f - ((float) wide)/2.0f);
	ypos = 0;
	
	surface()->DrawSetTextFont( hItemFont );
	surface()->DrawSetTextColor( 255, 255, 255, 255 );
	surface()->DrawSetTextPos( xpos, ypos + 48 + 4 );
	surface()->DrawPrintText( pTextLower, wcslen(pTextLower) );
}