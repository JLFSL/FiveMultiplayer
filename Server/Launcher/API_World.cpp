#include "stdafx.h"

namespace API
{
	const char *World::ThisNamespace = "API::World::";

	void World::GetTime(int *hour, int *minute, int *second)
	{
		*hour = CWorld::GetTime().Hour;
		*minute = CWorld::GetTime().Minute;
		*second = CWorld::GetTime().Second;
	}

	void World::SetTime(const int hour, const int minute, const int second)
	{
		CWorld::SetTime(hour, minute, second);
	}

	const std::wstring World::GetWeather()
	{
		return CWorld::GetWeather().Weather;
	}

	void World::SetWeather(const std::wstring weather)
	{
		CWorld::SetWeather(weather);
	}

	void World::LoadIPL(const std::wstring ipl)
	{
		CWorld::LoadIPL(ipl);
	}

	void World::LoadIPL(const int entity, const std::wstring ipl)
	{
		const int index = ServerEntity::GetIndex(entity);

		if (index != -1)
		{
			switch (g_Entities[index].GetType())
			{
			case CServerEntity::Type::Player:
				for (int i = 0; i < g_Players.size(); i++)
				{
					if (g_Players[i].GetId() == entity)
					{
						RakNet::BitStream sData;
						sData.Write(RakWString(ipl.c_str()));
						g_Server->GetNetworkManager()->GetRPC().Signal("LoadIPL", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, g_Players[i].GetGUID(), false, false);
						break;
					}
				}
			
				break;
			default:
				std::wcout << ThisNamespace << L"LoadIPL(const int entity, const std::wstring ipl) can only be used on players" << std::endl;
				break;
			}
		}
	}

	void World::UnloadIPL(const std::wstring ipl)
	{
		CWorld::UnloadIPL(ipl);
	}

	void World::UnloadIPL(const int entity, const std::wstring ipl)
	{
		const int index = ServerEntity::GetIndex(entity);

		if (index != -1)
		{
			switch (g_Entities[index].GetType())
			{
			case CServerEntity::Type::Player:
				for (int i = 0; i < g_Players.size(); i++)
				{
					if (g_Players[i].GetId() == entity)
					{
						RakNet::BitStream sData;
						sData.Write(RakWString(ipl.c_str()));
						g_Server->GetNetworkManager()->GetRPC().Signal("UnloadIPL", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, g_Players[i].GetGUID(), false, false);
						break;
					}
				}

				break;
			default:
				std::wcout << ThisNamespace << L"UnloadIPL(const int entity, const std::wstring ipl) can only be used on players" << std::endl;
				break;
			}
		}
	}
}