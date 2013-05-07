#include "hudelement.h"
#include <vgui_controls/Panel.h>
 
using namespace vgui;
 
class CHudBliink : public CHudElement, public Panel
{
   DECLARE_CLASS_SIMPLE( CHudBliink, Panel );
 
   public:
   CHudBliink( const char *pElementName );
   void togglePrint();
   virtual void OnThink();
 
   protected:
   virtual void Paint();
   int m_nImport;
};