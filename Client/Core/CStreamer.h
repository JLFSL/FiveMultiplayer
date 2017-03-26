#pragma once

class CStreamer
{
private:
	static struct streamedObject
	{
		int entity;
		float distance;
	};
	static std::vector<streamedObject> streamed;

	static float MaxRange;

	static int MaxPlayers;		// The max visable players to be shown
	static int PlayerCount;	// The current count of visable players
	static float PlayerRange;	// Should the 'MaxPlayers' be reached it'll store the range it reached at that point here for the streamingout to check.

	static int MaxVehicles;
	static int VehicleCount;
	static float VehicleRange;

	static int MaxObjects;
	static int ObjectCount;
	static float ObjectRange;

	static int MaxNpcs;
	static int NpcCount;
	static float NpcRange;

public:
	static void Start();
	static void Pulse();
	static void StreamObjectsIn(CVector3 position);
	static void StreamVehiclesIn(CVector3 position);
	static void StreamPlayersIn(CVector3 position);
	static void StreamOtherIn(CVector3 position);
	static void StreamOut(CVector3 position);
	static void ForceStreamOut();

	static int GetPlayerCount() { return PlayerCount; }
	static int GetVehicleCount() { return VehicleCount; }
	static int GetObjectCount() { return ObjectCount; }
	static int GetNpcCount() { return NpcCount; }
};