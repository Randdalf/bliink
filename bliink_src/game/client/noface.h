#include <vgui/VGUI.h>

// IMyPanel.h
class noface_panel
{
public:
	virtual void		Create( vgui::VPANEL parent ) = 0;
	virtual void		Destroy( void ) = 0;

};
 
extern noface_panel* nofacepanel;