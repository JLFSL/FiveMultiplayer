#pragma once
class CCore
{
private:
	std::unique_ptr<CNetworkManager>	g_NetworkManager;
	std::unique_ptr<CRPCManager>		g_RPCManager;
	std::unique_ptr<CLocalPlayer>		g_LocalPlayer;
	std::unique_ptr<Scripts>			g_Scipts;
	std::unique_ptr<Doors>				g_Doors;
	std::unique_ptr<Animations>			g_Animations;

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

