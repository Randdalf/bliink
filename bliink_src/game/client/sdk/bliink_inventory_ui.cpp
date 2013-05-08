#pragma once

 #include "bliink_inventory_ui.h"
 #include "Ibliink_inventory_ui.h"

 #include "c_bliink_player.h"

 // Constuctor: Initializes the Panel
bliink_inventory_ui::bliink_inventory_ui(vgui::VPANEL parent)
: BaseClass(NULL, "bliink_inventory_ui")
{
	SetParent( parent );
 
	SetTitle( "bliink_inventory_ui", false);
	SetKeyBoardInputEnabled( true );
	SetMouseInputEnabled( true );
 
	SetProportional( false );
	SetTitleBarVisible( true );
	SetMinimizeButtonVisible( false );
	SetMaximizeButtonVisible( false );
	SetCloseButtonVisible( false );
	SetSizeable( true );
	SetMoveable( true );
	SetVisible( true );
    
	SetScheme(vgui::scheme()->LoadSchemeFromFile("resource/SourceScheme.res", "Scheme"));
	LoadControlSettings("resource/UI/InventoryPanel.res");
	
	SetName("Inventory");
	SetBounds(90,70,370,500);
	SetMinimumSize(200,400);	

	vgui::ivgui()->AddTickSignal( GetVPanel(), 100 );
	DevMsg("bliink_inventory_ui has been constructed\n");

	// close button
		m_pCloseButton = new Button(this, "", "Close", this, "turnoff");
		m_pCloseButton->SetPos(430, 560);
		m_pCloseButton->SetDepressedSound("common/bugreporter_succeeded.wav");
		m_pCloseButton->SetReleasedSound("ui/buttonclick.wav");
		//m_pCloseButton->SetAutoResize(PIN_BOTTOMRIGHT,AUTORESIZE_DOWNANDRIGHT,0,0,0,0);

	// list view ? 

		l_listView = new ListPanel( this , "Items");
		l_listView->SetPos( 120, 100);
		l_listView->SetSize(340, 460);

	 //l_listView->AddColumnHeader(1 , const char *columnName, const char *columnText, int startingWidth, int minWidth, int maxWidth, int columnFlags = 0); 
	 l_listView->AddColumnHeader(1, "items", " text ", 50, 0 );


	 //l_listView->RemoveColumn(int column);	// removes a column
	 //l_listView->FindColumn(const char *columnName);
	 l_listView->SetColumnHeaderHeight( 100 );
	 l_listView->SetColumnHeaderText(1, "Items");

	 //l_listView->SetColumnHeaderText(int column, wchar_t *text);
	 //l_listView->SetColumnHeaderImage(int column, int imageListIndex);
	 //l_listView->setColumnHeaderTooltip(int column, const char *tooltipText);
	 //l_listView->SetColumnTextAlignment( int column, int align );

}

class InventoryInterface : public Ibliink_inventory_ui
{
private:
	Ibliink_inventory_ui *MyPanel;
public:

	InventoryInterface()
	{
		MyPanel = NULL;
	}
	void Create(vgui::VPANEL parent)
	{
		MyPanel = new bliink_inventory_ui(parent);
	}
	void Destroy()
	{
		if (MyPanel)
		{
			MyPanel->SetParent( (vgui::Panel *)NULL);
			delete MyPanel;
		}
	}
	void Activate( void )
	{
		if ( MyPanel )
		{
			MyPanel->Activate();
		}
	}
	
};

static InventoryInterface g_MyPanel;

Ibliink_inventory_ui* bliink_inventory_ui = (Ibliink_inventory_ui*)&g_MyPanel;

ConVar cl_showinventory("cl_showinventory", "0", FCVAR_CLIENTDLL, "Sets the state of the bliink_inventory_ui <state>");

ConVar additem("cl_additem" , "0", FCVAR_CLIENTDLL , "adds an item");

CON_COMMAND(AddItem, "ads item")
{
	additem.SetValue(!additem.GetBool());
	DevMsg ( "item add");
	ConMsg("item added ");
};

void bliink_inventory_ui::OnTick()
{
	BaseClass::OnTick();
	SetVisible(cl_showinventory.GetBool()); //cl_showinventory / 0 BY DEFAULT
}

CON_COMMAND(ToggleInventory, "Toggles bliink_inventory_ui on or off")
{
	cl_showinventory.SetValue(!cl_showinventory.GetBool());
	bliink_inventory_ui -> Activate();
	DevMsg ( "bliink_inventory_ui");
	ConMsg("bliink_inventory_ui Triggered");
};

void bliink_inventory_ui::OnCommand(const char* pcCommand)
{
	if(!Q_stricmp(pcCommand, "turnoff"))
		cl_showinventory.SetValue(0);
}