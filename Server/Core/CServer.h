#pragma once

#include "CInterface.h"

class CServer : public CInterface
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

	bool OnLoad(int argc, char ** argv);
	void OnUnload();

	void Process();
	void SetActive(bool bActive) { m_Active = bActive; }
	bool IsActive() { return m_Active; }
};

