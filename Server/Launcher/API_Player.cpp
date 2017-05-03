#include "stdafx.h"

namespace API
{
	const char *Player::ThisNamespace = "API::Player";

	const std::wstring Player::GetModel(const int entity)
	{
		for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == entity)
			{
				return g_Players[i].GetModel();
			}
		}

		std::cout << "[" << ThisNamespace << "::GetModel] Player Entity " << entity << " invalid." << std::endl;
	}

	void Player::SetModel(const int entity, const std::wstring model)
	{
		for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == entity)
			{
				RakNet::BitStream sData;
				sData.Write(RakWString(model.c_str()));
				g_Server->GetNetworkManager()->GetRPC().Signal("PlayerModel", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, g_Players[i].GetGUID(), false, false);

				CModelCache::AddModel(model);

				return g_Players[i].SetModel(model);
			}
		}

		std::cout << "[" << ThisNamespace << "::SetModel] Player Entity " << entity << " invalid." << std::endl;
	}

	const std::string Player::GetUsername(const int entity)
	{
		for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == entity)
			{
				return g_Players[i].GetUsername();
			}
		}

		std::cout << "[" << ThisNamespace << "::GetUsername] Player Entity " << entity << " invalid." << std::endl;
	}

	const bool Player::IsControllable(const int entity)
	{
		for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == entity)
			{
				return g_Players[i].IsControllable();
			}
		}

		std::cout << "[" << ThisNamespace << "::IsControllable] Player Entity " << entity << " invalid." << std::endl;
	}

	void Player::SetControllable(const int entity, bool disablecontrols, bool frozen)
	{
		for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == entity)
			{
				RakNet::BitStream sData;
				sData.Write(disablecontrols);
				sData.Write(frozen);
				g_Server->GetNetworkManager()->GetRPC().Signal("SetControllable", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, g_Players[i].GetGUID(), false, false);

				g_Players[i].SetFrozen(frozen);
				return g_Players[i].SetControllable(disablecontrols);
			}
		}

		std::cout << "[" << ThisNamespace << "::SetControllable] Player Entity " << entity << " invalid." << std::endl;
	}


	const std::string Player::GetIP(const int entity)
	{
		const int index = ServerEntity::GetIndex(entity);
		if (index > -1)
		{
			switch (g_Entities[index].GetType())
			{
			case CServerEntity::Player:
				for (int i = 0; i < g_Players.size(); i++)
				{
					if (g_Players[i].GetId() == entity)
					{
						return g_Players[i].GetIp().ToString();
					}
				}
				break;
			default:
				std::wcout << ThisNamespace << L"GetIP Entity " << entity << L" is not of type Player." << std::endl;
				break;
			}
		}
		else
		{
			std::wcout << ThisNamespace << L"GetIP Invalid Entity: " << entity << std::endl;
		}
	}
}