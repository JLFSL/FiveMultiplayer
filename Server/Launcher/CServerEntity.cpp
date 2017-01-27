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

CVector3 CServerEntity::GetPosition()
{
	switch(Data.type)
	{
	case Player:
		if (Data.player)
			return Data.player->GetPosition();

		std::cout << "[CServerEntity::GetPosition] Invalid player ID: " << Data.Id << std::endl;
		break;
	case Vehicle:
		if (Data.vehicle)
			return Data.vehicle->GetPosition();

		std::cout << "[CServerEntity::GetPosition] Invalid vehicle ID: " << Data.Id << std::endl;
		break;
	case Object:
		std::cout << "[CServerEntity::GetPosition] Invalid object ID: " << Data.Id << std::endl;
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
			std::cout << "[CServerEntity::SetPosition] Invalid player ID: " << Data.Id << std::endl;
		break;
	case Vehicle:
		if (Data.vehicle)
		{
			sData.Write(1);
			sData.Write(position.fX);
			sData.Write(position.fY);
			sData.Write(position.fZ);

			g_Server->GetNetworkManager()->GetRPC().Signal("SetPosition", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);

			Data.vehicle->SetPosition(position);
		}
		else
			std::cout << "[CServerEntity::SetPosition] Invalid vehicle ID: " << Data.Id << std::endl;
		break;
	case Object:
		std::cout << "[CServerEntity::SetPosition] Invalid object ID: " << Data.Id << std::endl;
		break;
	default:
		std::cout << "[CServerEntity::SetPosition] Invalid entity Type: " << Data.type << std::endl;
		break;
	}
}

namespace ServerEntity
{
	bool IsValid(int entity)
	{
		for (int i = 0; i < g_Entities.size(); i++)
		{
			if (entity == g_Entities[i].GetId())
			{
				switch (g_Entities[i].GetType())
				{
				case 0: // Player
					for (int i = 0; i < g_Players.size(); i++)
					{
						if (entity == g_Players[i].GetEntity())
							return true;
					}
					break;
				case 1: // Vehicle
					for (int i = 0; i < g_Vehicles.size(); i++)
					{
						if (entity == g_Vehicles[i].GetId())
							return true;
					}
					break;
				case 2: // Object
						/*for (int i = 0; i < g_Objects.size(); i++)
						{
						if (entity == g_Objects[i].GetId())
						return TRUE;
						}*/
					break;
				default:
					std::cout << "[ServerEntity::GetAssignee] Invalid entity" << std::endl;
					break;
				}
			}
		}

		return false;
	}

	RakNetGUID GetAssignee(int entity)
	{
		for (int i = 0; i < g_Entities.size(); i++)
		{
			if (entity == g_Entities[i].GetId())
			{
				switch (g_Entities[i].GetType())
				{
				case 0: // Player
					return UNASSIGNED_RAKNET_GUID;
					break;
				case 1: // Vehicle
					for (int i = 0; i < g_Vehicles.size(); i++)
					{
						if (entity == g_Vehicles[i].GetId())
							return g_Vehicles[i].GetAssignee();
					}
					break;
				case 2: // Object
						/*for (int i = 0; i < g_Objects.size(); i++)
						{
						if (entity == g_Objects[i].GetId())
						return g_Objects[i].GetAssignee();
						}*/
					break;
				default:
					std::cout << std::endl << "[ServerEntity::GetAssignee] Invalid entity" << std::endl;
					break;
				}
			}
		}

		return UNASSIGNED_RAKNET_GUID;
	}

	void SetAssignee(int entity, RakNetGUID assignee)
	{
		for (int i = 0; i < g_Entities.size(); i++)
		{
			if (entity == g_Entities[i].GetId())
			{
				switch (g_Entities[i].GetType())
				{
				case 0: // Player
					break;
				case 1: // Vehicle
					for (int i = 0; i < g_Vehicles.size(); i++)
					{
						if (entity == g_Vehicles[i].GetId())
							return g_Vehicles[i].SetAssignee(assignee);
					}
					break;
				case 2: // Object
						/*for (int i = 0; i < g_Objects.size(); i++)
						{
						if (entity == g_Objects[i].GetId())
						return g_Objects[i].SetAssignee(assignee);
						}*/
					break;
				default:
					std::cout << std::endl << "[ServerEntity::SetAssignee] Invalid entity" << std::endl;
					break;
				}
			}
		}
	}

	void RequestData(int entity, RakNetGUID requester)
	{
		for (int i = 0; i < g_Entities.size(); i++)
		{
			if (entity == g_Entities[i].GetId())
			{
				switch (g_Entities[i].GetType())
				{
				case 0: // Player
					break;
				case 1: // Vehicle
					for (int i = 0; i < g_Vehicles.size(); i++)
					{
						if (entity == g_Vehicles[i].GetId())
							return g_Vehicles[i].RequestData(requester);
					}
					break;
				case 2: // Object
						/*for (int i = 0; i < g_Objects.size(); i++)
						{
						if (entity == g_Objects[i].GetId())
						return g_Objects[i].RequestData(requester);
						}*/
					break;
				default:
					std::cout << std::endl << "[ServerEntity::RequestData] Invalid entity" << std::endl;
					break;
				}
			}
		}
	}
}