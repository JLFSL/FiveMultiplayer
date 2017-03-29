#include "stdafx.h"

namespace API
{
	const char *Checkpoint::ThisNamespace = "API::Checkpoint";

	const int Checkpoint::Create(const CVector3 position, const CVector3 pointto, const int type, const float radius, const Color color, const int reserved)
	{
		CCheckpointEntity newCp;
		newCp.Create(position, pointto, type, radius, color, reserved);
		g_Checkpoints.push_back(newCp);

		RakNet::BitStream sData;
		sData.Write(newCp.GetId());
		sData.Write(position.fX);
		sData.Write(position.fY);
		sData.Write(position.fZ);
		sData.Write(pointto.fX);
		sData.Write(pointto.fY);
		sData.Write(pointto.fZ);
		sData.Write(type);
		sData.Write(radius);
		sData.Write(color.Red);
		sData.Write(color.Green);
		sData.Write(color.Blue);
		sData.Write(color.Alpha);
		sData.Write(reserved);

		g_Server->GetNetworkManager()->GetRPC().Signal("CreateCheckpoint", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);

		return newCp.GetId();
	}

	const void Checkpoint::Display(const int checkpointentity, const int playerentity)
	{
		if (ServerEntity::IsValid(checkpointentity)) {
			if (playerentity != -1 && ServerEntity::IsValid(playerentity)) {
				for (int i = 0; i < g_Players.size(); i++) {
					if (g_Players[i].GetId() == playerentity) {
						RakNet::BitStream sData;
						sData.Write(checkpointentity);

						g_Server->GetNetworkManager()->GetRPC().Signal("DisplayCheckpoint", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, g_Players[i].GetGUID(), false, false);
						return;
					}
				}
			}
			else if (playerentity == -1)
			{
				RakNet::BitStream sData;
				sData.Write(checkpointentity);

				g_Server->GetNetworkManager()->GetRPC().Signal("DisplayCheckpoint", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);
				return;
			}
		}
	}

	const void Checkpoint::Hide(const int checkpointentity, const int playerentity)
	{
		if (ServerEntity::IsValid(checkpointentity)) {
			if (playerentity != -1 && ServerEntity::IsValid(playerentity)) {
				for (int i = 0; i < g_Players.size(); i++) {
					if (g_Players[i].GetId() == playerentity) {
						RakNet::BitStream sData;
						sData.Write(checkpointentity);

						g_Server->GetNetworkManager()->GetRPC().Signal("HideCheckpoint", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, g_Players[i].GetGUID(), false, false);
						return;
					}
				}
			}
			else if (playerentity == -1)
			{
				RakNet::BitStream sData;
				sData.Write(checkpointentity);

				g_Server->GetNetworkManager()->GetRPC().Signal("HideCheckpoint", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, false);
				return;
			}
		}
	}
}