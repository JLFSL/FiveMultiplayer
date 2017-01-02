#include "stdafx.h"

void CRPCVisual::ShowMessageAboveMap(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int iconType;
	RakNet::RakString message, pic, sender, subject;

	bitStream->Read(message);
	bitStream->Read(pic);
	bitStream->Read(iconType);
	bitStream->Read(sender);
	bitStream->Read(subject);

	CVisual::ShowMessageAboveMap(message.C_String(), pic, iconType, sender, subject);
}