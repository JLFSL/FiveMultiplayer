#include "stdafx.h"

#include "RPCManager.h"
#include "RPCEntity.h"

namespace RPC
{
	namespace Manager
	{
		RPCMessage rpcmessages[] = {
		#pragma region Assignment
			{ "TakeEntityAssignment", RPC::Entity::TakeEntityAssignment },
			{ "DropEntityAssignment", RPC::Entity::DropEntityAssignment },
		#pragma endregion
			{ "RequestEntityData", RPC::Entity::RequestData }
		};

		void RegisterRPCMessages()
		{
			for (int i = 0; i < sizeof(rpcmessages) / sizeof(RPCMessage); i++)
			{
				g_Network->GetRPC().RegisterSlot(rpcmessages[i].name, rpcmessages[i].functionPointer, 0);
			}

			std::cout << "[RPCManager] Registered RPC Messages" << std::endl;
		}

		void UnregisterRPCMessages()
		{
			for (int i = 0; i < sizeof(rpcmessages) / sizeof(RPCMessage); i++)
			{
				g_Network->GetRPC().UnregisterSlot(rpcmessages[i].name);
			}

			std::cout << "[RPCManager] Unregistered RPC Messages" << std::endl;
		}
	}
}