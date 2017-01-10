#include "stdafx.h"

void CRPCEntity::SetPosition(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int entity;
	CVector3 position;

	bitStream->Read(entity);
	bitStream->Read(position.fX);
	bitStream->Read(position.fY);
	bitStream->Read(position.fZ);

	if (entity != -1)
	{
		for (int i = 0; i < g_Entities.size(); i++)
		{
			//CEntity::SetPosition();
		}
	}
	else
	{
		STREAMING::LOAD_SCENE(position.fX, position.fY, position.fZ);
		ENTITY::SET_ENTITY_COORDS(g_Core->GetLocalPlayer()->GetPed(), position.fX, position.fY, position.fZ, false, false, false, false);
	}
}