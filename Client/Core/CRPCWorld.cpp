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
	RakString weather;

	bitStream->Read(weather);

	//GAMEPLAY::_SET_WEATHER_TYPE_OVER_TIME(weather, time);
	GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
	GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST((char*)weather.C_String());
}