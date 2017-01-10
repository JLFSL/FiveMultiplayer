#pragma once
class CNetworkData
{
private:
	
public:
	CNetworkData() {};
	~CNetworkData() {};

	void SyncPlayersLocalData(RakNetGUID GUID, int id);
	void SyncServerWorld(RakNetGUID GUID);
};

