#include "stdafx.h"

namespace API
{
	const char *Visual::ThisNamespace = "API::Visual";

	void Visual::ShowMessageAboveMap(const std::string message, const std::string pic, const int icontype, const std::string sender, const std::string subject)
	{
		RakNet::RakString rakMessage = RakNet::RakString(message.c_str());
		RakNet::RakString rakPic = RakNet::RakString(pic.c_str());
		RakNet::RakString rakSender = RakNet::RakString(sender.c_str());
		RakNet::RakString rakSubject = RakNet::RakString(subject.c_str());

		RakNet::BitStream sData;
		sData.Write(rakMessage);
		sData.Write(rakPic);
		sData.Write(icontype);
		sData.Write(rakSender);
		sData.Write(rakSubject);

		g_Server->GetNetworkManager()->GetRPC().Signal("ShowMessageAboveMap", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);
	}

	void Visual::ShowMessageAboveMapToPlayer(const int entity, const std::string message, const std::string pic, const int icontype, const std::string sender, const std::string subject)
	{
		RakNet::RakString rakMessage = RakNet::RakString(message.c_str());
		RakNet::RakString rakPic = RakNet::RakString(pic.c_str());
		RakNet::RakString rakSender = RakNet::RakString(sender.c_str());
		RakNet::RakString rakSubject = RakNet::RakString(subject.c_str());

		RakNet::BitStream sData;
		sData.Write(rakMessage);
		sData.Write(rakPic);
		sData.Write(icontype);
		sData.Write(rakSender);
		sData.Write(rakSubject);

		for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == entity)
			{
				g_Server->GetNetworkManager()->GetRPC().Signal("ShowMessageAboveMap", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, g_Players[i].GetGUID(), false, false);
				break;
			}
		}
	}
}
