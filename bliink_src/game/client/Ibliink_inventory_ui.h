
#ifndef IBLIINK_INVENTORY_UI
#define IBLIINK_INVENTORY_UI

class Ibliink_inventory_ui
{
public:
	virtual void		Create( vgui::VPANEL parent ) = 0;
	virtual void		Destroy( void ) = 0;
	virtual void		Activate( void ) = 0;
	virtual int			GetFirstEmptySlot ( void ) = 0;
};
 
extern Ibliink_inventory_ui* InventoryPanel;

#endif