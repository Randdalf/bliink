#ifndef BLIINK_GAMEVARS_SHARED_H
#define BLIINK_GAMEVARS_SHARED_H
#ifdef _WIN32
#pragma once
#endif

#include "convar.h"

extern ConVar Bliink_CountdownToLive;
extern ConVar Bliink_MinPlayers;
extern ConVar Bliink_MinSurvivors;
extern ConVar Bliink_ResultsTime;
extern ConVar Bliink_FogBaseTime;
extern ConVar Bliink_FogPlayerTime;

#ifdef CLIENT_DLL
extern ConCommand Bliink_BlinkOn;
extern ConCommand Bliink_BlinkOff;

extern ConCommand Bliink_Flashlight;

extern ConCommand Bliink_WelcomePlay;
extern ConCommand Bliink_SpectatePregameWelcome;
extern ConCommand Bliink_CancelReady;
extern ConCommand Bliink_WelcomeSpectate;

extern ConCommand Bliink_UpgradeWeaponSlots;
extern ConCommand Bliink_UpgradeHealth;
extern ConCommand Bliink_UpgradeFatigue;

extern ConCommand Bliink_DevAddExp;
extern ConCommand Bliink_DevGiveSlow;
extern ConCommand Bliink_DevGiveBurn;

extern ConCommand Bliink_InventoryPrint;
extern ConCommand Bliink_InventoryMove;
extern ConCommand Bliink_InventoryCraft;
extern ConCommand Bliink_InventoryDrop;
extern ConCommand Bliink_InventoryConsume;
extern ConCommand Bliink_InventoryDelete;
extern ConCommand Bliink_InventorySetNextAmmoType;

extern ConVar Bliink_ConnectIP;
#endif

#endif // BLIINK_GAMEVARS_SHARED_H