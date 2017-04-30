#include "stdafx.h"

RakPeerInterface		*CNetworkManager::g_RakPeer = nullptr;
RPC4					*CNetworkManager::g_RPC = nullptr;
DirectoryDeltaTransfer	*CNetworkManager::g_DirTransfer = nullptr;
FileListTransfer		*CNetworkManager::g_FileTransfer = nullptr;

std::string		CNetworkManager::g_lastIP;
std::string		CNetworkManager::g_lastPass;
int				CNetworkManager::g_lastPort;
SystemAddress	CNetworkManager::g_SystemAddr;

int CNetworkManager::g_ConnectionState = 0;

void CNetworkManager::Initialize()
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

	// Set our transfer directory
	g_DirTransfer->SetApplicationDirectory(".//");

	// Set the right transfer method
	g_DirTransfer->SetFileListTransferPlugin(g_FileTransfer);

	// RakPeerInterface Settings
	g_RakPeer->SetSplitMessageProgressInterval(100);

	Logger::Msg("CNetworkManager::Constructed");

	g_ConnectionState = CONSTATE_DISC;
}

void CNetworkManager::Destroy()
{
	// Stop RakNet, stops synchronization
	g_RakPeer->Shutdown(2000);

	// Detach RPC4 from RakPeerInterface
	g_RakPeer->DetachPlugin(g_RPC);

	// Detach RPC4, DirectoryDeltaTransfer and FileListTransfer from RakPeerInterface
	g_RakPeer->DetachPlugin(g_RPC);
	g_RakPeer->DetachPlugin(g_DirTransfer);
	g_RakPeer->DetachPlugin(g_FileTransfer);

	// Destroy RPC4, DirectoryDeltaTransfer and FileListTransfer
	RPC4::DestroyInstance(g_RPC);
	DirectoryDeltaTransfer::DestroyInstance(g_DirTransfer);
	FileListTransfer::DestroyInstance(g_FileTransfer);

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

	DirectXRenderer::ConnectionProg = "Establishing Connection";

	// Set our last connection so we can connect again later and we set our state to connecting
	SetLastConnection(ip, pass, port);
	g_ConnectionState = CONSTATE_CONN;

	// Connect to the server, leaving the result
	int Result = g_RakPeer->Connect(ip, port, pass, sizeof(pass));

	// Check if connection failed, then set our state to failed
	if (Result != 0)
	{
		DirectXRenderer::ConnectionProg = "Connection Failed";
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

	// Force streamout all entities
	CStreamer::ForceStreamOut();

	// Stop RakPeer from accepting anymore incoming packets
	g_RakPeer->CloseConnection(g_SystemAddr, true);

	// Set our state to disconnected
	g_ConnectionState = CONSTATE_DISC;

	// Unregister RPCs
	CRPCManager::UnregisterRPCMessages();

	// Reinitialize our RakPeerInterface
	Stop();
	Start();

	// Register RPCs
	CRPCManager::RegisterRPCMessages();

	// Clean the server GUID
	g_SystemAddr = UNASSIGNED_SYSTEM_ADDRESS;

	// Remove all existing entities
	if (!g_Entities.empty())
	{
		for (int i = (g_Entities.size() - 1); i > -1; i--)
		{
			g_Entities.erase(g_Entities.begin() + i);
		}
		// Shrink vector so size is correct.
		g_Entities.shrink_to_fit();
	}

	// Remove all existing players
	if (!g_Players.empty())
	{
		for (int i = (g_Players.size() - 1); i > -1; i--)
		{
			if (g_Players[i].IsCreated())
				g_Players[i].Destroy();
			g_Players.erase(g_Players.begin() + i);
		}
		// Shrink vector so size is correct.
		g_Players.shrink_to_fit();
	}
	
	if (!g_Vehicles.empty())
	{
		// Remove all existing vehicles
		for (int i = (g_Vehicles.size() - 1); i > -1; i--)
		{
			g_Vehicles[i].Destroy();
			g_Vehicles.erase(g_Vehicles.begin() + i);
		}
		// Shrink vector so size is correct.
		g_Vehicles.shrink_to_fit();
	}
	
	if (!g_Objects.empty())
	{
		// Remove all existing objects
		for (int i = (g_Objects.size() - 1); i > -1; i--)
		{
			g_Objects[i].Destroy();
			g_Objects.erase(g_Objects.begin() + i);
		}
		// Shrink vector so size is correct.
		g_Objects.shrink_to_fit();
	}
	
	if (!g_Npcs.empty())
	{
		// Remove all existing npcs
		for (int i = (g_Npcs.size() - 1); i > -1; i--)
		{
			g_Npcs[i].Destroy();
			g_Npcs.erase(g_Npcs.begin() + i);
		}
		// Shrink vector so size is correct.
		g_Npcs.shrink_to_fit();
	}
	
	if (!g_Checkpoints.empty())
	{
		// Remove all existing checkpoints
		for (int i = (g_Checkpoints.size() - 1); i > -1; i--)
		{
			g_Checkpoints[i].Destroy();
			g_Checkpoints.erase(g_Checkpoints.begin() + i);
		}
		// Shrink vector so size is correct.
		g_Checkpoints.shrink_to_fit();
	}

	CChat::ClearChat();
	
	CWorld::Destroy();
	
	CefRenderer::getBrowser()->GetMainFrame()->LoadURL(CefString("about:blank"));

	Logger::Msg("CNetworkManager::Disconnected");
}

class TestCB : public RakNet::FileListTransferCBInterface
{
public:
	bool OnFile(
		OnFileStruct *onFileStruct)
	{
		assert(onFileStruct->byteLengthOfThisFile >= onFileStruct->bytesDownloadedForThisFile);
		printf("%i. (100%%) %i/%i %s %ib / %ib\n", onFileStruct->setID, onFileStruct->fileIndex + 1, onFileStruct->numberOfFilesInThisSet, onFileStruct->fileName, onFileStruct->byteLengthOfThisFile, onFileStruct->byteLengthOfThisSet);

		// Return true to have RakNet delete the memory allocated to hold this file.
		// False if you hold onto the memory, and plan to delete it yourself later
		return true;
	}

	virtual void OnFileProgress(FileProgressStruct *fps)
	{
		assert(fps->onFileStruct->byteLengthOfThisFile >= fps->onFileStruct->bytesDownloadedForThisFile);
		printf("%i (%i%%) %i/%i %s %ib / %ib\n", fps->onFileStruct->setID, (int)(100.0*(double)fps->partCount / (double)fps->partTotal),
			fps->onFileStruct->fileIndex + 1,
			fps->onFileStruct->numberOfFilesInThisSet,
			fps->onFileStruct->fileName,
			fps->onFileStruct->byteLengthOfThisFile,
			fps->onFileStruct->byteLengthOfThisSet,
			fps->firstDataChunk);
	}

	virtual bool OnDownloadComplete(DownloadCompleteStruct *dcs)
	{
		printf("Download complete.\n");

		// Returning false automatically deallocates the automatically allocated handler that was created by DirectoryDeltaTransfer
		return false;
	}

} transferCallback;

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
			case ID_UNCONNECTED_PONG:
			{
				break;
			}
			case ID_ADVERTISE_SYSTEM:
			{
				break;
			}
			case ID_DOWNLOAD_PROGRESS:
			{
				break;
			}
			case ID_IP_RECENTLY_CONNECTED:
			{
				CNetworkManager::Disconnect();
				Logger::Msg("Failed to connect, recently connected", g_Packet->data[0]);
				break;
			}
			case ID_INCOMPATIBLE_PROTOCOL_VERSION:
			{
				CNetworkManager::Disconnect();
				Logger::Msg("Failed to connect, incompatible protocol version", g_Packet->data[0]);
				break;
			}
			case ID_ALREADY_CONNECTED:
			{
				CNetworkManager::Disconnect();
				Logger::Msg("Failed to connect, already connected", g_Packet->data[0]);
				break;
			}
			case ID_NO_FREE_INCOMING_CONNECTIONS:
			{
				CNetworkManager::Disconnect();
				Logger::Msg("Failed to connect, max client", g_Packet->data[0]);
				break;
			}
			case ID_INVALID_PASSWORD:
			{
				CNetworkManager::Disconnect();
				Logger::Msg("Failed to connect, invalid password", g_Packet->data[0]);
				break;
			}
			case ID_CONNECTION_ATTEMPT_FAILED:
			{
				CNetworkManager::Disconnect();
				Logger::Msg("Failed to connect, server not responding", g_Packet->data[0]);
				break;
			}
			case ID_CONNECTION_BANNED:
			{
				CNetworkManager::Disconnect();
				Logger::Msg("Failed to connect, banned", g_Packet->data[0]);
				break;
			}
			case ID_CONNECTION_REQUEST_ACCEPTED:
			{
				// Set the server Adress
				g_SystemAddr = g_Packet->systemAddress;

				// Set our state to connected
				//g_ConnectionState = CONSTATE_COND; //Too soon need to give models and stuff a chance to load and all data to be sent to the player
				DirectXRenderer::ConnectionProg = "Syncing with Server Data";

				// Set our last packet update so it sends our own packets too
				CLocalPlayer::SetLastSync(timeGetTime());

				char buffer[MAX_PATH];//always use MAX_PATH for filepaths
				GetModuleFileName(GetModuleHandle("Client.Core.dll"), buffer, sizeof(buffer));

				std::string filePath = buffer;
				filePath.erase(filePath.find("Client.Core.dll"), std::string("Client.Core.dll").size()); //removes the Client.Core.dll part leaving you with the file path not including the file itself

				char subdir[256] = "";
				char outputSubdir[256] = "..//dl";

				unsigned short setId;
				setId = g_DirTransfer->DownloadFromSubdirectory(subdir, outputSubdir, true, g_SystemAddr, &transferCallback, HIGH_PRIORITY, 0, 0);
				if (setId == (unsigned short)-1)
				{
					printf("Download failed.  Host unreachable.\n");
				}
				else
				{
					printf("Downloading set %i\n", setId);
				}

				BitStream bitstream;
				bitstream.Write((unsigned char)ID_REQUEST_SERVER_SYNC);
				bitstream.Write(RakString(CConfig::GetName().c_str()));
				CNetworkManager::GetInterface()->Send(&bitstream, MEDIUM_PRIORITY, RELIABLE_ORDERED, 0, CNetworkManager::GetSystemAddress(), false);

				Logger::Msg("CNetworkManager::Connected Stage 1");
				break;
			}
			case ID_DISCONNECTION_NOTIFICATION:
			{
				CNetworkManager::Disconnect();
				Logger::Msg("CNetworkManager::ConnectionClosed");
				break;
			}
			case ID_CONNECTION_LOST:
			{
				CNetworkManager::Disconnect();
				Logger::Msg("CNetworkManager::ConnectionLost");
				break;
			}
			case ID_PACKET_PLAYER:
			{
				RakNetGUID tempGUID;
				g_BitStream.Read(tempGUID);

				bool exists = false;
				if (!g_Players.empty())
				{
					for (int i = 0; i < g_Players.size(); i++)
					{
						if (std::strcmp(g_Players[i].GetGUID().ToString(), tempGUID.ToString()) == 0)
						{
							g_Players[i].Update(g_Packet);
							exists = true;
						}
					}
				}
				if (!exists)
				{
					int entityId;
					g_BitStream.Read(entityId);

					const int index = g_Players.size();

					CPlayerEntity newPlayer;
					newPlayer.Create("User", tempGUID, entityId);
					g_Players.push_back(newPlayer);
					g_Players[index].Update(g_Packet);

					std::cout << "[CPlayerEntity] Players Online: " << g_Players.size() << std::endl;
				}
				break;
			}
			case ID_PACKET_VEHICLE:
			{
				int t_Id;
				g_BitStream.Read(t_Id);

				bool exists = false;
				if (!g_Vehicles.empty())
				{
					for (int i = 0; i < g_Vehicles.size(); i++)
					{
						if (g_Vehicles[i].GetId() == t_Id)
						{
							g_Vehicles[i].Update(g_Packet);
							exists = true;
							break;
						}
					}
				}
				if (!exists)
				{
					const int index = g_Vehicles.size();

					CVehicleEntity newVehicle;
					newVehicle.Create(t_Id);
					g_Vehicles.push_back(newVehicle);
					g_Vehicles[index].Update(g_Packet);

					std::cout << "[CPlayerEntity] Vehicle Count: " << g_Vehicles.size() << std::endl;
				}
				break;
			}
			case ID_PACKET_OBJECT:
			{
				int t_Id;
				g_BitStream.Read(t_Id);

				bool exists = false;
				if (!g_Objects.empty())
				{
					for (int i = 0; i < g_Objects.size(); i++)
					{
						if (g_Objects[i].GetId() == t_Id)
						{
							g_Objects[i].Update(g_Packet);
							exists = true;
							break;
						}
					}
				}
				break;
			}
			case ID_PLAYER_LEFT:
			{
				int t_Id;
				g_BitStream.Read(t_Id);

				if (!g_Players.empty())
				{
					for (int p = 0; p < g_Players.size(); p++)
					{
						if (g_Players[p].GetId() == t_Id)
						{
							g_Players[p].Destroy();
							g_Players.erase(g_Players.begin() + p);
							g_Players.shrink_to_fit();
							break;
						}
					}
				}
				std::cout << "[CPlayerEntity] Players Online: " << g_Players.size() << std::endl;
				break;
			}
			case ID_REQUEST_SERVER_SYNC:
			{
				DirectXRenderer::ConnectionProg = "Connected";

				// Set our state to connected
				g_ConnectionState = CONSTATE_COND;

				Logger::Msg("CNetworkManager::Connected Stage 2 Final");
				break;
			}
			Logger::Msg("%d", g_Packet->data[0]);
		}
		g_RakPeer->DeallocatePacket(g_Packet);
	}
}

