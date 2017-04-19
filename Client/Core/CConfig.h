#pragma once
class CConfig
{
	static struct CConnection
	{
		std::string Ip;
		int			Port;
		std::string Pass;
	} Connection;

	static struct CInformation
	{
		std::string Name;
		bool		LatestVersion;
		bool		Steam;
	} Information;

	static struct CGame
	{
		bool		Editor;
		int			UILevel; /* 0 = chat only | 1 = chat and debug | 2 = nothing */
	} Game;

public:
	static bool Read();
	static void Save();
	
	static std::string		GetIp() { return Connection.Ip; }
	static int				GetPort() { return Connection.Port; }
	static std::string		GetPassword() { return Connection.Pass; }

	static std::string		GetServerName() { return Information.Name; }
	static bool				GetLatestVersion() { return Information.LatestVersion; }
	static bool				GetSteam() { return Information.Steam; }

	static bool				GetEditor() { return Game.Editor; }

	static const int		GetUILevel() { return Game.UILevel; }
	static void				SetUILevel(const int level);
};

