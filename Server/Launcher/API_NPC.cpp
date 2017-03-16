#include "stdafx.h"

namespace API
{
	const char *NPC::ThisNamespace = "API::NPC";

	const int NPC::Create(const std::string model, const CVector3 position, const float heading)
	{
		CNPCEntity newNPC;
		newNPC.Create(model, position, heading);
		g_Npcs.push_back(newNPC);

		RakNet::BitStream sData;
		sData.Write(newNPC.GetId());
		sData.Write(RakString(model.c_str()));
		sData.Write(position.fX);
		sData.Write(position.fY);
		sData.Write(position.fZ);
		sData.Write(newNPC.GetQuaternion().fX);
		sData.Write(newNPC.GetQuaternion().fY);
		sData.Write(newNPC.GetQuaternion().fZ);
		sData.Write(newNPC.GetQuaternion().fW);

		g_Server->GetNetworkManager()->GetRPC().Signal("CreateNPC", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);

		return newNPC.GetId();
	}
}