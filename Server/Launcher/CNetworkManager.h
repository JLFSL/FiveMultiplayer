#pragma once
class CNetworkManager
{
private:
	RakPeerInterface	*g_RakPeer;
	RPC4				*g_RPC;
	
public:
	CNetworkManager();
	~CNetworkManager();

	bool Start();
	void Pulse();
};

