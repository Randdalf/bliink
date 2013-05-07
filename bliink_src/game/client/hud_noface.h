#include "hudelement.h"
#include <vgui_controls/Panel.h>
 
using namespace vgui;
 
class CHudNoFace : public CHudElement, public Panel
{
   DECLARE_CLASS_SIMPLE( CHudNoFace, Panel );
 
   public:
   CHudNoFace( const char *pElementName );
   void togglePrint();
   virtual void OnThink();
 
   protected:
   virtual void Paint();
   int m_nImport;
};