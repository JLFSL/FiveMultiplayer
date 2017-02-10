#pragma once

class CRPCObject
{
public:
	static void Create(RakNet::BitStream *bitStream, RakNet::Packet *packet);
};