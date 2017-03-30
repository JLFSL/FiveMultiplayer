#pragma once

class CServer
{
private:
	static CServer* p_Instance;
	std::unique_ptr<CNetworkManager> s_NetworkManager;
	std::unique_ptr<CWorld> s_World;

	bool			p_Active;

	bool			p_ShowFPS;
	unsigned long	p_LastFPSUpdateTime;
	unsigned long	p_FrameCount;
	unsigned long	p_FPS;
	unsigned int	p_MaxFPS;

	unsigned int	p_SyncRate;

	std::chrono::system_clock::time_point timeNow;
	std::chrono::system_clock::time_point timeLast;
	std::chrono::duration<double, std::milli> timeTook;

public:
	CServer();
	~CServer();

	CNetworkManager *GetNetworkManager() { return s_NetworkManager.get(); }
	CWorld *GetWorld() { return s_World.get(); }

	bool Load(int argc, char ** argv);
	void Stop();

	void Process();
	void SetActive(bool bActive) { p_Active = bActive; }
	bool IsActive() { return p_Active; }

	void ShowFPS();

	static void Input(std::atomic<bool>& run);

	static CServer* GetInstance() { return p_Instance; }
	unsigned int GetSyncRate() { return p_SyncRate; }
};

#ifndef _WIN32
unsigned int timeGetTime();
#endif