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

	const bool Player::IsControlable(const int entity)
	{
		for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == entity)
			{
				return g_Players[i].IsControlable();
			}
		}

		std::cout << "[" << ThisNamespace << "::IsControlable] Player Entity " << entity << " invalid." << std::endl;
	}

	void Player::SetControlable(const int entity, bool disablecontrols, bool frozen)
	{
		for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == entity)
			{
				RakNet::BitStream sData;
				sData.Write(disablecontrols);
				sData.Write(frozen);
				g_Server->GetNetworkManager()->GetRPC().Signal("SetControlable", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, g_Players[i].GetGUID(), false, false);

				g_Players[i].SetFrozen(frozen);
				return g_Players[i].SetControlable(disablecontrols);
			}
		}

		std::cout << "[" << ThisNamespace << "::SetControlable] Player Entity " << entity << " invalid." << std::endl;
	}
}