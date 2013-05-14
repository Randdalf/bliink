#include "cbase.h"
#include "bliink_inventory_slot.h"
#include <vgui_controls/Label.h>
#include <vgui_controls/ImagePanel.h>
#include <vgui/ISystem.h>
#include <KeyValues.h>
#include <vgui/MouseCode.h>

#include <tier0/memdbgon.h>

using namespace vgui;

bliink_inventory_slot::bliink_inventory_slot(
	vgui::Panel *parent, 
	const char *panelName, 
	const char *labelTtext,
	const char *imgPanelName,
	const char *imgLabelpName,
	const char *imgLabelaName) :

	EditablePanel(parent, panelName)

{

	m_pImage = new vgui::ImagePanel(this, imgPanelName);
	m_aLabel = new vgui::Label(this, imgLabelaName, "0");	
	m_pLabel = new vgui::Label(this, imgLabelpName, labelTtext);
	
	ButtonInit();

}

void bliink_inventory_slot::ButtonInit()
{
	m_bButtonEnabled = true;
	SetEnabled(true);
	SetMouseInputEnabled(true);
	m_pImage->SetMouseInputEnabled(false);
	m_pLabel->SetMouseInputEnabled(false);
	m_aLabel->SetMouseInputEnabled(false);
	//m_pLabel->SetContentAlignment(vgui::Label::a_south);
	//m_aLabel->SetContentAlignment(vgui::Label::a_north);
	//m_aLabel->SetVisible(false);
	int w = 50  /* GetWide()*/;
	int t = 50  /*GetTall()*/;
	int x,y ;
	this->GetPos(x,y);

	m_pImage->SetSize(w,t);
	m_pImage->SetPos(x,y);

	m_pLabel->SetSize(70,20);

	m_aLabel->SetSize(15,15);


	m_aLabel->SetPos(x+7,y+5);
	m_pLabel->SetPos(x+1,y+30);
	vgui::IScheme *pScheme = vgui::scheme()->GetIScheme( GetScheme() );
	vgui::HFont font = pScheme ->GetFont("DefaultVerySmall",true) ;
	SetFont(font);

}

bliink_inventory_slot::~bliink_inventory_slot(){}

void bliink_inventory_slot::SetImage(const char *szFilename)
{
	if (( !IsCursorOver() || !m_bButtonEnabled) && m_pImage)
	{
		m_pImage->SetImage(szFilename);
		m_pImage->SetShouldScaleImage(true);
	}
}

void bliink_inventory_slot::OnThink()
{	
	BaseClass::OnThink();
}

void bliink_inventory_slot::SetFont(vgui::HFont font)
{
	m_Font = font;
	m_pLabel->SetFont(m_Font);
	m_aLabel->SetFont(m_Font);

}

void bliink_inventory_slot::ApplySchemeSettings(vgui::IScheme *pScheme)
{
	BaseClass::ApplySchemeSettings(pScheme);
	if (m_Font == vgui::INVALID_FONT)
	{
		m_Font = pScheme->GetFont( "Default", IsProportional() );
	}	
	m_pImage->SetShouldScaleImage(true);
	m_pLabel->SetFont(m_Font);
	m_aLabel->SetFont(m_Font);
}

void bliink_inventory_slot::OnMousePressed(vgui::MouseCode code)
{
	if (code == MOUSE_RIGHT)
	{
		if ( id == 0 )
			engine->ServerCmd(  "bliink_inventory_drop 0" );
		if ( id == 1 )
			engine->ServerCmd(  "bliink_inventory_drop 1" );
		if ( id == 2 )
			engine->ServerCmd(  "bliink_inventory_drop 2" );
		if ( id == 3 )
			engine->ServerCmd(  "bliink_inventory_drop 3" );
		if ( id == 4 )
			engine->ServerCmd(  "bliink_inventory_drop 4" );
		if ( id == 5 )
			engine->ServerCmd(  "bliink_inventory_drop 5" );
		if ( id == 6 )
			engine->ServerCmd(  "bliink_inventory_drop 6" );
		if ( id == 7 )
			engine->ServerCmd(  "bliink_inventory_drop 7" );
		if ( id == 8 )
			engine->ServerCmd(  "bliink_inventory_drop 8" );
		if ( id == 9 )
			engine->ServerCmd(  "bliink_inventory_drop 9" );
		if ( id == 10 )
			engine->ServerCmd(  "bliink_inventory_drop 10" );
		if ( id == 11 )
			engine->ServerCmd(  "bliink_inventory_drop 11" );
		if ( id == 12 )
			engine->ServerCmd(  "bliink_inventory_drop 12" );
		if ( id == 13 )
			engine->ServerCmd(  "bliink_inventory_drop 13" );
		if ( id == 14 )
			engine->ServerCmd(  "bliink_inventory_drop 14" );
		if ( id == 15 )
			engine->ServerCmd(  "bliink_inventory_drop 15" );
		if ( id == 16 )
			engine->ServerCmd(  "bliink_inventory_drop 16" );
		if ( id == 17 )
			engine->ServerCmd(  "bliink_inventory_drop 17" );
		if ( id == 18 )
			engine->ServerCmd(  "bliink_inventory_drop 18" );
		if ( id == 19 )
			engine->ServerCmd(  "bliink_inventory_drop 19" );
	}
}

void bliink_inventory_slot::OnMouseDoublePressed(vgui::MouseCode code)
{
	if (code == MOUSE_LEFT)
	{
		if ( id == 5 )
			engine->ServerCmd(  "bliink_inventory_consume 5" );
		if ( id == 6 )
			engine->ServerCmd(  "bliink_inventory_consume 6" );
		if ( id == 7 )
			engine->ServerCmd(  "bliink_inventory_consume 7" );
		if ( id == 8 )
			engine->ServerCmd(  "bliink_inventory_consume 8" );
		if ( id == 9 )
			engine->ServerCmd(  "bliink_inventory_consume 9" );
		if ( id == 10 )
			engine->ServerCmd(  "bliink_inventory_consume 10" );
		if ( id == 11 )
			engine->ServerCmd(  "bliink_inventory_consume 11" );
		if ( id == 12 )
			engine->ServerCmd(  "bliink_inventory_consume 12" );
		if ( id == 13 )
			engine->ServerCmd(  "bliink_inventory_consume 13" );
		if ( id == 14 )
			engine->ServerCmd(  "bliink_inventory_consume 14" );
		if ( id == 15 )
			engine->ServerCmd(  "bliink_inventory_consume 15" );
		if ( id == 16 )
			engine->ServerCmd(  "bliink_inventory_consume 16" );
		if ( id == 17 )
			engine->ServerCmd(  "bliink_inventory_consume 17" );
		if ( id == 18 )
			engine->ServerCmd(  "bliink_inventory_consume 18" );
		if ( id == 19 )
			engine->ServerCmd(  "bliink_inventory_consume 19" );
	}
}

void bliink_inventory_slot::SetButtonEnabled(bool bEnabled)
{
	if (bEnabled != m_bButtonEnabled)
	{
		m_bButtonEnabled = bEnabled;
	}
}

void bliink_inventory_slot::SetText(const char *text)
{
	if (m_pLabel)
		m_pLabel->SetText(text);
}

void bliink_inventory_slot::SetAmount(const char *text)
{
	if (m_aLabel)
		m_aLabel->SetText(text);
}
