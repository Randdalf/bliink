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

#ifdef CLIENT_DLL
extern ConCommand Bliink_WelcomePlay;
extern ConCommand Bliink_SpectatePregameWelcome;
extern ConCommand Bliink_CancelReady;
extern ConCommand Bliink_WelcomeSpectate;
#endif

#endif // BLIINK_GAMEVARS_SHARED_H