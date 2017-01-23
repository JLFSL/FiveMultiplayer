#include "stdafx.h"

/*PREP For moving away from bundling everything in stdafx
#include <iostream>

// Vendor.RakNet
#include <RakNet/BitStream.h>

#include "RPCEntity.h"
*/
namespace RPC
{
	namespace Entity
	{
		void TakeEntityAssignment(RakNet::BitStream *bitStream, RakNet::Packet *packet)
		{
			int entity;
			
			bitStream->Read(entity);

			if (ServerEntity::IsValid(entity))
			{
				ServerEntity::SetAssignee(entity, packet->guid);

				RakNet::BitStream sData;
				sData.Write(entity);
				sData.Write(packet->guid);
				CNetworkManager::instance()->GetRPC().Signal("TakeEntityAssignment", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->guid, true, false);
			}
		}

		void DropEntityAssignment(RakNet::BitStream *bitStream, RakNet::Packet *packet)
		{
			int entity;

			bitStream->Read(entity);

			if (ServerEntity::IsValid(entity))
			{
				if (ServerEntity::GetAssignee(entity) == packet->guid)
				{
					ServerEntity::SetAssignee(entity, UNASSIGNED_RAKNET_GUID);

					RakNet::BitStream sData;
					sData.Write(entity);
					CNetworkManager::instance()->GetRPC().Signal("DropEntityAssignment", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->guid, true, false);
				}
			}
		}

		void RequestData(RakNet::BitStream *bitStream, RakNet::Packet *packet)
		{
			int entity;

			bitStream->Read(entity);

			if (ServerEntity::IsValid(entity))
			{
				ServerEntity::RequestData(entity, packet->guid);
			}
		}
	}
}