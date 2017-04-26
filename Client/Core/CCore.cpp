#include "stdafx.h"

std::vector<CServerEntity>	g_Entities;
std::vector<CPlayerEntity>	g_Players;
std::vector<CVehicleEntity>	g_Vehicles;
std::vector<CObjectEntity>	g_Objects;
std::vector<CNPCEntity>		g_Npcs;
std::vector<CCheckpointEntity>		g_Checkpoints;

unsigned long CCore::LastCleanUp;
unsigned long CCore::LastUnlock;

bool showSettings = false;
int	 SettingsInst = -1;

bool CCore::Initialize()
{
	CLocalPlayer::Initialize();
	CNetworkManager::Initialize();

	ENTITY::FREEZE_ENTITY_POSITION(CLocalPlayer::GetPed(), TRUE);
	STREAMING::STOP_PLAYER_SWITCH();

	STREAMING::LOAD_SCENE(0.0f, 0.0f, 73.5f);
	ENTITY::SET_ENTITY_COORDS_NO_OFFSET(CLocalPlayer::GetPed(), 0.0f, 0.0f, 73.5f, false, false, false);
	AI::CLEAR_PED_TASKS_IMMEDIATELY(CLocalPlayer::GetPed());
	ENTITY::FREEZE_ENTITY_POSITION(CLocalPlayer::GetPed(), FALSE);

	PLAYER::SET_PLAYER_INVINCIBLE(PLAYER::PLAYER_ID(), true); // temp fix to stop players dieing and crashing their client

	//Loads multiplayer World (wish to have this executed sooner befor the loading screne is terminated)
	GAMEPLAY::_USE_FREEMODE_MAP_BEHAVIOR(true);
	DLC2::_LOAD_MP_DLC_MAPS();
	SCRIPT::SHUTDOWN_LOADING_SCREEN();

	//STREAMING::LOAD_ALL_OBJECTS_NOW();		// not ever sure what this does anymore.

	MapReveal::RevealFullMap();

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
	/*
	if (showSettings)
	{
		GRAPHICS::_SCREEN_DRAW_POSITION_RATIO(0.501f, 0.518f, 0.012f, 0.021f);
		GRAPHICS::DRAW_SCALEFORM_MOVIE(SettingsInst, 0.501f, 0.518f, 0.012f, 0.021f, 255, 255, 255, 255, 0);
		GRAPHICS::_SCREEN_DRAW_POSITION_END();
	}
	*/
	if (timeGetTime() >= LastCleanUp + 1000)
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

	if (KeyJustUp(VK_F9))
	{
		CNetworkManager::Disconnect();
		Logger::Msg("Disconnecting");
	}

	// Chat (Open)
	if ((KeyJustUp(VK_F6) || KeyJustUp(0x54)) && !CChat::InputOpen /*&& !WindowManager->BlockInput*/)
	{
		CChat::InputOpen = true;
	}

	// Chat (Close)
	if (KeyJustUp(VK_ESCAPE))
	{
		if (!CChat::InputOpen)
		{
			// "FE_MENU_VERSION_EMPTY_NO_BACKGROUND" = Blocsk all player input & removes all hud elements (ESC disables it)

			//"pause_menu_pages_settings" - "pause_menu_pages_keymap" - "pause_menu_pages_keymap" - "pause_menu_pages_map"
			if (/*UI::_GET_CURRENT_FRONTEND_MENU() != GAMEPLAY::GET_HASH_KEY("FE_MENU_VERSION_MP_PAUSE")*/ !showSettings)
			{
				/*SettingsInst = GRAPHICS::REQUEST_SCALEFORM_MOVIE_INSTANCE("PAUSE_MENU_PAGES_SETTINGS");
				while (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(SettingsInst))
					WAIT(0);*/

				//GRAPHICS::REQUEST_SCALEFORM_MOVIE("FE_MENU_VERSION_SP_PAUSE");
				//while (!GRAPHICS::HAS_SCALEFORM_MOVIE_LOADED(t)) WAIT(0);
				//UI::SET_FRONTEND_ACTIVE(0);
				
				showSettings = true;
				UI::SET_FRONTEND_ACTIVE(1);
				//UI::ACTIVATE_FRONTEND_MENU(GAMEPLAY::GET_HASH_KEY("FE_MENU_VERSION_SP_PAUSE"/*"FE_MENU_VERSION_EMPTY_NO_BACKGROUND"*/), 0, 0);
			}
			else
			{
				showSettings = false;
				UI::SET_FRONTEND_ACTIVE(0);
				//UI::DISABLE_FRONTEND_THIS_FRAME();
			}
			
		}
		else
		{
			CChat::InputOpen = false;
			//LocalPlayer->controllable = true;
			ImGuiIO& io = ImGui::GetIO();
			io.MouseDrawCursor = false;
		}

		ResetKeyState(VK_ESCAPE);
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
	GAMEPLAY::CLEAR_AREA_OF_PEDS(Position.x, Position.y, Position.z, 10000.0f, 1);
	GAMEPLAY::CLEAR_AREA_OF_VEHICLES(Position.x, Position.y, Position.z, 10000.0f, 0, 0, 0, 0, 0);
	GAMEPLAY::CLEAR_AREA_OF_COPS(Position.x, Position.y, Position.z, 10000.0f, 0);
	//GAMEPLAY::_DISABLE_AUTOMATIC_RESPAWN(true);
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
	if (CLocalPlayer::IsControlsDisabled())
	{
		for (int i = 0; i < 33; i++)
		{
			CONTROLS::DISABLE_ALL_CONTROL_ACTIONS(i);
		}
	}

	// Working
	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlFrontendPause, 1);
	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlFrontendPauseAlternate, 1);
	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlEnterCheatCode, 1);
	// Not Working as far as i can tell.
	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlEnter, 1);
	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlCharacterWheel, 1);
	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlFrontendSocialClub, 1);
	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlFrontendSocialClubSecondary, 1);
	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlDropWeapon, 1);
	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlDropAmmo, 1);
	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlSelectCharacterMichael, 1);
	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlSelectCharacterFranklin, 1);
	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlSelectCharacterTrevor, 1);
	CONTROLS::DISABLE_CONTROL_ACTION(2, ControlSelectCharacterMultiplayer, 1);
	//

	if (KeyJustUp(0x46) && !PED::IS_PED_IN_ANY_VEHICLE(CLocalPlayer::GetPed(), true) /*&& chatnotopen*/)
	{
		Vehicle vehicle = CVehicleEntity::getClosestVehicleFromPedPos(CLocalPlayer::GetPed(), 10.0f);
		if (vehicle)
		{
			for (int v = 0; v < g_Vehicles.size(); v++)
			{
				if (g_Vehicles[v].GetEntity() == vehicle)
				{
					if (g_Vehicles[v].GetOccupant(0) == -1)
					{
						AI::TASK_ENTER_VEHICLE(CLocalPlayer::GetPed(), vehicle, 5000, -1, 2.0, 1, 0);

						RakNet::BitStream sData;
						sData.Write(g_Vehicles[v].GetId());
						CNetworkManager::GetRPC().Signal("TakeEntityAssignment", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, CNetworkManager::GetSystemAddress(), false, false);
					}
					break;
				}
			}
		}
		else
		{
			AI::CLEAR_PED_TASKS(CLocalPlayer::GetPed());
		}
		
		ResetKeyState(0x46);
	}
	
	if (KeyJustUp(0x47) && !PED::IS_PED_IN_ANY_VEHICLE(CLocalPlayer::GetPed(), true) /*&& chatnotopen*/)
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
				seatpos.x = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_pside_r")).x;
				seatpos.y = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_pside_r")).y;
				seatpos.z = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_pside_r")).z;

				float distance = CVector3::Distance(playerPos, seatpos);
				if (g_Vehicles[vehicleIndex].GetOccupant(3) == -1)
					seat = 2;

				seatpos.x = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_pside_f")).x;
				seatpos.y = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_pside_f")).y;
				seatpos.z = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_pside_f")).z;
				
				if (CVector3::Distance(playerPos, seatpos) < distance)
				{
					if (g_Vehicles[vehicleIndex].GetOccupant(1) == -1)
					{
						distance = CVector3::Distance(playerPos, seatpos);
						seat = 0;
					}
				}

				seatpos.x = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_dside_r")).x;
				seatpos.y = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_dside_r")).y;
				seatpos.z = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_dside_r")).z;
				
				if (CVector3::Distance(playerPos, seatpos) < distance)
				{
					if (g_Vehicles[vehicleIndex].GetOccupant(2) == -1)
					{
						distance = CVector3::Distance(playerPos, seatpos);
						seat = 1;
					}
				}

				seatpos.x = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "seat_r")).x;
				seatpos.y = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "seat_r")).y;
				seatpos.z = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "seat_r")).z;
				
				if (CVector3::Distance(playerPos, seatpos) < distance)
				{
					if (VEHICLE::IS_VEHICLE_SEAT_FREE(vehicle, 0)) 
					{
						distance = CVector3::Distance(playerPos, seatpos);
						seat = 0;
					}
				}

				seatpos.x = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_dside_f")).x;
				seatpos.y = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_dside_f")).y;
				seatpos.z = ENTITY::GET_WORLD_POSITION_OF_ENTITY_BONE(vehicle, ENTITY::GET_ENTITY_BONE_INDEX_BY_NAME(vehicle, "door_dside_f")).z;

				if (CVector3::Distance(playerPos, seatpos) < distance)
				{
					if (g_Vehicles[vehicleIndex].GetOccupant(0) == -1)
					{
						distance = CVector3::Distance(playerPos, seatpos);
						seat = -1;

						g_Vehicles[vehicleIndex].SetAssignee(CNetworkManager::GetInterface()->GetMyGUID());

						RakNet::BitStream sData;
						sData.Write(g_Vehicles[vehicleIndex].GetId());
						CNetworkManager::GetRPC().Signal("TakeEntityAssignment", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, CNetworkManager::GetSystemAddress(), false, false);
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
		
		ResetKeyState(0x47);
	}

	if (CONTROLS::IS_CONTROL_PRESSED(0, ControlMoveUp) || CONTROLS::IS_CONTROL_PRESSED(0, ControlMoveDown) || CONTROLS::IS_CONTROL_PRESSED(0, ControlMoveLeft) || CONTROLS::IS_CONTROL_PRESSED(0, ControlMoveRight))
	{
		if (AI::GET_IS_TASK_ACTIVE(CLocalPlayer::GetPed(), 160))
		{
			AI::CLEAR_PED_TASKS(CLocalPlayer::GetPed());
		}
	}
}
