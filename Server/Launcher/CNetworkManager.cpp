#include "stdafx.h"

CNetworkManager::CNetworkManager()
{
	// Get RakPeerInterface
	g_RakPeer = RakPeerInterface::GetInstance();
	
	// Retrieve instances of RPC4, DirectoryDeltaTransfer and FileListTransfer
	g_RPC = RPC4::GetInstance();
	g_DirTransfer = DirectoryDeltaTransfer::GetInstance();
	g_FileTransfer = FileListTransfer::GetInstance();
	
	// Attach RPC4, DirectoryDeltaTransfer and FileListTransfer to RakPeerInterface
	g_RakPeer->AttachPlugin(g_RPC);
	g_RakPeer->AttachPlugin(g_DirTransfer);
	g_RakPeer->AttachPlugin(g_FileTransfer);

	// Set the right transfer method
	g_DirTransfer->SetFileListTransferPlugin(g_FileTransfer);

	// Set our transfer directory and shared folder
	g_DirTransfer->SetApplicationDirectory(".//");
	g_DirTransfer->AddUploadsFromSubdirectory("clientplugins");

	// RakPeerInterface Settings
	g_RakPeer->SetSplitMessageProgressInterval(100);

	std::cout << "[CNetworkManager] Constructed" << std::endl;
}


CNetworkManager::~CNetworkManager()
{
	// Stop RakNet, stops synchronization
	g_RakPeer->Shutdown(2000);

	// Detach RPC4, DirectoryDeltaTransfer and FileListTransfer from RakPeerInterface
	g_RakPeer->DetachPlugin(g_RPC);
	g_RakPeer->DetachPlugin(g_DirTransfer);
	g_RakPeer->DetachPlugin(g_FileTransfer);

	// Destroy RPC4, DirectoryDeltaTransfer and FileListTransfer
	RPC4::DestroyInstance(g_RPC);
	DirectoryDeltaTransfer::DestroyInstance(g_DirTransfer);
	FileListTransfer::DestroyInstance(g_FileTransfer);

	// Destroy RakPeerInterface
	RakPeerInterface::DestroyInstance(g_RakPeer);

	std::cout << "[CNetworkManager] Deconstructed" << std::endl;
}

bool CNetworkManager::Start()
{
	std::cout << "[CNetworkManager] Starting..." << std::endl;
	SocketDescriptor socketDescriptor;
	socketDescriptor.port = g_Config->GetPort();

	int Startup = g_RakPeer->Startup(g_Config->GetMaxPlayers(), &socketDescriptor, 1, 0);
	if (!Startup)
	{
		// Set all connection data after interface has started
		g_RakPeer->SetMaximumIncomingConnections(g_Config->GetMaxPlayers());
		g_RakPeer->SetIncomingPassword(g_Config->GetPassword().c_str(), sizeof(g_Config->GetPassword().c_str()));
		g_RakPeer->SetLimitIPConnectionFrequency(true);
		g_RakPeer->SetTimeoutTime(15000, UNASSIGNED_SYSTEM_ADDRESS);

		std::cout << "[CNetworkManager] Successfully started" << std::endl;
		std::cout << "[CNetworkManager] " << g_DirTransfer->GetNumberOfFilesForUpload() << " files suitable for upload to clients" << std::endl;

		// Send data to the masterlist, so others can see that the server is online.
		PulseMaster();
		return true;
	}
	std::cout << "[CNetworkManager] Startup error " << Startup << std::endl;
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
				// new connection
				break;
			}
			case ID_DISCONNECTION_NOTIFICATION:
			{
				PlayerLeft(g_Packet, 0);
				PulseMaster();
				break;
			}
			case ID_CONNECTION_LOST:
			{
				PlayerLeft(g_Packet, 1);
				PulseMaster();
				break;
			}
			case ID_PACKET_PLAYER:
			{
				for (int i = 0; i < g_Players.size(); i++) {
					if (g_Players[i].GetGUID() == g_Packet->guid) {
						g_Players[i].Update(g_Packet);
						break;
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
						break;
					}
				}
				break;
			}
			case ID_PACKET_OBJECT:
			{
				int t_Id;
				g_BitStream.Read(t_Id);

				for (int i = 0; i < g_Objects.size(); i++)
				{
					if (g_Objects[i].GetId() == t_Id)
					{
						g_Objects[i].Update(g_Packet);
						break;
					}
				}
				break;
			}
			case ID_CHAT_MESSAGE:
			{
				int chatid;

				for (int i = 0; i < g_Players.size(); i++)
				{
					if (g_Players[i].GetGUID() == g_Packet->guid)
					{
						chatid = g_Players[i].GetId();
						break;
					}
				}

				RakString message;
				g_BitStream.Read(message);
				
				if (message.C_String()[0] == '/')
				{
					for (int i = 0; i < g_ApiModules.size(); i++)
					{
						void *Instance = g_ApiModules[i].GetInstance();
						API::Network::OnPlayerCommand(Instance, chatid, message.C_String());
					}
				}
				else
				{
					for (int i = 0; i < g_ApiModules.size(); i++)
					{
						void *Instance = g_ApiModules[i].GetInstance();
						API::Network::OnPlayerMessage(Instance, chatid, message.C_String());
					}
				}
				break;
			}
			case ID_REQUEST_SERVER_SYNC:
			{
				// New connection
				NewIncomingConnection(g_Packet);

				// Ping Master
				PulseMaster();
				
				break;
			}
			std::cout << g_Packet->data[0] << std::endl;
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
		std::string playerList;

		if (!g_Players.empty()) {
			for (int p = 0; p < g_Players.size(); p++) {
				if (g_Players[p].GetId() != -1 && g_Players[p].GetId() != -1) {
					std::ostringstream oss;
					oss << "{\"id\":" << g_Players[p].GetId() << ",\"name\":\"" << g_Players[p].GetUsername() << "\"}";
					std::string player = oss.str();

					if (p < g_Players.size() - 1)
						player.push_back(',');

					playerList.append(player);
				}
			}
		}

		CURL *hnd = curl_easy_init();

		struct curl_slist *headers = NULL;
		char content[1024];

		std::sprintf(content, "{\"port\": %d, \"name\": \"%s\", \"players\": {\"amount\": %d, \"max\": %d, \"list\":[%s]}}", g_Config->GetPort(), g_Config->GetServerName().c_str(), CPlayerEntity::Amount, g_Config->GetMaxPlayers(), playerList.c_str());
		headers = curl_slist_append(headers, "cache-control: no-cache");
		headers = curl_slist_append(headers, "content-type: application/json");
		headers = curl_slist_append(headers, "authorization: Server 21992add0d9d4f718b29ebc8adeb46f5");

		curl_easy_setopt(hnd, CURLOPT_CUSTOMREQUEST, "POST");
		curl_easy_setopt(hnd, CURLOPT_URL, "http://api.five-multiplayer.net/api/v4/servers");
		curl_easy_setopt(hnd, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(hnd, CURLOPT_POSTFIELDS, content);
		curl_easy_setopt(hnd, CURLOPT_VERBOSE, 0L);
		curl_easy_setopt(hnd, CURLOPT_WRITEFUNCTION, &CNetworkManager::my_dummy_write);
		
		CURLcode ret = curl_easy_perform(hnd);

		curl_easy_cleanup(hnd);
	}
}

/* Never writes anything, just returns the size presented */
size_t CNetworkManager::my_dummy_write(char *ptr, size_t size, size_t nmemb, void *userdata)
{
	return size * nmemb;
}

void CNetworkManager::NewIncomingConnection(RakNet::Packet  *g_Packet)
{
	BitStream g_BitStream(g_Packet->data + 1, g_Packet->length + 1, false);
	RakString playerName, version, buildNumber;

	g_BitStream.Read(playerName);
	g_BitStream.Read(version);
	g_BitStream.Read(buildNumber);

	if (version.StrCmp(RakString(INFO_VERSION)) != 0 || buildNumber.StrCmp(RakString(INFO_BUILD_NUMBER)) != 0)
	{
		std::cout << "Invalid Version: " << version.C_String() << "." << buildNumber.C_String() << std::endl;
		g_RakPeer->CloseConnection(g_Packet->systemAddress, true);
		return;
	}

	// API::Network::OnPlayerConnecting Execute
	for (int i = 0; i < g_ApiModules.size(); i++)
	{
		void *Instance = g_ApiModules[i].GetInstance();
		if (!API::Network::OnPlayerConnecting(Instance, g_Packet->guid.ToString(), playerName.C_String()))
		{
			g_RakPeer->CloseConnection(g_Packet->systemAddress, true);
			return;
		}
	}

	NetworkSync::SyncServerWorld(g_Packet->guid);

	// Tell the client to load the models
	CModelCache::LoadModels(g_Packet->guid);

	// Tell the client they are now done connecting
	BitStream bitstream;
	bitstream.Write((unsigned char)ID_REQUEST_SERVER_SYNC);
	CNetworkManager::GetInterface()->Send(&bitstream, LOW_PRIORITY, RELIABLE_ORDERED, 0, g_Packet->systemAddress, false);

	const int index = g_Players.size();

	CPlayerEntity newPlayer;
	newPlayer.Create(playerName.C_String(), g_Packet->guid, g_Packet->systemAddress);
	g_Players.push_back(newPlayer);

	// API::Network::OnPlayerConnected Execute
	for (int i = 0; i < g_ApiModules.size(); i++)
	{
		void *Instance = g_ApiModules[i].GetInstance();
		API::Network::OnPlayerConnected(Instance, g_Players[index].GetId());
	}
}

void CNetworkManager::PlayerLeft(RakNet::Packet  *g_Packet, const int reason)
{
	for (int i = 0; i < g_Players.size(); i++)
	{
		if (g_Players[i].GetGUID() == g_Packet->guid)
		{
			if (g_Players[i].GetVehicle() != -1)
			{
				for (int v = 0; v < g_Vehicles.size(); v++)
				{
					if (g_Players[i].GetVehicle() == g_Vehicles[v].GetId())
					{
						g_Vehicles[v].SetOccupant(g_Players[i].GetVehicleSeat(), -1);
					}

					if (g_Vehicles[v].GetAssignee() == g_Packet->guid)
					{
						ServerEntity::SetAssignee(g_Vehicles[v].GetId(), UNASSIGNED_RAKNET_GUID);
					}
				}
			}

			// API::Network::OnPlayerConnected Execute
			for (int i = 0; i < g_ApiModules.size(); i++)
			{
				void *Instance = g_ApiModules[i].GetInstance();
				API::Network::OnPlayerDisconnected(Instance, g_Players[i].GetId(), reason);
			}


			g_Players[i].Destroy();
			g_Players.erase(g_Players.begin() + i);
			g_Players.shrink_to_fit();

			break;
		}
	}

	// UnAssignment of Phsyics types
	for (int i = 0; i < g_Vehicles.size(); i++) 
	{
		if (g_Vehicles[i].GetAssignee() == g_Packet->guid)
		{
			RakNet::BitStream sData;
			sData.Write(g_Vehicles[i].GetId());
			g_Server->GetNetworkManager()->GetRPC().Signal("DropEntityAssignment", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_RAKNET_GUID, true, false);
		}
	}

	for (int i = 0; i < g_Objects.size(); i++)
	{
		if (g_Objects[i].GetAssignee() == g_Packet->guid)
		{
			RakNet::BitStream sData;
			sData.Write(g_Objects[i].GetId());
			g_Server->GetNetworkManager()->GetRPC().Signal("DropEntityAssignment", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_RAKNET_GUID, true, false);
		}
	}

}