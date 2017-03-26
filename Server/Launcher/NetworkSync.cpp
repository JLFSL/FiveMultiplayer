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
		sData.Write(RakWString(g_Server->GetWorld()->GetWeather().Weather.c_str()));
		g_Server->GetNetworkManager()->GetRPC().Signal("SetWeather", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, user, false, false);


		// Sync Objects
		for (int o = 0; o < g_Objects.size(); o++)
		{
			sData.Reset();
			sData.Write(g_Objects[o].GetId());
			if (g_Objects[o].GetHash() == 0)
			{
				sData.Write(false);
				sData.Write(RakWString(g_Objects[o].GetModel().c_str()));
			}
			else
			{
				sData.Write(true);
				sData.Write(g_Objects[o].GetHash());
			}

			CVector3 Position = g_Objects[o].GetPosition();
			CVector3 Rotation = g_Objects[o].GetRotation();

			sData.Write(Position.fX);
			sData.Write(Position.fY);
			sData.Write(Position.fZ);
			sData.Write(Rotation.fX);
			sData.Write(Rotation.fY);
			sData.Write(Rotation.fZ);
			sData.Write(g_Objects[o].IsDynamic());

			g_Server->GetNetworkManager()->GetRPC().Signal("CreateObject", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, user, false, false);
		}

		// Sync NPCs
		for (int o = 0; o < g_Npcs.size(); o++)
		{
			sData.Reset();
			sData.Write(g_Npcs[o].GetId());
			sData.Write(RakWString(g_Npcs[o].GetModel().c_str()));

			CVector3 Position = g_Npcs[o].GetPosition();
			CVector3 Rotation = g_Npcs[o].GetRotation();

			sData.Write(Position.fX);
			sData.Write(Position.fY);
			sData.Write(Position.fZ);
			sData.Write(Rotation.fX);
			sData.Write(Rotation.fY);
			sData.Write(Rotation.fZ);

			g_Server->GetNetworkManager()->GetRPC().Signal("CreateNPC", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, user, false, false);
		}
	}

}