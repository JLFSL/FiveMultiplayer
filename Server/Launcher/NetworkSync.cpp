#include "stdafx.h"
namespace NetworkSync
{
	void SyncPlayersLocalData(RakNetGUID GUID, int id)
	{
		/*RakNet::BitStream sData;
		sData.Write(id);
		server->Send(&sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);*/
	}

	void SyncServerWorld(RakNetGUID GUID)
	{
		RakNet::BitStream sData;
		sData.Write(g_World->GetTime().Hour);
		sData.Write(g_World->GetTime().Minute);
		sData.Write(g_World->GetTime().Second);

		g_Network->GetRPC().Signal("SetTime", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, GUID, false, false);

		sData.Reset(); //Resets the BitStream for reuse, Handy
		sData.Write(RakString(g_World->GetWeather().Weather.c_str()));

		g_Network->GetRPC().Signal("SetWeather", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, GUID, false, false);
	}

}