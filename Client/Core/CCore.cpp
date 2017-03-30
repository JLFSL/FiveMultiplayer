#include "stdafx.h"

std::vector<CServerEntity>	g_Entities;
std::vector<CPlayerEntity>	g_Players;
std::vector<CVehicleEntity>	g_Vehicles;
std::vector<CObjectEntity>	g_Objects;
std::vector<CNPCEntity>		g_Npcs;
std::vector<CCheckpointEntity>		g_Checkpoints;

unsigned long CCore::LastCleanUp;
unsigned long CCore::LastUnlock;

bool CCore::Initialize()
{
	CLocalPlayer::Initialize();
	CNetworkManager::Initialize();

	//Loads multiplayer World (wish to have this executed sooner befor the loading screne is terminated)
	GAMEPLAY::_USE_FREEMODE_MAP_BEHAVIOR(true);
	DLC2::_LOAD_MP_DLC_MAPS();
	SCRIPT::SHUTDOWN_LOADING_SCREEN();

	STREAMING::LOAD_ALL_OBJECTS_NOW();		//I think this loads everyobject to memory

	TIME::PAUSE_CLOCK(true);
	GAMEPLAY::CLEAR_OVERRIDE_WEATHER();
	
	// Disables dispatch services
	for (int s = 1; s < 13; s++)
	{
		GAMEPLAY::ENABLE_DISPATCH_SERVICE(s, false);
	}

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

	// Call OnLoad
	if (!CNetworkManager::Start())
	{
		Logger::Msg("CNetworkManager could not be started");
		return false;
	}

	CRPCManager::RegisterRPCMessages();

	Scripts::StopAll();
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
		Scripts::Pulse();	// Script Clean Up
		PreventCheat();
	}

	if (timeGetTime() >= LastUnlock + 2000)
	{
		Scripts::Pulse();	// Unlocks doors
		LastUnlock = timeGetTime();
	}

	CleanUpTick();

	if (KeyJustUp(VK_F8))
	{
		CConfig::Read();
		CNetworkManager::Connect(CConfig::GetIp().c_str(), CConfig::GetPassword().c_str(), CConfig::GetPort());
		Logger::Msg("Connecting");
	}

	if (KeyJustUp(VK_F7))
	{
		CNetworkManager::Connect("176.31.142.113", "default", CON_PORT);
		Logger::Msg("Connecting");
	}

	if (KeyJustUp(VK_F6))
	{
		CNetworkManager::Connect("51.254.219.119", "default", 2323);
		Logger::Msg("Connecting");
	}

	if (KeyJustUp(VK_F5))
	{
		CNetworkManager::Connect("188.166.76.252", "default", CON_PORT);
		Logger::Msg("Connecting");
	}

	if (KeyJustUp(VK_F10))
	{
		CNetworkManager::Connect("83.128.145.20", "default", CON_PORT);
		Logger::Msg("Connecting");
	}

	if (KeyJustUp(VK_F9))
	{
		CNetworkManager::Disconnect();
		Logger::Msg("Disconnecting");
	}

	KeyCheck();

	CLocalPlayer::Pulse();
	CNetworkManager::Pulse();
	CStreamer::Pulse();
	
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

	if (!g_Objects.empty())
	{
		for (int i = 0; i < g_Objects.size(); i++)
		{
			g_Objects[i].Pulse();
		}
	}

	if (!g_Checkpoints.empty())
	{
		for (int i = 0; i < g_Checkpoints.size(); i++)
		{
			g_Checkpoints[i].Pulse();
		}
	}
}

void CCore::CleanUp()
{
	Vector3_t Position = CLocalPlayer::GetPositionEx();

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

	//MOBILE::DESTROY_MOBILE_PHONE();

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
	Ped tempped = CLocalPlayer::GetPed();

	PED::SET_PED_MAX_HEALTH(tempped, 200);
	PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(tempped, true);
}

void CCore::KeyCheck()
{
	if (CONTROLS::IS_CONTROL_PRESSED(0, ControlEnter) && !PED::IS_PED_IN_ANY_VEHICLE(CLocalPlayer::GetPed(), true) /*&& chatnotopen*/)
	{
		Vehicle vehicle = CVehicleEntity::getClosestVehicleFromPedPos(CLocalPlayer::GetPed(), 10.0f);
		if (vehicle)
		{
			int vehicleIndex = -1;

			for (int v = 0; v < g_Vehicles.size(); v++)
			{
				if (g_Vehicles[v].GetEntity() == vehicle)
				{
					vehicleIndex = v;
					break;
				}
			}

			if (vehicleIndex != -1)
			{
				int seat = 0;

				CVector3 playerPos = CLocalPlayer::GetPosition();
				CVector3 seatpos;
				seatpos.fX = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_pside_r")).x;
				seatpos.fY = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_pside_r")).y;
				seatpos.fZ = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_pside_r")).z;

				float distance = CVector3::Distance(playerPos, seatpos);
				if (g_Vehicles[vehicleIndex].GetOccupant(3) == -1)
					seat = 2;

				seatpos.fX = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_pside_f")).x;
				seatpos.fY = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_pside_f")).y;
				seatpos.fZ = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_pside_f")).z;
				
				if (CVector3::Distance(playerPos, seatpos) < distance)
				{
					if (g_Vehicles[vehicleIndex].GetOccupant(1) == -1)
					{
						distance = CVector3::Distance(playerPos, seatpos);
						seat = 0;
					}
				}

				seatpos.fX = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_dside_r")).x;
				seatpos.fY = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_dside_r")).y;
				seatpos.fZ = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_dside_r")).z;
				
				if (CVector3::Distance(playerPos, seatpos) < distance)
				{
					if (g_Vehicles[vehicleIndex].GetOccupant(2) == -1)
					{
						distance = CVector3::Distance(playerPos, seatpos);
						seat = 1;
					}
				}

				seatpos.fX = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "seat_r")).x;
				seatpos.fY = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "seat_r")).y;
				seatpos.fZ = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "seat_r")).z;
				
				if (CVector3::Distance(playerPos, seatpos) < distance)
				{
					if (VEHICLE::IS_VEHICLE_SEAT_FREE(vehicle, 0)) 
					{
						distance = CVector3::Distance(playerPos, seatpos);
						seat = 0;
					}
				}

				seatpos.fX = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_dside_f")).x;
				seatpos.fY = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_dside_f")).y;
				seatpos.fZ = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_dside_f")).z;

				if (CVector3::Distance(playerPos, seatpos) < distance)
				{
					if (g_Vehicles[vehicleIndex].GetOccupant(0) == -1)
					{
						distance = CVector3::Distance(playerPos, seatpos);
						seat = -1;
					}
				}

				AI::TASK_ENTER_VEHICLE(CLocalPlayer::GetPed(), vehicle, 5000, seat, 2.0, 1, 0);
			}
			else
			{
				AI::CLEAR_PED_TASKS(CLocalPlayer::GetPed());
			}
		}
		else
		{
			AI::CLEAR_PED_TASKS(CLocalPlayer::GetPed());
		}
	}
}
