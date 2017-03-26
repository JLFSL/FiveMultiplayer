#include "stdafx.h"

int CObjectEntity::Amount = 0;

CObjectEntity::CObjectEntity()
{
	Data.Model.textureIndex = 0;

	Network.Assigned = UNASSIGNED_RAKNET_GUID;
}

void CObjectEntity::Create(std::string model, CVector3 position, CVector3 rotation, bool dynamic)
{
	CServerEntity newServerEntity;
	newServerEntity.SetType(newServerEntity.Object);

	Data.Model.Model = model;
	Data.Model.ModelHash = 0;
	Data.Position = position;
	Data.Rotation = rotation;
	Information.Id = newServerEntity.Create();

	g_Entities.push_back(newServerEntity);

	Amount++;

	std::cout << "[CObjectEntity] Created Object [" << Information.Id << "] with model " << Data.Model.Model.c_str() << " [Dynamic: " << dynamic << "] at " << Data.Position.fX << ", " << Data.Position.fY << ", " << Data.Position.fZ << std::endl;
	std::cout << "[CObjectEntity] " << Amount << " objects in the world." << std::endl;

	Network.LastSyncSent = std::chrono::system_clock::now();
	Network.Synchronized = true;
}

void CObjectEntity::Create(int hash, CVector3 position, CVector3 rotation, bool dynamic)
{
	CServerEntity newServerEntity;
	newServerEntity.SetType(newServerEntity.Object);

	Data.Model.ModelHash = hash;
	Data.Position = position;
	Data.Rotation = rotation;
	Information.Id = newServerEntity.Create();

	g_Entities.push_back(newServerEntity);

	Amount++;

	std::cout << "[CObjectEntity] Created Object [" << Information.Id << "] with Hash " << Data.Model.ModelHash << " [Dynamic: " << dynamic << "] at " << Data.Position.fX << ", " << Data.Position.fY << ", " << Data.Position.fZ << std::endl;
	std::cout << "[CObjectEntity] " << Amount << " objects in the world." << std::endl;

	Network.LastSyncSent = std::chrono::system_clock::now();
	Network.Synchronized = true;
}

void CObjectEntity::Destroy()
{
	std::cout << "[CObjectEntity] Removing Object [" << Information.Id << "] " << Data.Model.Model.c_str() << std::endl;

	Information = {};
	Data = {};
	Network = {};

	Information.Id = -1;

	Amount--;

	std::cout << "[CObjectEntity] " << Amount << " objects in the world." << std::endl;
}

void CObjectEntity::Pulse()
{
	if (Data.Model.Dynamic)
	{
		if (std::chrono::duration_cast<std::chrono::milliseconds>(Network.LastSyncSent.time_since_epoch()).count() + (1000 / CServer::GetInstance()->GetSyncRate())
			<= std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count())
		{
			BitStream bitstream;
			bitstream.Write((unsigned char)ID_PACKET_OBJECT);

			bitstream.Write(Information.Id);

			bitstream.Write(Data.Position.fX);
			bitstream.Write(Data.Position.fY);
			bitstream.Write(Data.Position.fZ);

			bitstream.Write(Data.Velocity.fX);
			bitstream.Write(Data.Velocity.fY);
			bitstream.Write(Data.Velocity.fZ);

			bitstream.Write(Data.Rotation.fX);
			bitstream.Write(Data.Rotation.fY);
			bitstream.Write(Data.Rotation.fZ);

			g_Server->GetNetworkManager()->GetInterface()->Send(&bitstream, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 0, UNASSIGNED_RAKNET_GUID, true);

			Network.LastSyncSent = std::chrono::system_clock::now();
		}
	}
}

void CObjectEntity::Update(Packet *packet)
{
	BitStream bitstream(packet->data + 1, packet->length + 1, false);

	bitstream.Read(Information.Id);

	bitstream.Read(Data.Position.fX);
	bitstream.Read(Data.Position.fY);
	bitstream.Read(Data.Position.fZ);

	bitstream.Read(Data.Velocity.fX);
	bitstream.Read(Data.Velocity.fY);
	bitstream.Read(Data.Velocity.fZ);

	bitstream.Read(Data.Rotation.fX);
	bitstream.Read(Data.Rotation.fY);
	bitstream.Read(Data.Rotation.fZ);
}

void CObjectEntity::RequestData(RakNetGUID requester)
{
	RakNet::BitStream sData;

	// Assignment Data
	sData.Write(Information.Id);
	sData.Write(Network.Assigned);
	g_Server->GetNetworkManager()->GetRPC().Signal("TakeEntityAssignment", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);

	sData.Reset();

	sData.Write(Information.Id);
	sData.Write(Data.Model.textureIndex);

	g_Server->GetNetworkManager()->GetRPC().Signal("SetTextureVariation", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);
}