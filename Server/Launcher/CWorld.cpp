#include "stdafx.h"

struct CWorld::WorldTime CWorld::Time;
struct CWorld::WorldWeather CWorld::Weather;

std::vector<CWorld::IPL> CWorld::g_IPLs;

void CWorld::Initialize()
{
	Time.Hour = 12;
	Time.Minute = 00;
	Time.Second = 00;
	Weather.Weather = L"CLEAR";
	Weather.GroundSnow = false;
}

void CWorld::SetTime(int hour, int minute, int second)
{
	Time.Hour = hour;
	Time.Minute = minute;
	Time.Second = second;

	RakNet::BitStream sData;
	sData.Write(Time.Hour);
	sData.Write(Time.Minute);
	sData.Write(Time.Second);
	
	g_Server->GetNetworkManager()->GetRPC().Signal("SetTime", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);
}

void CWorld::SetWeather(std::wstring weather)
{ 
	Weather.Weather = weather;

	RakNet::BitStream sData;
	sData.Write(RakWString(weather.c_str()));

	g_Server->GetNetworkManager()->GetRPC().Signal("SetWeather", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);
}

void CWorld::LoadIPL(std::wstring ipl)
{
	bool exists = false;

	for (int i = 0; i < g_IPLs.size(); i++) {
		if (ipl.compare(g_IPLs[i].ipl) == 0)
		{
			if (!g_IPLs[i].enabled)
				g_IPLs[i].enabled = true;

			exists = true;
		}
	}

	if (!exists)
	{
		IPL newIPL;
		newIPL.ipl = ipl;
		newIPL.enabled = true;
		g_IPLs.push_back(newIPL);
	}

	RakNet::BitStream sData;
	sData.Write(RakWString(ipl.c_str()));
	g_Server->GetNetworkManager()->GetRPC().Signal("LoadIPL", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);
}

void CWorld::UnloadIPL(std::wstring ipl)
{
	bool exists = false;

	for (int i = 0; i < g_IPLs.size(); i++) {
		if (ipl.compare(g_IPLs[i].ipl) == 0)
		{
			if (g_IPLs[i].enabled)
				g_IPLs[i].enabled = false;

			exists = true;
		}
	}

	if (!exists)
	{
		IPL newIPL;
		newIPL.ipl = ipl;
		newIPL.enabled = false;
		g_IPLs.push_back(newIPL);
	}

	RakNet::BitStream sData;
	sData.Write(RakWString(ipl.c_str()));
	g_Server->GetNetworkManager()->GetRPC().Signal("UnloadIPL", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);
}

