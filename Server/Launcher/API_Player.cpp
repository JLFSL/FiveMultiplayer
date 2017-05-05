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

	void Player::SetUsername(const int entity, const std::string name)
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
						RakString username(name.c_str());

						/*RakNet::BitStream sData;
						sData.Write(username);
						g_Server->GetNetworkManager()->GetRPC().Signal("SetUsername", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, g_Players[i].GetGUID(), false, false);*/

						return g_Players[i].SetUsername(username);
					}
				}
				break;
			default:
				std::wcout << ThisNamespace << L"SetUsername Entity " << entity << L" is not of type Player." << std::endl;
				break;
			}
		}
		else
		{
			std::wcout << ThisNamespace << L"SetUsername Invalid Entity: " << entity << std::endl;
		}
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

	void Player::Kick(const int entity, const std::string reason)
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
						RakNet::BitStream sData;
						sData.Write(RakString(reason.c_str()));
						g_Server->GetNetworkManager()->GetRPC().Signal("Kick", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, g_Players[i].GetGUID(), false, false);

						return;
					}
				}
				break;
			default:
				std::wcout << ThisNamespace << L"Kick Entity " << entity << L" is not of type Player." << std::endl;
				break;
			}
		}
		else
		{
			std::wcout << ThisNamespace << L"Kick Invalid Entity: " << entity << std::endl;
		}
	}

	void Player::PutInVehicle(const int playerEntity, const int vehicleEntity, const int seat)
	{
		const int pIndex = ServerEntity::GetIndex(playerEntity);
		const int vIndex = ServerEntity::GetIndex(vehicleEntity);

		// Vehicle Check to make sure it a valid entity and the correct type.
		if (vIndex > -1)
		{
			switch (g_Entities[vIndex].GetType())
			{
			case CServerEntity::Vehicle:
				break;
			default:
				std::wcout << ThisNamespace << L"PutInVehicle Entity " << vehicleEntity << L" is not of type Vehicle." << std::endl;
				return;
			}
		}
		else
		{
			std::wcout << ThisNamespace << L"PutInVehicle Invalid Entity: " << vehicleEntity << std::endl;
			return;
		}

		// Player Check to make sure it a valid entity and the correct type.
		if (pIndex > -1)
		{
			switch (g_Entities[pIndex].GetType())
			{
			case CServerEntity::Player:
				for (int i = 0; i < g_Players.size(); i++)
				{
					if (g_Players[i].GetId() == playerEntity)
					{
						RakNet::BitStream sData;
						sData.Write(vehicleEntity);
						sData.Write(seat);
						g_Server->GetNetworkManager()->GetRPC().Signal("PutInVehicle", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, g_Players[i].GetGUID(), false, false);

						return;
					}
				}
				break;
			default:
				std::wcout << ThisNamespace << L"PutInVehicle Entity " << playerEntity << L" is not of type Player." << std::endl;
				break;
			}
		}
		else
		{
			std::wcout << ThisNamespace << L"PutInVehicle Invalid Entity: " << playerEntity << std::endl;
		}
	}

	const int Player::GetVehicle(const int entity)
	{
		const int index = ServerEntity::GetIndex(entity);

		// Player Check to make sure it a valid entity and the correct type.
		if (index > -1)
		{
			switch (g_Entities[index].GetType())
			{
			case CServerEntity::Player:
				for (int i = 0; i < g_Players.size(); i++)
				{
					if (g_Players[i].GetId() == entity)
					{
						return g_Players[i].GetVehicle();
					}
				}
				break;
			default:
				std::wcout << ThisNamespace << L"GetVehicle Entity " << entity << L" is not of type Player." << std::endl;
				return false;
				break;
			}
		}
		else
		{
			std::wcout << ThisNamespace << L"GetVehicle Invalid Entity: " << entity << std::endl;
			return false;
		}
	}

	const int Player::GetSeat(const int entity)
	{
		const int index = ServerEntity::GetIndex(entity);

		// Player Check to make sure it a valid entity and the correct type.
		if (index > -1)
		{
			switch (g_Entities[index].GetType())
			{
			case CServerEntity::Player:
				for (int i = 0; i < g_Players.size(); i++)
				{
					if (g_Players[i].GetId() == entity)
					{
						return g_Players[i].GetVehicleSeat();
					}
				}
				break;
			default:
				std::wcout << ThisNamespace << L"GetSeat Entity " << entity << L" is not of type Player." << std::endl;
				return false;
				break;
			}
		}
		else
		{
			std::wcout << ThisNamespace << L"GetSeat Invalid Entity: " << entity << std::endl;
			return false;
		}
	}
}