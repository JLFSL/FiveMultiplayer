#if defined _WIN32 || defined __CYGWIN__
#ifdef __GNUC__
#define DLL_PUBLIC __attribute__ ((dllexport))
#else
#define DLL_PUBLIC __declspec(dllexport)
#endif
#else
#define DLL_PUBLIC 
#endif

#include <iostream>

#include "../../Shared/Common.h"

// API Function Imports
#include "APIServer.h"
#include "APIVisual.h"

// When Plugin gets loaded
extern "C" DLL_PUBLIC bool API_Initialize(void) 
{
	API::Server::_PrintMessage("init");
	return true;
}

// When plugin gets unloaded
extern "C" DLL_PUBLIC bool API_Close(void) 
{
	std::cout << "close" << std::endl;
	return true;
}

// Every server tick this gets called
extern "C" DLL_PUBLIC bool API_OnTick(void) 
{
	API::Visual::_ShowMessageAboveMap("I don't like people!");
	return true;
}

// Player Connecting
extern "C" DLL_PUBLIC bool API_OnPlayerConnecting(const char *guid )
{
	API::Server::_PrintMessage(("Player connecting with [guid: %s]", guid));
	API::Visual::_ShowMessageAboveMap(("~p~You are Connecting [guid: %s]", guid));
	return true;
}

// Player Connected
extern "C" DLL_PUBLIC bool API_OnPlayerConnected(void)
{
	API::Visual::_ShowMessageAboveMap("~g~YOU CONNECTED!");
	return true;
}