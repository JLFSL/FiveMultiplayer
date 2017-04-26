#ifndef __CRPCCef_H__
#define __CRPCCef_H__

class CRPCCef
{
public:
	static void LoadURL(RakNet::BitStream *bitStream, RakNet::Packet *packet);
	static void JavaScriptCall(RakNet::BitStream *bitStream, RakNet::Packet *packet);
};

#endif