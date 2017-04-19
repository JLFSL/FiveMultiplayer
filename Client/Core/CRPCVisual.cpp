#include "stdafx.h"

void CRPCVisual::ShowMessageAboveMap(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCVisual::ShowMessageAboveMap" << std::endl;
	int iconType;
	RakNet::RakWString message, pic, sender, subject;

	bitStream->Read(message);
	bitStream->Read(pic);
	bitStream->Read(iconType);
	bitStream->Read(sender);
	bitStream->Read(subject);

	CVisual::ShowMessageAboveMap(CString::utf16ToUtf8(message.C_String()).c_str(), CString::utf16ToUtf8(pic.C_String()).c_str(), iconType, CString::utf16ToUtf8(sender.C_String()).c_str(), CString::utf16ToUtf8(subject.C_String()).c_str());
}