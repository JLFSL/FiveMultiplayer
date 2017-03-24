#include "stdafx.h"

void CRPCPlayer::PlayerModel(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	RakString model;

	bitStream->Read(model);

	GamePed::SetPedModel(g_Core->GetLocalPlayer()->GetPed(), model.C_String());
}
