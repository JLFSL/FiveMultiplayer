#include "stdafx.h"

int CObjectEntity::Amount = 0;

CObjectEntity::CObjectEntity()
{
	Data.Model.textureIndex = 0;

	Network.Assigned = UNASSIGNED_RAKNET_GUID;
}

void CObjectEntity::Create(std::wstring model, CVector3 position, CVector3 rotation, bool dynamic)
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

	std::cout << "[CObjectEntity] Created Object [" << Information.Id << "] with model " << Data.Model.Model.c_str() << " [Dynamic: " << dynamic << "] at " << Data.Position.x << ", " << Data.Position.y << ", " << Data.Position.z << std::endl;
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

	std::cout << "[CObjectEntity] Created Object [" << Information.Id << "] with Hash " << Data.Model.ModelHash << " [Dynamic: " << dynamic << "] at " << Data.Position.x << ", " << Data.Position.y << ", " << Data.Position.z << std::endl;
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

			bitstream.Write(Data.Position.x);
			bitstream.Write(Data.Position.y);
			bitstream.Write(Data.Position.z);

			bitstream.Write(Data.Velocity.x);
			bitstream.Write(Data.Velocity.y);
			bitstream.Write(Data.Velocity.z);

			bitstream.Write(Data.Rotation.x);
			bitstream.Write(Data.Rotation.y);
			bitstream.Write(Data.Rotation.z);

			if (!g_Players.empty())
			{
				for (int i = 0; i < g_Players.size(); i++)
				{
					CVector3 pos = g_Players[i].GetPosition();
					if (g_Players[i].GetId() != -1 && Math::GetDistanceBetweenPoints2D(Data.Position.x, Data.Position.y, pos.x, pos.y) <= 1000.0f)
					{
						g_Server->GetNetworkManager()->GetInterface()->Send(&bitstream, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 0, g_Players[i].GetGUID, false);
					}
				}
			}
			//g_Server->GetNetworkManager()->GetInterface()->Send(&bitstream, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 0, UNASSIGNED_RAKNET_GUID, true);

			Network.LastSyncSent = std::chrono::system_clock::now();
		}
	}
}

void CObjectEntity::Update(Packet *packet)
{
	BitStream bitstream(packet->data + 1, packet->length + 1, false);

	bitstream.Read(Information.Id);

	bitstream.Read(Data.Position.x);
	bitstream.Read(Data.Position.y);
	bitstream.Read(Data.Position.z);

	bitstream.Read(Data.Velocity.x);
	bitstream.Read(Data.Velocity.y);
	bitstream.Read(Data.Velocity.z);

	bitstream.Read(Data.Rotation.x);
	bitstream.Read(Data.Rotation.y);
	bitstream.Read(Data.Rotation.z);
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

	g_Server->GetNetworkManager()->GetRPC().Signal("SetTextureVariation", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);
}