#include "stdafx.h"

CServerEntity::CServerEntity()
{
	Data.Id = -1;
	Data.type = CServerEntity::Unknown;
}

void CServerEntity::Create(int entity, Type type)
{
	Data.Id = entity;
	Data.type = type;
}

void CServerEntity::Destroy()
{
	switch (Data.type)
	{
	case CServerEntity::Player:
		for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == Data.Id)
			{
				g_Players[i].Destroy();
				break;
			}
		}
		break;
	case CServerEntity::Vehicle:
		for (int i = 0; i < g_Vehicles.size(); i++)
		{
			if (g_Vehicles[i].GetId() == Data.Id)
			{
				g_Vehicles[i].Destroy();
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
				break;
			}
		}
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
	}

	return CVector3(0.0f, 0.0f, 0.0f);
}

void CServerEntity::SetPosition(CVector3 position)
{
	switch (Data.type)
	{
	case CServerEntity::Player:
		/*for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == Data.Id)
			{
				g_Players[i].SetPosition(position);
				break;
			}
		}*/
		break;
	case CServerEntity::Vehicle:
		for (int i = 0; i < g_Vehicles.size(); i++)
		{
			if (g_Vehicles[i].GetId() == Data.Id)
			{
				g_Vehicles[i].SetPosition(position);

				if(g_Vehicles[i].IsCreated())
					ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_Vehicles[i].GetEntity(), position.fX, position.fY, position.fZ, false, false, false);
				break;
			}
		}
		break;
	case CServerEntity::Object:
		for (int i = 0; i < g_Objects.size(); i++)
		{
			if (g_Objects[i].GetId() == Data.Id)
			{
				g_Objects[i].SetPosition(position);

				if (g_Objects[i].IsCreated())
					ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_Objects[i].GetEntity(), position.fX, position.fY, position.fZ, false, false, false);
				break;
			}
		}
		break;
	}
}

void CServerEntity::SetQuaternion(CVector4 quaternion)
{
	switch (Data.type)
	{
	case CServerEntity::Player:
		break;
	case CServerEntity::Vehicle:
		for (int i = 0; i < g_Vehicles.size(); i++)
		{
			if (g_Vehicles[i].GetId() == Data.Id)
			{
				g_Vehicles[i].SetQuaternion(quaternion);

				if (g_Vehicles[i].IsCreated())
					ENTITY::SET_ENTITY_QUATERNION(g_Vehicles[i].GetEntity(), quaternion.fX, quaternion.fY, quaternion.fZ, quaternion.fW);
				break;
			}
		}
		break;
	case CServerEntity::Object:
		for (int i = 0; i < g_Objects.size(); i++)
		{
			if (g_Objects[i].GetId() == Data.Id)
			{
				g_Objects[i].SetQuaternion(quaternion);

				if (g_Objects[i].IsCreated())
					ENTITY::SET_ENTITY_QUATERNION(g_Objects[i].GetEntity(), quaternion.fX, quaternion.fY, quaternion.fZ, quaternion.fW);
				break;
			}
		}
		break;
	}
}

void CServerEntity::SetAssignement(RakNetGUID guid)
{
	switch (Data.type)
	{
	case CServerEntity::Player:
		break;
	case CServerEntity::Vehicle:
		for (int i = 0; i < g_Vehicles.size(); i++)
		{
			if (g_Vehicles[i].GetId() == Data.Id)
			{
				g_Vehicles[i].SetAssignee(guid);
				break;
			}
		}
		break;
	case CServerEntity::Object:
		for (int i = 0; i < g_Objects.size(); i++)
		{
			if (g_Objects[i].GetId() == Data.Id)
			{
				g_Objects[i].SetAssignee(guid);
				break;
			}
		}
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
				case CServerEntity::Player:
					for (int v = 0; v < g_Players.size(); v++)
					{
						if (entity == g_Players[v].GetId())
							return true;
					}
					break;
				case CServerEntity::Vehicle:
					for (int v = 0; v < g_Vehicles.size(); v++)
					{
						if (entity == g_Vehicles[v].GetId())
							return true;
					}
					break;
				case CServerEntity::Object: 
					for (int i = 0; i < g_Objects.size(); i++)
					{
						if (entity == g_Objects[i].GetId())
							return true;
					}
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