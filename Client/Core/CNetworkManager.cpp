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

	Logger::Msg("CNetworkManager::Constructed");

	g_ConnectionState = CONSTATE_DISC;
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

	Logger::Msg("CNetworkManager::Deconstructed");
}

bool CNetworkManager::Start()
{
	Logger::Msg("CNetworkManager::Started");

	// Return whether Startup worked or not
	return (g_RakPeer->Startup(1, &SocketDescriptor(), 1, THREAD_PRIORITY_NORMAL) == RAKNET_STARTED);
}

void CNetworkManager::Stop()
{
	// Disconnect if we're connected
	if (g_ConnectionState == CONSTATE_COND)
		Disconnect();

	// Stop our RakPeerInterface
	g_RakPeer->Shutdown(500);

	Logger::Msg("CNetworkManager::Stopped");
}

void CNetworkManager::Connect(const char *ip, const char *pass, int port)
{
	// Disconnect if we're already connected
	if (g_ConnectionState == CONSTATE_COND)
		Disconnect();

	// Set our last connection so we can connect again later and we set our state to connecting
	SetLastConnection(ip, pass, port);
	g_ConnectionState = CONSTATE_CONN;

	// Connect to the server, leaving the result
	int Result = g_RakPeer->Connect(ip, port, pass, sizeof(pass));

	// Check if connection failed, then set our state to failed
	if (Result != 0)
	{
		g_ConnectionState = CONSTATE_FAIL;
		Logger::Msg("Failed to connect, errorcode: %d", Result);
		return;
	}
}

void CNetworkManager::Disconnect()
{
	// Don't do anything if we're not connected
	if (g_ConnectionState == CONSTATE_DISC)
		return;

	// Stop RakPeer from accepting anymore incoming packets
	g_RakPeer->CloseConnection(g_SystemAddr, true);

	// Set our state to disconnected
	g_ConnectionState = CONSTATE_DISC;

	// Reinitialize our RakPeerInterface
	Stop();
	Start();

	// Clean the server GUID
	g_SystemAddr = UNASSIGNED_SYSTEM_ADDRESS;

	// Remove all existing players
	for (int i = 0; i < g_Players.size(); i++) {
		g_Players[i].Destroy();
	}
	std::cout << "[CPlayerEntity] Players Online: " << g_Players.size() << std::endl;

	Logger::Msg("CNetworkManager::Disconnected");
}

void CNetworkManager::Pulse()
{
	// Don't do anything if we're disconnected
	if (g_ConnectionState == CONSTATE_DISC || g_ConnectionState == CONSTATE_FAIL)
		return;

	Packet *g_Packet = NULL;

	while (g_Packet = g_RakPeer->Receive())
	{
		BitStream g_BitStream(g_Packet->data + 1, g_Packet->length + 1, false);

		switch (g_Packet->data[0])
		{
			case ID_NO_FREE_INCOMING_CONNECTIONS:
			{
				Logger::Msg("Failed to connect, max client", g_Packet->data[0]);
				break;
			}
			case ID_INVALID_PASSWORD:
			{
				Logger::Msg("Failed to connect, invalid password", g_Packet->data[0]);
				break;
			}
			case ID_CONNECTION_ATTEMPT_FAILED:
			{
				Logger::Msg("Failed to connect, failed", g_Packet->data[0]);
				break;
			}
			case ID_CONNECTION_BANNED:
			{
				Logger::Msg("Failed to connect, banned", g_Packet->data[0]);
				break;
			}
			case ID_CONNECTION_REQUEST_ACCEPTED:
			{
				// Set the server GUID
				g_SystemAddr = g_Packet->systemAddress;

				// Set our state to connected
				g_ConnectionState = CONSTATE_COND;

				Logger::Msg("CNetworkManager::Connected");
				break;
			}
			case ID_PACKET_TEST:
			{
				RakNetGUID tempGUID;
				g_BitStream.Read(tempGUID);

				bool exist = false;

				if (!g_Players.empty()) {
					for (int i = 0; i < g_Players.size(); i++) {
						if (std::strcmp(g_Players[i].GetGUID().ToString(), tempGUID.ToString()) == 0) {
							g_Players[i].Update(g_Packet);
							exist = true;
							i = g_Players.size();
						}
					}
				}
				if (!exist) {
					CPlayerEntity newPlayer;
					newPlayer.Create("User", tempGUID);
					g_Players.push_back(newPlayer);

					std::cout << "[CPlayerEntity] Players Online: " << g_Players.size() << std::endl;
				}
				break;
			}
			Logger::Msg("%d", g_Packet->data[0]);
		}
		g_RakPeer->DeallocatePacket(g_Packet);
	}
}

