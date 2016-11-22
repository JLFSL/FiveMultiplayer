#include "stdafx.h"

CServer::CServer()
{
	m_ulFrameCount = 0;
	m_ulFramesPerSecond = 0;
	m_ulLastFPSUpdateTime = 0;
	m_ShowFPS = true;
	m_Active = true;

	cout << endl << "CServer Constructed" << endl;
}


CServer::~CServer()
{
	cout << endl << "CServer Deconstructed" << endl;
}

bool CServer::OnLoad(int argc, char ** argv)
{
#ifdef _WIN32
	// Set Window Title containing the modname, modversion and build type
	SetConsoleTitle(L"" INFO_NAME "(" INFO_VERSION ") - " INFO_BUILD);
#endif
	return true;
}

void CServer::OnUnload()
{
}

void CServer::Process()
{
	// Server Time
	unsigned long Time = timeGetTime();

#ifdef _WIN32
	// Is show fps enabled?
	if (m_ShowFPS)
	{
		// Get the amount of time elapsed since the last fps update
		unsigned long TimeElapsed = (Time - m_ulLastFPSUpdateTime);

		// Update the fps if a second or more has passed
		if (TimeElapsed >= 1000)
		{
			// Set the fps
			m_ulFramesPerSecond = m_ulFrameCount;

			// Set the server title
			char title[128];
			sprintf_s(title, "" INFO_NAME "(" INFO_VERSION ") - " INFO_BUILD " %dfps", m_ulFramesPerSecond);
			SetConsoleTitleA(title);

			// Reset the frame count
			m_ulFrameCount = 0;

			// Set the last fps update tick count
			m_ulLastFPSUpdateTime = Time;
		}

		// Increment the frame count
		m_ulFrameCount++;
	}
#endif
}
