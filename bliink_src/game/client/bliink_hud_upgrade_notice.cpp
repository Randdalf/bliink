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
 
class CBliinkHudUpgradeNotice : public CHudElement, public Panel
{
   DECLARE_CLASS_SIMPLE( CBliinkHudUpgradeNotice, Panel );
 
   public:
	   CBliinkHudUpgradeNotice( const char *pElementName );

   protected:
		virtual void Paint();
		virtual void UpdateKeys();
		virtual void OnThink();

		// Texture IDs
		int m_nUpgradeHealthBack;
		int m_nUpgradeFatigueBack;
		int m_nUpgradeSlotsBack;

		// Bind panels
		CBindPanel* m_pKeyUpgradeHealth;
		CBindPanel* m_pKeyUpgradeFatigue;
		CBindPanel* m_pKeyUpgradeSlots;

		// Animation vars
		CPanelAnimationVar( bool, m_bIsVisible, "IsVisible", "0" ); 
};
 
DECLARE_HUDELEMENT( CBliinkHudUpgradeNotice );

CBliinkHudUpgradeNotice::CBliinkHudUpgradeNotice( const char *pElementName ) : CHudElement( pElementName ), BaseClass( NULL, "BliinkHudUpgradeNotice" )
{
	Panel *pParent = GetClientMode()->GetViewport();
	SetParent( pParent );
 
	SetVisible( true );
	SetAlpha( 255 );
	SetPaintBackgroundEnabled(false);
	SetHiddenBits( HIDEHUD_PLAYERDEAD | HIDEHUD_NEEDSUIT );

	// Creating buttons
	m_pKeyUpgradeHealth = new CBindPanel(this, "KeyUpgradeHealth");
	m_pKeyUpgradeFatigue = new CBindPanel(this, "KeyUpgradeFatigue");
	m_pKeyUpgradeSlots = new CBindPanel(this, "KeyUpgradeSlots");

	// Creating texture IDs
	m_nUpgradeHealthBack = surface()->CreateNewTextureID();
	m_nUpgradeFatigueBack = surface()->CreateNewTextureID();
	m_nUpgradeSlotsBack = surface()->CreateNewTextureID();

	// Loading textures
	surface()->DrawSetTextureFile( m_nUpgradeHealthBack, "HUD/upgrade_health_back" , true, true);
	surface()->DrawSetTextureFile( m_nUpgradeFatigueBack, "HUD/upgrade_fatigue_back" , true, true);
	surface()->DrawSetTextureFile( m_nUpgradeSlotsBack, "HUD/upgrade_slots_back" , true, true);
}

void CBliinkHudUpgradeNotice::UpdateKeys()
{
	m_pKeyUpgradeHealth->SetBounds(48, 96, 32, 32);
	m_pKeyUpgradeFatigue->SetBounds(48+128+4, 96, 32, 32);
	m_pKeyUpgradeSlots->SetBounds(48+256+8, 96, 32, 32);

	if( !m_bIsVisible )
	{
		m_pKeyUpgradeHealth->SetVisible(false);
		m_pKeyUpgradeFatigue->SetVisible(false);
		m_pKeyUpgradeSlots->SetVisible(false);
	}
	else
	{
		m_pKeyUpgradeHealth->SetVisible(true);
		m_pKeyUpgradeFatigue->SetVisible(true);
		m_pKeyUpgradeSlots->SetVisible(true);
	}
}

void CBliinkHudUpgradeNotice::OnThink()
{
	m_pKeyUpgradeHealth->SetBind("bliink_upgrade_health");
	m_pKeyUpgradeFatigue->SetBind("bliink_upgrade_fatigue");
	m_pKeyUpgradeSlots->SetBind("bliink_upgrade_slots");	
	
	C_BliinkPlayer* pBliinkPlayer = ToBliinkPlayer(C_BasePlayer::GetLocalPlayer());

	if( !pBliinkPlayer )
		return;

	if( pBliinkPlayer->GetBliinkPlayerStats().GetUpgradePoints() <= 0 && m_bIsVisible )
	{
		GetClientMode()->GetViewportAnimationController()->StartAnimationSequence("BliinkCloseUpgradeNotice");
	}
	else if( pBliinkPlayer->GetBliinkPlayerStats().GetUpgradePoints() > 0 && !m_bIsVisible )
	{
		GetClientMode()->GetViewportAnimationController()->StartAnimationSequence("BliinkOpenUpgradeNotice");
	}

	UpdateKeys();
}

void CBliinkHudUpgradeNotice::Paint()
{
	if( !m_bIsVisible )
		return;

	C_BliinkPlayer* pBliinkPlayer = ToBliinkPlayer(C_BasePlayer::GetLocalPlayer());

	if( !pBliinkPlayer )
		return;

	if( pBliinkPlayer->State_Get() != STATE_BLIINK_SURVIVOR )
		return;

	CBliinkPlayerStats stats = pBliinkPlayer->GetBliinkPlayerStats();

	if( stats.GetUpgradePoints() <= 0 )
		return;

	vgui::IScheme* pScheme = vgui::scheme()->GetIScheme(GetScheme());
	int wide, tall;

	// Painting backs
	surface()->DrawSetTexture( m_nUpgradeHealthBack );
	surface()->DrawTexturedRect( 0, 32, 128, 96 );
	surface()->DrawSetTexture( m_nUpgradeFatigueBack );
	surface()->DrawTexturedRect( 0+128+4, 32, 128+128+4, 96 );
	surface()->DrawSetTexture( m_nUpgradeSlotsBack );
	surface()->DrawTexturedRect( 0+256+8, 32, 128+256+8, 96 );

	// Drawing upgrade notice
	wchar_t pNumberText[32];
	V_snwprintf( pNumberText, ARRAYSIZE(pNumberText), L"UPGRADE POINTS AVAILABLE: %d", stats.GetUpgradePoints() );
	vgui::HFont hNumberFont = pScheme->GetFont( "BliinkHUDUpgradeNotice" );
	
	surface()->GetTextSize(hNumberFont, pNumberText, wide, tall);
	
	int number_xpos = (int) floor(196.0f - ((float) wide)/2.0f);
	int number_ypos = 0;
 
	surface()->DrawSetTextFont( hNumberFont );
	surface()->DrawSetTextColor( 255, 255, 255, 255 );
	surface()->DrawSetTextPos( number_xpos, number_ypos );
	surface()->DrawPrintText( pNumberText, wcslen(pNumberText) );
}