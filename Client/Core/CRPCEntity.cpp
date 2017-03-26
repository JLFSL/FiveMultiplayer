#include "stdafx.h"

void CRPCEntity::Destroy(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
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
		// Load location
		STREAMING::LOAD_SCENE(position.fX, position.fY, position.fZ);
		// Force everything to stream out
		CStreamer::ForceStreamOut();
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
	int entity;

	bitStream->Read(entity);

	if (CServerEntity::IsValid(entity))
	{
		CServerEntity::SetAssignee(entity, UNASSIGNED_RAKNET_GUID);
	}
	
}


void CRPCEntity::PedComponent(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int entity, componentid, drawableid, paletteid, textureid;

	bitStream->Read(entity);
	bitStream->Read(componentid);
	bitStream->Read(drawableid);
	bitStream->Read(paletteid);
	bitStream->Read(textureid);

	if (entity != -1)
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

	if (entity != -1)
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
	int entity, overlayid, index, colorType, colorID, secondColorID;
	float opacity;

	bitStream->Read(entity);
	bitStream->Read(overlayid);
	bitStream->Read(index);
	bitStream->Read(colorType);
	bitStream->Read(colorID);
	bitStream->Read(secondColorID);
	bitStream->Read(opacity);

	if (entity != -1)
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

	if (entity != -1)
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
	int entity, index;
	float scale;

	bitStream->Read(entity);
	bitStream->Read(index);
	bitStream->Read(scale);

	if (entity != -1)
	{
		CServerEntity::SetPedFaceFeature(entity, index, scale);
	}
	else
	{
		GamePed::SetPedFaceFeature(CLocalPlayer::GetPed(), index, scale);
	}
}