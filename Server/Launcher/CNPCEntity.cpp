#include "stdafx.h"

int CNPCEntity::Amount = 0;

void CNPCEntity::Create(const std::wstring model, const CVector3 position, const CVector3 rotation)
{
	CServerEntity newServerEntity;
	newServerEntity.SetType(newServerEntity.NPC);

	Data.Model.Model = RakWString(model.c_str());
	Data.Position = position;

	Data.Rotation = rotation;
	Data.Id = newServerEntity.Create();

	g_Entities.push_back(newServerEntity);

	Amount++;

	std::cout << "[CNPCEntity] Created NPC [" << Data.Id << "] with model " << Data.Model.Model.C_String() << " at " << Data.Position.x << ", " << Data.Position.y << ", " << Data.Position.z << std::endl;
	std::cout << "[CNPCEntity] " << Amount << " npcs in the world." << std::endl;

	Network.LastSyncSent = std::chrono::system_clock::now();
	Network.Synchronized = true;
}

void CNPCEntity::Destroy()
{
	std::cout << "[CNPCEntity] Removing npc " << Data.Id << std::endl;

	Data = {};

	Data.Id = -1;

	Amount--;

	std::cout << "[CNPCEntity] " << Amount << " npcs in the world." << std::endl;
}

void CNPCEntity::RequestData(RakNetGUID requester)
{
	RakNet::BitStream sData;

	sData.Reset();
	sData.Write(Data.Id);
	sData.Write(Data.ModelHeadBlend.shapeFirst);
	sData.Write(Data.ModelHeadBlend.shapeMix);
	sData.Write(Data.ModelHeadBlend.shapeSecond);
	sData.Write(Data.ModelHeadBlend.shapeThird);
	sData.Write(Data.ModelHeadBlend.skinFirst);
	sData.Write(Data.ModelHeadBlend.skinMix);
	sData.Write(Data.ModelHeadBlend.skinSecond);
	sData.Write(Data.ModelHeadBlend.skinThird);
	sData.Write(Data.ModelHeadBlend.thirdMix);
	g_Server->GetNetworkManager()->GetRPC().Signal("PedHeadBlend", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);

	for (int i = 0; i < SizeOfArray(Data.ModelComponents); i++)
	{
		sData.Reset();
		sData.Write(Data.Id);
		sData.Write(i);
		sData.Write(Data.ModelComponents[i].drawableid);
		sData.Write(Data.ModelComponents[i].paletteid);
		sData.Write(Data.ModelComponents[i].textureid);
		g_Server->GetNetworkManager()->GetRPC().Signal("PedComponent", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);
	}

	for (int i = 0; i < SizeOfArray(Data.ModelFaceFeature); i++)
	{
		sData.Reset();
		sData.Write(Data.Id);
		sData.Write(i);
		sData.Write(Data.ModelFaceFeature[i].scale);
		g_Server->GetNetworkManager()->GetRPC().Signal("PedFaceFeature", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);
	}

	for (int i = 0; i < SizeOfArray(Data.ModelHeadOverlay); i++)
	{
		sData.Reset();
		sData.Write(Data.Id);
		sData.Write(i);
		sData.Write(Data.ModelHeadOverlay[i].index);
		sData.Write(Data.ModelHeadOverlay[i].colorType);
		sData.Write(Data.ModelHeadOverlay[i].colorID);
		sData.Write(Data.ModelHeadOverlay[i].secondColorID);
		sData.Write(Data.ModelHeadOverlay[i].opacity);
		g_Server->GetNetworkManager()->GetRPC().Signal("PedHeadOverlay", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);
	}

	for (int i = 0; i < SizeOfArray(Data.ModelProp); i++)
	{
		sData.Reset();
		sData.Write(Data.Id);
		sData.Write(i);
		sData.Write(Data.ModelProp[i].drawableid);
		sData.Write(Data.ModelProp[i].textureid);
		g_Server->GetNetworkManager()->GetRPC().Signal("PedProp", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, requester, false, false);
	}
}