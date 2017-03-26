#pragma once

class CRPCManager
{
public:
	static void RegisterRPCMessages();
	static void UnregisterRPCMessages();

	typedef struct
	{
		char *name;
		void(*functionPointer) (RakNet::BitStream *userData, Packet *packet);
	} RPCMessage;
};