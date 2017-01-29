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