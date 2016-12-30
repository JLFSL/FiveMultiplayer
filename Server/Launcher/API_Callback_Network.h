#pragma once

namespace API
{
	namespace Network
	{
		bool OnPlayerConnecting(void *Instance, const char *guid);
		bool OnPlayerConnected(void *Instance);
	}
}
