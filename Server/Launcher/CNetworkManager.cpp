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
	SocketDescriptor socketDescriptor;
	socketDescriptor.port = g_Config->GetPort();

	int Startup = g_RakPeer->Startup(g_Config->GetMaxPlayers(), &socketDescriptor, 1, 0);
	if (!Startup)
	{
		g_RakPeer->SetMaximumIncomingConnections(g_Config->GetMaxPlayers());
		g_RakPeer->SetIncomingPassword(g_Config->GetPassword().c_str(), sizeof(g_Config->GetPassword().c_str()));
		g_RakPeer->SetLimitIPConnectionFrequency(true);
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
		BitStream g_BitStream(g_Packet->data + 1, g_Packet->length + 1, false);

		switch (g_Packet->data[0])
		{
			case ID_NEW_INCOMING_CONNECTION:
			{
				// API::Network::OnPlayerConnecting Execute
				for (int i = 0; i < g_ApiModules.size(); i++)
				{
					void *Instance = g_ApiModules[i].GetInstance();
					if (!API::Network::OnPlayerConnecting(Instance, g_Packet->guid.ToString()))
					{
						g_RakPeer->CloseConnection(g_Packet->systemAddress, true);
					}
				}

				int playerID = -1;
				for (int i = 0; i < g_Players.size(); i++)
				{
					if (g_Players[i].GetPlayerID() == -1)
					{
						g_Players[i].SetPlayerID(i);
						playerID = i;
						break;
					}
				}

				if (playerID == -1)
				{
					playerID = g_Players.size();
					CPlayerEntity newPlayer;
					newPlayer.Create("User", g_Packet->guid, g_Packet->systemAddress);
					newPlayer.SetPlayerID(playerID);
					g_Players.push_back(newPlayer);
				}

				g_NetworkData->SyncServerWorld(g_Packet->guid);
				
				// API::Network::OnPlayerConnected Execute
				for (int i = 0; i < g_ApiModules.size(); i++)
				{
					void *Instance = g_ApiModules[i].GetInstance();
					API::Network::OnPlayerConnected(Instance, g_Players[playerID].GetEntity(), g_Players[playerID].GetPlayerID());
				}
				
				PulseMaster();
				break;
			}
			case ID_DISCONNECTION_NOTIFICATION:
			{
				for (int i = 0; i < g_Players.size(); i++) {
					if (g_Players[i].GetGUID() == g_Packet->guid)
						g_Players[i].Destroy();
				}
				PulseMaster();
				break;
			}
			case ID_CONNECTION_LOST:
			{
				for (int i = 0; i < g_Players.size(); i++)
				{
					if (g_Players[i].GetGUID() == g_Packet->guid)
						g_Players[i].Destroy();
				}
				PulseMaster();
				break;
			}
			case ID_PACKET_PLAYER:
			{
				for (int i = 0; i < g_Players.size(); i++) {
					if (g_Players[i].GetGUID() == g_Packet->guid) {
						g_Players[i].Update(g_Packet);
					}
				}
				break;
			}
			case ID_PACKET_VEHICLE:
			{
				int t_Id;
				g_BitStream.Read(t_Id);

				for (int i = 0; i < g_Vehicles.size(); i++) {
					if (g_Vehicles[i].GetId() == t_Id) {
						g_Vehicles[i].Update(g_Packet);
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
	if (g_Config->GetAnnounce()) {
		string playerList;

		if (!g_Players.empty()) {
			for (int p = 0; p < g_Players.size(); p++) {
				if (g_Players[p].GetEntity() != -1) {
					ostringstream oss;
					oss << "{\"id\":" << g_Players[p].GetEntity() << ",\"name\":\"" << g_Players[p].GetUsername() << "\"}";
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

		std::sprintf(content, "Content: {\"port\":%d, \"name\":\"%s\", \"players\":{\"amount\":%d, \"max\":%d, \"list\":[%s]}}", g_Config->GetPort(), g_Config->GetServerName().c_str(), g_Players.size(), g_Config->GetMaxPlayers(), playerList.c_str());
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
}
