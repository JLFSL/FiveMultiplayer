#include "stdafx.h"

#include "RPCManager.h"

CConfig*			g_Config;

CServer* CServer::p_Instance = nullptr;

std::vector<CServerEntity>	g_Entities;
std::vector<CPlayerEntity>	g_Players;
std::vector<CVehicleEntity>	g_Vehicles;
std::vector<CObjectEntity>	g_Objects;
std::vector<CNPCEntity>		g_Npcs;
std::vector<CCheckpointEntity>		g_Checkpoints;
std::vector<CAPI>			g_ApiModules;

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

	// Construct CConfig
	g_Config = new CConfig();

	// Construct CNetworkManager
	s_NetworkManager = std::unique_ptr<CNetworkManager>(new CNetworkManager);

	// Construct CWorld
	s_World = std::unique_ptr<CWorld>(new CWorld);

	timeNow = std::chrono::system_clock::now();
	timeLast = std::chrono::system_clock::now();
	timeTook = timeNow - timeLast;

	std::cout << "[CServer] Constructed" << std::endl;
}


CServer::~CServer()
{
	SAFE_DELETE(g_Config);

	std::cout << "[CServer] Deconstructed" << std::endl;
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
		std::cout << "[CConfig] Invalid" << std::endl;
		getc(stdin);
		return 1;
	}

	if (!g_Config->Read())
	{
		std::cout << "[CConfig] Could not read config file" << std::endl;
		getc(stdin);
		return 1;
	}

	if (!GetNetworkManager()->Start())
	{
		std::cout << "[CNetworkManager] Could not be started" << std::endl;
		getc(stdin);
		return 1;
	}

	// Register RPG Messages
	RPC::Manager::RegisterRPCMessages();
	
	// Split the plugin string for each defined plugin and insert into the pool.
	CAPI NewModule;
	std::string module = "./plugin/";
	
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
			module = "./plugin/";
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
			g_ApiModules.erase(g_ApiModules.begin() + i);
		}
	}
	
	g_ApiModules.shrink_to_fit();

	// Call Initialize function on our API
	for (int i = 0; i < g_ApiModules.size(); i++)
	{
		if (!g_ApiModules[i].Initialize())
		{
			std::cout << "[CAPI] " << g_ApiModules[i].ModuleName() << " could not be initialized" << std::endl;
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
			std::cout << "[CServer] " << g_ApiModules[i].ModuleName() << " could not be closed" << std::endl;
			getc(stdin);
		}
	}
	p_Active = false;
}

void CServer::Process()
{
	timeNow = std::chrono::system_clock::now();
	std::chrono::duration<float, std::milli> work_time = timeNow - timeLast;

	if (work_time.count() + timeTook.count() >= 1000.0f / g_Config->GetFPS())
	{
		timeLast = std::chrono::system_clock::now();

		// Keep CNetworkManager active
		GetNetworkManager()->Pulse();

		// Pulse all players
		for (int i = 0; i < g_Players.size(); i++) {
			g_Players[i].Pulse();
		}

		// Pulse all vehicles
		for (int i = 0; i < g_Vehicles.size(); i++)
		{
			g_Vehicles[i].Pulse();
		}

		for (int i = 0; i < g_Objects.size(); i++)
		{
			g_Objects[i].Pulse();
		}

		for (int i = 0; i < g_ApiModules.size(); i++)
		{
			g_ApiModules[i].OnTick();
		}

		// Show FPS in console window (windows only)
		if (p_ShowFPS) ShowFPS();

		// Lag Compensator, Adding this to the work_time will compensate for how long it takes to get threw the itteration
		// and ensures the fps set in the config unless somthing is seriously bottlenecking the server.
		timeTook = timeLast - std::chrono::system_clock::now();
	}
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

void CServer::Input(std::atomic<bool>& run) {
	std::wstring buffer;

	wchar_t message[256];

	while (run.load())
	{
		std::wcin >> buffer;

		if (buffer == L"quit")
		{
			puts("Quitting. (Temp Disabled)");
			//QUIT
			continue;
		}

		if (buffer == L"pingmaster")
		{
			g_Server->GetNetworkManager()->PulseMaster();
			continue;
		}

		if (buffer == L"stats")
		{
			RakNetStatistics rssSender;
			RakNetStatistics rssReceiver;
			unsigned short numSystems;
			char *message;

			g_Server->GetNetworkManager()->GetInterface()->GetConnectionList(0, &numSystems);
			if (numSystems > 0) {
				for (int i = 0; i < numSystems; i++)
				{
					g_Server->GetNetworkManager()->GetInterface()->GetStatistics(g_Server->GetNetworkManager()->GetInterface()->GetSystemAddressFromIndex(i), &rssSender);
					StatisticsToString(&rssSender, message, 2);
					printf("==== System %i ====\n", i + 1);
					printf("%s\n\n", message);
				}
			}

			std::wcout << "==== Pools ====" << std::endl;
			std::wcout << "+ " << g_Entities.size() << " Entities currently on the server." << std::endl;
			std::wcout << "+ " << CPlayerEntity::Amount << " Players." << std::endl;
			std::wcout << "+ " << CVehicleEntity::Amount << " Vehicles." << std::endl;
			std::wcout << "+ " << CObjectEntity::Amount << " Objects." << std::endl;
			std::wcout << "+ " << CNPCEntity::Amount << " NPCs." << std::endl;
			std::wcout << "+ " << CCheckpointEntity::Amount << " Checkpoints." << std::endl;

			continue;
		}

		if (buffer == L"playerlist")
		{
			RakNet::SystemAddress systems[10];
			unsigned short numConnections = g_Config->GetMaxPlayers();
			g_Server->GetNetworkManager()->GetInterface()->GetConnectionList((RakNet::SystemAddress*) &systems, &numConnections);
			for (int i = 0; i < numConnections; i++)
			{
				printf("%i. %s\n", i + 1, systems[i].ToString(true));
			}
			continue;
		}

		if (buffer == L"reloadplugins") {
			
			continue;
		}

		if (buffer[0] == '/')
		{
			
		}
		else {
			RakNet::RakWString textstring(message);

			RakNet::BitStream sData;
			sData.Write(textstring);
			sData.Write(RakNet::RakWString("CHAR_DEFAULT"));
			sData.Write(1);
			sData.Write(RakNet::RakWString("~r~SERVER"));
			sData.Write(RakNet::RakWString(""));

			g_Server->GetNetworkManager()->GetRPC().Signal("ShowMessageAboveMap", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);
		}
	}
	
}