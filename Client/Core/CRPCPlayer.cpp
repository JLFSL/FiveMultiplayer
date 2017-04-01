#include "stdafx.h"

void CRPCPlayer::PlayerModel(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	RakWString model;

	bitStream->Read(model);

	GamePed::SetPedModel(CLocalPlayer::GetPed(), CString::utf16ToUtf8(model.C_String()));
}
