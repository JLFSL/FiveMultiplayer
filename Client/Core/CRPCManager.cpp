#include "stdafx.h"

CRPCManager::RPCMessage rpcmessages[] = {
	{ "ShowMessageAboveMap", CRPCVisual::ShowMessageAboveMap }
};

void CRPCManager::RegisterRPCMessages()
{
	for (int i = 0; i < sizeof(rpcmessages) / sizeof(RPCMessage); i++)
	{
		g_Core->GetNetworkManager()->GetRPC().RegisterSlot(rpcmessages[i].name, rpcmessages[i].functionPointer, 0);
	}

	Logger::Msg("CRPCManager:: Registered RPC Messages");
}

void CRPCManager::UnregisterRPCMessages()
{
	for (int i = 0; i < sizeof(rpcmessages) / sizeof(RPCMessage); i++)
	{
		g_Core->GetNetworkManager()->GetRPC().UnregisterSlot(rpcmessages[i].name);
	}

	Logger::Msg("CRPCManager:: Unregistered RPC Messages");
}