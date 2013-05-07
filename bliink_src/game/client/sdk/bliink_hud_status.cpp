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
 
class CBliinkHudStatus : public CHudElement, public Panel
{
   DECLARE_CLASS_SIMPLE( CBliinkHudStatus, Panel );
 
   public:
	   CBliinkHudStatus( const char *pElementName );

   protected:
	   virtual void Paint();

	   // Texture IDs
	   int m_nStatusBurn;
	   int m_nStatusFogged;
	   int m_nStatusPoison;	   
	   int m_nStatusSlow;
};
 
DECLARE_HUDELEMENT( CBliinkHudStatus );

CBliinkHudStatus::CBliinkHudStatus( const char *pElementName ) : CHudElement( pElementName ), BaseClass( NULL, "BliinkHudStatus" )
{
	Panel *pParent = GetClientMode()->GetViewport();
	SetParent( pParent );
 
	SetVisible( true );
	SetAlpha( 255 );
	SetPaintBackgroundEnabled(false);
	SetHiddenBits( HIDEHUD_PLAYERDEAD | HIDEHUD_NEEDSUIT );

	// Creating texture IDs
	m_nStatusBurn = surface()->CreateNewTextureID();
	m_nStatusFogged = surface()->CreateNewTextureID();
	m_nStatusPoison = surface()->CreateNewTextureID(); 
	m_nStatusSlow = surface()->CreateNewTextureID();

	// Loading textures
	surface()->DrawSetTextureFile( m_nStatusBurn, "HUD/status_fire" , true, true);
	surface()->DrawSetTextureFile( m_nStatusFogged, "HUD/status_fogged" , true, true);
	surface()->DrawSetTextureFile( m_nStatusPoison, "HUD/status_poison" , true, true);
	surface()->DrawSetTextureFile( m_nStatusSlow, "HUD/status_slow" , true, true);
}

void CBliinkHudStatus::Paint()
{
	C_BliinkPlayer* pBliinkPlayer = ToBliinkPlayer(C_BasePlayer::GetLocalPlayer());

	if( !pBliinkPlayer )
		return;
	
	CBliinkPlayerStats stats = pBliinkPlayer->GetBliinkPlayerStats();

	if( pBliinkPlayer->State_Get() == STATE_BLIINK_SURVIVOR )
	{
		SetPaintBorderEnabled(false);

		int texture = 0;

		switch( stats.GetStatus() )
		{
		case BLIINK_STATUS_NORMAL:
			return;
		case BLIINK_STATUS_POISONED:
			texture = m_nStatusPoison; break;
		case BLIINK_STATUS_BURNING:
			texture = m_nStatusBurn; break;
		case BLIINK_STATUS_FOGGED:
			texture = m_nStatusFogged; break;
		case BLIINK_STATUS_SLOWED:
			texture = m_nStatusSlow; break;
		}

		// Drawing icons
		surface()->DrawSetTexture( texture );
		surface()->DrawTexturedRect( 0, 0, 64, 64 );
	}
}