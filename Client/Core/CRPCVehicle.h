#ifndef __RPCVEHICLE_H__
#define __RPCVEHICLE_H__

class CRPCVehicle
{
public:
	static void SetStandardColor(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void SetCustomColor(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void SetNumberPlate(RakNet::BitStream *bitStream, RakNet::Packet *packet);
};

#endif