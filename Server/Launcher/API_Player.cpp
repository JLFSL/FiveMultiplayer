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

		std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
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

				return g_Players[i].SetModel(model);
			}
		}

		std::cout << "[" << ThisNamespace << "] Player Entity " << entity << " invalid." << std::endl;
	}
}