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
 
#include "tier0/memdbgon.h"
 
using namespace vgui;
 
 
class CBliinkHudItemName : public CHudElement, public Panel
{
   DECLARE_CLASS_SIMPLE( CBliinkHudItemName, Panel );
 
   public:
	   CBliinkHudItemName( const char *pElementName );

   protected:
		virtual void Paint();
};
 
DECLARE_HUDELEMENT( CBliinkHudItemName );

CBliinkHudItemName::CBliinkHudItemName( const char *pElementName ) : CHudElement( pElementName ), BaseClass( NULL, "BliinkHudItemName" )
{
	Panel *pParent = GetClientMode()->GetViewport();
	SetParent( pParent );
 
	SetVisible( true );
	SetAlpha( 255 );
	SetPaintBackgroundEnabled(false);
}

void CBliinkHudItemName::Paint()
{
	C_BliinkPlayer* pBliinkPlayer = ToBliinkPlayer(C_BasePlayer::GetLocalPlayer());

	if( !pBliinkPlayer )
		return;

	if( pBliinkPlayer->State_Get() != STATE_BLIINK_SURVIVOR )
		return;

	vgui::IScheme* pScheme = vgui::scheme()->GetIScheme(GetScheme());
	int wide, tall;
	
	// Finding entity we're using.
	C_BaseEntity* pEntity = pBliinkPlayer->FindUseEntity();

	if( !pEntity )
		return;

	C_BliinkItemPickup* pPickup = static_cast< C_BliinkItemPickup* >( pEntity );

	if( !pPickup )
		return;

	CBliinkItemInfo* info = GetItemInfo( pPickup->GetHandle() );

	// Drawing upgrade notice
	wchar_t pItemText[128];
	V_UTF8ToUnicode( info->szItemDesc, pItemText, sizeof(wchar_t)*128 );
	//V_snwprintf( pItemText, ARRAYSIZE(pItemText), L"%s", info->szItemName );
	vgui::HFont hItemFont = pScheme->GetFont( "BliinkHUDRespawnTimer" );
	
	surface()->GetTextSize(hItemFont, pItemText, wide, tall);
	
	int number_xpos = (int) floor(196.0f - ((float) wide)/2.0f);
	int number_ypos = 0;
 
	surface()->DrawSetTextFont( hItemFont );
	surface()->DrawSetTextColor( 255, 255, 255, 255 );
	surface()->DrawSetTextPos( number_xpos, number_ypos );
	surface()->DrawPrintText( pItemText, wcslen(pItemText) );
}