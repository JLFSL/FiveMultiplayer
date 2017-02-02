#pragma once
class CCore
{
private:
	std::unique_ptr<CNetworkManager>	g_NetworkManager;
	std::unique_ptr<CRPCManager>		g_RPCManager;
	std::unique_ptr<CLocalPlayer>		g_LocalPlayer;

	unsigned long	LastCleanUp;
	unsigned long	LastUnlock;

public:
	CCore();
	~CCore();

	bool Initialize();
	void OnGameTick();

	void CleanUp();
	void CleanUpTick();

	void PreventCheat();

	CNetworkManager *GetNetworkManager()	{ return g_NetworkManager.get(); }
	CRPCManager *GetRPCManager()			{ return g_RPCManager.get(); }
	CLocalPlayer *GetLocalPlayer()			{ return g_LocalPlayer.get(); }
};

