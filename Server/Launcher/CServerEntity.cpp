#include "stdafx.h"

int CServerEntity::Create()
{
	if (g_Entities.empty())
		Data.Id = 0;
	else
		Data.Id = g_Entities.size();

	return Data.Id;
}

void CServerEntity::SetType(Type type)
{
	Data.type = type;
}

void CServerEntity::Destroy()
{
	RakNet::BitStream sData;
	switch (Data.type)
	{
	case Player:
			std::cout << "[CServerEntity::Destroy] Can not destroy a player!" << std::endl;
		break;
	case Vehicle:
		if (Data.vehicle)
		{
			Data.vehicle->Destroy();

			sData.Write(Data.Id);
			g_Server->GetNetworkManager()->GetRPC().Signal("DestroyEntity", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

			Data.vehicle = nullptr;
		}
		else
			std::cout << "[CServerEntity::Destroy] Invalid entity " << Data.Id << " of type Vehicle." << std::endl;
		break;
	case Object:
		if (Data.object)
		{
			Data.object->Destroy();

			sData.Write(Data.Id);
			g_Server->GetNetworkManager()->GetRPC().Signal("DestroyEntity", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

			Data.object = nullptr;
		}
		else
			std::cout << "[CServerEntity::Destroy] Invalid entity " << Data.Id << " of type Object." <<std::endl;
		break;
	default:
		std::cout << "[CServerEntity::Destroy] Invalid entity Type: " << Data.type << std::endl;
		break;
	}
}

CVector3 CServerEntity::GetPosition()
{
	switch(Data.type)
	{
	case Player:
		if (Data.player)
			return Data.player->GetPosition();

		std::cout << "[CServerEntity::GetPosition] Invalid entity " << Data.Id << " of type Player." << std::endl;
		break;
	case Vehicle:
		if (Data.vehicle)
			return Data.vehicle->GetPosition();

		std::cout << "[CServerEntity::GetPosition] Invalid entity " << Data.Id << " of type Vehicle." << std::endl;
		break;
	case Object:
		if (Data.object)
			return Data.object->GetPosition();

		std::cout << "[CServerEntity::GetPosition] Invalid entity " << Data.Id << " of type Object." << std::endl;
		break;
	default:
		std::cout << "[CServerEntity::GetPosition] Invalid entity Type: " << Data.type << std::endl;
		break;
	}
}

void CServerEntity::SetPosition(CVector3 position)
{
	RakNet::BitStream sData;
	switch(Data.type)
	{
	case Player:
		if (Data.player)
		{
			sData.Write(-1);
			sData.Write(position.fX);
			sData.Write(position.fY);
			sData.Write(position.fZ);

			g_Server->GetNetworkManager()->GetRPC().Signal("SetPosition", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, Data.player->GetGUID(), false, false);

			Data.player->SetPosition(position);
		}
		else
			std::cout << "[CServerEntity::SetPosition] Invalid entity " << Data.Id << " of type Player." << std::endl;
		break;
	case Vehicle:
		if (Data.vehicle)
		{
			sData.Write(Data.Id);
			sData.Write(position.fX);
			sData.Write(position.fY);
			sData.Write(position.fZ);

			g_Server->GetNetworkManager()->GetRPC().Signal("SetPosition", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

			Data.vehicle->SetPosition(position);
		}
		else
			std::cout << "[CServerEntity::SetPosition] Invalid entity " << Data.Id << " of type Vehicle." << std::endl;
		break;
	case Object:
		if (Data.object)
		{
			sData.Write(Data.Id);
			sData.Write(position.fX);
			sData.Write(position.fY);
			sData.Write(position.fZ);

			g_Server->GetNetworkManager()->GetRPC().Signal("SetPosition", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

			Data.object->SetPosition(position);
		}
		else
			std::cout << "[CServerEntity::SetPosition] Invalid entity " << Data.Id << " of type Object." << std::endl;
		break;
	default:
		std::cout << "[CServerEntity::SetPosition] Invalid entity Type: " << Data.type << std::endl;
		break;
	}
}

CVector4 CServerEntity::GetQuaternion()
{
	switch (Data.type)
	{
	case Player:
		if (Data.player)
			return Data.player->GetQuaternion();

		std::cout << "[CServerEntity::GetQuaternion] Invalid entity " << Data.Id << " of type Player." << std::endl;
		break;
	case Vehicle:
		if (Data.vehicle)
			return Data.vehicle->GetQuaternion();

		std::cout << "[CServerEntity::GetQuaternion] Invalid entity " << Data.Id << " of type Vehicle." << std::endl;
		break;
	case Object:
		if (Data.object)
			return Data.object->GetQuaternion();

		std::cout << "[CServerEntity::GetQuaternion] Invalid entity " << Data.Id << " of type Object." << std::endl;
		break;
	default:
		std::cout << "[CServerEntity::GetQuaternion] Invalid entity Type: " << Data.type << std::endl;
		break;
	}
}

void CServerEntity::SetQuaternion(CVector4 quaternion)
{
	RakNet::BitStream sData;
	switch (Data.type)
	{
	case Player:
		if (Data.player)
		{
			sData.Write(-1);
			sData.Write(quaternion.fX);
			sData.Write(quaternion.fY);
			sData.Write(quaternion.fZ);
			sData.Write(quaternion.fW);

			g_Server->GetNetworkManager()->GetRPC().Signal("SetQuaternion", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, Data.player->GetGUID(), false, false);
		}
		else
			std::cout << "[CServerEntity::SetQuaternion] Invalid entity " << Data.Id << " of type Player." << std::endl;
		break;
	case Vehicle:
		if (Data.vehicle)
		{
			sData.Write(Data.Id);
			sData.Write(quaternion.fX);
			sData.Write(quaternion.fY);
			sData.Write(quaternion.fZ);
			sData.Write(quaternion.fW);

			g_Server->GetNetworkManager()->GetRPC().Signal("SetQuaternion", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

			Data.vehicle->SetQuaternion(quaternion);
		}
		else
			std::cout << "[CServerEntity::SetQuaternion] Invalid entity " << Data.Id << " of type Vehicle." << std::endl;
		break;
	case Object:
		if (Data.object)
		{
			sData.Write(Data.Id);
			sData.Write(quaternion.fX);
			sData.Write(quaternion.fY);
			sData.Write(quaternion.fZ);
			sData.Write(quaternion.fW);

			g_Server->GetNetworkManager()->GetRPC().Signal("SetQuaternion", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

			Data.object->SetQuaternion(quaternion);
		}
		else
			std::cout << "[CServerEntity::SetQuaternion] Invalid entity " << Data.Id << " of type Object." << std::endl;
		break;
	default:
		std::cout << "[CServerEntity::SetQuaternion] Invalid entity Type: " << Data.type << std::endl;
		break;
	}
}

namespace ServerEntity
{
	int GetIndex(int entity)
	{
		if (!g_Entities.empty())
		{
			for (int i = 0; i < g_Entities.size(); i++)
			{
				if (entity == g_Entities[i].GetId())
				{
					return i;
				}
			}
		}
		return -1;
	}

	bool IsValid(int entity)
	{
		const int index = GetIndex(entity);
		if (index != -1)
		{
			switch (g_Entities[index].GetType())
			{
			case 0: // Player
				if (entity == g_Entities[index].GetPEntity()->GetEntity())
					return true;
				break;
			case 1: // Vehicle
				if (entity == g_Entities[index].GetVEntity()->GetId())
					return true;
				break;
			case 2: // Object
				/*if (entity == g_Entities[index].GetOEntity()->GetId())
					return true;}*/
				break;
			default:
				std::cout << "[ServerEntity::GetAssignee] Invalid entity" << std::endl;
				break;
			}
		}

		return false;
	}

	RakNetGUID GetAssignee(int entity)
	{
		const int index = GetIndex(entity);
		if (index != -1)
		{
			switch (g_Entities[index].GetType())
			{
			case 0: // Player
				return UNASSIGNED_RAKNET_GUID;
			case 1: // Vehicle
				return g_Entities[index].GetVEntity()->GetAssignee();
			case 2: // Object
				//return g_Entities[index].GetOEntity()->GetAssignee();
				break;
			default:
				std::cout << std::endl << "[ServerEntity::GetAssignee] Invalid entity" << std::endl;
				break;
			}
		}

		return UNASSIGNED_RAKNET_GUID;
	}

	void SetAssignee(int entity, RakNetGUID assignee)
	{
		const int index = GetIndex(entity);
		if (index != -1)
		{
			switch (g_Entities[index].GetType())
			{
			case 0: // Player
				break;
			case 1: // Vehicle
				g_Entities[index].GetVEntity()->SetAssignee(assignee);
				break;
			case 2: // Object
				//g_Entities[index].GetOEntity()->SetAssignee(assignee);
				break;
			default:
				std::cout << std::endl << "[ServerEntity::SetAssignee] Invalid entity" << std::endl;
				break;
			}

			if (assignee == UNASSIGNED_RAKNET_GUID)
			{
				RakNet::BitStream sData;
				sData.Write(entity);
				g_Server->GetNetworkManager()->GetRPC().Signal("DropEntityAssignment", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, assignee, true, false);
			}
			else
			{
				RakNet::BitStream sData;
				sData.Write(entity);
				sData.Write(assignee);
				g_Server->GetNetworkManager()->GetRPC().Signal("TakeEntityAssignment", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, assignee, true, false);
			}
		}
	}

	void RequestData(int entity, RakNetGUID requester)
	{
		const int index = GetIndex(entity);
		if (index != -1)
		{
			switch (g_Entities[index].GetType())
			{
			case 0: // Player
				g_Entities[index].GetPEntity()->RequestData(requester);
				break;
			case 1: // Vehicle
				g_Entities[index].GetVEntity()->RequestData(requester);
				break;
			case 2: // Object
				//g_Entities[index].GetOEntity()->RequestData(requester);
				break;
			default:
				std::cout << std::endl << "[ServerEntity::RequestData] Invalid entity" << std::endl;
				break;
			}
		}
	}
}