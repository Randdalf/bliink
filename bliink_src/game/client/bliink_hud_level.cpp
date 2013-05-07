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
 
#include "tier0/memdbgon.h"
 
using namespace vgui;
 
class CBliinkHudLevel : public CHudElement, public Panel
{
   DECLARE_CLASS_SIMPLE( CBliinkHudLevel, Panel );
 
   public:
	   CBliinkHudLevel( const char *pElementName );

   protected:
	   virtual void Paint();

	   // Texture IDs
	   int m_nLevelBack;
	   int m_nExpBack;
	   int m_nExpBar;
};
 
DECLARE_HUDELEMENT( CBliinkHudLevel );

CBliinkHudLevel::CBliinkHudLevel( const char *pElementName ) : CHudElement( pElementName ), BaseClass( NULL, "BliinkHudLevel" )
{
	Panel *pParent = GetClientMode()->GetViewport();
	SetParent( pParent );
 
	SetVisible( true );
	SetAlpha( 255 );
	SetPaintBackgroundEnabled(false);
	SetHiddenBits( HIDEHUD_PLAYERDEAD | HIDEHUD_NEEDSUIT );

	// Creating texture IDs
	m_nLevelBack = surface()->CreateNewTextureID();
	m_nExpBack = surface()->CreateNewTextureID();
	m_nExpBar = surface()->CreateNewTextureID();

	// Loading textures
	surface()->DrawSetTextureFile( m_nLevelBack, "HUD/level_back" , true, true);
	surface()->DrawSetTextureFile( m_nExpBack, "HUD/exp_bar_back" , true, true);
	surface()->DrawSetTextureFile( m_nExpBar, "HUD/exp_bar_full" , true, true);
}

void CBliinkHudLevel::Paint()
{
	C_BliinkPlayer* pBliinkPlayer = ToBliinkPlayer(C_BasePlayer::GetLocalPlayer());

	if( !pBliinkPlayer )
		return;

	if( pBliinkPlayer->State_Get() != STATE_BLIINK_SURVIVOR )
		return;

	CBliinkPlayerStats stats = pBliinkPlayer->GetBliinkPlayerStats();
	vgui::IScheme* pScheme = vgui::scheme()->GetIScheme(GetScheme());
	int wide, tall;

	// Getting player exp data for progress bar
	float fExp = (float) stats.GetExperience();
	float fMaxExp = (float) stats.GetMaxExperience();
	int iExpWidth = (int) floor(124.0f * (fExp/fMaxExp));

	SetPaintBorderEnabled(false);

	// Drawing background
	surface()->DrawSetTexture( m_nLevelBack );
	surface()->DrawTexturedRect( 0, 0, 128, 64 );
	surface()->DrawSetTexture( m_nExpBack );
	surface()->DrawTexturedRect( 0, 64, 128, 96 );

	// Drawing exp bar
	surface()->DrawSetTexture( m_nExpBar );
	surface()->DrawTexturedRect( 2, 64, 2+iExpWidth, 96 );

	// Drawing level number
	wchar_t pNumberText[10];
	V_snwprintf( pNumberText, ARRAYSIZE(pNumberText), L"LEVEL %d", stats.GetLevel() );
	vgui::HFont hNumberFont = pScheme->GetFont( "BliinkHUDLarge" );
	
	surface()->GetTextSize(hNumberFont, pNumberText, wide, tall);
	
	int number_xpos = (int) floor(64.0f - ((float) wide)/2.0f);
	int number_ypos = (int) floor(32.0f - ((float) tall)/2.0f);
 
	surface()->DrawSetTextFont( hNumberFont );
	surface()->DrawSetTextColor( 210, 210, 210, 255 );
	surface()->DrawSetTextPos( number_xpos, number_ypos );
	surface()->DrawPrintText( pNumberText, wcslen(pNumberText) );

	// Drawing EXP progress
	wchar_t pExpProgress[9];
	V_snwprintf( pExpProgress, ARRAYSIZE(pExpProgress), L"%d\\%d", stats.GetExperience(), stats.GetMaxExperience() );
	vgui::HFont hProgressFont = pScheme->GetFont( "BliinkHUDExp" );
	
	surface()->GetTextSize(hProgressFont, pExpProgress, wide, tall);
	
	int progress_xpos = (int) floor(64.0f - ((float) wide)/2.0f);
	int progress_ypos = 64 + (int) floor(16.0f - ((float) tall)/2.0f);
 
	surface()->DrawSetTextFont( hProgressFont );
	surface()->DrawSetTextColor( 255, 255, 255, 255 );
	surface()->DrawSetTextPos( progress_xpos, progress_ypos );
	surface()->DrawPrintText( pExpProgress, wcslen(pExpProgress) );
}