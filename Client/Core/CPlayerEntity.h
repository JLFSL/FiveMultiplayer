#pragma once

class CPlayerEntity {
private:
	struct GameInfo {
		Ped			Ped;
		bool		Created;
	} Game;

	struct PlayerInfo {
		int			Id;
		string		Name;
	} Information;
	
	struct PlayerStats{
		int			Score;
	} Statistics;
	
	struct PlayerData {
		CVector3	Position;
		CVector3	Velocity;
		CVector4	Quaternion;
	} Data;

	struct PlayerNetwork {
		unsigned long	LastSyncReceived;
		RakNetGUID		GUID;
	} Network;

	struct PlayerInterpolationData
	{
		struct
		{
			CVector3      Start;
			CVector3      Target;
			CVector3      Error;
			float         LastAlpha;
			unsigned long StartTime;
			unsigned long FinishTime;
		} Position;

		struct
		{
			CVector3      Start;
			CVector3      Target;
			CVector3      Error;
			float         LastAlpha;
			unsigned long StartTime;
			unsigned long FinishTime;
		} Rotation;
	};

public:
	static int Amount;

	CPlayerEntity() { };
	~CPlayerEntity() { };

	void Create(string Name, RakNetGUID GUID);
	void CreatePed();
	void Destroy();

	void Pulse();
	void Update(Packet *packet);

	void Interpolate();

	void UpdateTargetPosition();
	void SetTargetPosition();

	void UpdateTargetRotation();
	void SetTargetRotation();

	int GetId()					{ return Information.Id; };
	string GetUsername()		{ return Information.Name; };

	int GetScore()				{ return Statistics.Score; };

	CVector3 GetPosition()		{ return Data.Position; };
	CVector4 GetQuaternion()	{ return Data.Quaternion; };

	RakNetGUID GetGUID()		{ return Network.GUID; };

	PlayerInfo SetInfo(PlayerInfo newinfo)		{ Information = newinfo; }
	PlayerStats SetStats(PlayerStats newstats)	{ Statistics = newstats; }
	PlayerData SetData(PlayerData newdata)		{ Data = newdata; }

	PlayerInterpolationData	*InterpolationData;
};
extern vector<CPlayerEntity> g_Players;