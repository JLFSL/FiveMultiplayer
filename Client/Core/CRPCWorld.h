#ifndef __CRPCWORLD_H__
#define __CRPCWORLD_H__

class CRPCWorld
{
public:
	static void SetTime(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void SetWeather(RakNet::BitStream *bitStream, RakNet::Packet *packet);

	static void LoadIPL(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void UnloadIPL(RakNet::BitStream *bitStream, RakNet::Packet *packet);

	static void LoadStringModel(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void LoadHashModel(RakNet::BitStream *bitStream, RakNet::Packet *packet);
};

#endif