#include "stdafx.h"

void CRPCPlayer::PlayerModel(RakNet::BitStream *bitStream, RakNet::Packet *packet)
{
	int entity;
	RakString model;

	bitStream->Read(entity);
	bitStream->Read(model);

	GamePed::SetPedModel(g_Core->GetLocalPlayer()->GetPed(), model.C_String());
}

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
		for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == entity)
			{
				g_Players[i].SetPedComponentVariation(componentid, drawableid, textureid, paletteid);
				return;
			}
		}
	}
	else
	{
		GamePed::SetPedComponentVariation(g_Core->GetLocalPlayer()->GetPed(), componentid, drawableid, textureid, paletteid);
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
		for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == entity)
			{
				g_Players[i].SetPedHeadBlend(shapeFirst, shapeSecond, shapeThird, skinFirst, skinSecond, skinThird, shapeMix, skinMix, thirdMix);
				return;
			}
		}
	}
	else
	{
		GamePed::SetPedHeadBlend(g_Core->GetLocalPlayer()->GetPed(), shapeFirst, shapeSecond, shapeThird, skinFirst, skinSecond, skinThird, shapeMix, skinMix, thirdMix);
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
		for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == entity)
			{
				g_Players[i].SetPedHeadOverlayColor(overlayid, index, colorType, colorID, secondColorID, opacity);
				return;
			}
		}
	}
	else
	{
		GamePed::SetPedHeadOverlayColor(g_Core->GetLocalPlayer()->GetPed(), overlayid, index, colorType, colorID, secondColorID, opacity);
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
		for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == entity)
			{
				g_Players[i].SetPedProp(componentid, drawableid, textureid);
				return;
			}
		}
	}
	else
	{
		GamePed::SetPedProp(g_Core->GetLocalPlayer()->GetPed(), componentid, drawableid, textureid);
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
		for (int i = 0; i < g_Players.size(); i++)
		{
			if (g_Players[i].GetId() == entity)
			{
				g_Players[i].SetPedFaceFeature(index, scale);
				return;
			}
		}
	}
	else
	{
		GamePed::SetPedFaceFeature(g_Core->GetLocalPlayer()->GetPed(), index, scale);
	}
}