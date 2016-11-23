#include "stdafx.h"

typedef CEntityManager<CPlayerEntity, MAX_PLAYERS> CPlayerManager;

CNetworkManager	* g_Network;
CPlayerManager	* g_Players;

CServer* CServer::p_Instance = nullptr;

CServer::CServer()
{
	// Maximum amount of packets sent per second
	p_SyncRate = 20;
	// Unused, but it's supposed to limit the server FPS to 100.
	p_MaxFPS = 100;
	// If true, it shows the FPS in the console window. (windows only)
	p_ShowFPS = true;

	p_Instance = this;

	// Construct CNetworkManager
	g_Network = new CNetworkManager();

	cout << "CServer: Constructed" << endl;
}


CServer::~CServer()
{
	SAFE_DELETE(g_Players);

	cout << "CServer: Deconstructed" << endl;
}

bool CServer::Load(int argc, char ** argv)
{
	g_Players = new CPlayerManager();

	g_Network->Start();

#ifdef _WIN32
	// Set Window Title containing the modname, modversion and build type
	SetConsoleTitle(L"" INFO_NAME "(" INFO_VERSION ") - " INFO_BUILD);
#endif
	return true;
}

void CServer::Stop()
{
}

void CServer::Process()
{
	// Keep CNetworkManager active
	g_Network->Pulse();

	g_Players->Pulse();

	// Show FPS in console window (windows only)
	if (p_ShowFPS)
	{
		ShowFPS();
	}

	Sleep(10);
}

void CServer::ShowFPS()
{
#ifdef _WIN32
	unsigned long Time = timeGetTime();
	unsigned long TimeElapsed = (Time - p_LastFPSUpdateTime);

	if (TimeElapsed >= 1000)
	{
		p_FPS = p_FrameCount;

		char title[128];
		sprintf_s(title, "" INFO_NAME "(" INFO_VERSION ") - " INFO_BUILD " %dfps", p_FPS);
		SetConsoleTitleA(title);

		p_FrameCount = 0;
		p_LastFPSUpdateTime = Time;
	}
	p_FrameCount++;
#endif
}
