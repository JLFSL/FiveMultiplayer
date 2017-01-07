#include "stdafx.h"

void CServerEntity::Create(int entity)
{
	if (g_Entities.empty())
		Data.Id = 0;
	else
		Data.Id = g_Entities.size();
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