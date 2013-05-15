#include "cbase.h"
#include "bliink_inventory_slot.h"
#include <vgui_controls/Label.h>
#include <vgui_controls/ImagePanel.h>
#include <vgui/ISystem.h>
#include <KeyValues.h>
#include <vgui/MouseCode.h>
#include <vgui/IInput.h>
#include "Ibliink_inventory_ui.h"

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
	p = parent;
	m_pImage = new vgui::ImagePanel( this, imgPanelName );
	m_ePanel = new vgui::EditablePanel( this, imgLabelpName );
	m_aLabel = new vgui::Label(this, imgLabelaName, "0" );	
	m_pLabel = new vgui::Label(this, imgLabelpName, labelTtext );
	
	ButtonInit();

}

void bliink_inventory_slot::ButtonInit()
{
	vgui::IScheme *pScheme = vgui::scheme()->GetIScheme( GetScheme() );
	vgui::HFont font = pScheme ->GetFont("DefaultVerySmall",true) ;

	SetFont(font);

	m_bButtonEnabled = true;
	SetEnabled(true);
	SetMouseInputEnabled(true);

	m_pImage->SetMouseInputEnabled(false);
	m_pLabel->SetMouseInputEnabled(false);
	m_aLabel->SetMouseInputEnabled(false);

	int x,y ;
	this->GetPos(x,y);
	
	int w = 50  /* GetWide()*/;
	int t = 50  /*GetTall()*/;

	m_pImage->SetSize(w,t);
	m_pImage->SetPos(x,y);

	m_pLabel->SetSize(100,20);
	m_aLabel->SetSize(100,20);

	m_aLabel->SetPos(x,y);
	m_pLabel->SetPos(x,y);

	m_aLabel->SetVisible( false );
	m_pLabel->SetVisible( false );

	// epanel
	m_pImage->GetPos(x,y);
	m_ePanel->SetMouseInputEnabled( false );
	//m_ePanel->SetPos( x + 50, y );
	m_ePanel->SetSize( 100, 41 );
	m_ePanel->SetVisible( false );

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

	if ( IsCursorOver () /*&& amount != 0*/ ) 
	{
		int x,y;
		this->GetPos(x,y);
		m_pLabel->SetParent( p );
		m_aLabel->SetParent( p );
		m_aLabel->MoveToFront();
		m_pLabel->MoveToFront();

		int d = 3;
	
		m_aLabel->SetPos( x+d, y+70+d );
		m_pLabel->SetPos( x+d, y+50+d );

		if ( !Q_stricmp(name ,"empty_item") || !Q_stricmp(name ,"locked_item")) 
			m_aLabel->SetVisible( false );
		else
			m_aLabel->SetVisible( true );

		m_pLabel->SetVisible( true );
		
		vgui::HScheme pScheme = vgui::scheme()->LoadSchemeFromFile("resource/SourceScheme.res", "SourceScheme");
		vgui::IScheme *iScheme = vgui::scheme()->GetIScheme( pScheme );
		
		ApplySchemeSettings( iScheme );

	}
	else
	{
		m_ePanel->SetParent( this );
		m_ePanel->SetVisible( false );
		m_aLabel->SetVisible( false );
		m_pLabel->SetVisible( false );
	}
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
		m_Font = pScheme->GetFont( "DefaultVerySmall", IsProportional() );
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

	/*
	if (code == MOUSE_LEFT)
	{
		int x,y;
		vgui::input()->GetCursorPos(x,y);
		m_ePanel->SetPos(x,y);
		m_ePanel->SetVisible( true) ;
	}
	*/
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

		if ( id >= 5 ) 
		{
				for ( int j = 0 ; j < 5 ; j ++ )
				{
					int k = InventoryPanel->GetFirstEmptySlot();
					if ( k != -1 )
					{
						executeMove ( id , j );
					}
				}
		}
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

void bliink_inventory_slot::executeMove ( int id , int j )
{
	// well no comment :)
	if ( j == 0 )
	{
		if ( id == 5 ) engine->ServerCmd ( "bliink_inventory_move 5 0" );
		if ( id == 6 ) engine->ServerCmd ( "bliink_inventory_move 6 0" );
		if ( id == 7 ) engine->ServerCmd ( "bliink_inventory_move 7 0" );
		if ( id == 8 ) engine->ServerCmd ( "bliink_inventory_move 8 0" );
		if ( id == 9 ) engine->ServerCmd ( "bliink_inventory_move 9 0" );
		if ( id == 10 ) engine->ServerCmd ( "bliink_inventory_move 10 0" );
		if ( id == 11 ) engine->ServerCmd ( "bliink_inventory_move 11 0" );
		if ( id == 12 ) engine->ServerCmd ( "bliink_inventory_move 12 0" );
		if ( id == 13 ) engine->ServerCmd ( "bliink_inventory_move 13 0" );
		if ( id == 14 ) engine->ServerCmd ( "bliink_inventory_move 14 0" );
		if ( id == 15 ) engine->ServerCmd ( "bliink_inventory_move 15 0" );
		if ( id == 16 ) engine->ServerCmd ( "bliink_inventory_move 16 0" );
		if ( id == 17 ) engine->ServerCmd ( "bliink_inventory_move 17 0" );
		if ( id == 18 ) engine->ServerCmd ( "bliink_inventory_move 18 0" );
		if ( id == 19 ) engine->ServerCmd ( "bliink_inventory_move 19 0" );
	}
	if ( j == 1 )
	{
		if ( id == 5 ) engine->ServerCmd ( "bliink_inventory_move 5 1" );
		if ( id == 6 ) engine->ServerCmd ( "bliink_inventory_move 6 1" );
		if ( id == 7 ) engine->ServerCmd ( "bliink_inventory_move 7 1" );
		if ( id == 8 ) engine->ServerCmd ( "bliink_inventory_move 8 1" );
		if ( id == 9 ) engine->ServerCmd ( "bliink_inventory_move 9 1" );
		if ( id == 10 ) engine->ServerCmd ( "bliink_inventory_move 10 1" );
		if ( id == 11 ) engine->ServerCmd ( "bliink_inventory_move 11 1" );
		if ( id == 12 ) engine->ServerCmd ( "bliink_inventory_move 12 1" );
		if ( id == 13 ) engine->ServerCmd ( "bliink_inventory_move 13 1" );
		if ( id == 14 ) engine->ServerCmd ( "bliink_inventory_move 14 1" );
		if ( id == 15 ) engine->ServerCmd ( "bliink_inventory_move 15 1" );
		if ( id == 16 ) engine->ServerCmd ( "bliink_inventory_move 16 1" );
		if ( id == 17 ) engine->ServerCmd ( "bliink_inventory_move 17 1" );
		if ( id == 18 ) engine->ServerCmd ( "bliink_inventory_move 18 1" );
		if ( id == 19 ) engine->ServerCmd ( "bliink_inventory_move 19 1" );
	}
	if ( j == 2 )
	{
		if ( id == 5 ) engine->ServerCmd ( "bliink_inventory_move 5 2" );
		if ( id == 6 ) engine->ServerCmd ( "bliink_inventory_move 6 2" );
		if ( id == 7 ) engine->ServerCmd ( "bliink_inventory_move 7 2" );
		if ( id == 8 ) engine->ServerCmd ( "bliink_inventory_move 8 2" );
		if ( id == 9 ) engine->ServerCmd ( "bliink_inventory_move 9 2" );
		if ( id == 10 ) engine->ServerCmd ( "bliink_inventory_move 10 2" );
		if ( id == 11 ) engine->ServerCmd ( "bliink_inventory_move 11 2" );
		if ( id == 12 ) engine->ServerCmd ( "bliink_inventory_move 12 2" );
		if ( id == 13 ) engine->ServerCmd ( "bliink_inventory_move 13 2" );
		if ( id == 14 ) engine->ServerCmd ( "bliink_inventory_move 14 2" );
		if ( id == 15 ) engine->ServerCmd ( "bliink_inventory_move 15 2" );
		if ( id == 16 ) engine->ServerCmd ( "bliink_inventory_move 16 2" );
		if ( id == 17 ) engine->ServerCmd ( "bliink_inventory_move 17 2" );
		if ( id == 18 ) engine->ServerCmd ( "bliink_inventory_move 18 2" );
		if ( id == 19 ) engine->ServerCmd ( "bliink_inventory_move 19 2" );
	}
	if ( j == 3 )
	{
		if ( id == 5 ) engine->ServerCmd ( "bliink_inventory_move 5 3" );
		if ( id == 6 ) engine->ServerCmd ( "bliink_inventory_move 6 3" );
		if ( id == 7 ) engine->ServerCmd ( "bliink_inventory_move 7 3" );
		if ( id == 8 ) engine->ServerCmd ( "bliink_inventory_move 8 3" );
		if ( id == 9 ) engine->ServerCmd ( "bliink_inventory_move 9 3" );
		if ( id == 10 ) engine->ServerCmd ( "bliink_inventory_move 10 3" );
		if ( id == 11 ) engine->ServerCmd ( "bliink_inventory_move 11 3" );
		if ( id == 12 ) engine->ServerCmd ( "bliink_inventory_move 12 3" );
		if ( id == 13 ) engine->ServerCmd ( "bliink_inventory_move 13 3" );
		if ( id == 14 ) engine->ServerCmd ( "bliink_inventory_move 14 3" );
		if ( id == 15 ) engine->ServerCmd ( "bliink_inventory_move 15 3" );
		if ( id == 16 ) engine->ServerCmd ( "bliink_inventory_move 16 3" );
		if ( id == 17 ) engine->ServerCmd ( "bliink_inventory_move 17 3" );
		if ( id == 18 ) engine->ServerCmd ( "bliink_inventory_move 18 3" );
		if ( id == 19 ) engine->ServerCmd ( "bliink_inventory_move 19 3" );
	}
	if ( j == 4 )
	{
		if ( id == 5 ) engine->ServerCmd ( "bliink_inventory_move 5 4" );
		if ( id == 6 ) engine->ServerCmd ( "bliink_inventory_move 6 4" );
		if ( id == 7 ) engine->ServerCmd ( "bliink_inventory_move 7 4" );
		if ( id == 8 ) engine->ServerCmd ( "bliink_inventory_move 8 4" );
		if ( id == 9 ) engine->ServerCmd ( "bliink_inventory_move 9 4" );
		if ( id == 10 ) engine->ServerCmd ( "bliink_inventory_move 10 4" );
		if ( id == 11 ) engine->ServerCmd ( "bliink_inventory_move 11 4" );
		if ( id == 12 ) engine->ServerCmd ( "bliink_inventory_move 12 4" );
		if ( id == 13 ) engine->ServerCmd ( "bliink_inventory_move 13 4" );
		if ( id == 14 ) engine->ServerCmd ( "bliink_inventory_move 14 4" );
		if ( id == 15 ) engine->ServerCmd ( "bliink_inventory_move 15 4" );
		if ( id == 16 ) engine->ServerCmd ( "bliink_inventory_move 16 4" );
		if ( id == 17 ) engine->ServerCmd ( "bliink_inventory_move 17 4" );
		if ( id == 18 ) engine->ServerCmd ( "bliink_inventory_move 18 4" );
		if ( id == 19 ) engine->ServerCmd ( "bliink_inventory_move 19 4" );
	}


}