#pragma once

class CRPCPlayer
{
public:
	static void PlayerComponent(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void PlayerHeadBlend(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void PlayerHeadOverlay(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void PlayerProp(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void PlayerFaceFeature(RakNet::BitStream *bitStream, RakNet::Packet *packet);
};