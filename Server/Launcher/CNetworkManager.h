#pragma once
class CNetworkManager
{
private:
	RakPeerInterface		*g_RakPeer;
	RPC4					*g_RPC;
	DirectoryDeltaTransfer	*g_DirTransfer;
	FileListTransfer		*g_FileTransfer;

	unsigned long		p_LastMasterUpdate;
	
public:
	CNetworkManager();
	~CNetworkManager();

	bool Start();
	void Pulse();
	void PulseMaster();
	void PlayerLeft(RakNet::Packet *g_Packet);

	static size_t my_dummy_write(char *ptr, size_t size, size_t nmemb, void *userdata);

	void NewIncomingConnection(RakNet::Packet *g_Packet);

	RakPeerInterface *GetInterface() { return g_RakPeer; };
	RPC4& GetRPC() { return *g_RPC; };
};

