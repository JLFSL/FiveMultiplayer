#pragma once

namespace RPC
{
	namespace Entity
	{
		void TakeEntityAssignment(RakNet::BitStream *bitStream, RakNet::Packet *packet);
		void DropEntityAssignment(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	}
}