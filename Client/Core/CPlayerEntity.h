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
			std::string	Model;
			Hash		hModel;
			int			Type;
			int			MovementState;
		} Model;

		struct PlayerWeaponData {
			Hash			Weapon;

			bool			Reload;
			unsigned long	LastReload;
		} Weapon;

		struct PlayerVehicle
		{
			int			VehicleID;
			int			Seat;
		} Vehicle;

		struct PlayerComponent
		{
			int drawableid = -1;
			int textureid = -1;
			int paletteid = -1;
		} ModelComponents[12];

		struct PlayerHeadBlend
		{
			int shapeFirst = 0;
			int shapeSecond = 0;
			int shapeThird = 0;
			int skinFirst = 0;
			int skinSecond = 0;
			int skinThird = 0;
			float shapeMix = 0;
			float skinMix = 0;
			float thirdMix = 0;
		} ModelHeadBlend;

		struct PlayerHeadOverlay
		{
			int index = 0;
			float opacity = 0.0f;
			int colorType = 0;
			int colorID = 0;
			int secondColorID = 0;
		} ModelHeadOverlay[13];

		struct PlayerProp
		{
			int drawableid = 0;
			int textureid = 0;
		} ModelProp[3];

		struct PlayerFeature
		{
			float scale = 0.0f;
		} ModelFaceFeature[20];

		float				ForwardSpeed;
		int					Task;
		bool				isJumping;

		CVector3			Position;
		CVector3			Velocity;
		CVector3			Rotation;
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
	CPlayerEntity();
	~CPlayerEntity() { }

	void Create(std::string Name, RakNetGUID GUID, int entity);
	bool CreatePed();
	void RequestData();
	void Destroy();
	void Delete();

	void Pulse();
	void Update(Packet *packet);

	void Interpolate();

	void UpdateTargetPosition();
	void SetTargetPosition();

	void UpdateTargetRotation();
	void SetTargetRotation();

	void UpdateTargetAnimations();
	void UpdateTargetData();
	void UpdatePlayerModel();

	bool IsTargetAnimal();

	int GetId()					{ return Information.Id; }
	std::string GetUsername()	{ return Information.Name; }

	Ped	GetPed()				{ return Game.Ped; }
	bool IsCreated()			{ return Game.Created; }

	int GetScore()				{ return Statistics.Score; }

	CVector3 GetPosition()		{ return Data.Position; }
	CVector3 GetRotation()		{ return Data.Rotation; }

	RakNetGUID GetGUID()		{ return Network.GUID; }

	void SetInfo(PlayerInfo newinfo)		{ Information = newinfo; }
	void SetStats(PlayerStats newstats)		{ Statistics = newstats; }
	void SetData(PlayerData newdata)		{ Data = newdata; }

	void SetModelComponent(const int componentid, const int drawableid, const int textureid, const int paletteid);
	void SetModelHeadBlend(const int shapeFirst, const int shapeSecond, const int shapeThird, const int skinFirst, const int skinSecond, const int skinThird, const float shapeMix, const float skinMix, const float thirdMix);
	void SetModelHeadOverlay(const int overlayid, const int index, const int colorType, const int colorid, const int secondColorid, const float opacity);
	void SetModelProp(const int componentid, const int drawableid, const int textureid);
	void SetModelFaceFeature(const int index, const float scale);

	PlayerInterpolationData	InterpolationData;
};
extern std::vector<CPlayerEntity> g_Players;