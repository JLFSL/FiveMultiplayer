#include "stdafx.h"

namespace API
{
	const char *CEF::ThisNamespace = "API::CEF::";

	DLL_PUBLIC void CEF::LoadURL(const int entity, std::string url, std::string appcode, bool remote)
	{
		const int index = ServerEntity::GetIndex(entity);
		if (index != -1)
		{
			RakNet::BitStream sData;
			sData.Write(RakString(url.c_str()));
			sData.Write(RakString(appcode.c_str()));
			sData.Write(remote);

			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetId() == entity)
				{
					g_Server->GetNetworkManager()->GetRPC().Signal("LoadURL", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, g_Players[i].GetGUID(), false, false);
					break;
				}
			}
			return;
		}
		std::cout << "[" << ThisNamespace << "::LoadURL] Entity " << entity << " invalid." << std::endl;
	}

	DLL_PUBLIC void CEF::JavaScriptCall(const int entity, std::string call)
	{
		const int index = ServerEntity::GetIndex(entity);
		if (index != -1)
		{
			RakNet::BitStream sData;
			sData.Write(RakString(call.c_str()));

			for (int i = 0; i < g_Players.size(); i++)
			{
				if (g_Players[i].GetId() == entity)
				{
					g_Server->GetNetworkManager()->GetRPC().Signal("JavaScriptCall", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, g_Players[i].GetGUID(), false, false);
					break;
				}
			}
			return;
		}
		std::cout << "[" << ThisNamespace << "::JavaScriptCall] Entity " << entity << " invalid." << std::endl;
	}

}