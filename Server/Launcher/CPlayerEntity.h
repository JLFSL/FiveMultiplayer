#pragma once

class CPlayerEntity {
private:
	struct PlayerInfo {
		int					Entity;
		int					PlayerID;
		string				Name;
	} Information;

	struct PlayerStats {
		int					Score;
	} Statistics;

	struct PlayerData {
		struct PlayerModelData {
			unsigned long	Model;
			int				Type;
		} Model;

		struct PlayerWeaponData {
			unsigned long	Weapon;
			bool			Reload;
		} Weapon;

		float				ForwardSpeed;

		CVector3			Position;
		CVector3			Velocity;
		CVector4			Quaternion;
	} Data;

	struct PlayerNetwork {
		unsigned long		LastSyncSent;
		bool				Synchronized;
		RakNetGUID			GUID;
		SystemAddress		Ip;
	} Network;

public:
	static int Amount;

	CPlayerEntity() {};
	~CPlayerEntity() {};

	void Create(string Name, RakNetGUID GUID, SystemAddress Ip);
	void Destroy();

	void Pulse();
	void Update(Packet *packet);

	int				GetPlayerID() { return Information.PlayerID; };
	void			SetPlayerID(int playerid) { Information.PlayerID = playerid; };
	int				GetEntity() { return Information.Entity; };
	string			GetUsername() { return Information.Name; };

	int				GetScore() { return Statistics.Score; };

	CVector3		GetPosition() { return Data.Position; };
	void			SetPosition(CVector3 position) { Data.Position = position; };
	CVector4		GetQuaternion() { return Data.Quaternion; }

	bool			GetSynchronized()	{ return Network.Synchronized; }
	RakNetGUID		GetGUID()	{ return Network.GUID; };
	SystemAddress	GetIp()	{ return Network.Ip; }

	PlayerInfo		SetInfo(PlayerInfo newinfo) { Information = newinfo; }
	PlayerStats		SetStats(PlayerStats newstats) { Statistics = newstats; }
	PlayerData		SetData(PlayerData newdata) { Data = newdata; }

	PlayerInfo		GetInfo() { return Information; }
	PlayerStats		GetStats() { return Statistics; }
	PlayerData		GetData() { return Data; }
};
extern vector<CPlayerEntity> g_Players;