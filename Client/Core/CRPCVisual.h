#pragma once

class CRPCVisual
{
public:
	static void ShowMessageAboveMap(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void SendChatMessage(RakNet::BitStream *bitStream, RakNet::Packet *packet);
};