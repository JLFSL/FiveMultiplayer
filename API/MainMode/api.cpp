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
#include "APIWorld.h"
#include "APIEntity.h"
#include "APIVehicle.h"
#include "APIVisual.h"

// When Plugin gets loaded
extern "C" DLL_PUBLIC bool API_Initialize(void) 
{
	API::Server::PrintMessage("Gamemode Initializing...");

	API::Vehicle::CreateVehicle("elegy", CVector3{ -3.0f, 6.0f, 71.0f }, 360.0f);
	API::Vehicle::CreateVehicle("comet3", CVector3{ -6.0f, 8.0f, 71.0f }, 360.0f);
	API::Vehicle::CreateVehicle("blazer5", CVector3{ -9.0f, 10.0f, 71.0f }, 360.0f);
	API::Vehicle::CreateVehicle("voltic2", CVector3{ -12.0f, 12.0f, 71.0f }, 360.0f);

	API::World::SetTime(13, 0, 0);

	int hour, minute, second;
	API::World::GetTime(&hour, &minute, &second);
	std::cout << "Time: " << hour << ":" << minute << ":" << second << std::endl;

	API::Server::PrintMessage("Gamemode Initialized!");
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
extern "C" DLL_PUBLIC bool API_OnPlayerConnected(int entity, int playerid)
{
	std::ostringstream oss;
	oss << "~g~You Connected! ~o~[~w~ID: " << playerid << "~o~]";
	API::Visual::ShowMessageAboveMap(oss.str().c_str(), "CHAR_CREATOR_PORTRAITS", 1, "Server", "");

	API::Entity::SetPosition(entity, CVector3{ 0.0f,0.0f,75.0f });

	std::ostringstream oss2;
	CVector3 position = API::Entity::GetPosition(entity);
	oss2 << "~p~Position: " << position.fX << " " << position.fY << " " << position.fZ;
	API::Visual::ShowMessageAboveMap(oss2.str().c_str(), "CHAR_CREATOR_PORTRAITS", 5, "Server", "Position");
	return true;
}