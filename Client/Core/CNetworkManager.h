#pragma once
class CNetworkManager
{
private:
	// RakNet Interfaces
	RakPeerInterface	*g_RakPeer;
	RPC4				*g_RPC;

	/* Previous/Current connection */
	string			g_lastIP;
	string			g_lastPass;
	int				g_lastPort;
	SystemAddress	g_SystemAddr;

public:
	CNetworkManager();
	~CNetworkManager();

	bool Start();
	void Stop();

	void Connect();
	void Disconnect();

	void Pulse();

	void LastConnection(string ip, string pass, int port) { g_lastIP = ip; g_lastPass = pass; g_lastPort = port; }

	int g_ConnectionState;
	/*
		0 = Disconnected
		1 = Connecting
		2 = Connected
		3 = Connection Failed
	*/
};

