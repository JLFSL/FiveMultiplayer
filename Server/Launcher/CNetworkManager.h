#pragma once
class CNetworkManager
{
private:
	RakPeerInterface	*g_RakPeer;
	RPC4				*g_RPC;

	unsigned long		p_LastMasterUpdate;
	
public:
	CNetworkManager();
	~CNetworkManager();

	bool Start();
	void Pulse();
	void PulseMaster();

	RakPeerInterface *GetInterface() { return g_RakPeer; };
};

