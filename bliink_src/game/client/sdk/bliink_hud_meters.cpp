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
 
class CHudBliinkMeters : public CHudElement, public Panel
{
   DECLARE_CLASS_SIMPLE( CHudBliinkMeters, Panel );
 
   public:
	   CHudBliinkMeters( const char *pElementName );

   protected:
	   virtual void Paint();

	   // Texture IDs
	   int m_nMeterBack;
	   int m_nMeterEnd;
	   int m_nHealthBar;	   
	   int m_nHungerBar;
	   int m_nFatigueBar;
	   int m_nHealthIcon;
	   int m_nHungerIcon;
	   int m_nFatigueIcon;
	   int m_nSegmentEnd;
};
 
DECLARE_HUDELEMENT( CHudBliinkMeters );

CHudBliinkMeters::CHudBliinkMeters( const char *pElementName ) : CHudElement( pElementName ), BaseClass( NULL, "BliinkHudMeters" )
{
	Panel *pParent = GetClientMode()->GetViewport();
	SetParent( pParent );
 
	SetVisible( true );
	SetAlpha( 255 );
	SetPaintBackgroundEnabled(false);
	SetHiddenBits( HIDEHUD_PLAYERDEAD | HIDEHUD_NEEDSUIT );

	// Creating texture IDs
	m_nMeterBack = surface()->CreateNewTextureID();
	m_nMeterEnd = surface()->CreateNewTextureID();
	m_nHealthBar = surface()->CreateNewTextureID(); 
	m_nHungerBar = surface()->CreateNewTextureID();
	m_nFatigueBar = surface()->CreateNewTextureID();
	m_nHealthIcon = surface()->CreateNewTextureID();
	m_nHungerIcon = surface()->CreateNewTextureID();
	m_nFatigueIcon = surface()->CreateNewTextureID();
	m_nSegmentEnd = surface()->CreateNewTextureID();

	// Loading textures
	surface()->DrawSetTextureFile( m_nMeterBack, "HUD/meter_back" , true, true);
	surface()->DrawSetTextureFile( m_nMeterEnd, "HUD/meter_back_end" , true, true);
	surface()->DrawSetTextureFile( m_nHealthBar, "HUD/health_meter_full" , true, true);
	surface()->DrawSetTextureFile( m_nHungerBar, "HUD/hunger_meter_full" , true, true);
	surface()->DrawSetTextureFile( m_nFatigueBar, "HUD/fatigue_meter_full" , true, true);
	surface()->DrawSetTextureFile( m_nHealthIcon, "HUD/meters_icon_health" , true, true);
	surface()->DrawSetTextureFile( m_nHungerIcon, "HUD/meters_icon_hunger" , true, true);
	surface()->DrawSetTextureFile( m_nFatigueIcon, "HUD/meters_icon_fatigue" , true, true);
	surface()->DrawSetTextureFile( m_nSegmentEnd, "HUD/meter_segment_end" , true, true);
}

void CHudBliinkMeters::Paint()
{
	C_BliinkPlayer* pBliinkPlayer = ToBliinkPlayer(C_BasePlayer::GetLocalPlayer());

	if( !pBliinkPlayer )
		return;

	if( pBliinkPlayer->State_Get() != STATE_BLIINK_SURVIVOR )
		return;

	CBliinkPlayerStats stats = pBliinkPlayer->GetBliinkPlayerStats();

	// Getting player health
	float fHealth = (float) stats.GetHealth();
	int iHealthWidth = (int) floor(256.0f * (fHealth/stats.GetMaxHealth()));

	// Getting player hunger
	float fFatigue = (float) stats.GetFatigue();
	int iFatigueWidth = (int) floor(256.0f * (fFatigue/stats.GetMaxFatigue()));

	// Getting player fatigue
	float fHunger = (float) stats.GetHunger();
	int iHungerWidth = (int) floor(256.0f * (fHunger/BASE_HUNGER));

	SetPaintBorderEnabled(false);

	// Drawing icons
	surface()->DrawSetTexture( m_nHealthIcon );
	surface()->DrawTexturedRect( 0, 0, 32, 32 );
	surface()->DrawSetTexture( m_nHungerIcon );
	surface()->DrawTexturedRect( 0, 32, 32, 64 );
	surface()->DrawSetTexture( m_nFatigueIcon );
	surface()->DrawTexturedRect( 0, 64, 32, 96 );

	// Drawing meter backgrounds
	surface()->DrawSetTexture( m_nMeterBack );
	surface()->DrawTexturedRect( 32, 0, 288, 32 );
	surface()->DrawTexturedRect( 32, 32, 288, 64 );
	surface()->DrawTexturedRect( 32, 64, 288, 96 );

	// Drawing meter ends
	surface()->DrawSetTexture( m_nMeterEnd );
	surface()->DrawTexturedRect( 288, 0, 292, 32 );
	surface()->DrawTexturedRect( 288, 32, 292, 64 );
	surface()->DrawTexturedRect( 288, 64, 292, 96 );

	// Drawing health meter
	surface()->DrawSetTexture( m_nHealthBar );
	surface()->DrawTexturedRect( 32, 0+2, 32+iHealthWidth, 32-2 );

	// Drawing hunger meter
	surface()->DrawSetTexture( m_nHungerBar );
	surface()->DrawTexturedRect( 32, 32+2, 32+iHungerWidth, 64-2 );

	// Drawing fatigue meter
	surface()->DrawSetTexture( m_nFatigueBar );
	surface()->DrawTexturedRect( 32, 64+2, 32+iFatigueWidth, 96-2 );

	// Drawing health segment markers
	int iMaxSegments = (int) floor( stats.GetMaxHealth() / HEALTH_PER_SEGMENT );

	for(int ii=1; ii<iMaxSegments; ii++)
	{
		// Scaling position
		int iSegmentBegin = (int) floor(256.0f * ((((float)ii) * HEALTH_PER_SEGMENT)/stats.GetMaxHealth()));

		// Drawing surface
		surface()->DrawSetTexture( m_nSegmentEnd );
		surface()->DrawTexturedRect( 32 + iSegmentBegin-1, 0, 32+iSegmentBegin+2, 32 );
	}
}