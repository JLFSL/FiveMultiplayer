#include "stdafx.h"

namespace API
{
	namespace Network
	{
		const char *ThisNamespace = "API::Network";

		bool OnPlayerConnecting(void *Instance, const std::string guid)
		{
			if (Instance)
			{
				typedef bool(*API_OnPlayerConnecting_t)(const std::string);
#ifdef WIN32
				API_OnPlayerConnecting_t API_OnPlayerConnecting = (API_OnPlayerConnecting_t)::GetProcAddress((HMODULE)Instance, "API_OnPlayerConnecting");
#else
				API_OnPlayerConnecting_t API_OnPlayerConnecting = (API_OnPlayerConnecting_t)dlsym(Instance, "API_OnPlayerConnecting");
#endif
				return API_OnPlayerConnecting(guid);
			}
			return true;
		}

		bool OnPlayerConnected(void *Instance, int entity, int playerid)
		{
			if (Instance)
			{
				typedef bool(*API_OnPlayerConnected_t)(int, int);
#ifdef WIN32
				API_OnPlayerConnected_t API_OnPlayerConnected = (API_OnPlayerConnected_t)::GetProcAddress((HMODULE)Instance, "API_OnPlayerConnected");
#else
				API_OnPlayerConnected_t API_OnPlayerConnected = (API_OnPlayerConnected_t)dlsym(Instance, "API_OnPlayerConnected");
#endif
				return API_OnPlayerConnected(entity, playerid);
			}
			return true;
		}

		void OnPlayerCommand(void *Instance, const int entity, const std::string message)
		{
			if (Instance)
			{
				typedef void(*API_OnPlayerCommand_t)(int, std::string);
#ifdef WIN32
				API_OnPlayerCommand_t API_OnPlayerCommand = (API_OnPlayerCommand_t)::GetProcAddress((HMODULE)Instance, "API_OnPlayerCommand");
#else
				API_OnPlayerCommand_t API_OnPlayerCommand = (API_OnPlayerCommand_t)dlsym(Instance, "API_OnPlayerCommand");
#endif
				API_OnPlayerCommand(entity, message);
			}
		}

		void OnPlayerMessage(void *Instance, const int entity, const std::string message)
		{
			if (Instance)
			{
				typedef void(*API_OnPlayerMessage_t)(int, std::string);
#ifdef WIN32
				API_OnPlayerMessage_t API_OnPlayerMessage = (API_OnPlayerMessage_t)::GetProcAddress((HMODULE)Instance, "API_OnPlayerMessage");
#else
				API_OnPlayerMessage_t API_OnPlayerMessage = (API_OnPlayerMessage_t)dlsym(Instance, "API_OnPlayerMessage");
#endif
				API_OnPlayerMessage(entity, message);
			}
		}
	}
}
