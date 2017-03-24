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
	case CServerEntity::Player:
		std::cout << "[CServerEntity::Destroy] Can not destroy a player!" << std::endl;
		break;
	case CServerEntity::Vehicle:
		for (int i = 0; i < g_Vehicles.size(); i++)
		{
			if (g_Vehicles[i].GetId() == Data.Id)
			{
				g_Vehicles[i].Destroy();

				sData.Write(Data.Id);
				g_Server->GetNetworkManager()->GetRPC().Signal("DestroyEntity", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);
				break;
			}
		}
		break;
	case CServerEntity::Object:
		for (int i = 0; i < g_Objects.size(); i++)
		{
			if (g_Objects[i].GetId() == Data.Id)
			{
				g_Objects[i].Destroy();

				sData.Write(Data.Id);
				g_Server->GetNetworkManager()->GetRPC().Signal("DestroyEntity", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);
				break;
			}
		}
		break;
	default:
		std::cout << "[CServerEntity::Destroy] Invalid entity Type: " << Data.type << std::endl;
	}
}

CVector3 CServerEntity::GetPosition()
{
	switch (Data.type)
	{
	case CServerEntity::Player:
		for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == Data.Id)
			{
				return g_Players[i].GetPosition();
			}
		}
		break;
	case CServerEntity::Vehicle:
		for (int i = 0; i < g_Vehicles.size(); i++)
		{
			if (g_Vehicles[i].GetId() == Data.Id)
			{
				return g_Vehicles[i].GetPosition();
			}
		}
		break;
	case CServerEntity::Object:
		for (int i = 0; i < g_Objects.size(); i++)
		{
			if (g_Objects[i].GetId() == Data.Id)
			{
				return g_Objects[i].GetPosition();
			}
		}
		break;
	default:
		std::cout << "[CServerEntity::GetPosition] Invalid entity Type: " << Data.type << std::endl;
	}
}

void CServerEntity::SetPosition(CVector3 position)
{
	RakNet::BitStream sData;
	switch (Data.type)
	{
	case CServerEntity::Player:
		for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == Data.Id)
			{
				sData.Write(-1);
				sData.Write(position.fX);
				sData.Write(position.fY);
				sData.Write(position.fZ);

				g_Server->GetNetworkManager()->GetRPC().Signal("SetPosition", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, g_Players[i].GetGUID(), false, false);
				
				g_Players[i].SetPosition(position);
				break;
			}
		}
		break;
	case CServerEntity::Vehicle:
		for (int i = 0; i < g_Vehicles.size(); i++)
		{
			if (g_Vehicles[i].GetId() == Data.Id)
			{
				sData.Write(Data.Id);
				sData.Write(position.fX);
				sData.Write(position.fY);
				sData.Write(position.fZ);

				g_Server->GetNetworkManager()->GetRPC().Signal("SetPosition", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

				g_Vehicles[i].SetPosition(position);
				break;
			}
		}
		break;
	case CServerEntity::Object:
		for (int i = 0; i < g_Objects.size(); i++)
		{
			if (g_Objects[i].GetId() == Data.Id)
			{
				sData.Write(Data.Id);
				sData.Write(position.fX);
				sData.Write(position.fY);
				sData.Write(position.fZ);

				g_Server->GetNetworkManager()->GetRPC().Signal("SetPosition", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

				g_Objects[i].SetPosition(position);
				break;
			}
		}
		break;
	default:
		std::cout << "[CServerEntity::SetPosition] Invalid entity Type: " << Data.type << std::endl;
	}
}

CVector4 CServerEntity::GetQuaternion()
{
	switch (Data.type)
	{
	case CServerEntity::Player:
		for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == Data.Id)
			{
				return g_Players[i].GetQuaternion();
			}
		}
		break;
	case CServerEntity::Vehicle:
		for (int i = 0; i < g_Vehicles.size(); i++)
		{
			if (g_Vehicles[i].GetId() == Data.Id)
			{
				return g_Vehicles[i].GetQuaternion();
			}
		}
		break;
	case CServerEntity::Object:
		for (int i = 0; i < g_Objects.size(); i++)
		{
			if (g_Objects[i].GetId() == Data.Id)
			{
				return g_Objects[i].GetQuaternion();
			}
		}
		break;
	default:
		std::cout << "[CServerEntity::GetQuaternion] Invalid entity Type: " << Data.type << std::endl;
	}
}

void CServerEntity::SetQuaternion(CVector4 quaternion)
{
	RakNet::BitStream sData;
	switch (Data.type)
	{
	case CServerEntity::Player:
		for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == Data.Id)
			{
				sData.Write(-1);
				sData.Write(quaternion.fX);
				sData.Write(quaternion.fY);
				sData.Write(quaternion.fZ);
				sData.Write(quaternion.fW);

				g_Server->GetNetworkManager()->GetRPC().Signal("SetQuaternion", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, g_Players[i].GetGUID(), false, false);
				break;
			}
		}
		break;
	case CServerEntity::Vehicle:
		for (int i = 0; i < g_Vehicles.size(); i++)
		{
			if (g_Vehicles[i].GetId() == Data.Id)
			{
				sData.Write(Data.Id);
				sData.Write(quaternion.fX);
				sData.Write(quaternion.fY);
				sData.Write(quaternion.fZ);
				sData.Write(quaternion.fW);

				g_Server->GetNetworkManager()->GetRPC().Signal("SetQuaternion", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

				g_Vehicles[i].SetQuaternion(quaternion);
				break;
			}
		}
		break;
	case CServerEntity::Object:
		for (int i = 0; i < g_Objects.size(); i++)
		{
			if (g_Objects[i].GetId() == Data.Id)
			{
				sData.Write(Data.Id);
				sData.Write(quaternion.fX);
				sData.Write(quaternion.fY);
				sData.Write(quaternion.fZ);
				sData.Write(quaternion.fW);

				g_Server->GetNetworkManager()->GetRPC().Signal("SetQuaternion", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

				g_Objects[i].SetQuaternion(quaternion);
				break;
			}
		}
		break;
	default:
		std::cout << "[CServerEntity::SetQuaternion] Invalid entity Type: " << Data.type << std::endl;
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
			case CServerEntity::Player:
				for (int i = 0; i < g_Players.size(); i++)
				{
					if (g_Players[i].GetId() == entity)
					{
						return true;
					}
				}
				break;
			case CServerEntity::Vehicle:
				for (int i = 0; i < g_Vehicles.size(); i++)
				{
					if (g_Vehicles[i].GetId() == entity)
					{
						return true;
					}
				}
				break;
			case CServerEntity::Object:
				for (int i = 0; i < g_Objects.size(); i++)
				{
					if (g_Objects[i].GetId() == entity)
					{
						return true;
					}
				}
				break;
			case CServerEntity::NPC:
				for (int i = 0; i < g_Npcs.size(); i++)
				{
					if (g_Npcs[i].GetId() == entity)
					{
						return true;
					}
				}
				break;
			default:
				std::cout << "[ServerEntity::IsValid] Invalid entity" << std::endl;
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
			case CServerEntity::Player:
				for (int i = 0; i < g_Players.size(); i++)
				{
					if (g_Players[i].GetId() == entity)
					{
						return UNASSIGNED_RAKNET_GUID;
					}
				}
				break;
			case CServerEntity::Vehicle:
				for (int i = 0; i < g_Vehicles.size(); i++)
				{
					if (g_Vehicles[i].GetId() == entity)
					{
						return g_Vehicles[i].GetAssignee();
					}
				}
				break;
			case CServerEntity::Object:
				for (int i = 0; i < g_Objects.size(); i++)
				{
					if (g_Objects[i].GetId() == entity)
					{
						return g_Objects[i].GetAssignee();
					}
				}
				break;
			default:
				std::cout << "[ServerEntity::GetAssignee] Invalid entity" << std::endl;
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
			case CServerEntity::Player:
				break;
			case CServerEntity::Vehicle:
				for (int i = 0; i < g_Vehicles.size(); i++)
				{
					if (g_Vehicles[i].GetId() == entity)
					{
						g_Vehicles[i].SetAssignee(assignee);
						break;
					}
				}
				break;
			case CServerEntity::Object:
				for (int i = 0; i < g_Objects.size(); i++)
				{
					if (g_Objects[i].GetId() == entity)
					{
						g_Objects[i].SetAssignee(assignee);
						break;
					}
				}
				break;
			default:
				std::cout << "[ServerEntity::SetAssignee] Invalid entity" << std::endl;
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
			case CServerEntity::Player:
				for (int i = 0; i < g_Players.size(); i++)
				{
					if (g_Players[i].GetId() == entity)
					{
						g_Players[i].RequestData(requester);
						break;
					}
				}
				break;
			case CServerEntity::Vehicle:
				for (int i = 0; i < g_Vehicles.size(); i++)
				{
					if (g_Vehicles[i].GetId() == entity)
					{
						g_Vehicles[i].RequestData(requester);
						break;
					}
				}
				break;
			case CServerEntity::Object:
				for (int i = 0; i < g_Objects.size(); i++)
				{
					if (g_Objects[i].GetId() == entity)
					{
						g_Objects[i].RequestData(requester);
						break;
					}
				}
				break;
			default:
				std::cout << std::endl << "[ServerEntity::RequestData] Invalid entity" << std::endl;
				break;
			}
		}
	}
}