#include "stdafx.h"

std::unique_ptr<CWorld>	CWorld::s_instance = nullptr;

CWorld::CWorld()
{
	s_instance = std::unique_ptr<CWorld>(this);

	Time.Hour = 12;
	Time.Minute = 00;
	Time.Second = 00;
	Weather.Weather = "CLEAR";
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

	g_Network->GetRPC().Signal("SetTime", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);
}

void CWorld::SetWeather(std::string weather)
{ 
	Weather.Weather = weather;

	RakNet::BitStream sData;
	sData.Write(RakString(weather.c_str()));

	g_Network->GetRPC().Signal("SetWeather", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, UNASSIGNED_SYSTEM_ADDRESS, true, false);
}