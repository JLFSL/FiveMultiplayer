#ifndef __LUAVEHICLE_H__
#define __LUAVEHICLE_H__

class CRPCVehicle
{
public:
	static void SetStandardColor(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void SetCustomColor(RakNet::BitStream *bitStream, RakNet::Packet *packet);
};

#endif