#ifndef __CRPCNPC_H__
#define __CRPCNPC_H__

class CRPCNpc
{
public:
	static void Create(RakNet::BitStream *bitStream, RakNet::Packet *packet);
};

#endif