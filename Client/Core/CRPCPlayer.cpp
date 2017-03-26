#include "stdafx.h"

void CRPCPlayer::PlayerModel(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	RakString model;

	bitStream->Read(model);

	GamePed::SetPedModel(CLocalPlayer::GetPed(), model.C_String());
}
