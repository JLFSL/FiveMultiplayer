#include "stdafx.h"

CServerEntity::CServerEntity()
{
	Data.Id = -1;
	Data.type = CServerEntity::Unknown;
	Data.viewDistance = 1000.0f;
}

void CServerEntity::Create(const int entity, const Type type)
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
	case CServerEntity::NPC:
		for (int i = 0; i < g_Npcs.size(); i++)
		{
			if (g_Npcs[i].GetId() == Data.Id)
			{
				g_Npcs[i].Destroy();
				break;
			}
		}
		break;
	default:
		std::cout << std::endl << "[CServerEntity::Destroy] Invalid entity" << std::endl;
		return;
		break;
	}
}

void CServerEntity::SetType(const Type type)
{
	Data.type = type;
}

const CVector3 CServerEntity::GetPosition()
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
	case CServerEntity::NPC:
		for (int i = 0; i < g_Npcs.size(); i++)
		{
			if (g_Npcs[i].GetId() == Data.Id)
			{
				return g_Npcs[i].GetPosition();
			}
		}
		break;
	default:
		std::cout << std::endl << "[CServerEntity::GetPosition] Invalid entity" << std::endl;

		return CVector3(0.0f, 0.0f, 0.0f);
		break;
	}

	return CVector3(0.0f, 0.0f, 0.0f);
}

void CServerEntity::SetPosition(const CVector3 position)
{
	switch (Data.type)
	{
	case Type::Player:
		/*for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == Data.Id)
			{
				g_Players[i].SetPosition(position);
				break;
			}
		}*/
		break;
	case Type::Vehicle:
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
	case Type::Object:
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
	case Type::NPC:
		for (int i = 0; i < g_Npcs.size(); i++)
		{
			if (g_Npcs[i].GetId() == Data.Id)
			{
				g_Npcs[i].SetPosition(position);

				if (g_Npcs[i].IsCreated())
					ENTITY::SET_ENTITY_COORDS_NO_OFFSET(g_Npcs[i].GetEntity(), position.fX, position.fY, position.fZ, false, false, false);
				break;
			}
		}
		break;
	default:
		std::cout << std::endl << "[CServerEntity::SetPosition] Invalid entity" << std::endl;
		return;
		break;
	}
}

void CServerEntity::SetRotation(const CVector3 rotation)
{
	switch (Data.type)
	{
	case Type::Vehicle:
		for (int i = 0; i < g_Vehicles.size(); i++)
		{
			if (g_Vehicles[i].GetId() == Data.Id)
			{
				g_Vehicles[i].SetRotation(rotation);

				if (g_Vehicles[i].IsCreated())
					ENTITY::SET_ENTITY_ROTATION(g_Vehicles[i].GetEntity(), rotation.fX, rotation.fY, rotation.fZ, 2, false);
				return;
			}
		}
		break;
	case Type::Object:
		for (int i = 0; i < g_Objects.size(); i++)
		{
			if (g_Objects[i].GetId() == Data.Id)
			{
				g_Objects[i].SetRotation(rotation);

				if (g_Objects[i].IsCreated())
					ENTITY::SET_ENTITY_ROTATION(g_Objects[i].GetEntity(), rotation.fX, rotation.fY, rotation.fZ, 2, true);
				return;
			}
		}
		break;
	case Type::NPC:
		for (int i = 0; i < g_Npcs.size(); i++)
		{
			if (g_Npcs[i].GetId() == Data.Id)
			{
				g_Npcs[i].SetRotation(rotation);

				if (g_Npcs[i].IsCreated())
					ENTITY::SET_ENTITY_ROTATION(g_Objects[i].GetEntity(), rotation.fX, rotation.fY, rotation.fZ, 2, true);
				return;
			}
		}
		break;
	default:
		std::cout << std::endl << "[CServerEntity::SetRotation] Invalid entity" << std::endl;
		return;
		break;
	}
}

void CServerEntity::SetAssignement(const RakNetGUID guid)
{
	switch (Data.type)
	{
	case Type::Vehicle:
		for (int i = 0; i < g_Vehicles.size(); i++)
		{
			if (g_Vehicles[i].GetId() == Data.Id)
			{
				return g_Vehicles[i].SetAssignee(guid);
			}
		}
		break;
	case Type::Object:
		for (int i = 0; i < g_Objects.size(); i++)
		{
			if (g_Objects[i].GetId() == Data.Id)
			{
				return g_Objects[i].SetAssignee(guid);
			}
		}
		break;
	case Type::NPC:
		for (int i = 0; i < g_Npcs.size(); i++)
		{
			if (g_Npcs[i].GetId() == Data.Id)
			{
				return /*g_Npcs[i].SetAssignee(guid)*/;
			}
		}
		break;
	default:
		std::cout << std::endl << "[CServerEntity::SetAssignement] Invalid entity" << std::endl;
		return;
		break;
	}
}

const bool CServerEntity::IsValid(const int entity)
{
	for (int i = 0; i < g_Entities.size(); i++)
	{
		if (entity == g_Entities[i].GetId())
		{
			switch (g_Entities[i].GetType())
			{
			case Type::Player:
				for (int v = 0; v < g_Players.size(); v++)
				{
					if (entity == g_Players[v].GetId())
						return true;
				}
				break;
			case Type::Vehicle:
				for (int v = 0; v < g_Vehicles.size(); v++)
				{
					if (entity == g_Vehicles[v].GetId())
						return true;
				}
				break;
			case Type::Object:
				for (int v = 0; v < g_Objects.size(); v++)
				{
					if (entity == g_Objects[v].GetId())
						return true;
				}
				break;
			case Type::NPC:
				for (int v = 0; v < g_Npcs.size(); v++)
				{
					if (entity == g_Npcs[v].GetId())
						return true;
				}
				break;
			default:
				std::cout << std::endl << "[CServerEntity::IsValid] Invalid entity" << std::endl;
				return false;
				break;
			}
		}
	}

	return false;
}

const RakNetGUID CServerEntity::GetAssignee(const int entity)
{
	for (int i = 0; i < g_Entities.size(); i++)
	{
		if (entity == g_Entities[i].GetId())
		{
			switch (g_Entities[i].GetType())
			{
			case Type::Vehicle: // Vehicle
				for (int p = 0; p < g_Vehicles.size(); p++)
				{
					if (entity == g_Vehicles[p].GetId())
						return g_Vehicles[p].GetAssignee();
				}
				break;
			case Type::Object:
				for (int p = 0; p < g_Objects.size(); p++)
				{
					if (entity == g_Objects[p].GetId())
						return g_Objects[p].GetAssignee();
				}
				break;
			default:
				std::cout << std::endl << "[CServerEntity::GetAssignee] Invalid entity" << std::endl;
				return UNASSIGNED_RAKNET_GUID;
				break;
			}
		}
	}

	return UNASSIGNED_RAKNET_GUID;
}

void CServerEntity::SetAssignee(const int entity, const RakNetGUID assignee)
{
	for (int i = 0; i < g_Entities.size(); i++)
	{
		if (entity == g_Entities[i].GetId())
		{
			switch (g_Entities[i].GetType())
			{
			case Type::Vehicle:
				for (int p = 0; p < g_Vehicles.size(); p++)
				{
					if (entity == g_Vehicles[p].GetId())
					{
						return g_Vehicles[p].SetAssignee(assignee);
						break;
					}
				}
				break;
			case Type::Object:
				for (int p = 0; p < g_Objects.size(); p++)
				{
					if (entity == g_Objects[p].GetId())
						return g_Objects[p].SetAssignee(assignee);
				}
				break;
			default:
				std::cout << std::endl << "[CServerEntity::SetAssignee] Invalid entity" << std::endl;
				return;
				break;
			}
		}
	}
}

void CServerEntity::SetPedComponentVariation(const int entity, const int componentid, const int drawableid, const int textureid, const int paletteid)
{
	for (int i = 0; i < g_Entities.size(); i++)
	{
		if (entity == g_Entities[i].GetId())
		{
			switch (g_Entities[i].GetType())
			{
			case Type::Player:
				for (int p = 0; p < g_Players.size(); p++)
				{
					if (entity == g_Players[p].GetId())
					{
						return g_Players[p].SetModelComponent(componentid, drawableid, textureid, paletteid);
						break;
					}
				}
				break;
			case Type::NPC:
				for (int p = 0; p < g_Npcs.size(); p++)
				{
					if (entity == g_Npcs[p].GetId())
					{
						return g_Npcs[p].SetModelComponent(componentid, drawableid, textureid, paletteid);
						break;
					}
				}
				break;
			default:
				std::cout << std::endl << "[CServerEntity::SetPedComponentVariation] Invalid entity, must by of type Player or NPC." << std::endl;
				return;
				break;
			}
		}
	}
}

void CServerEntity::SetPedHeadBlend(const int entity, const int shapeFirst, const int shapeSecond, const int shapeThird, const int skinFirst, const int skinSecond, const int skinThird, const float shapeMix, const float skinMix, const float thirdMix)
{
	for (int i = 0; i < g_Entities.size(); i++)
	{
		if (entity == g_Entities[i].GetId())
		{
			switch (g_Entities[i].GetType())
			{
			case Type::Player:
				for (int p = 0; p < g_Players.size(); p++)
				{
					if (entity == g_Players[p].GetId())
					{
						return g_Players[p].SetModelHeadBlend(shapeFirst, shapeSecond, shapeThird, skinFirst, skinSecond, skinThird, shapeMix, skinMix, thirdMix);
						break;
					}
				}
				break;
			case Type::NPC:
				for (int p = 0; p < g_Npcs.size(); p++)
				{
					if (entity == g_Npcs[p].GetId())
					{
						return g_Npcs[p].SetModelHeadBlend(shapeFirst, shapeSecond, shapeThird, skinFirst, skinSecond, skinThird, shapeMix, skinMix, thirdMix);
						break;
					}
				}
				break;
			default:
				std::cout << std::endl << "[CServerEntity::SetPedHeadBlend] Invalid entity, must by of type Player or NPC." << std::endl;
				return;
				break;
			}
		}
	}
}

void CServerEntity::SetPedHeadOverlayColor(const int entity, const int overlayid, const int index, const int colorType, const int colorid, const int secondColorid, const float opacity)
{
	for (int i = 0; i < g_Entities.size(); i++)
	{
		if (entity == g_Entities[i].GetId())
		{
			switch (g_Entities[i].GetType())
			{
			case Type::Player:
				for (int p = 0; p < g_Players.size(); p++)
				{
					if (entity == g_Players[p].GetId())
					{
						return g_Players[p].SetModelHeadOverlay(overlayid, index, colorType, colorid, secondColorid, opacity);
						break;
					}
				}
				break;
			case Type::NPC:
				for (int p = 0; p < g_Npcs.size(); p++)
				{
					if (entity == g_Npcs[p].GetId())
					{
						return g_Npcs[p].SetModelHeadOverlay(overlayid, index, colorType, colorid, secondColorid, opacity);
						break;
					}
				}
				break;
			default:
				std::cout << std::endl << "[CServerEntity::SetPedHeadOverlayColor] Invalid entity, must by of type Player or NPC." << std::endl;
				return;
				break;
			}
		}
	}
}

void CServerEntity::SetPedProp(const int entity, const int componentid, const int drawableid, const int textureid)
{
	for (int i = 0; i < g_Entities.size(); i++)
	{
		if (entity == g_Entities[i].GetId())
		{
			switch (g_Entities[i].GetType())
			{
			case Type::Player:
				for (int p = 0; p < g_Players.size(); p++)
				{
					if (entity == g_Players[p].GetId())
					{
						return g_Players[p].SetModelProp(componentid, drawableid, textureid);
						break;
					}
				}
				break;
			case Type::NPC:
				for (int p = 0; p < g_Npcs.size(); p++)
				{
					if (entity == g_Npcs[p].GetId())
					{
						return g_Npcs[p].SetModelProp(componentid, drawableid, textureid);
						break;
					}
				}
				break;
			default:
				std::cout << std::endl << "[CServerEntity::SetPedProp] Invalid entity, must by of type Player or NPC." << std::endl;
				return;
				break;
			}
		}
	}
}

void CServerEntity::SetPedFaceFeature(const int entity, const int index, const float scale)
{
	for (int i = 0; i < g_Entities.size(); i++)
	{
		if (entity == g_Entities[i].GetId())
		{
			switch (g_Entities[i].GetType())
			{
			case Type::Player:
				for (int p = 0; p < g_Players.size(); p++)
				{
					if (entity == g_Players[p].GetId())
					{
						return g_Players[p].SetModelFaceFeature(index, scale);
						break;
					}
				}
				break;
			case Type::NPC:
				for (int p = 0; p < g_Npcs.size(); p++)
				{
					if (entity == g_Npcs[p].GetId())
					{
						return g_Npcs[p].SetModelFaceFeature(index, scale);
						break;
					}
				}
				break;
			default:
				std::cout << std::endl << "[CServerEntity::SetPedFaceFeature] Invalid entity, must by of type Player or NPC." << std::endl;
				return;
				break;
			}
		}
	}
}