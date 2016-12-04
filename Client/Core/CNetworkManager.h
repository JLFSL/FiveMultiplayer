#pragma once

struct sPlayerEntity_InterpolationData
{
	struct
	{
		CVector3      vecStart;
		CVector3      vecTarget;
		CVector3      vecError;
		float         fLastAlpha;
		unsigned long ulStartTime;
		unsigned long ulFinishTime;
	}				pPosition;
	struct
	{
		CVector3         fStart;
		CVector3         fTarget;
		CVector3         fError;
		float         fLastAlpha;
		unsigned long ulStartTime;
		unsigned long ulFinishTime;
	}				pRotation;
};

class CNetworkManager
{
private:
	// RakNet Interfaces
	RakPeerInterface	*g_RakPeer;
	RPC4				*g_RPC;

	/* Previous/Current connection */
	string			g_lastIP;
	string			g_lastPass;
	int				g_lastPort;
	SystemAddress	g_SystemAddr;

public:
	CNetworkManager();
	~CNetworkManager();

	bool Start();
	void Stop();

	void Connect();
	void Disconnect();

	void Update();
	void UpdateRotation();

	void Pulse();

	void LastConnection(string ip, string pass, int port) { g_lastIP = ip; g_lastPass = pass; g_lastPort = port; }

	int g_ConnectionState;
	/*
		0 = Disconnected
		1 = Connecting
		2 = Connected
		3 = Connection Failed
	*/

	sPlayerEntity_InterpolationData			* m_pInterpolationData;
};

