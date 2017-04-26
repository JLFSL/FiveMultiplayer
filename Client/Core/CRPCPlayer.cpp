#include "stdafx.h"

void CRPCPlayer::PlayerModel(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCPlayer::PlayerModel" << std::endl;
	RakWString model;

	bitStream->Read(model);

	//GamePed::SetPedModel(CLocalPlayer::GetPed(), CString::utf16ToUtf8(model.C_String()));
}

void CRPCPlayer::DisableControls(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCPlayer::DisableControls" << std::endl;
	bool disable;

	bitStream->Read(disable);

	CLocalPlayer::DisableControls(disable);
}
