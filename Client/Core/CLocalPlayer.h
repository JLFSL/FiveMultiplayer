#pragma once
class CLocalPlayer
{
	struct GameInfo {
		Player		Player;
		Ped			Ped;

		Vehicle		VehicleEntering;
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

		struct PlayerVehicle
		{
			int			VehicleID;
			int			Seat;
		} Vehicle;

		float			ForwardSpeed;

		CVector3		Position;
		CVector3		Velocity;
		CVector4		Quaternion;
	} Data;

	struct PlayerControl
	{
		bool			ControlVehicleExit;
	} Control;

	struct PlayerNetwork {
		unsigned long LastSyncSent;
	} Network;

public:
	CLocalPlayer();
	~CLocalPlayer();

	void Pulse();
	void VehicleChecks();

	Player GetPlayer()		{ return Game.Player; }
	Ped	GetPed()			{ return Game.Ped; }
	void SetPed(Ped ped)	{ Game.Ped = ped; }
	int	GetId()				{ return Information.Id; }
	void SetId(int id)		{ Information.Id = id; }

	bool IsInAnyVehicle()	{ return (bool)PED::IS_PED_IN_ANY_VEHICLE(Game.Ped, FALSE); }

	CVector3 GetPos()		{ return Data.Position; }
	Vector3_t GetPosEx()	{ Vector3_t Pos = { Data.Position.fX, Data.Position.fY, Data.Position.fZ }; return Pos; }

	CVector4 GetQuat()		{ return Data.Quaternion; }

	int GetVehicleId()		{ return Data.Vehicle.VehicleID; }
	int GetSeat()			{ return Data.Vehicle.Seat; }

	void SetLastSync(unsigned long Time) { Network.LastSyncSent = Time; }

	BOOL IsPlaying() { return PLAYER::IS_PLAYER_PLAYING(Game.Player); }
};

