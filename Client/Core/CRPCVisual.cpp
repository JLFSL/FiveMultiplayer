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

void CRPCVisual::ShowSubtitle(RakNet::BitStream * bitStream, RakNet::Packet * packet)
{
	std::cout << "CRPCVisual::ShowSubtitle" << std::endl;
	RakNet::RakWString message;
	int duration;
	bool shownow;

	bitStream->Read(message);
	bitStream->Read(duration);
	bitStream->Read(shownow);

	CVisual::ShowSubtitle(CString::utf16ToUtf8(message.C_String()).c_str(), duration, shownow);
}

void CRPCVisual::SendChatMessage(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCVisual::SendMessage" << std::endl;
	RakNet::RakString message;

	bitStream->Read(message);

	CChat::AddChatMessage(message.C_String());
}

void CRPCVisual::ShowCursor(RakNet::BitStream * bitStream, RakNet::Packet * packet)
{
	std::cout << "CRPCVisual::ShowCursor" << std::endl;
	bool show;

	bitStream->Read(show);

	DirectXRenderer::showCursor = show;
}
