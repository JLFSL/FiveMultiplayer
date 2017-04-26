#ifndef __CRPCPLAYER_H__
#define __CRPCPLAYER_H__

class CRPCPlayer
{
public:
	static void PlayerModel(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void SetControllable(RakNet::BitStream *bitStream, RakNet::Packet *packet);
};

#endif