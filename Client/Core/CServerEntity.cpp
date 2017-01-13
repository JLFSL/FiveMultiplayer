#include "stdafx.h"

void CServerEntity::Create(int entity)
{
	if (g_Entities.empty())
		Data.Id = 0;
	else
		Data.Id = (int)g_Entities.size();
}

void CServerEntity::SetType(Type type)
{
	Data.type = type;
}

CVector3 CServerEntity::GetPosition()
{
	switch (Data.type)
	{
	case Player:
		if (!g_Players.empty())
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetId() == Data.Id)
					return g_Players[i].GetPosition();
			}
		}

		std::cout << std::endl << "[CServerEntity::GetPosition] Invalid player ID: " << Data.Id << std::endl;
		break;
	case Vehicle:
		std::cout << std::endl << "[CServerEntity::GetPosition] Invalid vehicle ID: " << Data.Id << std::endl;
		break;
	case Object:
		std::cout << std::endl << "[CServerEntity::GetPosition] Invalid object ID: " << Data.Id << std::endl;
		break;
	default:
		std::cout << std::endl << "[CServerEntity::GetPosition] Invalid entity" << std::endl;
		break;
	}
}

void CServerEntity::SetPosition(CVector3 position)
{
	switch (Data.type)
	{
	case Player:
		break;
	case Vehicle:
		std::cout << std::endl << "[CServerEntity::SetPosition] Invalid vehicle ID: " << Data.Id << std::endl;
		break;
	case Object:
		std::cout << std::endl << "[CServerEntity::SetPosition] Invalid object ID: " << Data.Id << std::endl;
		break;
	default:
		std::cout << std::endl << "[CServerEntity::SetPosition] Invalid entity" << std::endl;
		break;
	}
}

void CServerEntity::SetAssignement(RakNetGUID guid)
{
	switch (Data.type)
	{
	case Player:
		std::cout << std::endl << "[CServerEntity::SetAssignement] Players can not be assigned." << Data.Id << std::endl;
		break;
	case Vehicle:
		for (int i = 0; i < g_Vehicles.size(); i++)
		{
			if (Data.Id == g_Vehicles[i].GetId())
			{
				g_Vehicles[i].SetAssignee(guid);
				return;
			}
		}
		std::cout << std::endl << "[CServerEntity::SetAssignement] Invalid vehicle ID: " << Data.Id << std::endl;
		break;
	case Object:
		std::cout << std::endl << "[CServerEntity::SetAssignement] Invalid object ID: " << Data.Id << std::endl;
		break;
	default:
		std::cout << std::endl << "[CServerEntity::SetAssignement] Invalid entity" << std::endl;
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
						if (entity == g_Players[i].GetId())
							return TRUE;
					}
					break;
				case 1: // Vehicle
					for (int i = 0; i < g_Vehicles.size(); i++)
					{
						if (entity == g_Vehicles[i].GetId())
							return TRUE;
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
					std::cout << std::endl << "[ServerEntity::GetAssignee] Invalid entity" << std::endl;
					break;
				}
			}
		}

		return FALSE;
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
}