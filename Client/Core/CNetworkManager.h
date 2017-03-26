#pragma once

class CNetworkManager
{
private:
	// RakNet Interfaces
	static RakPeerInterface		*g_RakPeer;
	static RPC4					*g_RPC;
	static DirectoryDeltaTransfer	*g_DirTransfer;
	static FileListTransfer		*g_FileTransfer;

	/* Previous/Current connection */
	static std::string		g_lastIP;
	static std::string		g_lastPass;
	static int				g_lastPort;
	static SystemAddress	g_SystemAddr;

public:
	static void Initialize();
	static void Destroy();

	static bool Start();
	static void Stop();

	static void Connect(const char *ip, const char *pass, int port);
	static void Disconnect();

	static void Pulse();

	static void SetLastConnection(const char *ip, const char *pass, int port) { g_lastIP = ip; g_lastPass = pass; g_lastPort = port; }

	static RakPeerInterface *GetInterface() { return g_RakPeer; }
	static SystemAddress GetSystemAddress() { return g_SystemAddr; }
	static RPC4& GetRPC() { return *g_RPC; };

	static int g_ConnectionState; /* 0 = Disconnected - 1 = Connecting - 2 = Connected - 3 = Connection Failed */
};

