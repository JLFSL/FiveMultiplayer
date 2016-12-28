#pragma once
class CLocalPlayer
{
	struct GameInfo {
		Player		Player;
		Ped			Ped;
	} Game;

	struct PlayerInfo {
		int			Id;
		std::string	Name;
	} Information;

	struct PlayerStats {
		int			Score;
	} Statistics;

	struct PlayerData {
		struct PlayerModelData {
			Hash		Model;
			int			Type;
		} Model;

		struct PlayerWeaponData {
			Hash		Weapon;
			bool		Reload;
		} Weapon;

		float			ForwardSpeed;

		CVector3		Position;
		CVector3		Velocity;
		CVector4		Quaternion;
	} Data;

	struct PlayerNetwork {
		unsigned long LastSyncSent;
	} Network;

public:
	CLocalPlayer();
	~CLocalPlayer();

	void Pulse();

	Player GetPlayer()	{ return Game.Player; }
	Ped	GetPed()		{ return Game.Ped; }

	CVector3 GetPos()		{ return Data.Position; }
	Vector3_t GetPosEx()	{ Vector3_t Pos = { Data.Position.fX, Data.Position.fY, Data.Position.fZ }; return Pos; }

	void SetLastSync(unsigned long Time) { Network.LastSyncSent = Time; }

	BOOL IsPlaying() { return PLAYER::IS_PLAYER_PLAYING(Game.Player); }
};

