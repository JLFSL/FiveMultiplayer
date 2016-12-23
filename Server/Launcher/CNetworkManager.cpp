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

	cout << "[CNetworkManager] Constructed" << endl;
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
	SocketDescriptor socketDescriptor(g_Config->GetPort(), g_Config->GetIp().c_str());

	int Startup = g_RakPeer->Startup(g_Config->GetMaxPlayers(), &socketDescriptor, 1, 0);
	if (!Startup)
	{
		g_RakPeer->SetMaximumIncomingConnections(g_Config->GetMaxPlayers());
		g_RakPeer->SetIncomingPassword(g_Config->GetPassword().c_str(), sizeof(g_Config->GetPassword().c_str()));
		g_RakPeer->SetTimeoutTime(15000, UNASSIGNED_SYSTEM_ADDRESS);

		cout << "[CNetworkManager] Successfully started" << endl;
		return true;
	}
	cout << "[CNetworkManager] Startup error " << Startup << endl;
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
				CPlayerEntity newPlayer;
				newPlayer.Create("User", g_Packet->guid, g_Packet->systemAddress);
				g_Players.push_back(newPlayer);

				PulseMaster();
				break;
			}
			
			case ID_DISCONNECTION_NOTIFICATION:
			{
				for (int i = 0; i < g_Players.size(); i++) {
					if (g_Players[i].GetGUID() == g_Packet->guid) {
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
				for (int i = 0; i < g_Players.size(); i++) {
					if (g_Players[i].GetGUID() == g_Packet->guid) {
						g_Players[i].Update(g_Packet);
					}
				}
				break;
			}
			cout << g_Packet->data[0] << endl;
		}
		g_RakPeer->DeallocatePacket(g_Packet);
	}
	
	if (clock() - p_LastMasterUpdate > (120 * 1000)) {
		PulseMaster();
		p_LastMasterUpdate = clock();
	}
}

void CNetworkManager::PulseMaster()
{
#ifdef _WIN32
	if (g_Config->GetAnnounce()) {
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

		sprintf_s(content, "Content: {\"port\":%d, \"name\":\"%s\", \"players\":{\"amount\":%d, \"max\":%d, \"list\":[%s]}}", g_Config->GetPort(), g_Config->GetServerName().c_str(), g_Players.size(), g_Config->GetMaxPlayers(), playerList.c_str());
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
#endif
}
