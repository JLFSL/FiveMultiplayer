#include "stdafx.h"

namespace API
{
	const char *Visual::ThisNamespace = "API::Visual";

	void Visual::ShowMessageAboveMap(const std::wstring message, const std::wstring pic, const int icontype, const std::wstring sender, const std::wstring subject)
	{
		RakNet::BitStream sData;
		sData.Write(RakNet::RakWString(message.c_str()));
		sData.Write(RakNet::RakWString(pic.c_str()));
		sData.Write(icontype);
		sData.Write(RakNet::RakWString(sender.c_str()));
		sData.Write(RakNet::RakWString(subject.c_str()));

		g_Server->GetNetworkManager()->GetRPC().Signal("ShowMessageAboveMap", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);
	}

	void Visual::ShowMessageAboveMapToPlayer(const int entity, const std::wstring message, const std::wstring pic, const int icontype, const std::wstring sender, const std::wstring subject)
	{
		RakNet::BitStream sData;
		sData.Write(RakNet::RakWString(message.c_str()));
		sData.Write(RakNet::RakWString(pic.c_str()));
		sData.Write(icontype);
		sData.Write(RakNet::RakWString(sender.c_str()));
		sData.Write(RakNet::RakWString(subject.c_str()));

		for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == entity)
			{
				g_Server->GetNetworkManager()->GetRPC().Signal("ShowMessageAboveMap", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, g_Players[i].GetGUID(), false, false);
				break;
			}
		}
	}

	void Visual::SendChatMessage(const std::string message)
	{
		RakNet::BitStream sData;
		sData.Write(RakNet::RakString(message.c_str()));

		g_Server->GetNetworkManager()->GetRPC().Signal("SendMessage", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);
	}

	void Visual::SendChatMessageToPlayer(const int entity, const std::string message)
	{
		RakNet::BitStream sData;
		sData.Write(RakNet::RakString(message.c_str()));

		for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == entity)
			{
				g_Server->GetNetworkManager()->GetRPC().Signal("SendMessage", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, g_Players[i].GetGUID(), false, false);
				break;
			}
		}
	}
	DLL_PUBLIC void Visual::ShowCursor(const int entity, bool show)
	{
		RakNet::BitStream sData;
		sData.Write(show);

		for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == entity)
			{
				g_Server->GetNetworkManager()->GetRPC().Signal("ShowCursor", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, g_Players[i].GetGUID(), false, false);
				break;
			}
		}
	}
}
