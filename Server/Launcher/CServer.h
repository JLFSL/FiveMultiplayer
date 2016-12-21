#pragma once

class CServer
{
private:
	static CServer	*p_Instance;

	bool			p_Active;

	bool			p_ShowFPS;
	unsigned long	p_LastFPSUpdateTime;
	unsigned long	p_FrameCount;
	unsigned long	p_FPS;
	unsigned int	p_MaxFPS;

	unsigned int	p_SyncRate;

public:
	CServer();
	~CServer();

	bool Load(int argc, char ** argv);
	void Stop();

	void Process();
	void SetActive(bool bActive) { p_Active = bActive; }
	bool IsActive() { return p_Active; }

	void ShowFPS();

	static CServer* GetInstance() { return p_Instance; }
	unsigned int GetSyncRate() { return p_SyncRate; }
};

#ifndef _WIN32
unsigned int timeGetTime()
#endif