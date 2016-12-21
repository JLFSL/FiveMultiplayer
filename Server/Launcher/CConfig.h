#pragma once
class CConfig
{
	struct CConnection {
		string Ip;
		int Port;
		string Pass;
		bool Announce;
	} Connection;

	struct CLimits {
		int MaxPlayers;
	} Limits;

	struct CInformation {
		string Name;
	} Information;

	struct CPlugins {
		string Language;
		string Additional;
	} Plugins;

public:
	bool Read();

	string GetIp()					{ return Connection.Ip; };
	int GetPort()					{ return Connection.Port; };
	string GetPassword()			{ return Connection.Pass; };
	bool GetAnnounce()				{ return Connection.Announce; }
	unsigned short GetMaxPlayers()	{ return Limits.MaxPlayers; };
	string GetServerName()			{ return Information.Name; };
	string GetLanguage()			{ return Plugins.Language; };
	string GetAdditionalPlugins()	{ return Plugins.Additional; };
};

