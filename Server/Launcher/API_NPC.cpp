#include "stdafx.h"

namespace API
{
	const char *NPC::ThisNamespace = "API::NPC";

	const int NPC::Create(const std::wstring model, const CVector3 position, const CVector3 rotation)
	{
		CNPCEntity newNPC;
		newNPC.Create(model, position, rotation);
		g_Npcs.push_back(newNPC);

		RakNet::BitStream sData;
		sData.Write(newNPC.GetId());
		sData.Write(RakWString(model.c_str()));
		sData.Write(position.fX);
		sData.Write(position.fY);
		sData.Write(position.fZ);
		sData.Write(rotation.fX);
		sData.Write(rotation.fY);
		sData.Write(rotation.fZ);

		g_Server->GetNetworkManager()->GetRPC().Signal("CreateNPC", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);

		CModelCache::AddModel(model);

		return newNPC.GetId();
	}
}