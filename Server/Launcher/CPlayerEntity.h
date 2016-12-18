#pragma once

class CPlayerEntity {
private:
	struct PlayerInfo {
		int			Id;
		string		Name;
		const char	*Guid;
		const char	*Ip;
	} Information;

	struct PlayerStats {
		int			Score;
	} Statistics;

	struct PlayerData {
		CVector3	Position;
		CVector3	Velocity;
		CVector4	Quaternion;
	} Data;

	struct PlayerNetwork {
		unsigned long LastSyncSent;
	} Network;

public:
	static int Amount;

	CPlayerEntity() { };
	~CPlayerEntity() { };

	void Create(string Name, const char *Guid, const char *Ip);
	void Destroy();

	void Pulse();
	void Update(BitStream *bitstream);

	int GetId() { return Information.Id; };
	string GetUsername() { return Information.Name; };
	const char *GetGuid() { return Information.Guid; };
	const char *GetIp() { return Information.Ip; };

	int GetScore() { return Statistics.Score; };

	CVector3 GetPosition() { return Data.Position; };
	CVector4 GetQuaternion() { return Data.Quaternion; }

	PlayerInfo SetInfo(PlayerInfo newinfo) { Information = newinfo; }
	PlayerStats SetStats(PlayerStats newstats) { Statistics = newstats; }
	PlayerData SetData(PlayerData newdata) { Data = newdata; }
};
extern vector<CPlayerEntity> g_Players;