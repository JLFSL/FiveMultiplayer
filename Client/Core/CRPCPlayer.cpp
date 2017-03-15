#include "stdafx.h"

void CRPCPlayer::PlayerModel(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int entity;
	RakString model;

	bitStream->Read(entity);
	bitStream->Read(model);

	GamePed::SetPedModel(g_Core->GetLocalPlayer()->GetPed(), model.C_String());
}
