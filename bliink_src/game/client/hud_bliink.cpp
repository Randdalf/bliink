#include "hud.h"
#include "cbase.h"
#include "hud_bliink.h"
#include "iclientmode.h"
#include "hud_macros.h"
#include "vgui_controls/controls.h"
#include "vgui/ISurface.h"
 
#include "tier0/memdbgon.h"
 
using namespace vgui;
 
DECLARE_HUDELEMENT( CHudBliink );

CHudBliink::CHudBliink( const char *pElementName ) : CHudElement( pElementName ), BaseClass( NULL, "HudBliink" )
{
   Panel *pParent = GetClientMode()->GetViewport();
   SetParent( pParent );   
 
   SetVisible( false );
   SetAlpha( 255 );
 
   //AW Create Texture for Looking around
   m_nImport = surface()->CreateNewTextureID();
   surface()->DrawSetTextureFile( m_nImport, "HUD/import" , true, true);
 
   SetHiddenBits( HIDEHUD_PLAYERDEAD | HIDEHUD_NEEDSUIT );
}

void CHudBliink::Paint()
{
	SetPaintBorderEnabled(false);
	surface()->DrawSetColor(0,0,0,255);
	surface()->DrawFilledRect(0,0,4000,2400);
  //  surface()->DrawSetTexture( m_nImport );
 //  surface()->DrawTexturedRect( 0, 0, 1200, 1200 );
}

//static ConVar show_beta("show_beta", "0", 0, "toggles beta icon in upper right corner");
ConVar cl_showmybliink("cl_showmybliink", "0", FCVAR_CLIENTDLL, "Sets the state of myPanel <state>");

/*void CHudBliink::togglePrint()
{
   if (!show_beta.GetBool())
      this->SetVisible(false);
   else
      this->SetVisible(true);
}*/

void CHudBliink::OnThink()
{
 //  togglePrint();
 
   BaseClass::OnThink();
   this->SetVisible(cl_showmybliink.GetBool()); //CL_SHOWMYPANEL / 1 BY DEFAULT

}

void showBliinkPan ( const CCommand &args )
{
	cl_showmybliink.SetValue(true);
}
 
ConCommand my_saybliink( "BlinkGUIOn", showBliinkPan , "say something", 0);

void hideBliinkPan ( const CCommand &args )
{
	cl_showmybliink.SetValue(false);
}
 
ConCommand my_saybliink2( "BlinkGUIOff", hideBliinkPan , "say something", 0);