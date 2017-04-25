#include "stdafx.h"

void CRPCNpc::Create(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCNpc::Create" << std::endl;
	int entity;
	RakWString model;
	CVector3 position;
	CVector3 rotation;

	bitStream->Read(entity);
	bitStream->Read(model);
	bitStream->Read(position.x);
	bitStream->Read(position.y);
	bitStream->Read(position.z);
	bitStream->Read(rotation.x);
	bitStream->Read(rotation.y);
	bitStream->Read(rotation.z);

	CNPCEntity newNpc;
	
	if (newNpc.Create(entity, CString::utf16ToUtf8(model.C_String()).c_str(), position, rotation))
		g_Npcs.push_back(newNpc);
}