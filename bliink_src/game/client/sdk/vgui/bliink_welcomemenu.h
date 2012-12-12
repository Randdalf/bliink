#ifndef BLIINK_WELCOMEMENU_H
#define BLIINK_WELCOMEMENU_H
#ifdef _WIN32
#pragma once
#endif

#include "vgui_bitmapbutton.h"

// Menu displayed when the player enters the game, choice is between spectator
// or player.
class CBliinkWelcomeMenu : public vgui::Frame
{
	DECLARE_CLASS_SIMPLE(CBliinkWelcomeMenu, vgui::Frame); 

	CBliinkWelcomeMenu(vgui::VPANEL parent);
	~CBliinkWelcomeMenu(){};

protected:	
 	virtual void OnTick();
 	virtual void OnCommand(const char* pcCommand);
	virtual void ApplySchemeSettings( vgui::IScheme *pScheme );

private:
	// Button you press to trigger "bliink_welcome_play"
	CBitmapButton *m_pPlayButton;

	// Button you press to trigger "bliink_welcome_specate"
	CBitmapButton *m_pSpectateButton;
 
};


#endif // BLIINK_WELCOMEMENU_H