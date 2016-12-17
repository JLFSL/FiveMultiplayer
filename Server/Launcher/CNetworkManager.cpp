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

unsigned long m_ulLastSyncSent;

float x;
float y;
float z;

float vx;
float vy;
float vz;

float rx;
float ry;
float rz;
float rw;

bool veh = true;

void CNetworkManager::Pulse()
{
	Packet *g_Packet = NULL;

	while (g_Packet = g_RakPeer->Receive())
	{
		BitStream playerpackrec(g_Packet->data + 1, g_Packet->length + 1, false);

		switch (g_Packet->data[0])
		{
			case ID_NEW_INCOMING_CONNECTION:
			{
				cout << "CNetworkManager::Incoming connection: " << g_Packet->systemAddress.ToString(false) << endl;

				CPlayerEntity newPlayer;
				newPlayer.Create("test", g_Packet->guid.ToString());

				g_Players.push_back(newPlayer);
				break;
			}
			
			case ID_DISCONNECTION_NOTIFICATION:
			{
				cout << "CNetworkManager::Disconnection: " << g_Packet->systemAddress.ToString(false) << endl;

				for (int i = 0; i < g_Players.size(); i++) {
					if (g_Players[i].GetGuid() == g_Packet->guid.ToString()) {
						g_Players.erase(g_Players.begin() + i);
						g_Players.shrink_to_fit();
					}
				}
				break;
			}

			case ID_PACKET_TEST:
			{
				playerpackrec.Read(x);
				playerpackrec.Read(y);
				playerpackrec.Read(z);
				playerpackrec.Read(rx);
				playerpackrec.Read(ry);
				playerpackrec.Read(rz);
				playerpackrec.Read(rw);
				playerpackrec.Read(vx);
				playerpackrec.Read(vy);
				playerpackrec.Read(vz);

				//cout << "packet received" << endl;
				break;
			}
			cout << g_Packet->data[0] << endl;
		}
		g_RakPeer->DeallocatePacket(g_Packet);
	}

	if (m_ulLastSyncSent + (1000 / CServer::GetInstance()->GetSyncRate()) <= clock())
	{
		BitStream playerpack;

		playerpack.Write((unsigned char)ID_PACKET_TEST);
		playerpack.Write(x);
		playerpack.Write(y);
		if (!veh)
		{
			playerpack.Write(z - 1.0f);
		}
		else
		{
			playerpack.Write(z);
		}

		playerpack.Write(rx);
		playerpack.Write(ry);
		playerpack.Write(rz);
		playerpack.Write(rw);
		playerpack.Write(vx);
		playerpack.Write(vy);
		playerpack.Write(vz);

		g_RakPeer->Send(&playerpack, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 0, UNASSIGNED_SYSTEM_ADDRESS, true);

		//cout << "packetsent" << endl;

		m_ulLastSyncSent = clock();
	}
}
