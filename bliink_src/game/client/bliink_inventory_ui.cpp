 #include "cbase.h"

#include "bliink_inventory_ui.h"
#include "bliink_gamevars_shared.h"
#include <vgui/IInput.h>

#define MAX_INVENTORY 20

bliink_inventory_ui::bliink_inventory_ui(vgui::VPANEL parent)
: BaseClass(NULL, "bliink_inventory_ui")
{

	this->SetParent( parent );
	this->SetTitle("Inventory",true);

	this->SetPos(100,100);
	this->SetSize(500,300);
	this->SetBuildModeEditable( false );
	
	this->SetKeyBoardInputEnabled( false );
	this->SetMouseInputEnabled( true );

	this->SetProportional( false );
	this->SetTitleBarVisible( false );
	this->SetMinimizeButtonVisible( false );
	this->SetMaximizeButtonVisible( false );
	this->SetCloseButtonVisible( false );
	this->SetSizeable( false );
	this->SetMoveable( false );
	this->SetVisible( false );

	Init();

	SetScheme(vgui::scheme()->LoadSchemeFromFile("resource/ClientScheme.res", "ClientScheme"));
 
	LoadControlSettings("resource/UI/NewInventoryPanel.res");

	vgui::ivgui()->AddTickSignal( GetVPanel(), 100 );

	DevMsg("InventoryPanel has been constructed\n");

}

void bliink_inventory_ui::Init(void) 
{
	for ( int i = 0 ; i< 20 ; i++ )
	{
		if ( i == 0)
			InventorySlots[i] = new bliink_inventory_slot(this, "Slot_0", "empty", "Img_0", "Name_0", "Nr_0");
		if ( i == 1)
			InventorySlots[i] = new bliink_inventory_slot(this, "Slot_1", "empty", "Img_1", "Name_1", "Nr_1");
		if ( i == 2)
			InventorySlots[i] = new bliink_inventory_slot(this, "Slot_2", "empty", "Img_2", "Name_2", "Nr_2");
		if ( i == 3)
			InventorySlots[i] = new bliink_inventory_slot(this, "Slot_3", "empty", "Img_3", "Name_3", "Nr_3");
		if ( i == 4)
			InventorySlots[i] = new bliink_inventory_slot(this, "Slot_4", "empty", "Img_4", "Name_4", "Nr_4");
		if ( i == 5)
			InventorySlots[i] = new bliink_inventory_slot(this, "Slot_5", "empty", "Img_5", "Name_5", "Nr_5");
		if ( i == 6)
			InventorySlots[i] = new bliink_inventory_slot(this, "Slot_6", "empty", "Img_6", "Name_6", "Nr_6");
		if ( i == 7)
			InventorySlots[i] = new bliink_inventory_slot(this, "Slot_7", "empty", "Img_7", "Name_7", "Nr_7");
		if ( i == 8)
			InventorySlots[i] = new bliink_inventory_slot(this, "Slot_8", "empty", "Img_8", "Name_8", "Nr_8");
		if ( i == 9)
			InventorySlots[i] = new bliink_inventory_slot(this, "Slot_9", "empty", "Img_9", "Name_9", "Nr_9");
		if ( i == 10)
			InventorySlots[i] = new bliink_inventory_slot(this, "Slot_10", "empty", "Img_10", "Name_10", "Nr_10");
		if ( i == 11)
			InventorySlots[i] = new bliink_inventory_slot(this, "Slot_11", "empty", "Img_11", "Name_11", "Nr_11");
		if ( i == 12)
			InventorySlots[i] = new bliink_inventory_slot(this, "Slot_12", "empty", "Img_12", "Name_12", "Nr_12");
		if ( i == 13)
			InventorySlots[i] = new bliink_inventory_slot(this, "Slot_13", "empty", "Img_13", "Name_13", "Nr_13");
		if ( i == 14)
			InventorySlots[i] = new bliink_inventory_slot(this, "Slot_14", "empty", "Img_14", "Name_14", "Nr_14");
		if ( i == 15)
			InventorySlots[i] = new bliink_inventory_slot(this, "Slot_15", "empty", "Img_15", "Name_15", "Nr_15");
		if ( i == 16)
			InventorySlots[i] = new bliink_inventory_slot(this, "Slot_16", "empty", "Img_16", "Name_16", "Nr_16");
		if ( i == 17)
			InventorySlots[i] = new bliink_inventory_slot(this, "Slot_17", "empty", "Img_17", "Name_17", "Nr_17");
		if ( i == 18)
			InventorySlots[i] = new bliink_inventory_slot(this, "Slot_18", "empty", "Img_18", "Name_18", "Nr_18");
		if ( i == 19)
			InventorySlots[i] = new bliink_inventory_slot(this, "Slot_19", "empty", "Img_19", "Name_0", "Nr_0");
	}


}

class InventoryInterface : public Ibliink_inventory_ui
{

public:
	bliink_inventory_ui *InventoryPanel;

	InventoryInterface() { InventoryPanel = NULL; }

	void Create(vgui::VPANEL parent) 
	{ 
		InventoryPanel = new bliink_inventory_ui(parent); 
	}
	void Destroy()
	{
		if (InventoryPanel)
		{
			InventoryPanel -> SetParent( (vgui::Panel *)NULL);
			delete InventoryPanel;
		}
	}
	void Activate( void )
	{
		if ( InventoryPanel )
		{
			InventoryPanel->SetVisible( true );
		}
	}
	int GetFirstEmptySlot( void ) 
	{
		for ( int j = 0 ; j < 5 ; j ++ )
		{
			int t = InventoryPanel->InventorySlots[j]->amount;
			if ( t == 0 )
			{
				return j;
			}
		}

		return -1;
	}
};

static InventoryInterface g_MyPanel;

Ibliink_inventory_ui* InventoryPanel = (Ibliink_inventory_ui*)&g_MyPanel;

ConVar bliink_inventory("bliink_inventory", "0", FCVAR_CLIENTDLL, "Set the state th Inventory");

ConVar bliink_updateInventory("bliink_updateInventory", "0", FCVAR_CLIENTDLL, "Updates the Inventory");

ConVar bliink_inventoryToggle("bliink_invetoryToggle","0", FCVAR_CLIENTDLL, "Updates the Inventory");

CON_COMMAND(ToggleInventory, "Toggles bliink_inventory_ui on or off")
{
	bliink_updateInventory.SetValue(1);
	bliink_inventory.SetValue(!bliink_inventory.GetBool());
	InventoryPanel -> Activate();
	DevMsg ( "Invetory!");
	ConMsg("Inventory Triggered");
};

CON_COMMAND(UpdateInventory,"Updates the inventory")
{
	bliink_updateInventory.SetValue(1);
}

void bliink_inventory_ui::OnTick()
{
	BaseClass::OnTick();
	bliink_updateInventory.SetValue(1);
	pPlayer = ToBliinkPlayer( C_BasePlayer::GetLocalPlayer() );

	if(pPlayer)
	{
		CBliinkItemInventory inv = pPlayer->GetBliinkInventory();

		SetVisible(bliink_inventory.GetBool()); 
		if(bliink_updateInventory.GetBool()) 
		{
			Updated = false; 
			bliink_updateInventory.SetValue(0); 
		}
		if( bliink_inventory.GetBool() && !Updated ) 
		{	
			for(int i = 0; i < MAX_INVENTORY; i++)
			{
					
				char *name = inv.GetItemName(i);
				int amount = inv.GetItemStackCounts(i);
				char *description = inv.GetItemDescription(i);
				if( name != NULL ) 
				{

					InventorySlots[i]->SetText(description); 
					
					char * text;
					if ( amount == 0 ) text = "Amount : 0";
					if ( amount == 1 ) text = "Amount : 1";
					if ( amount == 2 ) text = "Amount : 2";
					if ( amount == 3 ) text = "Amount : 3";
					if ( amount == 4 ) text = "Amount : 4";
					if ( amount == 5 ) text = "Amount : 5";
					if ( amount == 6 ) text = "Amount : 6";
					if ( amount == 7 ) text = "Amount : 7";
					if ( amount == 8 ) text = "Amount : 8";
					if ( amount == 9 ) text = "Amount : 9";
					if ( amount == 10 ) text = "Amount : 10";

					InventorySlots[i]->m_aLabel->SetText(text);
					InventorySlots[i]->id = i;
					InventorySlots[i]->name = name;
					InventorySlots[i]->amount = amount;

					InventorySlots[i]->m_pLabel->SetVisible(false);
					InventorySlots[i]->m_pImage->SetImage(name);
					//InventorySlots[i]->m_pImage->Paint();
				}
			}
			Updated = true;
		}
	} else 
		SetVisible(0);

	SetVisible(bliink_inventory.GetBool());

}

void bliink_inventory_ui::OnCommand(const char* cmd)
{
	if(!Q_stricmp(cmd, "turnoff")) 
		bliink_inventory.SetValue(0); 
	if(!Q_stricmp(cmd, "update")) 
		bliink_updateInventory.SetValue(1);
}
