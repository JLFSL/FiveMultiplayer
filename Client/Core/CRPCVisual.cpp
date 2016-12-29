#include "stdafx.h"

void CRPCVisual::ShowMessageAboveMap(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	RakNet::RakString message;

	bitStream->Read(message);

	CVisual::ShowMessageAboveMap(message.C_String());
}