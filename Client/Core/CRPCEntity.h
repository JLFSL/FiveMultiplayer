#pragma once

class CRPCEntity
{
public:
	static void SetPosition(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void TakeEntityAssignment(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void DropEntityAssignment(RakNet::BitStream *bitStream, RakNet::Packet *packet);
};