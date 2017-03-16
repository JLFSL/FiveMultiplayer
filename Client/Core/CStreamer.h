#pragma once

class CStreamer
{
private:
	struct streamedObject
	{
		int entity;
		float distance;
	};
	std::vector<streamedObject> streamed;

	float MaxRange;

	int MaxPlayers;		// The max visable players to be shown
	int PlayerCount;	// The current count of visable players
	float PlayerRange;	// Should the 'MaxPlayers' be reached it'll store the range it reached at that point here for the streamingout to check.

	int MaxVehicles;
	int VehicleCount;
	float VehicleRange;

	int MaxObjects;
	int ObjectCount;
	float ObjectRange;

	int MaxNpcs;
	int NpcCount;
	float NpcRange;

public:
	CStreamer();
	~CStreamer() {}

	static void Start();
	void Pulse();
	void StreamIn(CVector3 position);
	void StreamOut(CVector3 position);
	void ForceStreamOut();

	int GetPlayerCount() { return PlayerCount; }
	int GetVehicleCount() { return VehicleCount; }
	int GetObjectCount() { return ObjectCount; }
};