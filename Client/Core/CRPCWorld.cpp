#include "stdafx.h"

void CRPCWorld::SetTime(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCWorld::SetTime" << std::endl;
	int hour, minute, second;

	bitStream->Read(hour);
	bitStream->Read(minute);
	bitStream->Read(second);

	TIME::SET_CLOCK_TIME(hour, minute, second);
}

void CRPCWorld::SetWeather(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCWorld::SetWeather" << std::endl;
	RakWString weather;

	bitStream->Read(weather);

	//GAMEPLAY::_SET_WEATHER_TYPE_OVER_TIME(weather, time);
	GAMEPLAY::CLEAR_WEATHER_TYPE_PERSIST();
	GAMEPLAY::SET_WEATHER_TYPE_NOW_PERSIST((char*)CString::utf16ToUtf8(weather.C_String()).c_str());
}

void CRPCWorld::LoadIPL(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCWorld::LoadIPL" << std::endl;
	RakWString ipl;

	bitStream->Read(ipl);

	CWorld::LoadIPL(ipl.C_String());
}

void CRPCWorld::UnloadIPL(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCWorld::UnloadIPL" << std::endl;
	RakWString ipl;

	bitStream->Read(ipl);

	CWorld::UnloadIPL(ipl.C_String());
}

void CRPCWorld::LoadStringModel(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCWorld::LoadStringModel" << std::endl;
	RakWString model;

	bitStream->Read(model);

	CWorld::LoadModel(model.C_String());
}

void CRPCWorld::LoadHashModel(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCWorld::LoadHashModel" << std::endl;
	int model;

	bitStream->Read(model);

	CWorld::LoadModel(model);
}