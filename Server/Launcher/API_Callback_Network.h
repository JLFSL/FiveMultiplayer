#ifndef __APICALLNETWORK_H__
#define __APICALLNETWORK_H__
namespace API
{
	namespace Network
	{
		bool OnPlayerConnecting(void *Instance, const std::string guid, const std::string playername);
		bool OnPlayerConnected(void *Instance, int entity);

		void OnPlayerDisconnected(void *Instance, int entity, int reason);

		void OnPlayerCommand(void *Instance, const int entity, const std::string message);
		void OnPlayerMessage(void *Instance, const int entity, const std::string message);
	}
}
#endif