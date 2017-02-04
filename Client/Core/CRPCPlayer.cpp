#include "stdafx.h"

void CRPCPlayer::PlayerComponent(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int entity, componentid, drawableid, paletteid, textureid;

	bitStream->Read(entity);
	bitStream->Read(componentid);
	bitStream->Read(drawableid);
	bitStream->Read(paletteid);
	bitStream->Read(textureid);
	
	if (entity != -1)
	{
		for (int i = 0; i < g_Entities.size(); i++)
		{
			if (g_Entities[i].GetId() == entity)
			{
				GamePed::SetPedComponentVariation(g_Entities[i].GetPEntity()->GetPed(), componentid, drawableid, textureid, paletteid);
				 return;
			}
		}
	}
}

void CRPCPlayer::PlayerHeadBlend(RakNet::BitStream *bitStream, RakNet::Packet *packet)
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
		for (int i = 0; i < g_Entities.size(); i++)
		{
			if (g_Entities[i].GetId() == entity)
			{
				GamePed::SetPedHeadBlend(g_Entities[i].GetPEntity()->GetPed(), shapeFirst, shapeSecond, shapeThird, skinFirst, skinSecond, skinThird, shapeMix, skinMix, thirdMix);
				return;
			}
		}
	}
}

void CRPCPlayer::PlayerHeadOverlay(RakNet::BitStream *bitStream, RakNet::Packet *packet)
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
		for (int i = 0; i < g_Entities.size(); i++)
		{
			if (g_Entities[i].GetId() == entity)
			{
				GamePed::SetPedHeadOverlayColor(g_Entities[i].GetPEntity()->GetPed(), overlayid, index, colorType, colorID, secondColorID, opacity);
				return;
			}
		}
	}
}

void CRPCPlayer::PlayerProp(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int entity, componentid, drawableid, textureid;
	float opacity;

	bitStream->Read(entity);
	bitStream->Read(componentid);
	bitStream->Read(drawableid);
	bitStream->Read(textureid);

	if (entity != -1)
	{
		for (int i = 0; i < g_Entities.size(); i++)
		{
			if (g_Entities[i].GetId() == entity)
			{
				GamePed::SetPedProp(g_Entities[i].GetPEntity()->GetPed(), componentid, drawableid, textureid);
				return;
			}
		}
	}
}

void CRPCPlayer::PlayerFaceFeature(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int entity, index;
	float scale;

	bitStream->Read(entity);
	bitStream->Read(index);
	bitStream->Read(scale);

	if (entity != -1)
	{
		for (int i = 0; i < g_Entities.size(); i++)
		{
			if (g_Entities[i].GetId() == entity)
			{
				GamePed::SetPedFaceFeature(g_Entities[i].GetPEntity()->GetPed(), index, scale);
				return;
			}
		}
	}
}