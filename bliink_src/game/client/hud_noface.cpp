#include "hud.h"
#include "cbase.h"
#include "hud_noface.h"
#include "iclientmode.h"
#include "hud_macros.h"
#include "vgui_controls/controls.h"
#include "vgui/ISurface.h"
 
#include "tier0/memdbgon.h"
 
using namespace vgui;
 
DECLARE_HUDELEMENT( CHudNoFace );

CHudNoFace::CHudNoFace( const char *pElementName ) : CHudElement( pElementName ), BaseClass( NULL, "HudNoFace" )
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

void CHudNoFace::Paint()
{
	SetPaintBorderEnabled(false);
//	surface()->DrawSetColor(60,70,65,255);
//	surface()->DrawFilledRect(0,0,100,100);

	vgui::IScheme* pScheme = vgui::scheme()->GetIScheme(GetScheme());
		int wide, tall;
	wchar_t pNumberText[52];
	V_snwprintf( pNumberText, ARRAYSIZE(pNumberText), L"No Face could be found." );
	vgui::HFont hNumberFont = pScheme->GetFont( "BliinkHUDUpgradeNotice" );
	
	surface()->GetTextSize(hNumberFont, pNumberText, wide, tall);
 
	surface()->DrawSetTextFont( hNumberFont );
	surface()->DrawSetTextColor( 255, 255, 255, 255 );
	surface()->DrawSetTextPos( 10,10);
	surface()->DrawPrintText( pNumberText, wcslen(pNumberText) );


  //  surface()->DrawSetTexture( m_nImport );
 //  surface()->DrawTexturedRect( 0, 0, 1200, 1200 );
}

//static ConVar show_beta("show_beta", "0", 0, "toggles beta icon in upper right corner");
ConVar cl_shownoface("cl_shownoface", "0", FCVAR_CLIENTDLL, "Sets the state of myPanel <state>");

/*void CHudBliink::togglePrint()
{
   if (!show_beta.GetBool())
      this->SetVisible(false);
   else
      this->SetVisible(true);
}*/

void CHudNoFace::OnThink()
{
 //  togglePrint();
 
   BaseClass::OnThink();
   this->SetVisible(cl_shownoface.GetBool()); //CL_SHOWMYPANEL / 1 BY DEFAULT

}

void showNoFacePanGUI ( const CCommand &args )
{
	cl_shownoface.SetValue(true);
}
 
ConCommand my_saynoface( "NoFaceGUIOn", showNoFacePanGUI , "say something", 0);

void hideNoFacePanGUI ( const CCommand &args )
{
	cl_shownoface.SetValue(false);
}
 
ConCommand my_saynoface2( "NoFaceGUIOff", hideNoFacePanGUI , "say something", 0);

