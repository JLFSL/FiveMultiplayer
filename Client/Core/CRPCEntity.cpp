#include "stdafx.h"

void CRPCEntity::Destroy(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCEntity::Destroy" << std::endl;
	int entity;

	bitStream->Read(entity);

	if (entity != -1)
	{
		for (int i = 0; i < g_Entities.size(); i++)
		{
			if (g_Entities[i].GetId() == entity)
				return g_Entities[i].Destroy();
		}
	}
}

void CRPCEntity::SetPosition(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int entity;
	CVector3 position;

	bitStream->Read(entity);
	bitStream->Read(position.fX);
	bitStream->Read(position.fY);
	bitStream->Read(position.fZ);
	std::cout << "CRPCEntity::SetPosition for entity " << entity << " to " << std::to_string(position.fX) << ", " << std::to_string(position.fY) << ", " << std::to_string(position.fZ) << std::endl;
	
	if (entity != -1)
	{
		for (int i = 0; i < g_Entities.size(); i++)
		{
			if (entity == g_Entities[i].GetId())
				return g_Entities[i].SetPosition(position);
		}
	}
	else
	{
		// Force everything to stream out
		CStreamer::ForceStreamOut();
		// Load location
		STREAMING::LOAD_SCENE(position.fX, position.fY, position.fZ);
		// Stream in everything at the position
		CStreamer::StreamObjectsIn(position);
		CStreamer::StreamVehiclesIn(position);
		CStreamer::StreamPlayersIn(position);
		CStreamer::StreamOtherIn(position);
		// Send player to the position
		ENTITY::SET_ENTITY_COORDS(CLocalPlayer::GetPed(), position.fX, position.fY, position.fZ, false, false, false, false);
	}

}

void CRPCEntity::SetRotation(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCEntity::SetRotation" << std::endl;
	int entity;
	CVector3 rotation;

	bitStream->Read(entity);
	bitStream->Read(rotation.fX);
	bitStream->Read(rotation.fY);
	bitStream->Read(rotation.fZ);

	if (entity != -1)
	{
		for (int i = 0; i < g_Entities.size(); i++)
		{
			if (entity == g_Entities[i].GetId())
				return g_Entities[i].SetRotation(rotation);
		}
	}
	else
	{
		ENTITY::SET_ENTITY_ROTATION(CLocalPlayer::GetPed(), rotation.fX, rotation.fY, rotation.fZ, 2, true);
	}
}

void CRPCEntity::TakeEntityAssignment(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCEntity::TakeEntityAssignment" << std::endl;
	int entity;
	RakNetGUID guid;

	bitStream->Read(entity);
	bitStream->Read(guid);

	if (CServerEntity::IsValid(entity))
	{
		CServerEntity::SetAssignee(entity, guid);
	}
}

void CRPCEntity::DropEntityAssignment(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCEntity::DropEntityAssignment" << std::endl;
	int entity;

	bitStream->Read(entity);

	if (CServerEntity::IsValid(entity))
	{
		CServerEntity::SetAssignee(entity, UNASSIGNED_RAKNET_GUID);
	}
	
}


void CRPCEntity::PedComponent(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCEntity::PedComponent" << std::endl;
	int entity, componentid, drawableid, paletteid, textureid;

	bitStream->Read(entity);
	bitStream->Read(componentid);
	bitStream->Read(drawableid);
	bitStream->Read(paletteid);
	bitStream->Read(textureid);

	if (entity != CLocalPlayer::GetId())
	{
		CServerEntity::SetPedComponentVariation(entity, componentid, drawableid, textureid, paletteid);
	}
	else
	{
		GamePed::SetPedComponentVariation(CLocalPlayer::GetPed(), componentid, drawableid, textureid, paletteid);
	}
}

void CRPCEntity::PedHeadBlend(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCEntity::PedHeadBlend" << std::endl;
	int entity, shapeFirst, shapeSecond, shapeThird, skinFirst, skinSecond, skinThird;
	float shapeMix, skinMix, thirdMix;

	bitStream->Read(entity);
	bitStream->Read(shapeFirst);
	bitStream->Read(shapeMix);
	bitStream->Read(shapeSecond);
	bitStream->Read(shapeThird);
	bitStream->Read(skinFirst);
	bitStream->Read(skinMix);
	bitStream->Read(skinSecond);
	bitStream->Read(skinThird);
	bitStream->Read(thirdMix);

	if (entity != CLocalPlayer::GetId())
	{
		CServerEntity::SetPedHeadBlend(entity, shapeFirst, shapeSecond, shapeThird, skinFirst, skinSecond, skinThird, shapeMix, skinMix, thirdMix);
	}
	else
	{
		GamePed::SetPedHeadBlend(CLocalPlayer::GetPed(), shapeFirst, shapeSecond, shapeThird, skinFirst, skinSecond, skinThird, shapeMix, skinMix, thirdMix);
	}
}

void CRPCEntity::PedHeadOverlay(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCEntity::PedHeadOverlay" << std::endl;
	int entity, overlayid, index, colorType, colorID, secondColorID;
	float opacity;

	bitStream->Read(entity);
	bitStream->Read(overlayid);
	bitStream->Read(index);
	bitStream->Read(colorType);
	bitStream->Read(colorID);
	bitStream->Read(secondColorID);
	bitStream->Read(opacity);

	if (entity != CLocalPlayer::GetId())
	{
		CServerEntity::SetPedHeadOverlayColor(entity, overlayid, index, colorType, colorID, secondColorID, opacity);
	}
	else
	{
		GamePed::SetPedHeadOverlayColor(CLocalPlayer::GetPed(), overlayid, index, colorType, colorID, secondColorID, opacity);
	}
}

void CRPCEntity::PedProp(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int entity, componentid, drawableid, textureid;
	float opacity;

	bitStream->Read(entity);
	bitStream->Read(componentid);
	bitStream->Read(drawableid);
	bitStream->Read(textureid);
	std::cout << "CRPCEntity::PedProp for entity " << entity << " with " << componentid << ", " << drawableid << ", " << textureid << std::endl;

	if (entity != CLocalPlayer::GetId())
	{
		CServerEntity::SetPedProp(entity, componentid, drawableid, textureid);
	}
	else
	{
		GamePed::SetPedProp(CLocalPlayer::GetPed(), componentid, drawableid, textureid);
	}
}

void CRPCEntity::PedFaceFeature(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCEntity::PedFaceFeature" << std::endl;
	int entity, index;
	float scale;

	bitStream->Read(entity);
	bitStream->Read(index);
	bitStream->Read(scale);

	if (entity != CLocalPlayer::GetId())
	{
		CServerEntity::SetPedFaceFeature(entity, index, scale);
	}
	else
	{
		GamePed::SetPedFaceFeature(CLocalPlayer::GetPed(), index, scale);
	}
}

void CRPCEntity::SetViewDistance(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	std::cout << "CRPCEntity::SetViewDistance" << std::endl;
	int entity;
	float distance;

	bitStream->Read(entity);
	bitStream->Read(distance);

	for (int i = 0; i < g_Entities.size(); i++) {
		if (entity == g_Entities[i].GetId()) {
			g_Entities[i].SetViewDistance(distance);
			break;
		}
	}
}