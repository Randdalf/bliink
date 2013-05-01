#ifndef BLIINK_HUD_RESPAWN_TIMER
#define BLIINk_HUD_RESPAWN_TIMER

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
 
 
class CBliinkHudRespawnTimer : public CHudElement, public Panel, public IViewPortPanel
{
   DECLARE_CLASS_SIMPLE( CBliinkHudRespawnTimer, Panel );
 
   public:
	   CBliinkHudRespawnTimer( const char *pElementName );

   protected:
		virtual void Paint();
};

#endif