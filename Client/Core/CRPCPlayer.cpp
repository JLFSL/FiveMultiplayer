#include "stdafx.h"

void CRPCPlayer::PlayerModel(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCPlayer::PlayerModel" << std::endl;
	RakWString model;

	bitStream->Read(model);

	//GamePed::SetPedModel(CLocalPlayer::GetPed(), CString::utf16ToUtf8(model.C_String()));
}

void CRPCPlayer::SetControlable(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCPlayer::SetControlable" << std::endl;
	bool disablecotnrols, frozen;

	bitStream->Read(disablecotnrols);
	bitStream->Read(frozen);

	CLocalPlayer::SetControlable(disablecotnrols);
	CLocalPlayer::SetFrozen(frozen);

	if(frozen)
		ENTITY::FREEZE_ENTITY_POSITION(CLocalPlayer::GetPed(), frozen);
}
