#include "cbase.h"

// VGUI headers
#include <vgui/IVgui.h>
#include <vgui_controls/Frame.h>
#include "vgui_bitmapbutton.h"

#include "bliink_welcomemenu.h"

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

using namespace vgui;

// Initialises the panel and creates the buttons
CBliinkWelcomeMenu::CBliinkWelcomeMenu(vgui::VPANEL parent) : BaseClass(NULL, "BliinkWelcomeMenu")
{
	SetParent( parent );
 
	SetKeyBoardInputEnabled( true );
	SetMouseInputEnabled( true );
 
	SetProportional( false );
	SetTitleBarVisible( true );
	SetMinimizeButtonVisible( false );
	SetMaximizeButtonVisible( false );
	SetCloseButtonVisible( false );
	SetSizeable( false );
	SetMoveable( false );
	SetVisible( true ); 
 
	SetScheme("SourceScheme");
 
	vgui::ivgui()->AddTickSignal( GetVPanel(), 100 );

	m_pSpectateButton = new CBitmapButton(this, "SpectateButton", "");
	m_pPlayButton = new CBitmapButton(this, "PlayButton", "");
}

// Empty for now, may use later
void CBliinkWelcomeMenu::OnTick()
{
	BaseClass::OnTick();
}

// Applies visual settings to the buttons
void CBliinkWelcomeMenu::ApplySchemeSettings( vgui::IScheme *pScheme )
{
	BaseClass::ApplySchemeSettings( pScheme );	
 
	LoadControlSettings("resource/UI/Bliink/WelcomeMenu.res");

	color32 black;
	black.r = 0;
	black.g = 0;
	black.b = 0;
	black.a = 255;

	m_pPlayButton->SetImage(CBitmapButton::BUTTON_ENABLED, "vgui/bliink/play_button", black);
	m_pSpectateButton->SetImage(CBitmapButton::BUTTON_ENABLED, "vgui/bliink/spectate_button", black); 
}

// Responds to the buttons being pressed
void CBliinkWelcomeMenu::OnCommand( const char* pcCommand )
{
	if ( !Q_stricmp( pcCommand, "SpectateButton" ) )
	{
		engine->ClientCmd( "bliink_welcome_spectate" );
	}
	else if( !Q_stricmp( pcCommand, "PlayButton" ) )
	{
		engine->ClientCmd( "bliink_welcome_play" );
	}

	BaseClass::OnCommand( pcCommand );
}
