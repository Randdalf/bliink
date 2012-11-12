//========= Copyright © 1996-2005, Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
//=============================================================================//

#include "cbase.h"
#include "sdk_playerclass_info_parse.h"
#include "weapon_sdkbase.h"
#include <KeyValues.h>

// memdbgon must be the last include file in a .cpp file!!!
#include "tier0/memdbgon.h"

//Tony; due to the nature of the base code.. I must do this !

FilePlayerClassInfo_t* CreatePlayerClassInfo()
{
	return new FilePlayerClassInfo_t;
}