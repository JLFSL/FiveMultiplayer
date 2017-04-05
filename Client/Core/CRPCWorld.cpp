#include "stdafx.h"

void CRPCWorld::SetTime(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int hour, minute, second;

	bitStream->Read(hour);
	bitStream->Read(minute);
	bitStream->Read(second);

	TIME::SET_CLOCK_TIME(hour, minute, second);
}

void CRPCWorld::SetWeather(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	RakWString weather;

	bitStream->Read(weather);

	//GAMEPLAY::_SET_WEATHER_TYPE_OVER_TIME(weather, time);
	GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
	GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST((char*)CString::utf16ToUtf8(weather.C_String()).c_str());
}

void CRPCWorld::LoadIPL(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	RakWString ipl;

	bitStream->Read(ipl);

	CWorld::LoadIPL(ipl.C_String());
}

void CRPCWorld::UnloadIPL(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	RakWString ipl;

	bitStream->Read(ipl);

	CWorld::UnloadIPL(ipl.C_String());
}