#ifndef __CRPCVISUAL_H__
#define __CRPCVISUAL_H__

class CRPCVisual
{
public:
	static void ShowMessageAboveMap(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void ShowSubtitle(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void SendChatMessage(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void ShowCursor(RakNet::BitStream *bitStream, RakNet::Packet *packet);
};

#endif