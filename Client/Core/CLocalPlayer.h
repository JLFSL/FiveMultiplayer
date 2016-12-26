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

	BOOL IsPlaying() { return PLAYER::IS_PLAYER_PLAYING(Game.Player); }
};

