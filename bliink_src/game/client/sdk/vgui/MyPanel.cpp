 #include "cbase.h"
 #include "IMyPanel.h"

 using namespace vgui;
 #include <vgui/IVGui.h>
 #include <vgui_controls/Frame.h>
 
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
 	virtual void OnCommand(const char* pcCommand);
 
 private:
 	//Other used VGUI control Elements:
 
 };

 // Constuctor: Initializes the Panel
CMyPanel::CMyPanel(vgui::VPANEL parent) : BaseClass(NULL, "MyPanel")
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
 
	LoadControlSettings("resource/UI/MyPanel.res");
 
	vgui::ivgui()->AddTickSignal( GetVPanel(), 100 );
 
	DevMsg("MyPanel has been constructed\n");
}

//Class: CMyPanelInterface Class. Used for construction.
class CMyPanelInterface : public IMyPanel
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
IMyPanel* mypanel = (IMyPanel*)&g_MyPanel;