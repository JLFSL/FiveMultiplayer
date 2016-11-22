#pragma once
class CServer
{
private:
	bool			m_Active;
	bool			m_ShowFPS;
	unsigned long	m_ulLastFPSUpdateTime;
	unsigned long	m_ulFrameCount;
	unsigned long	m_ulFramesPerSecond;
public:
	CServer();
	~CServer();

	bool OnLoad(int argc, char *argv[]);
	void OnUnload();

	void Process();
};

