  
 #include "cbase.h"
 #include <vgui/IVGui.h>

 #include <vgui_controls/Frame.h>
 #include <vgui_controls/Button.h>
 #include <vgui_controls/Scrollbar.h>
 #include <vgui_controls/EditablePanel.h>
 #include <vgui_controls/ImagePanel.h>
 #include <vgui_controls/ListPanel.h>
 #include <vgui_controls/ListViewPanel.h>
 #include <vgui_controls/Menu.h>
 #include <KeyValues.h>

 using namespace vgui;


//bliink_inventory_ui class: Tutorial example class
 class bliink_inventory_ui  : public vgui::Frame
 {
 	DECLARE_CLASS_SIMPLE(bliink_inventory_ui, vgui::Frame); 
 	//bliink_inventory_ui : This Class / vgui::Frame : BaseClass
 
 	bliink_inventory_ui(vgui::VPANEL parent); 	
 	~bliink_inventory_ui(){};
 
 protected:
 	//VGUI overrides:
 	virtual void OnTick();
 	virtual void OnCommand(const char* pcCommand);
 
 private:
 	//Other used VGUI control Elements:
 
        // Our Code Defined Control
        Button *m_pCloseButton;
		ListPanel *l_listView;

 public :
		void add();
 
 };