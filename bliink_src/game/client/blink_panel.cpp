 //The following include files are necessary to allow your MyPanel.cpp to compile.
 #include "cbase.h"
 #include "blink_panel.h"
 using namespace vgui;
 #include <vgui/IVGui.h>
 #include <iostream>
 #include <vgui_controls/TextEntry.h>
 #include <vgui_controls/Frame.h>
 #include <vgui_controls/ImagePanel.h>
 #include <vgui_controls/Button.h>
 
 //CMyPanel class: Tutorial example class
 class CMyPanel : public vgui::Frame
 {
 	DECLARE_CLASS_SIMPLE(CMyPanel, vgui::Frame); 
 	//CMyPanel : This Class / vgui::Frame : BaseClass
 
 	CMyPanel(vgui::VPANEL parent); 	// Constructor
 	~CMyPanel(){};				// Destructor
 
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
CMyPanel::CMyPanel(vgui::VPANEL parent)
: BaseClass(NULL, "MyPanel")
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

	LoadControlSettings("resource/UI/blinkpanel.res");

	SetBgColor (Color (0,0,0,128));

	vgui::ivgui()->AddTickSignal( GetVPanel(), 100 );
 
	DevMsg("MyPanel has been constructed\n");
}


//Class: CMyPanelInterface Class. Used for construction.
class CMyPanelInterface : public blink_panel
{
private:
	CMyPanel *MyPanel;
public:
	CMyPanelInterface()
	{
		MyPanel = NULL;
	}
	void Create(vgui::VPANEL parent)
	{
		MyPanel = new CMyPanel(parent);
	}
	void Destroy()
	{
		if (MyPanel)
		{
			MyPanel->SetParent( (vgui::Panel *)NULL);
			delete MyPanel;
		}
	}
};

static CMyPanelInterface g_MyPanel;
blink_panel* blinkpanel = (blink_panel*)&g_MyPanel;

ConVar cl_showmypanel("cl_showmypanel", "1", FCVAR_CLIENTDLL, "Sets the state of myPanel <state>");

void CMyPanel::OnTick()
{
	BaseClass::OnTick();
	SetVisible(cl_showmypanel.GetBool()); //CL_SHOWMYPANEL / 1 BY DEFAULT
}


void showBlinkPan ( const CCommand &args )
{
	cl_showmypanel.SetValue(true);
}
 
ConCommand my_say( "BlinkPanelOn", showBlinkPan , "say something", 0);

void hideBlinkPan ( const CCommand &args )
{
	cl_showmypanel.SetValue(false);
}
 
ConCommand my_say2( "BlinkPanelOff", hideBlinkPan , "say something", 0);