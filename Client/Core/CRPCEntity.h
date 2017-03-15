#pragma once

class CRPCEntity
{
public:
	static void Destroy(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void SetPosition(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void SetQuaternion(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void TakeEntityAssignment(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void DropEntityAssignment(RakNet::BitStream *bitStream, RakNet::Packet *packet);

	static void PedComponent(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void PedHeadBlend(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void PedHeadOverlay(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void PedProp(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void PedFaceFeature(RakNet::BitStream *bitStream, RakNet::Packet *packet);
};