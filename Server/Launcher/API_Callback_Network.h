#pragma once

namespace API
{
	namespace Network
	{
		bool OnPlayerConnecting(void *Instance, const std::string guid);
		bool OnPlayerConnected(void *Instance, int entity, int playerid);
	}
}
