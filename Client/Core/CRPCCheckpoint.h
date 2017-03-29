#pragma once

class CRPCCheckpoint 
{
public:
	static void Create(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void Display(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void Hide(RakNet::BitStream *bitStream, RakNet::Packet *packet);
};