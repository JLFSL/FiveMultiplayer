#include "stdafx.h"

std::vector<std::wstring> CModelCache::stringModels;
std::vector<int> CModelCache::hashModels;

void CModelCache::LoadModels(RakNetGUID user)
{
	for (int i = 0; i < CModelCache::stringModels.size(); i++)
	{
		BitStream sData;
		sData.Write(RakWString(stringModels[i].c_str()));
		g_Server->GetNetworkManager()->GetRPC().Signal("LoadStringModel", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, user, false, false);
	}

	for (int i = 0; i < CModelCache::hashModels.size(); i++)
	{
		BitStream sData;
		sData.Write(hashModels[i]);
		g_Server->GetNetworkManager()->GetRPC().Signal("LoadHashModel", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, user, false, false);
	}
}

void CModelCache::AddModel(const std::wstring model)
{
	for (int i = 0; i < CModelCache::stringModels.size(); i++)
	{
		if (stringModels[i] == model)
			return;
	}

	stringModels.push_back(model);
}

void CModelCache::AddModel(const int model)
{
	for (int i = 0; i < CModelCache::hashModels.size(); i++)
	{
		if (hashModels[i] == model)
			return;
	}

	hashModels.push_back(model);
}