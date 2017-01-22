#include "stdafx.h"

std::vector<CServerEntity>	g_Entities;
std::vector<CPlayerEntity>	g_Players;
std::vector<CVehicleEntity>	g_Vehicles;

CCore::CCore()
{
	// Construct CNetworkManager
	g_NetworkManager = std::unique_ptr<CNetworkManager>(new CNetworkManager);
	g_RPCManager = std::unique_ptr<CRPCManager>(new CRPCManager);
	g_LocalPlayer = std::unique_ptr<CLocalPlayer>(new CLocalPlayer);
	g_Scipts = std::unique_ptr<Scripts>(new Scripts);
	g_Doors = std::unique_ptr<Doors>(new Doors);
	g_Animations = std::unique_ptr<Animations>(new Animations);
}

CCore::~CCore()
{
	/*SAFE_DELETE(g_NetworkManager);
	SAFE_DELETE(g_RPCManager);
	SAFE_DELETE(g_LocalPlayer);
	SAFE_DELETE(g_Scipts);
	SAFE_DELETE(g_Doors);
	SAFE_DELETE(g_Animations);*/
}

bool CCore::Initialize()
{
	//Loads multiplayer World (wish to have this executed sooner befor the loading screne is terminated)
	GAMEPLAY::_ENABLE_MP_DLC_MAPS(true);
	DLC2::_LOAD_MP_DLC_MAPS();
	SCRIPT::SHUTDOWN_LOADING_SCREEN();

	STREAMING::LOAD_ALL_OBJECTS_NOW();		//I think this loads everyobject to memory

	TIME::PAUSE_CLOCK(true);
	GAMEPLAY::CLEAR_OVERRIDE_WEATHER();

	//Disable Hospitals
	for (int i = 0; i <= 5; i++)
	{
		GAMEPLAY::DISABLE_HOSPITAL_RESTART(i, true);
	}
	//Disable Stunt Jumps
	for (int i = 0; i < 50; i++)
	{
		GAMEPLAY::DISABLE_STUNT_JUMP_SET(i);
		GAMEPLAY::DELETE_STUNT_JUMP(i);
	}

	// Check if CServer is created
	if (!g_NetworkManager)
	{
		Logger::Msg("CNetworkManager is invalid");
		return false;
	}

	// Call OnLoad
	if (!g_NetworkManager->Start())
	{
		Logger::Msg("CNetworkManager could not be started");
		return false;
	}

	g_RPCManager->RegisterRPCMessages();

	g_Scipts->StopAll();
	CleanUp();

	return true;
}

void CCore::OnGameTick()
{
	//if (g_LocalPlayer->IsPlaying() == FALSE)
		//return;

	if (timeGetTime() >= LastCleanUp + 10000)
	{
		CleanUp();			// World Clean Up
		g_Scipts->Pulse();	// Script Clean Up
		PreventCheat();
	}

	if (timeGetTime() >= LastUnlock + 2000)
	{
		g_Doors->Pulse();	// Unlocks doors
		LastUnlock = timeGetTime();
	}

	CleanUpTick();

	if (KeyJustUp(VK_F8))
	{
		g_NetworkManager->Connect("127.0.0.1", "default", CON_PORT);
		Logger::Msg("Connecting");
	}

	if (KeyJustUp(VK_F7))
	{
		g_NetworkManager->Connect("176.31.142.113", "default", CON_PORT);
		Logger::Msg("Connecting");
	}

	if (KeyJustUp(VK_F6))
	{
		g_NetworkManager->Connect("192.168.56.101", "default", CON_PORT);
		Logger::Msg("Connecting");
	}

	if (KeyJustUp(VK_F5))
	{
		g_NetworkManager->Connect("188.166.76.252", "default", CON_PORT);
		Logger::Msg("Connecting");
	}

	if (KeyJustUp(VK_F10))
	{
		g_NetworkManager->Connect("83.128.145.20", "default", CON_PORT);
		Logger::Msg("Connecting");
	}

	if (KeyJustUp(VK_F9))
	{
		g_NetworkManager->Disconnect();
		Logger::Msg("Disconnecting");
	}

	g_LocalPlayer->Pulse();
	g_NetworkManager->Pulse();
	
	if (!g_Players.empty()) {
		for (int i = 0; i < g_Players.size(); i++) {
			g_Players[i].Pulse();
		}
	}

	if (!g_Vehicles.empty()) {
		for (int i = 0; i < g_Vehicles.size(); i++) {
			g_Vehicles[i].Pulse();
		}
	}
}

void CCore::CleanUp()
{
	Vector3_t Position = g_LocalPlayer->GetPosEx();

	PLAYER::DISABLE_PLAYER_VEHICLE_REWARDS(PLAYER::PLAYER_ID());
	PLAYER::SET_MAX_WANTED_LEVEL(0);
	
	VEHICLE::SET_GARBAGE_TRUCKS(false);
	VEHICLE::SET_RANDOM_BOATS(false);
	VEHICLE::SET_RANDOM_TRAINS(false);
	VEHICLE::SET_FAR_DRAW_VEHICLES(false);
	VEHICLE::_DISPLAY_DISTANT_VEHICLES(false);
	VEHICLE::DELETE_ALL_TRAINS();
	VEHICLE::SET_NUMBER_OF_PARKED_VEHICLES(-1);
	VEHICLE::SET_ALL_LOW_PRIORITY_VEHICLE_GENERATORS_ACTIVE(false);
	VEHICLE::REMOVE_VEHICLES_FROM_GENERATORS_IN_AREA(-9999.0f, -9999.0f, -9999.0f, 9999.0f, 9999.0f, 9999.0f, false);

	PED::SET_CREATE_RANDOM_COPS_NOT_ON_SCENARIOS(false);
	PED::SET_CREATE_RANDOM_COPS(false);
	PED::SET_CREATE_RANDOM_COPS_ON_SCENARIOS(false);

	GAMEPLAY::SET_TIME_SCALE(1.0f);
	GAMEPLAY::CLEAR_AREA_OF_PEDS(Position.x, Position.y, Position.z, 10000.0f, true);
	GAMEPLAY::CLEAR_AREA_OF_VEHICLES(Position.x, Position.y, Position.z, 10000.0f, 0, 0, 0, 0, 0);
	GAMEPLAY::_DISABLE_AUTOMATIC_RESPAWN(true);
	GAMEPLAY::IGNORE_NEXT_RESTART(true);
	GAMEPLAY::SET_MISSION_FLAG(true);
	GAMEPLAY::SET_FADE_OUT_AFTER_DEATH(false);

	MOBILE::DESTROY_MOBILE_PHONE();

	//std::cout << "[CCore] Clean up" << std::endl;

	LastCleanUp = timeGetTime();
}

void CCore::CleanUpTick()
{
	PED::SET_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
	PED::SET_SCENARIO_PED_DENSITY_MULTIPLIER_THIS_FRAME(0.0f, 0.0f);
	VEHICLE::SET_RANDOM_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
	VEHICLE::SET_VEHICLE_DENSITY_MULTIPLIER_THIS_FRAME(0.0f);
	DECISIONEVENT::SUPPRESS_SHOCKING_EVENTS_NEXT_FRAME();
	DECISIONEVENT::SUPPRESS_AGITATION_EVENTS_NEXT_FRAME();
}

void CCore::PreventCheat()
{
	Ped tempped = g_LocalPlayer->GetPed();

	PED::SET_PED_MAX_HEALTH(tempped, 200);
	PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(tempped, true);
}
