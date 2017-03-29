#pragma once
class CConfig
{
	struct CConnection {
		std::string Ip;
		int Port;
		std::string Pass;
		bool Announce;
	} Connection;

	struct CLimits {
		int MaxPlayers;
		int MaxFPS;
	} Limits;

	struct CInformation {
		std::string Name;
	} Information;

	struct CPlugins {
		std::string Language;
		std::string Additional;
	} Plugins;

public:
	bool Read();

	std::string GetIp()					{ return Connection.Ip; }
	const int GetPort()					{ return Connection.Port; }
	std::string GetPassword()			{ return Connection.Pass; }
	bool GetAnnounce()					{ return Connection.Announce; }
	unsigned short GetMaxPlayers()		{ return Limits.MaxPlayers; }
	std::string GetServerName()			{ return Information.Name; }
	std::string GetLanguage()			{ return Plugins.Language; }
	std::string GetAdditionalPlugins()	{ return Plugins.Additional; }
	const int GetFPS()					{ return Limits.MaxFPS; }
};

