#include "stdafx.h"

CLocalPlayer::CLocalPlayer()
{
	Game.Player				= PLAYER::PLAYER_ID();
	Game.Ped				= PLAYER::GET_PLAYER_PED(Game.Player);
	Game.VehicleEntering	= 0;

	Information.Id			= 0;

	Data.Vehicle.VehicleID	= -1;
	Data.Vehicle.Seat		= -1;
}

CLocalPlayer::~CLocalPlayer()
{
	Game.Player				= NULL;
	Game.Ped				= 0;
	Game.VehicleEntering	= 0;

	Data.Vehicle.VehicleID	= -1;
	Data.Vehicle.Seat		= -1;
}

void CLocalPlayer::Pulse()
{
	unsigned long ulCurrentTime = timeGetTime();
	if (ulCurrentTime >= Network.LastSyncSent + (1000.0f / 50))
	{
		if (g_Core->GetNetworkManager()->g_ConnectionState != CONSTATE_COND)
			return;

		// Update the local players Data
		Vector3 Coordinates = ENTITY::GET_ENTITY_COORDS(Game.Ped, ENTITY::IS_ENTITY_DEAD(Game.Ped));
		ENTITY::GET_ENTITY_QUATERNION(Game.Ped, &Data.Quaternion.fX, &Data.Quaternion.fY, &Data.Quaternion.fZ, &Data.Quaternion.fW);
		Vector3 Velocity = ENTITY::GET_ENTITY_VELOCITY(Game.Ped);

		Data.Model.Model = ENTITY::GET_ENTITY_MODEL(Game.Ped);
		Data.Model.Type = PED::GET_PED_TYPE(Game.Ped);

		WEAPON::GET_CURRENT_PED_WEAPON(Game.Ped, &Data.Weapon.Weapon, true);
		Data.Weapon.Reload = (bool)WEAPON::_IS_PED_RELOADING(Game.Ped);

		Data.ForwardSpeed = ENTITY::GET_ENTITY_SPEED(Game.Ped);
		Data.Position = { Coordinates.x, Coordinates.y, Coordinates.z };
		Data.Velocity = { Velocity.x, Velocity.y, Velocity.z };

		VehicleChecks();

		Data.Vehicle.VehicleID = GamePed::GetVehicleID(Game.Ped);
		Data.Vehicle.Seat = GamePed::GetVehicleSeat(Game.Ped);

		// Send to server
		BitStream bitstream;
		bitstream.Write((unsigned char)ID_PACKET_PLAYER);

		bitstream.Write(Statistics.Score);
		
		bitstream.Write(Data.Model.Type);

		bitstream.Write(Data.Weapon.Weapon);
		bitstream.Write(Data.Weapon.Reload);

		bitstream.Write(Data.ForwardSpeed);

		bitstream.Write(Data.Position.fX);
		bitstream.Write(Data.Position.fY);
		bitstream.Write(Data.Position.fZ);

		bitstream.Write(Data.Velocity.fX);
		bitstream.Write(Data.Velocity.fY);
		bitstream.Write(Data.Velocity.fZ);

		bitstream.Write(Data.Quaternion.fX);
		bitstream.Write(Data.Quaternion.fY);
		bitstream.Write(Data.Quaternion.fZ);
		bitstream.Write(Data.Quaternion.fW);

		bitstream.Write(Data.Vehicle.VehicleID);
		bitstream.Write(Data.Vehicle.Seat);

		bitstream.Write(GamePed::GetPedTask(Game.Ped));

		g_Core->GetNetworkManager()->GetInterface()->Send(&bitstream, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 0, g_Core->GetNetworkManager()->GetSystemAddress(), false);

		Network.LastSyncSent = timeGetTime();
	}
}

void CLocalPlayer::VehicleChecks()
{
	// Single BitStream define we just reset each time we need it fresh
	RakNet::BitStream sData;

	// Check if player is exiting a vehicle
	if (Data.Vehicle.VehicleID > -1 && CONTROLS::IS_CONTROL_PRESSED(0, ControlVehicleExit) && !Control.ControlVehicleExit)
	{
		Control.ControlVehicleExit = true;

		/*sData.Reset();
		sData.Write(Data.Vehicle.VehicleID);
		g_Core->GetNetworkManager()->GetRPC().Signal("OnPlayerExitingVehicle", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, g_Core->GetNetworkManager()->GetSystemAddress(), false, false);*/
	}
	else if (Control.ControlVehicleExit)
	{
		Control.ControlVehicleExit = false;
	}

	// Check the Vehicle the player is attempting to enter
	/*if (PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(Game.Ped))
	{
		Vehicle enteringVehicle = PED::GET_VEHICLE_PED_IS_TRYING_TO_ENTER(Game.Ped);
		if (enteringVehicle != Game.VehicleEntering)
		{
			for (int i = 0; i < g_Vehicles.size(); i++)
			{
				if (enteringVehicle == g_Vehicles[i].GetEntity())
				{
					if (g_Vehicles[i].GetOccupant(0) != -1)
					{
						AI::CLEAR_PED_TASKS_IMMEDIATELY(Game.Ped);
					}
					else
					{
						Game.VehicleEntering = enteringVehicle;

						//sData.Reset();
						//sData.Write(g_Vehicles[i].GetId());
						//g_Core->GetNetworkManager()->GetRPC().Signal("OnPlayerEnteringVehicle", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, g_Core->GetNetworkManager()->GetSystemAddress(), false, false);
					}
					break;
				}
			}
		}
	}*/


	// Check the Vehicle the Player is in
	if (Data.Vehicle.VehicleID != GamePed::GetVehicleID(Game.Ped))
	{
		if (GamePed::GetVehicleSeat(Game.Ped) == 0 && GamePed::GetVehicleID(Game.Ped) != -1)
		{
			for (int i = 0; i < g_Vehicles.size(); i++)
			{
				if (GamePed::GetVehicleID(Game.Ped) == g_Vehicles[i].GetId())
				{
					if (g_Vehicles[i].GetAssignee() == g_Core->GetNetworkManager()->GetInterface()->GetMyGUID() && g_Vehicles[i].GetOccupant(0) == -1)
					{
						sData.Reset();
						sData.Write(GamePed::GetVehicleID(Game.Ped));
						g_Core->GetNetworkManager()->GetRPC().Signal("TakeEntityAssignment", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, g_Core->GetNetworkManager()->GetSystemAddress(), false, false);
					}
					else if (g_Vehicles[i].GetOccupant(0) != -1)
					{
						AI::TASK_STAND_STILL(Game.Ped, 1);
						//AI::CLEAR_PED_TASKS_IMMEDIATELY(Game.Ped);
					}
					break;
				}
			}
		}
	}
}
