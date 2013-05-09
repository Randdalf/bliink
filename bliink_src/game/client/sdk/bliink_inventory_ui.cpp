 #include "cbase.h"

#include "bliink_inventory_ui.h"
#include "bliink_gamevars_shared.h"

#define MAX_INVENTORY 20

bliink_inventory_ui::bliink_inventory_ui(vgui::VPANEL parent)
: BaseClass(NULL, "bliink_inventory_ui")
{
	//Color panel_color = Color(1,1,1);

	this->SetParent( parent );

	this->SetTitle("Inventory",true);

	this->SetPos(100,100);
	this->SetSize(500,300);
	this->SetBuildModeEditable( true );
	
	this->SetKeyBoardInputEnabled( true );
	this->SetMouseInputEnabled( true );

	this->SetProportional( true );
	this->SetTitleBarVisible( true );
	this->SetMinimizeButtonVisible( false );
	this->SetMaximizeButtonVisible( false );
	this->SetCloseButtonVisible( false );
	this->SetSizeable( false );
	this->SetMoveable( false );
	this->SetVisible( false );

	ConsumablesL = new SectionedListPanel(this,"ConsumablesL"); 
	ConsumablesL->AddSection(0, "ConsumablesL");
	ConsumablesL->AddColumnToSection(0, "Name", "Name", 0, 80);
	ConsumablesL->AddColumnToSection(0, "Amount", "Amount", 0, 40);
	ConsumablesL->SetVisible(true);
	
	//NewList = new ListPanel(this, "NewList");
	//NewList->AddColumnHeader(0, "Header" ,"ColumnText", 50);

	AmmoL = new SectionedListPanel(this,"AmmoL"); 
	AmmoL->AddSection(0, "AmmoL"); 
	AmmoL->AddColumnToSection(0, "Name", "Name", 0, 80);
	AmmoL->AddColumnToSection(0, "Amount", "Amount", 0, 40);
	AmmoL->SetVisible(true);

	WeaponsL = new SectionedListPanel(this,"WeaponsL"); 
	WeaponsL->AddSection(0, "WeaponsL"); 
	WeaponsL->AddColumnToSection(0, "Name", "Name", 0, 80);
	WeaponsL->AddColumnToSection(0, "Amount", "Amount", 0, 40); 
	WeaponsL->SetVisible(true);

	DropB = new Button(this,"Drop","Drop"); 
	DropB->SetCommand("dropitem");

	ConsumablesB = new Button(this,"Consumables","Consumables"); 
	ConsumablesB->SetCommand("Consumables");

	WeaponsB = new Button(this,"Weapons","Weapons"); 
	WeaponsB->SetCommand("Consumables");
	
	AmmoB = new Button(this,"Ammo","Ammo"); 
	AmmoB->SetCommand("Ammo");
	
	Consume = new Button(this,"Consume","Consume"); 
	Consume->SetCommand("Consume");
 
	SetScheme(vgui::scheme()->LoadSchemeFromFile("resource/SourceScheme.res", "SourceScheme"));
 
	LoadControlSettings("resource/UI/InventoryPanel.res");
 
	vgui::ivgui()->AddTickSignal( GetVPanel(), 100 );
 
	DevMsg("InventoryPanel has been constructed\n");
}

class InventoryInterface : public Ibliink_inventory_ui
{
private:

	bliink_inventory_ui *InventoryPanel;

public:

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
	
	pPlayer = ToBliinkPlayer( C_BasePlayer::GetLocalPlayer() );
	
	if(pPlayer)
	{
		CBliinkItemInventory inv = pPlayer->GetBliinkInventory();

		SetVisible(bliink_inventory.GetBool()); 
		if(bliink_updateInventory.GetBool()) 
		{
			ConsumablesL->RemoveAll();
			AmmoL->RemoveAll(); 
			WeaponsL->RemoveAll(); 
			Updated = false; 
			bliink_updateInventory.SetValue(0); 
		}
		if( bliink_inventory.GetBool() && !Updated ) 
		{	
			for(int i = 0; i < MAX_INVENTORY; i++)
			{
				char *name = inv.GetItemName(i);
				int amount = inv.GetItemStackCounts(i);
				if( name != NULL ) 
				{	
					KeyValues *kv = new KeyValues("data"); 
					kv->SetString("Name", name);
					char buffer[20];
					kv->SetString("Amount", itoa(amount,buffer,10) );

					if ( i >= 5)
						ConsumablesL->AddItem(0,kv);
					if ( i < 5 )
						WeaponsL->AddItem(0,kv);
					//AmmoL->AddItem(0,kv);

					//NewList->AddItem(kv,0,false,false);
					
					kv->Clear(); 
					kv->deleteThis(); 
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

	if(!Q_stricmp(cmd, "dropitem"))
	{
		
		pPlayer = ToBliinkPlayer( C_BasePlayer::GetLocalPlayer() );
		CBliinkItemInventory inv = pPlayer->GetBliinkInventory() ;

		int idc = ConsumablesL->GetSelectedItem();
		int idw = WeaponsL->GetSelectedItem();

		char* comand;
		

		if ( idc != -1) 
		{
			//sprintf(comand, "bliink_inventory_drop 5" /*, idc + 5*/ );
			engine->ServerCmd(  "bliink_inventory_drop 5" );
		}
		if ( idw != -1)
		{
			//sprintf(comand, "bliink_inventory_drop 0" ,/* idw*/ );
			engine->ServerCmd( "bliink_inventory_drop 0" );
		}
		
		//inv.Command_Drop( id );
		
		//char* name = (char*) ConsumablesL->GetColumnTextBySection(0,id);
		//char* a = (char*) ConsumablesL->GetColumnTextBySection(1,id);
		//int amount = atoi(a);
		//if ( amount > 0 ) {

			//DevMsg ( "Drop!");
		
		

		//	amount -- ;
		//}
		
		/*
		ConsumablesL->RemoveItem(id);
		KeyValues *kv = new KeyValues("data"); 
		kv->SetString("Name", name);
		char buffer[20];
		kv->SetString("Amount", itoa(amount,buffer,10) ); 
		ConsumablesL->AddItem(0,kv);
		*/

		bliink_updateInventory.SetValue(1);
		
	}

	if(!Q_stricmp(cmd, "moveitem"))
	{
		
	}
	if(!Q_stricmp(cmd, "Consume"))
	{


		int idc = ConsumablesL->GetSelectedItem();
		if ( idc != -1 )
		{
			char* comand;
			//sprintf(comand, "bliink_inventory_drop 1"/* , idc + 5*/ );
			engine->ServerCmd( "bliink_inventory_consume 0" );
		}

	}
	if(!Q_stricmp(cmd, "craftitems"))
	{

	}
	if(!Q_stricmp(cmd, "Ammo"))
	{
		bliink_updateInventory.SetValue(1);
		//AmmoL->SetVisible(true);
		//ConsumablesL->SetVisible(false);
		//WeaponsL->SetVisible(false);
	}
	if(!Q_stricmp(cmd, "Consumables"))
	{
		bliink_updateInventory.SetValue(1);
		//AmmoL->SetVisible(false);
		//ConsumablesL->SetVisible(true);
		//WeaponsL->SetVisible(false);
	}
	if(!Q_stricmp(cmd, "Weapons"))
	{
		bliink_updateInventory.SetValue(1);
		//AmmoL->SetVisible(false);
		//ConsumablesL->SetVisible(false);
		//WeaponsL->SetVisible(true);
	}
}
