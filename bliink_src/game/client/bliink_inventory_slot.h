#ifndef BLINK_INVENTORY_SLOT
#define BLINK_INVENTORY_SLOT

#ifdef _WIN32
#pragma once
#endif

#include <vgui/VGUI.h>
#include <vgui_controls/EditablePanel.h>
#include <vgui_controls/Label.h>

namespace vgui
{
	class Label;
	class ImagePanel;
}

class bliink_inventory_slot : public vgui::EditablePanel
{
	DECLARE_CLASS_SIMPLE( bliink_inventory_slot, vgui::EditablePanel );

public:

	bliink_inventory_slot(
		vgui::Panel *parent, 
		const char *panelName, 
		const char *text,
		const char *imgPanelName,
		const char *imgLabelpName,
		const char *imgLabelaName);

	virtual ~bliink_inventory_slot();

	virtual void ButtonInit();
	virtual void OnThink();
	virtual void ApplySchemeSettings(vgui::IScheme *pScheme);
	
	virtual void OnMousePressed(vgui::MouseCode code);
	virtual void OnMouseDoublePressed(vgui::MouseCode code);

	virtual void SetText(const char *text);
	virtual void SetAmount(const char *text);
	virtual void SetFont(vgui::HFont font);
	virtual void SetButtonEnabled(bool bEnabled);
	virtual void SetImage(const char *szFilename);

	vgui::ImagePanel *m_pImage;
	vgui::Label *m_pLabel;
	vgui::Label *m_aLabel;
	bool m_bButtonEnabled;
	vgui::HFont m_Font;

	int id; // relative inventory id
	char* type; // weapon , consumable , ammo
	char* name; // empty , locked , name
	int amount; // stack counts

};

#endif