#pragma once

class CVehicleEntity {
private:
	struct GameInfo {
		Vehicle		Vehicle;
		bool		Created;

		Blip		Blip;
	} Game;

	struct VehicleInfo {
		int			Id;
	} Information;

	struct VehicleData {
		std::string	Model;

		float		ForwardSpeed;
		
		bool		EngineState			= 0;
		int			ForceEngineState	= -1;

		uint16_t	Gear				= 0;
		float		RPM					= .0f;

		float		Clutch				= .0f;
		float		Turbo				= .0f;
		float		Acceleration		= .0f;
		float		Brake				= .0f;

		float		WheelSpeed			= .0f;
		float		SteeringAngle		= .0f;
		float		ForwardWheelAngle	= .0f;

		unsigned long	LastWheelspeed;

		struct VehiclePaintLayer
		{
			int		color				= 0;
			int		type				= 0;
			bool	custom				= 0;
			Color	customCol;
		} Colors[2];

		struct VehicleExtras
		{
			bool enabled				= 0;
		} Extras[15];

		std::wstring	Plate			= L"FiveMP";
		int				PlateStyle		= 0;

		int				DoorsLockState  = 0;

		struct VehicleMods
		{
			int		index				= 0;
		} Mods[49];

		float			Heading;
		CVector3		Position;
		CVector3		Velocity;
		CVector3		Rotation;
	} Data;

	struct VehicleNetwork {
		RakNetGUID		Assigned;
		unsigned long	LastSyncReceived;
		unsigned long	LastSyncSent;
	} Network;

	struct VehicleInterpolationData
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

	Vehicles vdata;

	int Occupants[12];

public:
	CVehicleEntity();
	~CVehicleEntity() { };

	void Create(int entity);
	bool CreateVehicle();
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

	void SetTargetData();

	static Vehicle getClosestVehicleFromPedPos(Ped ped, int maxDistance);

	int				GetId() { return Information.Id; }
	Vehicle			GetEntity() { return Game.Vehicle; }
	bool			IsCreated() { return Game.Created; }

	int				GetOccupant(int seat) { return Occupants[seat]; }

	CVector3		GetPosition() { return Data.Position; }
	void			SetPosition(CVector3 position) { Data.Position = position; }
	CVector3		GetRotation() { return Data.Rotation; }
	void			SetRotation(CVector3 rotation) { Data.Rotation = rotation; }

	RakNetGUID		GetAssignee() { return Network.Assigned; }
	void			SetAssignee(RakNetGUID assignee) { Network.Assigned = assignee; }

	void			SetInfo(VehicleInfo newinfo) { Information = newinfo; }
	void			SetData(VehicleData newdata) { Data = newdata; }

	void			SetColor(const int layer, const int painttype, const int color);
	void			SetColor(const int layer, const Color color);
	void			SetNumberPlate(const std::wstring plate);
	void			SetMod(const int modType, const int modIndex);
	void			SetEngineState(const bool state);
	void			SetDoorsLockState(const int state);
	void			SetNumberPlateStyle(const int style);
	void			SetExtra(const int extra, const bool toggle);

	VehicleInterpolationData InterpolationData;
};
extern std::vector<CVehicleEntity> g_Vehicles;