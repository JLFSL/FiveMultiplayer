#ifndef __CRPCOBJECT_H__
#define __CRPCOBJECT_H__

class CRPCObject
{
public:
	static void Create(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void SetTextureVariation(RakNet::BitStream *bitStream, RakNet::Packet *packet);
};

#endif