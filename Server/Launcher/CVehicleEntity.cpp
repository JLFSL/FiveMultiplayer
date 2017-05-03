#include "stdafx.h"

int CVehicleEntity::Amount = 0;

CVehicleEntity::CVehicleEntity()
{
	Network.Assigned = UNASSIGNED_RAKNET_GUID;

	Data = Data;
	Information = Information;

	for (int i = 0; i < SizeOfArray(Occupants); i++)
	{
		Occupants[i] = -1;
	}
}

void CVehicleEntity::Create(std::wstring model, CVector3 position, float heading)
{
	CServerEntity newServerEntity;
	newServerEntity.SetType(newServerEntity.Vehicle);

	Data.Model = model;
	Data.Position = position;
	Data.Heading = heading;
	Data.Rotation = CVector3(0, 0, heading);
	Information.Id = newServerEntity.Create();

	g_Entities.push_back(newServerEntity);

	Amount++;

	std::wcout << L"[CVehicleEntity] Create Vehicle [" << Information.Id << L"] " << Data.Model.c_str() << L" at " << Data.Position.x << L", " << Data.Position.y << L", " << Data.Position.z << std::endl;
	std::wcout << L"[CVehicleEntity] " << Amount << L" vehicles in the world." << std::endl;

	Network.LastSyncSent = std::chrono::system_clock::now();
	Network.Synchronized = true;
}

void CVehicleEntity::Create(std::wstring model, CVector3 position, CVector3 rotation)
{
	CServerEntity newServerEntity;
	newServerEntity.SetType(newServerEntity.Vehicle);

	Data.Model = model;
	Data.Position = position;
	Data.Rotation = rotation;
	Information.Id = newServerEntity.Create();

	g_Entities.push_back(newServerEntity);

	Amount++;

	std::wcout << L"[CVehicleEntity] Create Vehicle [" << Information.Id << L"] " << Data.Model.c_str() << L" at " << Data.Position.x << L", " << Data.Position.y << L", " << Data.Position.z << std::endl;
	std::wcout << L"[CVehicleEntity] " << Amount << L" vehicles in the world." << std::endl;

	Network.LastSyncSent = std::chrono::system_clock::now();
	Network.Synchronized = true;
}

void CVehicleEntity::Destroy()
{
	std::wcout << L"[CVehicleEntity] Removing Vehicle [" << Information.Id << L"] " << Data.Model.c_str() << std::endl;

	Information = {};
	Data = {};
	Network = {};

	Information.Id = -1;

	Amount--;

	std::wcout << L"[CVehicleEntity] " << Amount << L" vehicles in the world." << std::endl;
}

void CVehicleEntity::Pulse()
{
	if (std::chrono::duration_cast<std::chrono::milliseconds>(Network.LastSyncSent.time_since_epoch()).count() + (1000 / CServer::GetInstance()->GetSyncRate()) 
		<= std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count())
	{
		BitStream bitstream;
		bitstream.Write((unsigned char)ID_PACKET_VEHICLE);

		bitstream.Write(Information.Id);

		bitstream.Write(RakWString(Data.Model.c_str()));

		bitstream.Write(Data.Heading);

		bitstream.Write(Data.Position.x);
		bitstream.Write(Data.Position.y);
		bitstream.Write(Data.Position.z);

		bitstream.Write(Data.ForwardSpeed);

		bitstream.Write(true);

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

		bitstream.Write(Data.EngineHealth);
		bitstream.Write(Data.FuelTankHealth);

		for (int i = 0; i < SizeOfArray(Occupants); i++)
		{
			bitstream.Write(Occupants[i]);
		}

		if (!g_Players.empty())
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				CVector3 pos = g_Players[i].GetPosition();
				if (g_Players[i].GetId() != -1 && Math::GetDistanceBetweenPoints2D(Data.Position.x, Data.Position.y, pos.x, pos.y) <= 1000.0f)
				{
					g_Server->GetNetworkManager()->GetInterface()->Send(&bitstream, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 0, g_Players[i].GetGUID(), false);
				}
			}
		}
		//g_Server->GetNetworkManager()->GetInterface()->Send(&bitstream, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 0, UNASSIGNED_RAKNET_GUID, true);

		Network.LastSyncSent = std::chrono::system_clock::now();
	}
}

void CVehicleEntity::Update(Packet *packet)
{
	BitStream bitstream(packet->data + 1, packet->length + 1, false);

	bitstream.Read(Information.Id);

	//bitstream.Read(Information.Driver);

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

	bitstream.Read(Data.EngineHealth);
	bitstream.Read(Data.FuelTankHealth);
}

void CVehicleEntity::RequestData(RakNetGUID requester)
{
	RakNet::BitStream sData;

	// Assignment Data
	sData.Write(Information.Id);
	sData.Write(Network.Assigned);
	g_Server->GetNetworkManager()->GetRPC().Signal("TakeEntityAssignment", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);
	
	if (!Data.Colors[0].custom)
	{
		sData.Reset();
		sData.Write(Information.Id);
		sData.Write(1);
		sData.Write(Data.Colors[0].type);
		sData.Write(Data.Colors[0].color);

		g_Server->GetNetworkManager()->GetRPC().Signal("SetStandardColor", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);
	}
	else
	{
		sData.Reset();
		sData.Write(Information.Id);
		sData.Write(1);
		sData.Write(Data.Colors[0].customCol.Red);
		sData.Write(Data.Colors[0].customCol.Green);
		sData.Write(Data.Colors[0].customCol.Blue);

		g_Server->GetNetworkManager()->GetRPC().Signal("SetCustomColor", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);
	}

	if (!Data.Colors[1].custom)
	{
		sData.Reset();
		sData.Write(Information.Id);
		sData.Write(2);
		sData.Write(Data.Colors[1].type);
		sData.Write(Data.Colors[1].color);

		g_Server->GetNetworkManager()->GetRPC().Signal("SetStandardColor", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);
	}
	else
	{
		sData.Reset();
		sData.Write(Information.Id);
		sData.Write(2);
		sData.Write(Data.Colors[1].customCol.Red);
		sData.Write(Data.Colors[1].customCol.Green);
		sData.Write(Data.Colors[1].customCol.Blue);

		g_Server->GetNetworkManager()->GetRPC().Signal("SetCustomColor", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);
	}

	sData.Reset();
	sData.Write(Information.Id);
	sData.Write(RakNet::RakWString(Data.Plate.c_str()));

	g_Server->GetNetworkManager()->GetRPC().Signal("SetNumberPlate", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);

	for (int i = 0; i < SizeOfArray(Data.Mods); i++)
	{
		sData.Reset();
		sData.Write(Information.Id);
		sData.Write(i);
		sData.Write(Data.Mods[i].index);

		g_Server->GetNetworkManager()->GetRPC().Signal("SetMod", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);
	}

	if (Data.ForcedEngineState > -1)
	{
		sData.Reset();
		sData.Write(Information.Id);
		sData.Write(Data.ForcedEngineState);

		g_Server->GetNetworkManager()->GetRPC().Signal("SetEngineState", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);
	}

	sData.Reset();
	sData.Write(Information.Id);
	sData.Write(Data.DoorsLockState);

	g_Server->GetNetworkManager()->GetRPC().Signal("SetDoorsLockState", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);

	sData.Reset();
	sData.Write(Information.Id);
	sData.Write(Data.PlateStyle);

	g_Server->GetNetworkManager()->GetRPC().Signal("SetNumberPlateStyle", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);

	for (int i = 1; i < SizeOfArray(Data.Extras); i++)
	{
		sData.Reset();
		sData.Write(Information.Id);
		sData.Write(i);
		sData.Write(!Data.Extras[i].enabled);

		g_Server->GetNetworkManager()->GetRPC().Signal("SetExtra", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);
	}

	sData.Reset();
	sData.Write(Information.Id);
	sData.Write(Data.EngineHealth);
	g_Server->GetNetworkManager()->GetRPC().Signal("SetEngineHealth", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);

	sData.Reset();
	sData.Write(Information.Id);
	sData.Write(Data.FuelTankHealth);
	g_Server->GetNetworkManager()->GetRPC().Signal("SetFuelTankHealth", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);

	sData.Reset();
	sData.Write(Information.Id);
	sData.Write(Data.TaxiLight);
	g_Server->GetNetworkManager()->GetRPC().Signal("SetTaxiLightState", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);

	sData.Reset();
	sData.Write(Information.Id);
	sData.Write(0);
	sData.Write(Data.RightIndicator);
	g_Server->GetNetworkManager()->GetRPC().Signal("SetIndicatorState", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);

	sData.Reset();
	sData.Write(Information.Id);
	sData.Write(1);
	sData.Write(Data.LeftIndicator);
	g_Server->GetNetworkManager()->GetRPC().Signal("SetIndicatorState", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);

	sData.Reset();
	sData.Write(Information.Id);
	sData.Write(Data.InteriorLight);
	g_Server->GetNetworkManager()->GetRPC().Signal("SetInteriorLightState", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);
	
	sData.Reset();
}

void CVehicleEntity::SetColor(const int layer, const int painttype, const int color)
{
	if (layer == 1)
	{
		Data.Colors[0].type = painttype;
		Data.Colors[0].color = color;
		Data.Colors[0].custom = false;
	}
	else if(layer == 2)
	{
		Data.Colors[1].type = painttype;
		Data.Colors[1].color = color;
		Data.Colors[1].custom = false;
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
}