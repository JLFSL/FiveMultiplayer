#pragma once
class CCore
{
private:
	std::unique_ptr<CNetworkManager>	g_NetworkManager;
	std::unique_ptr<CRPCManager>		g_RPCManager;
	std::unique_ptr<CLocalPlayer>		g_LocalPlayer;
	std::unique_ptr<CStreamer>			g_Streamer;

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
	void KeyCheck();

	CNetworkManager *GetNetworkManager()	{ return g_NetworkManager.get(); }
	CRPCManager *GetRPCManager()			{ return g_RPCManager.get(); }
	CLocalPlayer *GetLocalPlayer()			{ return g_LocalPlayer.get(); }
	CStreamer *GetStreamer()				{ return g_Streamer.get(); }
};

