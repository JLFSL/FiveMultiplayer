#pragma once
class CCore
{
private:
	CNetworkManager	*g_NetworkManager;

public:
	CCore();
	~CCore();

	bool Initialize();

	void OnGameTick();

	CNetworkManager *GetNetworkManager() { return g_NetworkManager; }
};

