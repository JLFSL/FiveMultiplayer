#include "stdafx.h"

CConfig*			g_Config;
CNetworkManager*	g_Network;

CServer* CServer::p_Instance = nullptr;

vector<CServerEntity>	g_Entities;
vector<CPlayerEntity>	g_Players;
vector<CAPI>			g_ApiModules;

CServer::CServer()
{
	// Tell CServer we're using this particular class
	p_Instance = this;

	// Maximum amount of packets sent per second
	p_SyncRate = 10;
	// Unused, but it's supposed to limit the server FPS to 100.
	p_MaxFPS = 100;
	// If true, it shows the FPS in the console window. (windows only)
	p_ShowFPS = true;

	cout << endl;

	// Construct CConfig
	g_Config = new CConfig();

	// Construct CNetworkManager
	g_Network = new CNetworkManager();

	cout << "[CServer] Constructed" << endl;
}


CServer::~CServer()
{
	SAFE_DELETE(g_Network);
	SAFE_DELETE(g_Config);

	cout << "[CServer] Deconstructed" << endl;
}

#define USEAPI

bool CServer::Load(int argc, char ** argv)
{
#ifdef _WIN32
	// Set Window Title containing the modname, modversion and build type
	SetConsoleTitle(L"" INFO_NAME "(" INFO_VERSION ") - " INFO_BUILD);
#endif

	if (!g_Config)
	{
		cout << "[CConfig] Invalid" << endl;
		getc(stdin);
		return 1;
	}

	if (!g_Config->Read())
	{
		cout << "[CConfig] Could not read config file" << endl;
		getc(stdin);
		return 1;
	}

	if (!g_Network)
	{
		cout << "[CNetworkManager] Invalid" << endl;
		getc(stdin);
		return 1;
	}

	if (!g_Network->Start())
	{
		cout << "[CNetworkManager] Could not be started" << endl;
		getc(stdin);
		return 1;
	}
	
	// Split the plugin string for each defined plugin and insert into the pool.
	CAPI NewModule;
	string module = "plugin/";

	for (int c = 0; c < g_Config->GetLanguage().size(); c++)
	{
		if (g_Config->GetLanguage()[c] != ' ')
		{
			module.push_back(g_Config->GetLanguage()[c]);
		}
		else
		{
			module += LIBRARY_EXTENSION;
			NewModule.SetModuleName(module);
			g_ApiModules.push_back(NewModule);
			module = "plugin/";
		}

		if (c == g_Config->GetLanguage().size() - 1)
		{
			module += LIBRARY_EXTENSION;
			NewModule.SetModuleName(module);
			g_ApiModules.push_back(NewModule);
		}
	}

#ifdef USEAPI
	// Load plugin modules
	for (int i = 0; i < g_ApiModules.size(); i++)
	{
		if (!g_ApiModules[i].Load(g_ApiModules[i].ModuleName().c_str()))
		{
			cout << "[CAPI] " << g_ApiModules[i].ModuleName() << " could not be loaded" << endl;
			getc(stdin);
			return false;
		}
	}

	// Call Initialize function on our API
	for (int i = 0; i < g_ApiModules.size(); i++)
	{
		if (!g_ApiModules[i].Initialize())
		{
			cout << "[CAPI] " << g_ApiModules[i].ModuleName() << " could not be initialized" << endl;
			getc(stdin);
			return false;
		}
	}
#endif

	p_Active = true;
	return true;
}

void CServer::Stop()
{
	// Call Close function on our API
	for (int i = 0; i < g_ApiModules.size(); i++)
	{
		if (!g_ApiModules[i].Close())
		{
			cout << "[CServer] " << g_ApiModules[i].ModuleName() << " could not be closed" << endl;
			getc(stdin);
		}
	}
	p_Active = false;
}

void CServer::Process()
{
	// Keep CNetworkManager active
	g_Network->Pulse();

	// Pulse all players
	for (int i = 0; i < g_Players.size(); i++) {
		g_Players[i].Pulse();
	}

	for (int i = 0; i < g_ApiModules.size(); i++)
	{
		g_ApiModules[i].OnTick();
	}

	// Show FPS in console window (windows only)
	if (p_ShowFPS) ShowFPS();
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

#ifndef _WIN32
unsigned int timeGetTime()
{
	struct timeval now;
	gettimeofday(&now, NULL);
	return now.tv_usec / 1000;
}
#endif