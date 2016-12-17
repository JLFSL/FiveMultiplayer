#pragma once

class CPlayerEntity {
private:
	struct PlayerInfo {
		int			Id;
		string		Name;
		const char	*Guid;
	} Information;
	
	struct PlayerStats{
		int			Score;
	} Statistics;
	
	struct PlayerData {
		CVector3	Position;
		CVector3	Velocity;
		CVector4	Quaternion;
	} Data;

public:
	static int Amount;

	CPlayerEntity();
	~CPlayerEntity();

	void Create(string Name, const char *Guid);

	void Pulse();
	void Update(Packet packet);

	int GetId()					{ return Information.Id; };
	string GetUsername()		{ return Information.Name; };
	const char *GetGuid()		{ return Information.Guid; };

	int GetScore()				{ return Statistics.Score; };

	CVector3 GetPosition()		{ return Data.Position; };
	CVector4 GetQuaternion()	{ return Data.Quaternion; }
};
extern vector<CPlayerEntity> g_Players;