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
#include "bliink_gamevars_shared.h"
 
#include "tier0/memdbgon.h"
 
using namespace vgui;
 
class CBliinkHudInstructions : public CHudElement, public Panel
{
   DECLARE_CLASS_SIMPLE( CBliinkHudInstructions, Panel );
 
   public:
	   CBliinkHudInstructions( const char *pElementName );

   protected:
	   virtual void Paint();

	   // Texture IDs
	   int m_nInstructionsPC;
	   int m_nInstructionsXbox;
};
 
DECLARE_HUDELEMENT( CBliinkHudInstructions );

CBliinkHudInstructions::CBliinkHudInstructions( const char *pElementName ) : CHudElement( pElementName ), BaseClass( NULL, "BliinkHudInstructions" )
{
	Panel *pParent = GetClientMode()->GetViewport();
	SetParent( pParent );
 
	SetVisible( true );
	SetAlpha( 255 );
	SetPaintBackgroundEnabled(false);
	SetHiddenBits( HIDEHUD_PLAYERDEAD | HIDEHUD_NEEDSUIT );

	// Creating texture IDs
	m_nInstructionsPC = surface()->CreateNewTextureID();
	m_nInstructionsXbox = surface()->CreateNewTextureID();

	// Loading textures
	surface()->DrawSetTextureFile( m_nInstructionsPC, "HUD/pc_instructions" , true, true);
	surface()->DrawSetTextureFile( m_nInstructionsXbox, "HUD/xbox_instructions" , true, true);
}

void CBliinkHudInstructions::Paint()
{
	C_BliinkPlayer* pBliinkPlayer = ToBliinkPlayer(C_BasePlayer::GetLocalPlayer());

	if( !pBliinkPlayer )
		return;

	if( pBliinkPlayer->State_Get() != STATE_BLIINK_WELCOME &&
		pBliinkPlayer->State_Get() != STATE_BLIINK_WAITING_FOR_PLAYERS )
		return;

	SetPaintBorderEnabled(false);

	// Counting players
	if( Bliink_UseXboxInstructions.GetBool() )
	{
		surface()->DrawSetTexture( m_nInstructionsXbox );
		surface()->DrawTexturedRect( 0, 0, 512, 512 );
	}
	else
	{
		surface()->DrawSetTexture( m_nInstructionsPC );
		surface()->DrawTexturedRect( 0, 0, 512, 512 );
	}
}