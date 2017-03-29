#include <iostream>
#include <sstream>

#include "api.h"

// Math
#include "sdk/CVector3.h"
#include "sdk/CVector4.h"

// API Function Imports
#include "sdk/APIServer.h"
#include "sdk/APIWorld.h"
#include "sdk/APIEntity.h"
#include "sdk/APIVehicle.h"
#include "sdk/APIVisual.h"
#include "sdk/APIPlayer.h"
#include "sdk/APIObject.h"
#include "sdk/APICheckpoint.h"

extern "C" DLL_PUBLIC bool API_Initialize(void) {
	// When Plugin gets loaded
	API::Server::PrintMessage(L"Initialized");
	return true;
}

extern "C" DLL_PUBLIC bool API_Close(void) {
	// When plugin gets unloaded
	API::Server::PrintMessage(L"Closed");
	return true;
}

extern "C" DLL_PUBLIC bool API_OnTick(void) {
	// Every server tick this gets called
	API::Server::PrintMessage(L"Tick");
	return true;
}

extern "C" DLL_PUBLIC bool API_OnPlayerConnecting(const char *guid)
{
	// When a player connects (still loading everything from the server)	
	API::Server::PrintMessage(L"Connecting");
	return true;
}

extern "C" DLL_PUBLIC bool API_OnPlayerConnected(int player)
{
	// When the player is successfully connected (loaded in, but not spawned yet)
	API::Server::PrintMessage(L"Connected");
	return true;
}