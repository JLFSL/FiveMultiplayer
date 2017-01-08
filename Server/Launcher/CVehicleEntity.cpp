#include "stdafx.h"

int CVehicleEntity::Amount = 0;

void CVehicleEntity::Create(string model, CVector3 position, float heading)
{
	CServerEntity newServerEntity;
	newServerEntity.SetType(newServerEntity.Vehicle);

	Data.Model = model;
	Data.Position = position;
	Data.Heading = heading;
	Information.Id = newServerEntity.Create();

	g_Entities.push_back(newServerEntity);

	Amount++;

	cout << "[CVehicleEntity] Create Vehicle [" << Information.Id << "] " << Data.Model.c_str() << " at " << Data.Position.fX << ", " << Data.Position.fY << ", " << Data.Position.fZ << endl;
	cout << "[CVehicleEntity] " << Amount << " vehicles in the world." << endl;

	Network.LastSyncSent = timeGetTime();
	Network.Synchronized = true;
}

void CVehicleEntity::Destroy()
{
	cout << "[CVehicleEntity] Removing Vehicle [" << Information.Id << "] " << Data.Model.c_str() << endl;

	Information = {};
	Data = {};
	Network = {};

	Information.Id = -1;

	Amount--;

	cout << "[CVehicleEntity] " << Amount << " vehicles in the world." << endl;
}

void CVehicleEntity::Pulse()
{
	if (Network.LastSyncSent + (1000 / CServer::GetInstance()->GetSyncRate()) <= timeGetTime())
	{
		BitStream bitstream;
		bitstream.Write((unsigned char)ID_PACKET_VEHICLE);

		bitstream.Write(Information.Id);

		bitstream.Write(RakString(Data.Model.c_str()));

		//bitstream.Write(Information.Driver);

		bitstream.Write(Data.Heading);

		bitstream.Write(Data.Position.fX);
		bitstream.Write(Data.Position.fY);
		bitstream.Write(Data.Position.fZ);

		bitstream.Write(Data.ForwardSpeed);

		bitstream.Write(Data.Velocity.fX);
		bitstream.Write(Data.Velocity.fY);
		bitstream.Write(Data.Velocity.fZ);

		bitstream.Write(Data.Quaternion.fX);
		bitstream.Write(Data.Quaternion.fY);
		bitstream.Write(Data.Quaternion.fZ);
		bitstream.Write(Data.Quaternion.fW);

		g_Network->GetInterface()->Send(&bitstream, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 0, UNASSIGNED_RAKNET_GUID, true);

		Network.LastSyncSent = timeGetTime();
	}
}

void CVehicleEntity::Update(Packet *packet)
{
	BitStream bitstream(packet->data + 1, packet->length + 1, false);

	bitstream.Read(Information.Id);

	RakString model;
	bitstream.Read(model);
	Data.Model = model.C_String();

	//bitstream.Read(Information.Driver);

	bitstream.Read(Data.Position.fX);
	bitstream.Read(Data.Position.fY);
	bitstream.Read(Data.Position.fZ);

	bitstream.Read(Data.ForwardSpeed);

	bitstream.Read(Data.Velocity.fX);
	bitstream.Read(Data.Velocity.fY);
	bitstream.Read(Data.Velocity.fZ);

	bitstream.Read(Data.Quaternion.fX);
	bitstream.Read(Data.Quaternion.fY);
	bitstream.Read(Data.Quaternion.fZ);
	bitstream.Read(Data.Quaternion.fW);
}