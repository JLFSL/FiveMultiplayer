#pragma once

class CPlayerEntity {
private:
	struct GameInfo {
		Ped			Ped;
		bool		Created;

		Blip		Blip;
	} Game;

	struct PlayerInfo {
		int			Id;
		std::string	Name;
	} Information;
	
	struct PlayerStats{
		int			Score;
	} Statistics;
	
	struct PlayerData {
		struct PlayerModelData {
			Hash		Model;
			int			Type;
			int			MovementState;
		} Model;

		struct PlayerWeaponData {
			Hash			Weapon;

			bool			Reload;
			unsigned long	LastReload;
		} Weapon;

		float				ForwardSpeed;

		CVector3			Position;
		CVector3			Velocity;
		CVector4			Quaternion;
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
			CVector4      Start;
			CVector4      Target;
			CVector4      Error;
			float         LastAlpha;
			unsigned long StartTime;
			unsigned long FinishTime;
		} Rotation;
	};

public:
	CPlayerEntity() { Game.Created = false; Game.Ped = NULL; };
	~CPlayerEntity() { };

	void Create(std::string Name, RakNetGUID GUID, int entity);
	void CreatePed();
	void Destroy();

	void Pulse();
	void Update(Packet *packet);

	void Interpolate();

	void UpdateTargetPosition();
	void SetTargetPosition();

	void UpdateTargetRotation();
	void SetTargetRotation();

	void UpdateTargetAnimations();
	void UpdateTargetData();

	bool IsTargetAnimal();

	int GetId()					{ return Information.Id; };
	std::string GetUsername()	{ return Information.Name; };
	Ped	GetPed()				{ return Game.Ped; };

	int GetScore()				{ return Statistics.Score; };

	CVector3 GetPosition()		{ return Data.Position; };
	CVector4 GetQuaternion()	{ return Data.Quaternion; };

	RakNetGUID GetGUID()		{ return Network.GUID; };

	void SetInfo(PlayerInfo newinfo)		{ Information = newinfo; }
	void SetStats(PlayerStats newstats)		{ Statistics = newstats; }
	void SetData(PlayerData newdata)		{ Data = newdata; }

	PlayerInterpolationData	InterpolationData;
};
extern std::vector<CPlayerEntity> g_Players;