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
 
class CBliinkHudAmmo : public CHudElement, public Panel
{
   DECLARE_CLASS_SIMPLE( CBliinkHudAmmo, Panel );
 
   public:
	   CBliinkHudAmmo( const char *pElementName );

   protected:
	   virtual void Paint();

	   // Texture IDs
	   int m_nAmmoBack;
};
 
DECLARE_HUDELEMENT( CBliinkHudAmmo );

CBliinkHudAmmo::CBliinkHudAmmo( const char *pElementName ) : CHudElement( pElementName ), BaseClass( NULL, "BliinkHudAmmo" )
{
	Panel *pParent = GetClientMode()->GetViewport();
	SetParent( pParent );
 
	SetVisible( true );
	SetAlpha( 255 );
	SetPaintBackgroundEnabled(false);
	SetHiddenBits( HIDEHUD_PLAYERDEAD | HIDEHUD_NEEDSUIT );

	// Creating texture IDs
	m_nAmmoBack = surface()->CreateNewTextureID();

	// Loading textures
	surface()->DrawSetTextureFile( m_nAmmoBack, "HUD/ammo_back" , true, true);
}

void CBliinkHudAmmo::Paint()
{
	C_BliinkPlayer* pBliinkPlayer = ToBliinkPlayer(C_BasePlayer::GetLocalPlayer());

	if( !pBliinkPlayer )
		return;

	if( pBliinkPlayer->State_Get() != STATE_BLIINK_SURVIVOR )
		return;

	C_BaseCombatWeapon* pWeapon = pBliinkPlayer->GetActiveWeapon();

	if( !pWeapon )
		return;

	if( pWeapon->IsMeleeWeapon() )
		return;

	int iClipCount = pWeapon->Clip1();
	int iAmmoCount = pBliinkPlayer->GetAmmoCount( pWeapon->GetPrimaryAmmoType() );

	vgui::IScheme* pScheme = vgui::scheme()->GetIScheme(GetScheme());
	int wide, tall;

	SetPaintBorderEnabled(false);

	// Drawing background
	surface()->DrawSetTexture( m_nAmmoBack );
	surface()->DrawTexturedRect( 0, 0, 128, 64 );

	// Drawing ammo count (clip/ammo)
	wchar_t pNumberText[12];
	V_snwprintf( pNumberText, ARRAYSIZE(pNumberText), L"%d : %d", iClipCount, iAmmoCount );
	vgui::HFont hNumberFont = pScheme->GetFont( "BliinkHUDLarge" );
	
	surface()->GetTextSize(hNumberFont, pNumberText, wide, tall);
	
	int number_xpos = (int) floor(64.0f - ((float) wide)/2.0f);
	int number_ypos = (int) floor(32.0f - ((float) tall)/2.0f);
 
	surface()->DrawSetTextFont( hNumberFont );
	surface()->DrawSetTextColor( 210, 210, 210, 255 );
	surface()->DrawSetTextPos( number_xpos, number_ypos );
	surface()->DrawPrintText( pNumberText, wcslen(pNumberText) );
}