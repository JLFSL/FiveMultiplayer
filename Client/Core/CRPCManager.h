#pragma once

class CRPCManager
{
private:
	
public:
	CRPCManager() {};
	~CRPCManager() {};
	
	void RegisterRPCMessages();
	void UnregisterRPCMessages();


	typedef struct
	{
		char *name;
		void(*functionPointer) (RakNet::BitStream *userData, Packet *packet);
	} RPCMessage;
};