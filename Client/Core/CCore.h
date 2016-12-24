#pragma once
class CCore
{
private:
	CNetworkManager	*g_NetworkManager;
	CLocalPlayer	*g_LocalPlayer;
	Scripts			*g_Scipts;
	Doors			*g_Doors;

	unsigned long	LastCleanUp;
	unsigned long	LastUnlock;

public:
	CCore();
	~CCore();

	bool Initialize();

	void OnGameTick();
	void CleanUp();
	void CleanUpTick();

	CNetworkManager *GetNetworkManager()	{ return g_NetworkManager; }
	CLocalPlayer *GetLocalPlayer() { return g_LocalPlayer; }
};

