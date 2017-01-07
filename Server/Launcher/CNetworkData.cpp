#include "stdafx.h"

void CNetworkData::SyncPlayersLocalData(RakNetGUID GUID, int id)
{
	/*RakNet::BitStream sData;
	sData.Write(id);
	server->Send(&sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);*/
}

void CNetworkData::SyncServerWorld(RakNetGUID GUID)
{
	//RakNet::BitStream sData;
	//sData.Write(id);
	/*sData.Write(Config->ServerTimeHour);
	sData.Write(Config->ServerTimeMinute);
	sData.Write(Config->ServerTimeFreeze);
	sData.Write(Config->ServerWeather);
	sData.Write(Config->ServerDateDay);
	sData.Write(Config->ServerDateMonth);
	sData.Write(Config->ServerDateYear);*/
	//server->Send(&sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, packet->systemAddress, false);
}