#pragma once
class CConfig
{
	struct CConnection
	{
		std::string Ip;
		int			Port;
		std::string Pass;
	} Connection;

	struct CInformation
	{
		std::string Name;
		bool		LatestVersion;
		bool		Steam;
	} Information;

	struct CGame
	{
		bool		Editor;
	} Game;

public:
	bool Read();

	std::string		GetIp() { return Connection.Ip; };
	int				GetPort() { return Connection.Port; };
	std::string		GetPassword() { return Connection.Pass; };

	std::string		GetServerName() { return Information.Name; }
	bool			GetLatestVersion() { return Information.LatestVersion; };
	bool			GetSteam() { return Information.Steam; };

	bool			GetEditor() { return Game.Editor; };
};

