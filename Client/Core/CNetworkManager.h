#pragma once

class CNetworkManager
{
private:
	// RakNet Interfaces
	RakPeerInterface	*g_RakPeer;
	RPC4				*g_RPC;

	/* Previous/Current connection */
	std::string		g_lastIP;
	std::string		g_lastPass;
	int				g_lastPort;
	SystemAddress	g_SystemAddr;

public:
	CNetworkManager();
	~CNetworkManager();

	bool Start();
	void Stop();

	void Connect(const char *ip, const char *pass, int port);
	void Disconnect();

	void Pulse();

	void SetLastConnection(const char *ip, const char *pass, int port) { g_lastIP = ip; g_lastPass = pass; g_lastPort = port; }

	RakPeerInterface *GetInterface() { return g_RakPeer; }
	SystemAddress GetSystemAddress() { return g_SystemAddr; }

	int g_ConnectionState; /* 0 = Disconnected - 1 = Connecting - 2 = Connected - 3 = Connection Failed */
};

