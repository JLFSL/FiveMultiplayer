#pragma once
class CLocalPlayer
{
	static struct GameInfo {
		Player		Player;
		Ped			Ped;

		Vehicle		VehicleEntering;
	} Game;

	static struct PlayerInfo {
		int			Id;
		std::string	Name;
	} Information;

	static struct PlayerStats {
		int			Score;
	} Statistics;

	static struct PlayerData {
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
		CVector3		Rotation;
	} Data;

	static struct PlayerControl
	{
		bool			ControlVehicleExit;
	} Control;

	static struct PlayerNetwork {
		unsigned long LastSyncSent;
	} Network;

public:
	static void Initialize();
	static void Destroy();

	static void Pulse();
	static void VehicleChecks();

	static Player GetPlayer()		{ return Game.Player; }
	static Ped	GetPed();
	static void SetPed(Ped ped)		{ Game.Ped = ped; }
	static int	GetId()				{ return Information.Id; }
	static void SetId(int id)		{ Information.Id = id; }

	static bool IsInAnyVehicle()	{ return (bool)PED::IS_PED_IN_ANY_VEHICLE(Game.Ped, FALSE); }

	static CVector3 GetPosition()		{ return Data.Position; }
	static Vector3_t GetPositionEx()	{ Vector3_t Pos = { Data.Position.x, Data.Position.y, Data.Position.z }; return Pos; }

	static CVector3 GetRotation()		{ return Data.Rotation; }

	static int GetVehicleId()		{ return Data.Vehicle.VehicleID; }
	static int GetSeat()			{ return Data.Vehicle.Seat; }

	static void SetLastSync(unsigned long Time) { Network.LastSyncSent = Time; }

	static BOOL IsPlaying() { return PLAYER::IS_PLAYER_PLAYING(Game.Player); }
};

