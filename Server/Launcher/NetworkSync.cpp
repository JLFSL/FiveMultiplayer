#include "stdafx.h"
namespace NetworkSync
{
	void SyncPlayersLocalData(RakNetGUID GUID, int id)
	{
		/*RakNet::BitStream sData;
		sData.Write(id);
		server->Send(&sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);*/
	}

	void SyncServerWorld(RakNetGUID user)
	{
		RakNet::BitStream sData;

		// Sync Time
		sData.Reset();
		sData.Write(g_Server->GetWorld()->GetTime().Hour);
		sData.Write(g_Server->GetWorld()->GetTime().Minute);
		sData.Write(g_Server->GetWorld()->GetTime().Second);
		g_Server->GetNetworkManager()->GetRPC().Signal("SetTime", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, user, false, false);

		// Sync Weather
		sData.Reset();
		sData.Write(RakString(g_Server->GetWorld()->GetWeather().Weather.c_str()));
		g_Server->GetNetworkManager()->GetRPC().Signal("SetWeather", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, user, false, false);


		// Sync Objects
		for (int o = 0; o < g_Objects.size(); o++)
		{
			sData.Reset();
			sData.Write(g_Objects[o].GetId());
			if (g_Objects[o].GetHash() == 0)
			{
				sData.Write(false);
				sData.Write(RakString(g_Objects[o].GetModel().c_str()));
			}
			else
			{
				sData.Write(true);
				sData.Write(g_Objects[o].GetHash());
			}
			sData.Write(g_Objects[o].GetPosition().fX);
			sData.Write(g_Objects[o].GetPosition().fY);
			sData.Write(g_Objects[o].GetPosition().fZ);
			sData.Write(g_Objects[o].GetQuaternion().fX);
			sData.Write(g_Objects[o].GetQuaternion().fY);
			sData.Write(g_Objects[o].GetQuaternion().fZ);
			sData.Write(g_Objects[o].GetQuaternion().fW);
			sData.Write(g_Objects[o].IsDynamic());

			g_Server->GetNetworkManager()->GetRPC().Signal("CreateObject", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, user, false, false);
		}

		// Sync NPCs
		for (int o = 0; o < g_Npcs.size(); o++)
		{
			sData.Reset();
			sData.Write(g_Npcs[o].GetId());
			sData.Write(RakString(g_Npcs[o].GetModel().c_str()));
			sData.Write(g_Npcs[o].GetPosition().fX);
			sData.Write(g_Npcs[o].GetPosition().fY);
			sData.Write(g_Npcs[o].GetPosition().fZ);
			sData.Write(g_Npcs[o].GetQuaternion().fX);
			sData.Write(g_Npcs[o].GetQuaternion().fY);
			sData.Write(g_Npcs[o].GetQuaternion().fZ);
			sData.Write(g_Npcs[o].GetQuaternion().fW);

			g_Server->GetNetworkManager()->GetRPC().Signal("CreateNPC", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, user, false, false);
		}
	}

}