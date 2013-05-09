
#include <vgui_controls/Frame.h>
 #include <vgui_controls/Button.h>
 #include <vgui_controls/Scrollbar.h>
 #include <vgui_controls/EditablePanel.h>
 #include <vgui_controls/ImagePanel.h>
 #include <vgui_controls/ListPanel.h>
 #include <vgui_controls/SectionedListPanel.h>
 #include <vgui_controls/Menu.h>
 #include <KeyValues.h>
 #include <vgui/IVGui.h>


 #include "c_bliink_player.h"
 #include "Ibliink_inventory_ui.h"
 using namespace vgui;

class bliink_inventory_ui  : public vgui::Frame
 {
 	DECLARE_CLASS_SIMPLE(bliink_inventory_ui, vgui::Frame); 
 
 	bliink_inventory_ui(vgui::VPANEL parent); 	
 	~bliink_inventory_ui(){};
 
 protected:

 	virtual void OnTick();
 	virtual void OnCommand(const char* pcCommand);
 
 private:

		C_BliinkPlayer *pPlayer;

        Button *DropB;
		Button *AmmoB;
		Button *WeaponsB;
		Button *ConsumablesB;
		Button *Consume;

		SectionedListPanel *ConsumablesL;
		SectionedListPanel *WeaponsL;	
		SectionedListPanel *AmmoL;

		//ListPanel *NewList;


		bool Updated;

 public :

		void add();
 
 };