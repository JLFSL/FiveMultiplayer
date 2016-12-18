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

	cout << endl << "[CNetworkManager] Constructed" << endl;
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

	cout << endl << "[CNetworkManager] Deconstructed" << endl;
}

bool CNetworkManager::Start()
{
	cout << endl << "[CNetworkManager] Starting..." << endl;
	SocketDescriptor socketDescriptor(2322, "127.0.0.1");

	if (g_RakPeer->Startup(MAX_PLAYERS, &socketDescriptor, 1, 0) == RAKNET_STARTED)
	{
		const char *pass = "test";

		g_RakPeer->SetMaximumIncomingConnections(MAX_PLAYERS);
		g_RakPeer->SetIncomingPassword(pass, sizeof(pass));
		g_RakPeer->SetTimeoutTime(15000, UNASSIGNED_SYSTEM_ADDRESS);

		cout << "[CNetworkManager] Successfully started" << endl;
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
				CPlayerEntity newPlayer;
				newPlayer.Create("User", g_Packet->guid.ToString(), g_Packet->systemAddress.ToString(false));

				g_Players.push_back(newPlayer);

				PulseMaster();
				break;
			}
			
			case ID_DISCONNECTION_NOTIFICATION:
			{
				for (int i = 0; i < g_Players.size(); i++) {
					if (strcmp(g_Players[i].GetIp(), g_Packet->systemAddress.ToString(false)) == 0) {
						g_Players[i].Destroy();

						g_Players.erase(g_Players.begin() + i);
						g_Players.shrink_to_fit();
					}
				}
				PulseMaster();
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
	
	if (clock() - p_LastMasterUpdate > (120 * 1000)) {
		PulseMaster();
		p_LastMasterUpdate = clock();
	}
}

void CNetworkManager::PulseMaster()
{
	string playerList;

	if (!g_Players.empty()) {
		for (int p = 0; p < g_Players.size(); p++) {
			if (g_Players[p].GetId() != -1) {
				ostringstream oss;
				oss << "{\"id\":" << g_Players[p].GetId() << ",\"name\":\"" << g_Players[p].GetUsername() << "\"}";
				string player = oss.str();

				if (p < g_Players.size() - 1)
					player.push_back(',');

				playerList.append(player);
			}
		}
	}

	CURL *hnd = curl_easy_init();

	struct curl_slist *headers = NULL;
	char content[1024];

	sprintf_s(content, "Content: {\"port\":%s, \"name\":\"%s\", \"players\":{\"amount\":%d, \"max\":%d, \"list\":[%s]}}", "2322", "(0.2a) Testing Server [Ubuntu,FR]", g_Players.size(), 50, playerList.c_str());
	headers = curl_slist_append(headers, "content-type: application/x-www-form-urlencoded");
	headers = curl_slist_append(headers, "cache-control: no-cache");
	headers = curl_slist_append(headers, content);
	headers = curl_slist_append(headers, "authorization: FiveMP Token 13478817f618329e");

	curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
	curl_easy_setopt(hnd, CURLOPT_URL, "http://176.31.142.113:7001/v2/servers");
	curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);
	curl_easy_setopt(hnd, CURLOPT_NOBODY, 1);

	CURLcode ret = curl_easy_perform(hnd);
}
