#pragma once
class CCore
{
private:
	CNetworkManager	*g_NetworkManager;
	CRPCManager		*g_RPCManager;
	CLocalPlayer	*g_LocalPlayer;
	Scripts			*g_Scipts;
	Doors			*g_Doors;
	Animations		*g_Animations;

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

	CNetworkManager *GetNetworkManager()	{ return g_NetworkManager; }
	CRPCManager *GetRPCManager() { return g_RPCManager; }
	CLocalPlayer *GetLocalPlayer() { return g_LocalPlayer; }
};

