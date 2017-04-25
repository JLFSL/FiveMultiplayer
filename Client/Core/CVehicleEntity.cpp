#include "stdafx.h"

CVehicleEntity::CVehicleEntity()
{
	Game.Created = false; 
	Game.Vehicle = NULL;

	Information.Id = -1;

	Network.Assigned = RakNetGUID(2017);
	
	for (int i = 0; i < SizeOfArray(Occupants); i++) 
	{ 
		Occupants[i] = -1; 
	}
}

void CVehicleEntity::Create(int entity)
{
	Information.Id	= entity;

	CServerEntity newServerEntity;
	newServerEntity.Create(entity, CServerEntity::Vehicle);
	g_Entities.push_back(newServerEntity);

	RequestData();

	std::cout << "[CVehicleEntity] Added Vehicle: " << Information.Id << std::endl;
}

bool CVehicleEntity::CreateVehicle()
{
	if (!Game.Created)
	{
		STREAMING::SET_VEHICLE_POPULATION_BUDGET(3000);

		Hash model = GAMEPLAY::GET_HASH_KEY((char*)Data.Model.c_str());
		if (!STREAMING::IS_MODEL_IN_CDIMAGE(model) || !STREAMING::IS_MODEL_VALID(model))
		{
			std::cout << "[CVehicleEntity::CreateVehicle] invalid vehicle for " << Information.Id << " reverting to dilettante." << std::endl;
			model = GAMEPLAY::GET_HASH_KEY("dilettante");
			Data.Model = "dilettante";
		}

		STREAMING::REQUEST_MODEL(model);

		while (!STREAMING::HAS_MODEL_LOADED(model))
		{
			WAIT(200);

			if (!STREAMING::HAS_MODEL_LOADED(model))
				return false;
		}

		std::cout << "[CVehicleEntity] " << Information.Id << " is beign Spawned with model " << Data.Model << "." << std::endl;

		Game.Vehicle = VEHICLE::CREATE_VEHICLE(model, Data.Position.x, Data.Position.y, Data.Position.z, Data.Heading, FALSE, TRUE);
		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);

		ENTITY::FREEZE_ENTITY_POSITION(Game.Vehicle, TRUE);
		STREAMING::REQUEST_COLLISION_AT_COORD(Data.Position.x, Data.Position.y, Data.Position.z);
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(Game.Vehicle, Data.Position.x, Data.Position.y, Data.Position.z, FALSE, FALSE, FALSE);

		ENTITY::SET_ENTITY_LOAD_COLLISION_FLAG(Game.Vehicle, TRUE);
		ENTITY::SET_ENTITY_COLLISION(Game.Vehicle, TRUE, FALSE);
		ENTITY::SET_ENTITY_ROTATION(Game.Vehicle, Data.Rotation.x, Data.Rotation.y, Data.Rotation.z, 2, true);

		VEHICLE::SET_TAXI_LIGHTS(Game.Vehicle, TRUE);

		// Vehicle Number Plate
		//VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Game.Vehicle, (char *)CString::utf16ToUtf8(Data.Plate).c_str());

		const int Class = VEHICLE::GET_VEHICLE_CLASS(Game.Vehicle);
		if (Class == 18 || Class == 17 || Class == 15 || Class == 16 || Class == 20 || Class == 14)
		{
			VEHICLE::SET_VEHICLE_MOD(Game.Vehicle, 48, 0, 0);
			VEHICLE::SET_VEHICLE_LIVERY(Game.Vehicle, 0);
		}

		// Vehicle Mods
		/*VEHICLE::SET_VEHICLE_MOD_KIT(Game.Vehicle, 0);
		for (int i = 0; i < SizeOfArray(Data.Mods); i++)
		{
			VEHICLE::SET_VEHICLE_MOD(Game.Vehicle, i, Data.Mods[i].index, false);
			if(i = 48)
				VEHICLE::SET_VEHICLE_LIVERY(Game.Vehicle, Data.Mods[i].index);
		}
		*/
		// Vehicle Colors
		/*if (!Data.Colors[0].custom)
		{
			VEHICLE::SET_VEHICLE_MOD_COLOR_1(Game.Vehicle, Data.Colors[0].type, Data.Colors[0].color, 0);
		}
		else
		{
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Game.Vehicle, Data.Colors[0].customCol.Red, Data.Colors[0].customCol.Green, Data.Colors[0].customCol.Blue);
		}

		if (!Data.Colors[1].custom)
		{
			VEHICLE::SET_VEHICLE_MOD_COLOR_2(Game.Vehicle, Data.Colors[1].type, Data.Colors[1].color);
		}
		else
		{
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Game.Vehicle, Data.Colors[1].customCol.Red, Data.Colors[1].customCol.Green, Data.Colors[1].customCol.Blue);
		}*/

		// Engine State (Forces Non-Vanilla engine state)
		/*if (Data.ForceEngineState > -1)
		{
			VEHICLE::SET_VEHICLE_ENGINE_ON(Game.Vehicle, Data.ForceEngineState, true, true);
			VEHICLE::SET_VEHICLE_UNDRIVEABLE(Game.Vehicle, !Data.ForceEngineState);
		}*/

		//VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Game.Vehicle, Data.PlateStyle);

		/*for (int i = 1; i < SizeOfArray(Data.Extras); i++)
		{
			VEHICLE::SET_VEHICLE_EXTRA(Game.Vehicle, i, Data.Extras[i].enabled);
		}*/

		//VEHICLE::SET_VEHICLE_DOORS_LOCKED(Game.Vehicle, Data.DoorsLockState);

		ENTITY::FREEZE_ENTITY_POSITION(Game.Vehicle, FALSE);
		ENTITY::SET_ENTITY_DYNAMIC(Game.Vehicle, TRUE);
		std::cout << "[CVehicleEntity] Created Vehicle" << std::endl;
		Game.Created = true;
		
		return true;
	}

	std::cout << "[CVehicleEntity] Vehicle already created" << std::endl;
	return false;
}

// Gets the data thats only needed once thats not synced constantly
void CVehicleEntity::RequestData()
{
	RakNet::BitStream sData;
	sData.Write(Information.Id);
	CNetworkManager::GetRPC().Signal("RequestEntityData", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, CNetworkManager::GetSystemAddress(), false, false);
}

void CVehicleEntity::Destroy()
{
	if (Game.Vehicle)
		VEHICLE::DELETE_VEHICLE(&Game.Vehicle);

	Game.Created = false;

	if (Game.Blip)
		UI::REMOVE_BLIP(&Game.Blip);

	Game = {};
	Information = {};
	Data = {};
	Network = {};
	InterpolationData = {};

	Information.Id = -1;
}

void CVehicleEntity::Delete()
{
	if (Game.Vehicle)
		VEHICLE::DELETE_VEHICLE(&Game.Vehicle);

	if (Game.Blip)
		UI::REMOVE_BLIP(&Game.Blip);

	if (CNetworkManager::GetInterface()->GetMyGUID() == Network.Assigned)
	{
		RakNet::BitStream sData;
		sData.Write(Information.Id);
		CNetworkManager::GetRPC().Signal("DropEntityAssignment", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, CNetworkManager::GetSystemAddress(), false, false);
	}

	Game.Created = false;
}

void CVehicleEntity::Pulse()
{
	if (Game.Created && Information.Id != -1)
	{
		const int t_CurrentVehicle = CLocalPlayer::GetVehicleId();
		
		// Assignment System
		if (Network.Assigned == UNASSIGNED_RAKNET_GUID && Occupants[0] == -1)
		{
			if (CVector3::Distance(CLocalPlayer::GetPosition(), Data.Position) < 50.0f)
			{
				Network.Assigned = CNetworkManager::GetInterface()->GetMyGUID();

				RakNet::BitStream sData;
				sData.Write(Information.Id);
				CNetworkManager::GetRPC().Signal("TakeEntityAssignment", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, CNetworkManager::GetSystemAddress(), false, false);
			}
		}
		else
		{
			if (CNetworkManager::GetInterface()->GetMyGUID() == Network.Assigned)
			{
				if (CVector3::Distance(CLocalPlayer::GetPosition(), Data.Position) > 50.0f)
				{
					Network.Assigned = UNASSIGNED_RAKNET_GUID;

					RakNet::BitStream sData;
					sData.Write(Information.Id);
					CNetworkManager::GetRPC().Signal("DropEntityAssignment", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, CNetworkManager::GetSystemAddress(), false, false);
				}
			}
		}

		// Sync
		if ((t_CurrentVehicle != Information.Id || (t_CurrentVehicle == Information.Id && CLocalPlayer::GetSeat() != 0)) && CNetworkManager::GetInterface()->GetMyGUID() != Network.Assigned)
		{
			Interpolate();
		}
		else
		{
			if ((t_CurrentVehicle == Information.Id || CNetworkManager::GetInterface()->GetMyGUID() == Network.Assigned))
			{
				Vector3 Coordinates = ENTITY::GET_ENTITY_COORDS(Game.Vehicle, ENTITY::IS_ENTITY_DEAD(Game.Vehicle));
				Vector3 Rotation = ENTITY::GET_ENTITY_ROTATION(Game.Vehicle, 2);
				Vector3 Velocity = ENTITY::GET_ENTITY_VELOCITY(Game.Vehicle);

				Data.ForwardSpeed = ENTITY::GET_ENTITY_SPEED(Game.Vehicle);
				Data.Position = { Coordinates.x, Coordinates.y, Coordinates.z };
				Data.Rotation = { Rotation.x, Rotation.y, Rotation.z };
				Data.Velocity = { Velocity.x, Velocity.y, Velocity.z };

				Data.EngineState = VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(Game.Vehicle);

				Data.Gear = vdata.GetCurrentGear(Game.Vehicle);
				Data.RPM = vdata.GetCurrentRPM(Game.Vehicle);

				Data.Clutch = vdata.GetClutch(Game.Vehicle);
				Data.Turbo = vdata.GetTurbo(Game.Vehicle);
				Data.Acceleration = vdata.GetAcceleration(Game.Vehicle);
				Data.Brake = vdata.GetBrake(Game.Vehicle);

				Data.WheelSpeed = vdata.GetWheelSpeed(Game.Vehicle);
				Data.SteeringAngle = vdata.GetSteeringAngle(Game.Vehicle);
				Data.ForwardWheelAngle = vdata.GetForwardWheelAngle(Game.Vehicle);

				BitStream bitstream;
				bitstream.Write((unsigned char)ID_PACKET_VEHICLE);

				bitstream.Write(Information.Id);

				bitstream.Write(Data.Position.x);
				bitstream.Write(Data.Position.y);
				bitstream.Write(Data.Position.z);

				bitstream.Write(Data.ForwardSpeed);

				bitstream.Write(Data.EngineState);

				bitstream.Write(Data.Gear);
				bitstream.Write(Data.RPM);

				bitstream.Write(Data.Clutch);
				bitstream.Write(Data.Turbo);
				bitstream.Write(Data.Acceleration);
				bitstream.Write(Data.Brake);

				bitstream.Write(Data.WheelSpeed);
				bitstream.Write(Data.SteeringAngle);
				bitstream.Write(Data.ForwardWheelAngle);

				bitstream.Write(Data.Velocity.x);
				bitstream.Write(Data.Velocity.y);
				bitstream.Write(Data.Velocity.z);

				bitstream.Write(Data.Rotation.x);
				bitstream.Write(Data.Rotation.y);
				bitstream.Write(Data.Rotation.z);

				CNetworkManager::GetInterface()->Send(&bitstream, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 0, CNetworkManager::GetSystemAddress(), false);

				Network.LastSyncSent = timeGetTime();
			}
		}
	}
}

void CVehicleEntity::Update(Packet * packet)
{
	BitStream bitstream(packet->data + 1, packet->length + 1, false);

	bitstream.Read(Information.Id);

	RakWString model;
	bitstream.Read(model);
	Data.Model = CString::utf16ToUtf8(model.C_String());

	bitstream.Read(Data.Heading);

	bitstream.Read(Data.Position.x);
	bitstream.Read(Data.Position.y);
	bitstream.Read(Data.Position.z);

	bitstream.Read(Data.ForwardSpeed);

	bitstream.Read(Data.EngineState);

	bitstream.Read(Data.Gear);
	bitstream.Read(Data.RPM);

	bitstream.Read(Data.Clutch);
	bitstream.Read(Data.Turbo);
	bitstream.Read(Data.Acceleration);
	bitstream.Read(Data.Brake);

	bitstream.Read(Data.WheelSpeed);
	bitstream.Read(Data.SteeringAngle);
	bitstream.Read(Data.ForwardWheelAngle);

	bitstream.Read(Data.Velocity.x);
	bitstream.Read(Data.Velocity.y);
	bitstream.Read(Data.Velocity.z);

	bitstream.Read(Data.Rotation.x);
	bitstream.Read(Data.Rotation.y);
	bitstream.Read(Data.Rotation.z);

	for (int i = 0; i < SizeOfArray(Occupants); i++)
	{
		bitstream.Read(Occupants[i]);
	}
	
	if (CLocalPlayer::GetVehicleId() != Information.Id) {
		UpdateTargetPosition();
		SetTargetData();
		UpdateTargetRotation();

		Network.LastSyncReceived = timeGetTime();
	}
}

void CVehicleEntity::Interpolate()
{
	SetTargetPosition();
	SetTargetRotation();
	SetTargetData();
}

void CVehicleEntity::UpdateTargetPosition()
{
	if (Game.Created) {
		unsigned long CurrentTime = timeGetTime();
		unsigned int InterpolationTime = CurrentTime - Network.LastSyncReceived;

		// Get our position
		Vector3 Coordinates = ENTITY::GET_ENTITY_COORDS(Game.Vehicle, ENTITY::IS_ENTITY_DEAD(Game.Vehicle));
		CVector3 CurrentPosition = { Coordinates.x, Coordinates.y, Coordinates.z };

		// Set the target position
		CVector3 TargetPosition = { Data.Position.x, Data.Position.y, Data.Position.z };
		InterpolationData.Position.Target = TargetPosition;

		// Calculate the relative error
		InterpolationData.Position.Error = TargetPosition - CurrentPosition;

		// Apply the error over 400ms (i.e. 1/4 per 100ms)
		InterpolationData.Position.Error *= Math::Lerp<const float>(0.25f, Math::UnlerpClamped(100, InterpolationTime, 400), 1.0f);

		// Get the interpolation interval
		InterpolationData.Position.StartTime = CurrentTime;
		InterpolationData.Position.FinishTime = (CurrentTime + InterpolationTime);

		// Initialize the interpolation
		InterpolationData.Position.LastAlpha = 0.0f;
	}
}

void CVehicleEntity::SetTargetPosition()
{
	if (InterpolationData.Position.FinishTime != 0 && Game.Created) {
		// Get our position
		Vector3 Coordinates = ENTITY::GET_ENTITY_COORDS(Game.Vehicle, ENTITY::IS_ENTITY_DEAD(Game.Vehicle));
		CVector3 vecCurrentPosition = { Coordinates.x, Coordinates.y, Coordinates.z };

		// Get the factor of time spent from the interpolation start to the current time.
		unsigned long CurrentTime = timeGetTime();
		float fAlpha = Math::Unlerp(InterpolationData.Position.StartTime, CurrentTime, InterpolationData.Position.FinishTime);

		// Don't let it overcompensate the error
		fAlpha = Math::Clamp(0.0f, fAlpha, 1.0f);

		// Get the current error portion to compensate
		float fCurrentAlpha = (fAlpha - InterpolationData.Position.LastAlpha);
		InterpolationData.Position.LastAlpha = fAlpha;

		// Apply the error compensation
		CVector3 vecCompensation = Math::Lerp(CVector3(), fCurrentAlpha, InterpolationData.Position.Error);

		// If we finished compensating the error, finish it for the next pulse
		if (fAlpha == 1.0f)
			InterpolationData.Position.FinishTime = 0;

		// Calculate the new position
		CVector3 vecNewPosition = vecCurrentPosition + vecCompensation;

		// Check if the distance to interpolate is too far
		if (CVector3::Distance(vecCurrentPosition, InterpolationData.Position.Target) > 150.0f)
		{
			// Abort all interpolation
			InterpolationData.Position.FinishTime = 0;
			vecNewPosition = InterpolationData.Position.Target;
		}

		// Set our new position
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(Game.Vehicle, vecNewPosition.x, vecNewPosition.y, vecNewPosition.z, false, false, false);
		ENTITY::SET_ENTITY_VELOCITY(Game.Vehicle, Data.Velocity.x, Data.Velocity.y, Data.Velocity.z);
	}
}

void CVehicleEntity::UpdateTargetRotation()
{
	if (Game.Created)
	{
		unsigned int interpolationtime = timeGetTime() - Network.LastSyncReceived;
		unsigned long CurrentTime = timeGetTime();

		// Get our rotation
		Vector3 CurrentRotationVec = ENTITY::GET_ENTITY_ROTATION(Game.Vehicle, 2);
		CVector3 CurrentRotation(CurrentRotationVec.x, CurrentRotationVec.y, CurrentRotationVec.z);

		// Set the target rotation
		CVector3 TargetRotation = { Data.Rotation.x, Data.Rotation.y, Data.Rotation.z };
		InterpolationData.Rotation.Target = TargetRotation;

		// Get the error
		//InterpolationData.Rotation.Error = Math::GetOffsetDegrees(vecLocalRotation, vecRotation);
		InterpolationData.Rotation.Error = TargetRotation - CurrentRotation;
		InterpolationData.Rotation.Error *= Math::Lerp < const float >(0.40f, Math::UnlerpClamped(100, interpolationtime, 400), 1.0f);

		// Get the interpolation interval
		InterpolationData.Rotation.StartTime = CurrentTime;
		InterpolationData.Rotation.FinishTime = (CurrentTime + interpolationtime);

		// Initialize the interpolation
		InterpolationData.Rotation.LastAlpha = 0.0f;
	}
}

void CVehicleEntity::SetTargetRotation()
{
	if (Game.Created)
	{
		if (InterpolationData.Rotation.FinishTime != 0 && Game.Created)
		{
			// Get our rotation
			Vector3 CurrentRotationVec = ENTITY::GET_ENTITY_ROTATION(Game.Vehicle, 2);
			CVector3 CurrentRotation(CurrentRotationVec.x, CurrentRotationVec.y, CurrentRotationVec.z);

			if (InterpolationData.Rotation.Target.z > 178.0f || InterpolationData.Rotation.Target.z < -178.0f)
			{
				ENTITY::SET_ENTITY_ROTATION(Game.Vehicle, Data.Rotation.x, Data.Rotation.y, Data.Rotation.z, 2, true);
				InterpolationData.Rotation.FinishTime = 0;
			}
			else
			{
				// Get the factor of time spent from the interpolation start to the current time.
				unsigned long CurrentTime = timeGetTime();
				float fAlpha = Math::Unlerp(InterpolationData.Rotation.StartTime, CurrentTime, InterpolationData.Rotation.FinishTime);

				// Don't let it overcompensate the error
				fAlpha = Math::Clamp(0.0f, fAlpha, 1.0f);

				// Get the current error portion to compensate
				float fCurrentAlpha = (fAlpha - InterpolationData.Rotation.LastAlpha);
				InterpolationData.Rotation.LastAlpha = fAlpha;

				// Apply the error compensation
				CVector3 vecCompensation = Math::Lerp(CVector3(), fCurrentAlpha, InterpolationData.Rotation.Error);

				// If we finished compensating the error, finish it for the next pulse
				if (fAlpha == 1.0f)
					InterpolationData.Rotation.FinishTime = 0;

				// Calculate the new position
				CVector3 vecNewRotation = CurrentRotation + vecCompensation;

				// Set our new position
				ENTITY::SET_ENTITY_ROTATION(Game.Vehicle, vecNewRotation.x, vecNewRotation.y, vecNewRotation.z, 2, true);
			}
		}
	}
}

void CVehicleEntity::SetTargetData()
{
	if (Game.Created)
	{
		if (VEHICLE::GET_IS_VEHICLE_ENGINE_RUNNING(Game.Vehicle) != Data.EngineState)
		{
			VEHICLE::SET_VEHICLE_ENGINE_ON(Game.Vehicle, Data.EngineState, false, true);
			//VEHICLE::SET_VEHICLE_UNDRIVEABLE(Game.Vehicle, !Data.EngineState);
		}

		vdata.SetCurrentGear(Game.Vehicle, Data.Gear);
		vdata.SetCurrentRPM(Game.Vehicle, Data.RPM);

		vdata.SetClutch(Game.Vehicle, Data.Clutch);
		vdata.SetTurbo(Game.Vehicle, Data.Turbo);
		vdata.SetAcceleration(Game.Vehicle, Data.Acceleration);
		vdata.SetBrake(Game.Vehicle, Data.Brake);

		vdata.SetSteeringAngle(Game.Vehicle, Data.SteeringAngle);
		vdata.SetForwardWheelAngle(Game.Vehicle, Data.ForwardWheelAngle);
		vdata.SetWheelSpeed(Game.Vehicle, Data.WheelSpeed);
	}
}


Vehicle CVehicleEntity::getClosestVehicleFromPedPos(Ped ped, int maxDistance)
{
	Vector3 ppos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(ped, 0.0, 0.0, -1.0f);
	CVector3 playerPos = CVector3(ppos.x, ppos.y, ppos.z);

	Vehicle vehicle = 0;
	float lastMaxDistance = maxDistance;

	if (!g_Vehicles.empty())
	{
		for (int i = 0; i < g_Vehicles.size(); i++)
		{
			if (g_Vehicles[i].GetId() != -1)
			{
				Vector3 vpos = ENTITY::GET_OFFSET_FROM_ENTITY_IN_WORLD_COORDS(g_Vehicles[i].GetEntity(), 0.0, 0.0, 0.0f);
				CVector3 vehiclePos = CVector3(vpos.x, vpos.y, vpos.z);

				float distance = Math::GetDistanceBetweenPoints3D(ppos.x, ppos.y, ppos.z, vpos.x, vpos.y, vpos.z);
				if (distance < lastMaxDistance)
				{
					lastMaxDistance = distance;
					vehicle = g_Vehicles[i].GetEntity();
				}

			}
		}
	}

	return vehicle;
}

void CVehicleEntity::SetColor(const int layer, const int painttype, const int color)
{
	if (layer == 1)
	{
		Data.Colors[0].type = painttype;
		Data.Colors[0].color = color;
		Data.Colors[0].custom = false;
	}
	else if (layer == 2)
	{
		Data.Colors[1].type = painttype;
		Data.Colors[1].color = color;
		Data.Colors[1].custom = false;
	}

	if (Game.Created)
	{
		if(layer == 1)
			VEHICLE::SET_VEHICLE_MOD_COLOR_1(Game.Vehicle, painttype, color, 0);
		else if(layer == 2)
			VEHICLE::SET_VEHICLE_MOD_COLOR_2(Game.Vehicle, painttype, color);
	}
}

void CVehicleEntity::SetColor(const int layer, const Color color)
{
	if (layer == 1)
	{
		Data.Colors[0].custom = true;
		Data.Colors[0].customCol = color;
	}
	else if (layer == 2)
	{
		Data.Colors[1].custom = true;
		Data.Colors[1].customCol = color;
	}

	if (Game.Created)
	{
		if (layer == 1)
			VEHICLE::SET_VEHICLE_CUSTOM_PRIMARY_COLOUR(Game.Vehicle, color.Red, color.Green, color.Blue);
		else if (layer == 2)
			VEHICLE::SET_VEHICLE_CUSTOM_SECONDARY_COLOUR(Game.Vehicle, color.Red, color.Green, color.Blue);
	}
}

void CVehicleEntity::SetNumberPlate(const std::wstring plate)
{
	Data.Plate = plate;

	if(Game.Created)
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Game.Vehicle, (char *)CString::utf16ToUtf8(Data.Plate).c_str());
}

void CVehicleEntity::SetMod(const int modType, const int modIndex)
{
	Data.Mods[modType].index = modIndex;

	if (Game.Created)
		VEHICLE::SET_VEHICLE_MOD(Game.Vehicle, modType, modIndex, false);
}

void CVehicleEntity::SetEngineState(const bool state)
{
	Data.ForceEngineState = state;
	Data.EngineState = state;

	if (Game.Created) 
	{
		VEHICLE::SET_VEHICLE_ENGINE_ON(Game.Vehicle, state, true, true);
		VEHICLE::SET_VEHICLE_UNDRIVEABLE(Game.Vehicle, !state);
	}
}

void CVehicleEntity::SetDoorsLockState(const int state)
{
	Data.DoorsLockState = state;

	if (Game.Created)
	{
		VEHICLE::SET_VEHICLE_DOORS_LOCKED(Game.Vehicle, state);
	}
}

void CVehicleEntity::SetNumberPlateStyle(const int style)
{
	Data.PlateStyle = style;

	if (Game.Created)
	{
		VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT_INDEX(Game.Vehicle, style);
	}
}

void CVehicleEntity::SetExtra(const int extra, const bool toggle)
{
	Data.Extras[extra].enabled = !toggle;

	if (Game.Created)
	{
		VEHICLE::SET_VEHICLE_EXTRA(Game.Vehicle, extra, !toggle);
	}
}