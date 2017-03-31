#include "stdafx.h"

void CRPCNpc::Create(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int entity;
	RakWString model;
	CVector3 position;
	CVector3 rotation;

	bitStream->Read(entity);
	bitStream->Read(model);
	bitStream->Read(position.fX);
	bitStream->Read(position.fY);
	bitStream->Read(position.fZ);
	bitStream->Read(rotation.fX);
	bitStream->Read(rotation.fY);
	bitStream->Read(rotation.fZ);

	CNPCEntity newNpc;
	
	if (newNpc.Create(entity, FString::utf16ToUtf8(model.C_String()).c_str(), position, rotation))
		g_Npcs.push_back(newNpc);
}