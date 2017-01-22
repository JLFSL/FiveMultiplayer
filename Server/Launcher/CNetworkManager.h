#pragma once
class CNetworkManager
{
private:
	static std::unique_ptr<CNetworkManager> s_instance;

	RakPeerInterface	*g_RakPeer;
	RPC4				*g_RPC;

	unsigned long		p_LastMasterUpdate;
	
public:
	CNetworkManager();
	~CNetworkManager();

	static CNetworkManager *instance()
	{
		if (!s_instance)
			s_instance = std::unique_ptr<CNetworkManager>(new CNetworkManager);
		return s_instance.get();
	}

	bool Start();
	void Pulse();
	void PulseMaster();

	RakPeerInterface *GetInterface() { return g_RakPeer; };
	RPC4& GetRPC() { return *g_RPC; };
};

