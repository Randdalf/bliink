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
 
#include "tier0/memdbgon.h"
 
using namespace vgui;
 
class CBliinkHudRespawnTimer : public CHudElement, public Panel
{
   DECLARE_CLASS_SIMPLE( CBliinkHudRespawnTimer, Panel );
 
   public:
	   CBliinkHudRespawnTimer( const char *pElementName );

   protected:
		virtual void Paint();
};
 
DECLARE_HUDELEMENT( CBliinkHudRespawnTimer );

CBliinkHudRespawnTimer::CBliinkHudRespawnTimer( const char *pElementName ) : CHudElement( pElementName ), BaseClass( NULL, "BliinkHudRespawnTimer" )
{
	Panel *pParent = GetClientMode()->GetViewport();
	SetParent( pParent );
 
	SetVisible( true );
	SetAlpha( 255 );
	SetPaintBackgroundEnabled(false);
	SetHiddenBits( HIDEHUD_PLAYERDEAD | HIDEHUD_NEEDSUIT );
}

void CBliinkHudRespawnTimer::Paint()
{
	C_BliinkPlayer* pBliinkPlayer = ToBliinkPlayer(C_BasePlayer::GetLocalPlayer());

	if( !pBliinkPlayer )
		return;

	if( pBliinkPlayer->State_Get() != STATE_BLIINK_STALKER_RESPAWN )
		return;

	int timeLeft = (int) floor(pBliinkPlayer->GetDeathTime( ) + BLIINK_STALKER_RESPAWN_TIME - gpGlobals->curtime);

	vgui::IScheme* pScheme = vgui::scheme()->GetIScheme(GetScheme());
	int wide, tall;

	// Drawing upgrade notice
	wchar_t pNumberText[32];
	V_snwprintf( pNumberText, ARRAYSIZE(pNumberText), L"RESPAWNING IN %d SECONDS", timeLeft );
	vgui::HFont hNumberFont = pScheme->GetFont( "BliinkHUDUpgradeNotice" );
	
	surface()->GetTextSize(hNumberFont, pNumberText, wide, tall);
	
	int number_xpos = (int) floor(196.0f - ((float) wide)/2.0f);
	int number_ypos = 0;
 
	surface()->DrawSetTextFont( hNumberFont );
	surface()->DrawSetTextColor( 255, 255, 255, 255 );
	surface()->DrawSetTextPos( number_xpos, number_ypos );
	surface()->DrawPrintText( pNumberText, wcslen(pNumberText) );
}