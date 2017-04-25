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
		sData.Write(position.x);
		sData.Write(position.y);
		sData.Write(position.z);
		sData.Write(rotation.x);
		sData.Write(rotation.y);
		sData.Write(rotation.z);

		g_Server->GetNetworkManager()->GetRPC().Signal("CreateNPC", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);

		CModelCache::AddModel(model);

		return newNPC.GetId();
	}
}