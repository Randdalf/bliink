
#ifdef _WIN32
#pragma once
#endif

class Ibliink_inventory_ui
{
public:
	virtual void		Create( vgui::VPANEL parent ) = 0;
	virtual void		Destroy( void ) = 0;
	virtual void		Activate( void ) = 0;
};
 
extern Ibliink_inventory_ui* InventoryPanel;