#include "stdafx.h"

vector<CPlayerEntity> g_Players;

CCore::CCore()
{
	// Construct CNetworkManager
	g_NetworkManager = new CNetworkManager;
	g_LocalPlayer = new CLocalPlayer;
}

CCore::~CCore()
{
	SAFE_DELETE(g_NetworkManager);
	SAFE_DELETE(g_LocalPlayer);
}

bool CCore::Initialize()
{
	// Check if CServer is created
	if (!g_NetworkManager)
	{
		Logger::Msg("CNetworkManager is invalid");
		return false;
	}

	// Call OnLoad
	if (!g_NetworkManager->Start())
	{
		Logger::Msg("CNetworkManager could not be started");
		return false;
	}

	return true;
}

void CCore::OnGameTick()
{
	if (g_LocalPlayer->IsPlaying() == FALSE)
		return;

	if (KeyJustUp(VK_F8))
	{
		g_NetworkManager->Connect("127.0.0.1", "default", CON_PORT);
		Logger::Msg("Connecting");
	}

	if (KeyJustUp(VK_F7))
	{
		g_NetworkManager->Connect("83.128.145.20", "default", CON_PORT);
		Logger::Msg("Connecting");
	}

	if (KeyJustUp(VK_F9))
	{
		g_NetworkManager->Disconnect();
		Logger::Msg("Disconnecting");
	}

	g_NetworkManager->Pulse();
	
	for (int i = 0; i < g_Players.size(); i++)
	{
		g_Players[i].Pulse();
	}
}
