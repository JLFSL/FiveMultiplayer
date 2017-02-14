#include "stdafx.h"

void CServerEntity::Create(int entity)
{
	if (g_Entities.empty())
		Data.Id = 0;
	else
		Data.Id = (int)g_Entities.size();
}

void CServerEntity::Destroy()
{
	switch (Data.type)
	{
	case Player:
		if (!g_Players.empty())
		{
			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetId() == Data.Id)
					g_Players[i].Destroy();
			}
		}

		Data = {};

		std::cout << std::endl << "[CServerEntity::Destroy] Invalid player ID: " << Data.Id << std::endl;
		break;
	case Vehicle:
		if (!g_Vehicles.empty())
		{
			for (int i = 0; i < g_Vehicles.size(); i++)
			{
				if (g_Vehicles[i].GetId() == Data.Id)
					g_Vehicles[i].Destroy();
			}
		}

		Data = {};

		std::cout << std::endl << "[CServerEntity::Destroy] Invalid vehicle ID: " << Data.Id << std::endl;
		break;
	case Object:
		std::cout << std::endl << "[CServerEntity::Destroy] Invalid object ID: " << Data.Id << std::endl;
		break;
	default:
		std::cout << std::endl << "[CServerEntity::Destroy] Invalid entity" << std::endl;
		break;
	}
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
		if (Data.vehicle)
		{
			Data.vehicle->SetPosition(position);

			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(Data.vehicle->GetEntity(), position.fX, position.fY, position.fZ, false, false, false);
		}
		else
			std::cout << std::endl << "[CServerEntity::SetPosition] Invalid vehicle ID: " << Data.Id << std::endl;
		break;
	case Object:
		if (Data.object)
		{
			Data.object->SetPosition(position);

			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(Data.object->GetEntity(), position.fX, position.fY, position.fZ, false, false, false);
		}
		else
			std::cout << std::endl << "[CServerEntity::SetPosition] Invalid object ID: " << Data.Id << std::endl;
		break;
	default:
		std::cout << std::endl << "[CServerEntity::SetPosition] Invalid entity" << std::endl;
		break;
	}
}

void CServerEntity::SetQuaternion(CVector4 quaternion)
{
	switch (Data.type)
	{
	case Player:
		break;
	case Vehicle:
		if (Data.vehicle)
		{
			Data.vehicle->SetQuaternion(quaternion);

			ENTITY::SET_ENTITY_QUATERNION(Data.vehicle->GetEntity(), quaternion.fX, quaternion.fY, quaternion.fZ, quaternion.fW);
		}
		else
			std::cout << std::endl << "[CServerEntity::SetQuaternion] Invalid vehicle ID: " << Data.Id << std::endl;
		break;
	case Object:
		if (Data.object)
		{
			Data.object->SetQuaternion(quaternion);

			ENTITY::SET_ENTITY_QUATERNION(Data.object->GetEntity(), quaternion.fX, quaternion.fY, quaternion.fZ, quaternion.fW);
		}
		else
			std::cout << std::endl << "[CServerEntity::SetQuaternion] Invalid object ID: " << Data.Id << std::endl;
		break;
	default:
		std::cout << std::endl << "[CServerEntity::SetQuaternion] Invalid entity" << std::endl;
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
					for (int v = 0; v < g_Players.size(); v++)
					{
						if (entity == g_Players[v].GetId())
							return true;
					}
					break;
				case 1: // Vehicle
					for (int v = 0; v < g_Vehicles.size(); v++)
					{
						if (entity == g_Vehicles[v].GetId())
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
					std::cout << std::endl << "[ServerEntity::GetAssignee] Invalid entity" << std::endl;
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
					for (int v = 0; v < g_Vehicles.size(); v++)
					{
						if (entity == g_Vehicles[v].GetId())
							return g_Vehicles[v].GetAssignee();
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
					for (int v = 0; v < g_Vehicles.size(); v++)
					{
						if (entity == g_Vehicles[v].GetId())
						{
							return g_Vehicles[v].SetAssignee(assignee);
							break;
						}
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