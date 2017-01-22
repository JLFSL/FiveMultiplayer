#pragma once
namespace RPC
{
	namespace Manager
	{
		void RegisterRPCMessages();
		void UnregisterRPCMessages();


		typedef struct
		{
			const char *name;
			void(*functionPointer) (RakNet::BitStream *userData, Packet *packet);
		} RPCMessage;
	}
}