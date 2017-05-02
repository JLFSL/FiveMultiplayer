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
		sData.Write(CWorld::GetTime().Hour);
		sData.Write(CWorld::GetTime().Minute);
		sData.Write(CWorld::GetTime().Second);
		g_Server->GetNetworkManager()->GetRPC().Signal("SetTime", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, user, false, false);

		// Sync Weather
		sData.Reset();
		sData.Write(RakWString(CWorld::GetWeather().Weather.c_str()));
		g_Server->GetNetworkManager()->GetRPC().Signal("SetWeather", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, user, false, false);

		// Sync IPLs
		if (!CWorld::g_IPLs.empty())
		{
			for (int i = 0; i < CWorld::g_IPLs.size(); i++)
			{
				if (CWorld::g_IPLs[i].enabled)
				{
					RakNet::BitStream sData;
					sData.Write(RakWString(CWorld::g_IPLs[i].ipl.c_str()));
					g_Server->GetNetworkManager()->GetRPC().Signal("LoadIPL", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, user, false, false);
				}
				else
				{
					RakNet::BitStream sData;
					sData.Write(RakWString(CWorld::g_IPLs[i].ipl.c_str()));
					g_Server->GetNetworkManager()->GetRPC().Signal("UnloadIPL", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, user, false, false);
				}
			}
		}

		// Init vehicles
		if (!g_Vehicles.empty())
		{
			for (int i = 0; i < g_Vehicles.size(); i++)
			{
				sData.Reset();
				CVector3 Position = g_Vehicles[i].GetPosition();
				CVector3 Rotation = g_Vehicles[i].GetRotation();

				sData.Write(g_Vehicles[i].GetId());
				sData.Write(RakWString(g_Vehicles[i].GetModel().c_str()));
				sData.Write(Position.x);
				sData.Write(Position.y);
				sData.Write(Position.z);
				sData.Write(Rotation.x);
				sData.Write(Rotation.y);
				sData.Write(Rotation.z);

				g_Server->GetNetworkManager()->GetRPC().Signal("InitVehicle", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, user, false, false);
			}
		}

		// Sync Objects
		if (!g_Objects.empty())
		{
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

				sData.Write(Position.x);
				sData.Write(Position.y);
				sData.Write(Position.z);
				sData.Write(Rotation.x);
				sData.Write(Rotation.y);
				sData.Write(Rotation.z);
				sData.Write(g_Objects[o].IsDynamic());

				g_Server->GetNetworkManager()->GetRPC().Signal("CreateObject", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, user, false, false);
			}
		}

		// Sync NPCs
		if (!g_Npcs.empty())
		{
			for (int o = 0; o < g_Npcs.size(); o++)
			{
				sData.Reset();
				sData.Write(g_Npcs[o].GetId());
				sData.Write(RakWString(g_Npcs[o].GetModel().c_str()));

				CVector3 Position = g_Npcs[o].GetPosition();
				CVector3 Rotation = g_Npcs[o].GetRotation();

				sData.Write(Position.x);
				sData.Write(Position.y);
				sData.Write(Position.z);
				sData.Write(Rotation.x);
				sData.Write(Rotation.y);
				sData.Write(Rotation.z);

				g_Server->GetNetworkManager()->GetRPC().Signal("CreateNPC", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, user, false, false);
			}
		}

		// Sync Checkpoints
		for (int i = 0; i < g_Checkpoints.size(); i++) 
		{
			RakNet::BitStream sData;
			sData.Write(g_Checkpoints[i].GetId());

			const CVector3 Position = g_Checkpoints[i].GetPosition();
			const CVector3 PointTo = g_Checkpoints[i].GetPointTo();
			const Color Col = g_Checkpoints[i].GetColor();

			sData.Write(Position.x);
			sData.Write(Position.y);
			sData.Write(Position.z);
			sData.Write(PointTo.x);
			sData.Write(PointTo.y);
			sData.Write(PointTo.z);
			sData.Write(g_Checkpoints[i].GetType());
			sData.Write(g_Checkpoints[i].GetRadius());
			sData.Write(Col.Red);
			sData.Write(Col.Green);
			sData.Write(Col.Blue);
			sData.Write(Col.Alpha);
			sData.Write(g_Checkpoints[i].GetRadius());

			g_Server->GetNetworkManager()->GetRPC().Signal("CreateCheckpoint", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, user, false, false);
		}
	}

}