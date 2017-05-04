#pragma once

namespace RPC
{
	namespace Entity
	{
		void TakeEntityAssignment(RakNet::BitStream *bitStream, RakNet::Packet *packet);
		void DropEntityAssignment(RakNet::BitStream *bitStream, RakNet::Packet *packet);
		void RequestData(RakNet::BitStream *bitStream, RakNet::Packet *packet);
		void OnEntityEnterCheckpoint(RakNet::BitStream *bitStream, RakNet::Packet *packet);
		void OnEntityExitCheckpoint(RakNet::BitStream *bitStream, RakNet::Packet *packet);
		void OnCefFinishLoad(RakNet::BitStream *bitStream, RakNet::Packet *packet);
		void OnCefSendData(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	}
}