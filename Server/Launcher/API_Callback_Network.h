#pragma once

namespace API
{
	namespace Network
	{
		bool OnPlayerConnecting(void *Instance, const std::string guid);
		bool OnPlayerConnected(void *Instance, int entity);
		void OnPlayerCommand(void *Instance, const int entity, const std::string message);
		void OnPlayerMessage(void *Instance, const int entity, const std::string message);
	}
}
