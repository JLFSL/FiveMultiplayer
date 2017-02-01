#include "stdafx.h"

int CVehicleEntity::Amount = 0;

CVehicleEntity::CVehicleEntity()
{
	Network.Assigned = UNASSIGNED_RAKNET_GUID;

	for (int i = 0; i < SizeOfArray(Occupants); i++)
	{
		Occupants[i] = -1;
	}
}

void CVehicleEntity::Create(std::string model, CVector3 position, float heading)
{
	CServerEntity newServerEntity;
	newServerEntity.SetType(newServerEntity.Vehicle);
	newServerEntity.SetEntity(this);

	Data.Model = model;
	Data.Position = position;
	Data.Heading = heading;
	Information.Id = newServerEntity.Create();

	g_Entities.push_back(newServerEntity);

	Amount++;

	std::cout << "[CVehicleEntity] Create Vehicle [" << Information.Id << "] " << Data.Model.c_str() << " at " << Data.Position.fX << ", " << Data.Position.fY << ", " << Data.Position.fZ << std::endl;
	std::cout << "[CVehicleEntity] " << Amount << " vehicles in the world." << std::endl;

	Network.LastSyncSent = std::chrono::system_clock::now();
	Network.Synchronized = true;
}

void CVehicleEntity::Destroy()
{
	std::cout << "[CVehicleEntity] Removing Vehicle [" << Information.Id << "] " << Data.Model.c_str() << std::endl;

	Information = {};
	Data = {};
	Network = {};

	Information.Id = -1;

	Amount--;

	std::cout << "[CVehicleEntity] " << Amount << " vehicles in the world." << std::endl;
}

void CVehicleEntity::Pulse()
{
	if (std::chrono::duration_cast<std::chrono::milliseconds>(Network.LastSyncSent.time_since_epoch()).count() + (1000 / CServer::GetInstance()->GetSyncRate()) 
		<= std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count())
	{
		BitStream bitstream;
		bitstream.Write((unsigned char)ID_PACKET_VEHICLE);

		bitstream.Write(Information.Id);

		bitstream.Write(RakString(Data.Model.c_str()));

		bitstream.Write(Data.Heading);

		bitstream.Write(Data.Position.fX);
		bitstream.Write(Data.Position.fY);
		bitstream.Write(Data.Position.fZ);

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
		

		bitstream.Write(Data.Velocity.fX);
		bitstream.Write(Data.Velocity.fY);
		bitstream.Write(Data.Velocity.fZ);

		bitstream.Write(Data.Quaternion.fX);
		bitstream.Write(Data.Quaternion.fY);
		bitstream.Write(Data.Quaternion.fZ);
		bitstream.Write(Data.Quaternion.fW);

		for (int i = 0; i < SizeOfArray(Occupants); i++)
		{
			bitstream.Write(Occupants[i]);
		}

		g_Server->GetNetworkManager()->GetInterface()->Send(&bitstream, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 0, UNASSIGNED_RAKNET_GUID, true);

		Network.LastSyncSent = std::chrono::system_clock::now();
	}
}

void CVehicleEntity::Update(Packet *packet)
{
	BitStream bitstream(packet->data + 1, packet->length + 1, false);

	bitstream.Read(Information.Id);

	//bitstream.Read(Information.Driver);

	bitstream.Read(Data.Position.fX);
	bitstream.Read(Data.Position.fY);
	bitstream.Read(Data.Position.fZ);

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

	bitstream.Read(Data.Velocity.fX);
	bitstream.Read(Data.Velocity.fY);
	bitstream.Read(Data.Velocity.fZ);

	bitstream.Read(Data.Quaternion.fX);
	bitstream.Read(Data.Quaternion.fY);
	bitstream.Read(Data.Quaternion.fZ);
	bitstream.Read(Data.Quaternion.fW);

}

void CVehicleEntity::RequestData(RakNetGUID requester)
{
	RakNet::BitStream sData;

	// Assignment Data
	sData.Write(Information.Id);
	sData.Write(Network.Assigned);
	g_Server->GetNetworkManager()->GetRPC().Signal("TakeEntityAssignment", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);
	
	sData.Reset();
}