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
#include <sstream>

#include "../../Shared/Common.h"

// Math
#include "Common.h"
#include "CVector3.h"
#include "CVector4.h"

// API Function Imports
#include "APIServer.h"
#include "APIEntity.h"
#include "APIVehicle.h"
#include "APIVisual.h"

// When Plugin gets loaded
extern "C" DLL_PUBLIC bool API_Initialize(void) 
{
	API::Server::PrintMessage("init");
	API::Vehicle::CreateVehicle("dilettante", CVector3{ 0.0f,0.0f,100.0f }, 90.0f);
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
	//API::Visual::ShowMessageAboveMap("I don't like people!", "CHAR_DEFAULT", 1, "Jack", "");
	return true;
}

// Player Connecting
extern "C" DLL_PUBLIC bool API_OnPlayerConnecting(const char *guid )
{
	API::Server::PrintMessage(("Player connecting with [guid: %s]", guid));
	API::Visual::ShowMessageAboveMap(("~p~You are Connecting [guid: %s]", guid), "CHAR_DEFAULT", 1, "Server", "Connecting...");
	return true;
}

// Player Connected
extern "C" DLL_PUBLIC bool API_OnPlayerConnected(int player)
{
	std::ostringstream oss;
	oss << "~g~You Connected! [ID: " << player << "]";
	API::Visual::ShowMessageAboveMap(oss.str().c_str(), "CHAR_CREATOR_PORTRAITS", 1, "Server", "");

	API::Entity::SetPosition(player, CVector3{ 0.0f,0.0f,75.0f });

	CVector3 position = API::Entity::GetPosition(player);
	oss = std::ostringstream("");
	oss << "~p~Position: " << position.fX << " " << position.fY << " " << position.fZ;
	
	API::Visual::ShowMessageAboveMap(oss.str().c_str(), "CHAR_STRIPPER_CHEETAH", 5, "Server", "Position");
	return true;
}