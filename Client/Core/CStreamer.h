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

	int MaxPlayers;
	int PlayerCount;

	int MaxVehicles;
	int VehicleCount;

	int MaxObjects;
	int ObjectCount;

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