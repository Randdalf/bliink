 //The following include files are necessary to allow your MyPanel.cpp to compile.
 #include "cbase.h"
 #include "noface.h"
 using namespace vgui;
 #include <vgui/IVGui.h>
 #include <iostream>
 #include <vgui_controls/TextEntry.h>
 #include <vgui_controls/Frame.h>
 #include <vgui_controls/ImagePanel.h>
 #include <vgui_controls/Button.h>
 
 //CMyPanel class: Tutorial example class
 class CMynoPanel : public vgui::Frame
 {
 	DECLARE_CLASS_SIMPLE(CMynoPanel, vgui::Frame); 
 	//CMyPanel : This Class / vgui::Frame : BaseClass
 
 	CMynoPanel(vgui::VPANEL parent); 	// Constructor
 	~CMynoPanel(){};				// Destructor
 
 protected:
 	//VGUI overrides:
	 virtual void OnTick();
	 virtual void OnCommand(const char* pcCommand){};
 
 public:
/*	 virtual void PaintBackground()
	{
		SetBgColor(Color(36,32,45));
		SetPaintBackgroundType( 0 );
		BaseClass::PaintBackground();
	}*/

 private:
 	//Other used VGUI control Elements:
 };


 // Constuctor: Initializes the Panel
CMynoPanel::CMynoPanel(vgui::VPANEL parent)
: BaseClass(NULL, "MynoPanel")
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
 
	SetScheme(vgui::scheme()->LoadSchemeFromFile("resource/SourceScheme.res", "SourceScheme"));

	LoadControlSettings("resource/UI/NofacePanel.res");

	SetBgColor (Color (0,0,0,128));

	vgui::ivgui()->AddTickSignal( GetVPanel(), 100 );
 
	DevMsg("MynoPanel has been constructed\n");
}


//Class: CMyPanelInterface Class. Used for construction.
class CMynoPanelInterface : public noface_panel
{
private:
	CMynoPanel *MynoPanel;
public:
	CMynoPanelInterface()
	{
		MynoPanel = NULL;
	}
	void Create(vgui::VPANEL parent)
	{
		MynoPanel = new CMynoPanel(parent);
	}
	void Destroy()
	{
		if (MynoPanel)
		{
			MynoPanel->SetParent( (vgui::Panel *)NULL);
			delete MynoPanel;
		}
	}
};

static CMynoPanelInterface g_MynoPanel;
noface_panel* nofacepanel = (noface_panel*)&g_MynoPanel;

ConVar clno_showmypanel("clno_showmypanel", "1", FCVAR_CLIENTDLL, "Sets the state of myPanel <state>");

void CMynoPanel::OnTick()
{
	BaseClass::OnTick();
	SetVisible(clno_showmypanel.GetBool()); //CL_SHOWMYPANEL / 1 BY DEFAULT
}


void showNoFacePan ( const CCommand &args )
{
	clno_showmypanel.SetValue(true);
}
 
ConCommand my_sayno( "NoFacePanelOn", showNoFacePan , "say something", 0);

void hideNoFacePan ( const CCommand &args )
{
	clno_showmypanel.SetValue(false);
}
 
ConCommand my_sayno2( "NoFacePanelOff", hideNoFacePan , "say something", 0);