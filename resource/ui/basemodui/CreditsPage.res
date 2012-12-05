"Resource/UI/CreditsPage.res"
{
	"CreditsPage"
	{
		"ControlName"		"Frame"
		"fieldName"			"CreditsPage"
		"xpos"				"0"
		"ypos"				"0"
		"wide"				"f0"
		"tall"				"f0"
		"autoResize"		"0"
		"pinCorner"			"0"
		"visible"			"1"
		"enabled"			"1"
		"tabPosition"		"0"
	}
	
	"ImgBackground" [$WIN32]
	{
		"ControlName"			"L4DMenuBackground"
		"fieldName"				"ImgBackground"
		"xpos"					"0"
		"ypos"					"99"
		"zpos"					"-1"
		"wide"					"f0"
		"tall"					"300"
		"autoResize"			"0"
		"pinCorner"				"0"
		"visible"				"1"
		"enabled"				"1"
		"tabPosition"			"0"
		"fillColor"				"0 0 0 0"
	}
	
	"SDK_UI_Game_Title"
	{
		"ControlName"			"Label"
		"fieldName"				"SDK_UI_Game_Title"
		"xpos"					"75"
		"ypos"					"115" 
		"wide"					"200"
		"tall"					"20"
		"autoResize"			"1"
		"pinCorner"				"0"
		"visible"				"1"
		"enabled"				"1"
		"tabPosition"			"0"
		"labelText"				"#SDK_UI_Game_Title"
		"font"					"DefaultLarge"
	}
	
	"Valve"
	{
		"ControlName"			"Label"
		"fieldName"				"Valve"
		"xpos"					"75"
		"ypos"					"215" 
		"wide"					"100"
		"tall"					"10"
		"autoResize"			"1"
		"pinCorner"				"0"
		"visible"				"1"
		"visible"				"1"
		"enabled"				"1"
		"tabPosition"			"0"
		"labelText"				"Valve"
		"font"					"DefaultMedium"
	}

	"IconBackArrow" [$WIN32]
	{
		"ControlName"			"ImagePanel"
		"fieldName"				"IconBackArrow"
		"xpos"					"c-195"
		"ypos"					"420"
		"wide"					"15"
		"tall"					"15"
		"scaleImage"			"1"
		"pinCorner"				"0"
		"visible"				"1"
		"enabled"				"1"
		"tabPosition"			"0"
		"image"					"icon_button_arrow_left"
		"scaleImage"			"1"
	}

	"BtnCancel" [$WIN32]
	{
		"ControlName"			"BaseModHybridButton"
		"fieldName"				"BtnCancel"
		"xpos"					"c-180"
		"ypos"					"420"
		"zpos"					"1"
		"wide"					"250"
		"tall"					"15"
		"autoResize"			"1"
		"pinCorner"				"0"
		"visible"				"1"
		"enabled"				"1"
		"tabPosition"			"0"
		"wrap"					"1"
		"labelText"				"#L4D360UI_Done"
		"tooltiptext"			"#L4D360UI_Tooltip_Back"
		"style"					"MainMenuSmallButton"
		"command"				"Back"
		"proportionalToParent"	"1"
		"usetitlesafe" 			"0"
		EnabledTextInsetX		"2"
		DisabledTextInsetX		"2"
		FocusTextInsetX			"2"
		OpenTextInsetX			"2"
		"allcaps"				"1"
	}
}