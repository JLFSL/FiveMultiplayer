#include "stdafx.h"

void CRPCNpc::Create(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int entity;
	RakString model;
	CVector3 position;
	CVector4 quaternion;

	bitStream->Read(entity);
	bitStream->Read(model);
	bitStream->Read(position.fX);
	bitStream->Read(position.fY);
	bitStream->Read(position.fZ);
	bitStream->Read(quaternion.fX);
	bitStream->Read(quaternion.fY);
	bitStream->Read(quaternion.fZ);
	bitStream->Read(quaternion.fW);

	CNPCEntity newNpc;

	if (newNpc.Create(entity, model, position, quaternion))
		g_Npcs.push_back(newNpc);
}