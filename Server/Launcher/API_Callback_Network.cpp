#include "stdafx.h"

namespace API
{
	namespace Network
	{
		char *ThisNamespace = "API::Network";

		bool OnPlayerConnecting(void *Instance, const char *guid)
		{
			if (Instance)
			{
				typedef void(*API_OnPlayerConnecting_t)(const char*);
#ifdef WIN32
				API_OnPlayerConnecting_t API_OnPlayerConnecting = (API_OnPlayerConnecting_t)::GetProcAddress((HMODULE)Instance, "API_OnPlayerConnecting");
#else
				API_OnPlayerConnecting_t API_OnPlayerConnecting = (API_OnPlayerConnecting_t)dlsym(&Instance, "API_OnPlayerConnecting");
#endif
				API_OnPlayerConnecting(guid);
				if (!API_OnPlayerConnecting)
					return false;
				return true;
			}
			return false;
		}

		bool OnPlayerConnected(void *Instance)
		{
			if (Instance)
			{
				typedef void(*API_OnPlayerConnected_t)();
#ifdef WIN32
				API_OnPlayerConnected_t API_OnPlayerConnected = (API_OnPlayerConnected_t)::GetProcAddress((HMODULE)Instance, "API_OnPlayerConnected");
#else
				API_OnPlayerConnected_t API_OnPlayerConnected = (API_OnPlayerConnected_t)dlsym(&Instance, "API_OnPlayerConnected");
#endif
				API_OnPlayerConnected();
				if (!API_OnPlayerConnected)
					return false;
				return true;
			}
			return false;
		}
	}
}
