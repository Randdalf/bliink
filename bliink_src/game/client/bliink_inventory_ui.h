
 #include <vgui_controls/Frame.h>
 #include <vgui_controls/Button.h>
 #include <vgui_controls/ImagePanel.h>

 #include <KeyValues.h>
 #include <vgui/IVGui.h>

 #include "c_bliink_player.h"
 #include "Ibliink_inventory_ui.h"
 #include "bliink_inventory_slot.h"

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

		///Button *UpdateInventory;

		bool Updated;

		bliink_inventory_slot* InventorySlots[20];

 public :

		void Init(void);
		void Add();
 
 };