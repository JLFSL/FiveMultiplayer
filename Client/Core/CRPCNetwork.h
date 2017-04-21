#ifndef __CRPCNETWORK_H__
#define __CRPCNETWORK_H__

class CRPCNetwork
{
public:
	static void FinishedSync(RakNet::BitStream *bitStream, RakNet::Packet *packet);
};

#endif