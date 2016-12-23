#include "stdafx.h"

bool CConfig::Read()
{
	// I wana make this the same location as the dll which we can do once everything is at the fivemp installl directory using the regkeys
	INIReader Config("Client.Config.ini");

	if (Config.ParseError() < 0)
	{
		std::cout << "[CConfig] Can't read configuration file" << std::endl;
		return false;
#ifdef NDEBUG
	}
	else
	{
#endif
		std::cout << "[CConfig] Loaded config" << std::endl;

		Connection.Ip = Config.Get("Connection", "ip", "127.0.0.1");
		Connection.Port = Config.GetInteger("Connection", "port", 2322);
		Connection.Pass = Config.Get("Connection", "pass", "default");
		
		Information.Name = Config.Get("Information", "Name", "Player");
		Information.LatestVersion = Config.GetBoolean("Information", "LatestVersion", true);
		Information.Steam = Config.GetBoolean("Information", "Steam", false);

		std::cout << "[CConfig] Read config" << std::endl;
		return true;
	}
	return false;
}