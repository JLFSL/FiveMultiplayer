#include "stdafx.h"

CNetworkManager::CNetworkManager()
{
	// Get RakPeerInterface
	g_RakPeer = RakPeerInterface::GetInstance();
	
	// Get RPC4
	g_RPC = RPC4::GetInstance();

	// Attach RPC4 to RakPeerInterface
	g_RakPeer->AttachPlugin(g_RPC);

	// RakPeerInterface Settings
	g_RakPeer->SetSplitMessageProgressInterval(100);

	cout << endl << "CNetworkManager::Constructed" << endl;
}


CNetworkManager::~CNetworkManager()
{
	// Stop RakNet, stops synchronization
	g_RakPeer->Shutdown(2000);

	// Detach RPC4 from RakPeerInterface
	g_RakPeer->DetachPlugin(g_RPC);

	// Destroy RPC4
	RPC4::DestroyInstance(g_RPC);

	// Destroy RakPeerInterface
	RakPeerInterface::DestroyInstance(g_RakPeer);

	cout << endl << "CNetworkManager::Deconstructed" << endl;
}

bool CNetworkManager::Start()
{
	cout << endl << "CNetworkManager::Starting..." << endl;
	SocketDescriptor socketDescriptor(2322, "127.0.0.1");

	if (g_RakPeer->Startup(MAX_PLAYERS, &socketDescriptor, 1, 0) == RAKNET_STARTED)
	{
		g_RakPeer->SetMaximumIncomingConnections(MAX_PLAYERS);
		g_RakPeer->SetIncomingPassword(CON_PASS, sizeof(CON_PASS));
		g_RakPeer->SetTimeoutTime(15000, UNASSIGNED_SYSTEM_ADDRESS);

		cout << "CNetworkManager::Successfully started" << endl;
		return true;
	}
	return false;
}

void CNetworkManager::Pulse()
{
	Packet *g_Packet = NULL;

	while (g_Packet = g_RakPeer->Receive())
	{
		switch (g_Packet->data[0])
		{
			case ID_NEW_INCOMING_CONNECTION:
			{
				cout << "CNetworkManager::Incoming connection: " << g_Packet->systemAddress.ToString(false) << endl;
				break;
			}
			
			case ID_DISCONNECTION_NOTIFICATION:
			{
				cout << "CNetworkManager::Disconnection: " << g_Packet->systemAddress.ToString(false) << endl;
				break;
			}
			cout << g_Packet->data[0] << endl;
		}
		g_RakPeer->DeallocatePacket(g_Packet);
	}
}
