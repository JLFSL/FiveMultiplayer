#include "stdafx.h"

namespace API
{
	namespace Network
	{
		char *ThisNamespace = "API::Callback::Network";

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
