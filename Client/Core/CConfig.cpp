#include "stdafx.h"

struct CConfig::CConnection CConfig::Connection;
struct CConfig::CInformation CConfig::Information;
struct CConfig::CGame CConfig::Game;

bool CConfig::Read()
{
	char buffer[MAX_PATH];//always use MAX_PATH for filepaths
	GetModuleFileName(GetModuleHandle("Client.Core.dll"), buffer, sizeof(buffer));
	
	std::string filePath = buffer;
	filePath.erase(filePath.find("Client.Core.dll"), std::string("Client.Core.dll").size());

	INIReader Config(filePath + "Client.Config.ini");

	if (Config.ParseError() < 0)
	{
		std::cout << "[CConfig] Can't read configuration file" << std::endl;
		return false;
	}
	else
	{
		std::cout << "[CConfig] Loaded config" << std::endl;

		Connection.Ip = Config.Get("Connection", "ip", "127.0.0.1");
		Connection.Port = Config.GetInteger("Connection", "port", 2322);
		Connection.Pass = Config.Get("Connection", "pass", "default");
		
		Information.Name = Config.Get("Information", "name", "Player");
		Information.LatestVersion = Config.GetBoolean("Information", "latestversion", true);

		Game.Editor = Config.GetBoolean("Game", "editor", false);
		Game.UILevel = Config.GetInteger("Game", "uilevel", 0);

		std::cout << "[CConfig] Read config" << std::endl;
		return true;
	}
	return false;
}

void CConfig::Save() {
	std::wcout << L"[CConfig] Saving Settings." << std::endl;

	char buffer[MAX_PATH];		//always use MAX_PATH for filepaths
	GetModuleFileName(GetModuleHandle("Client.Core.dll"), buffer, sizeof(buffer));

	std::string filePath = buffer;
	filePath.erase(filePath.find("Client.Core.dll"), std::string("Client.Core.dll").size());

	INIWriter Config(filePath + "Client.Config.ini");

	Config.WriteString("Connection", "ip", Connection.Ip);
	Config.WriteInteger("Connection", "port", Connection.Port);
	Config.WriteString("Connection", "pass", Connection.Pass);

	Config.WriteString("Information", "name", Information.Name);
	Config.WriteBoolean("Information", "latestversion", Information.LatestVersion);

	Config.WriteBoolean("Game", "editor", Game.Editor);
	Config.WriteInteger("Game", "uilevel", Game.UILevel);
}

void CConfig::SetUILevel(const int level)
{
	Game.UILevel = level;
	CConfig::Save();
}