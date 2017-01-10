#pragma once

class CRPCWorld
{
public:
	static void SetTime(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void SetWeather(RakNet::BitStream *bitStream, RakNet::Packet *packet);
};