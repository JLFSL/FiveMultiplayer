#pragma once

class CVehicleEntity
{
private:
	struct VehicleInfo
	{
		int				Id;
	} Information;

	struct VehicleData
	{
		std::wstring	Model;

		float		ForwardSpeed;

		bool		EngineState			= 0;
		int			ForcedEngineState	= -1;

		float		EngineHealth		= 1000.0f;
		float		FuelTankHealth		= 1000.0f;

		uint16_t	Gear				= 0;
		float		RPM					= .0f;

		float		Clutch				= .0f;
		float		Turbo				= .0f;
		float		Acceleration		= .0f;
		float		Brake				= .0f;

		float		WheelSpeed			= .0f;
		float		SteeringAngle		= .0f;
		float		ForwardWheelAngle	= .0f;

		bool		TaxiLight			= false;

		bool		LeftIndicator		= false;
		bool		RightIndicator		= false;

		bool		InteriorLight		= false;

		bool		SirenSound			= false;

		struct VehiclePaintLayer
		{
			int color					= 0;
			int type					= 0;
			bool custom					= 0;
			Color customCol;
		} Colors[2];

		struct VehicleMods
		{
			int index					= 0;
		} Mods[49];

		struct VehicleExtras
		{
			bool enabled				= 0;
		} Extras[15];

		std::wstring	Plate			= L"FiveMP";
		int				PlateStyle		= 0;

		int				DoorsLockState  = 0;

		float			Heading;
		CVector3		Position;
		CVector3		Velocity;
		CVector3		Rotation;
	} Data;

	struct VehicleNetwork
	{
		RakNetGUID		Assigned;
		std::chrono::time_point<std::chrono::system_clock> LastSyncSent;
		bool			Synchronized;
	} Network;

	int Occupants[12];

public:
	static int Amount;

	CVehicleEntity();
	~CVehicleEntity() {};

	void Create(std::wstring model, CVector3 position, float heading);
	void Create(std::wstring model, CVector3 position, CVector3 rotation);
	void Destroy();

	void Pulse();
	void Update(Packet *packet);

	int				GetId() { return Information.Id; }

	const std::wstring GetModel() { return Data.Model; }

	int				GetOccupant(int seat) { return Occupants[seat]; }
	void			SetOccupant(int seat, int player) {  Occupants[seat] = player; }
	
	CVector3		GetPosition() { return Data.Position; };
	void			SetPosition(CVector3 position) { Data.Position = position; };

	CVector3		GetRotation() { return Data.Rotation; }
	void			SetRotation(CVector3 rotation) { Data.Rotation = rotation; }

	bool			GetSynchronized() { return Network.Synchronized; }

	RakNetGUID		GetAssignee() { return Network.Assigned; }
	void			SetAssignee(RakNetGUID assignee) { Network.Assigned = assignee; }

	void			RequestData(RakNetGUID requester);

	VehicleInfo		SetInfo(VehicleInfo newinfo) { Information = newinfo; }
	VehicleData		SetData(VehicleData newdata) { Data = newdata; }

	VehicleInfo		GetInfo() { return Information; }
	VehicleData		GetData() { return Data; }

	void			SetColor(const int layer, const int painttype, const int color);
	void			SetColor(const int layer, const Color color);

	std::wstring	GetNumberPlate() { return Data.Plate; }
	void			SetNumberPlate(const std::wstring plate) { Data.Plate = plate; }

	const int		GetMod(const int modType) { return Data.Mods[modType].index; }
	void			SetMod(const int modType, const int modIndex) { Data.Mods[modType].index = modIndex; }

	const bool		GetEngineState() { return Data.EngineState; }
	void			SetEngineState(const bool state) { Data.EngineState = state; Data.ForcedEngineState = state; }

	const int		GetDoorsLockState() { return Data.DoorsLockState; }
	void			SetDoorsLockState(const int state) { Data.DoorsLockState = state; }

	const int		GetNumberPlateStyle() { return Data.PlateStyle; }
	void			SetNumberPlateStyle(const int style) { Data.PlateStyle = style; }

	// Extras 0 = ON & 1 = OFF, Which is why i invert the input
	const bool		GetExtra(const int extra) { return !Data.Extras[extra].enabled; }
	void			SetExtra(const int extra, const bool toggle) { Data.Extras[extra].enabled = !toggle; }

	const float		GetEngineHealth() { return Data.EngineHealth; }
	void			SetEngineHealth(const float health) { Data.EngineHealth = health; }

	const float		GetFuelTankHealth() { return Data.FuelTankHealth; }
	void			SetFuelTankHealth(const float health) { Data.FuelTankHealth = health; }

	const bool		GetTaxiLightState() { return Data.TaxiLight; }
	void			SetTaxiLightState(const bool state) { Data.TaxiLight = state; }

	const bool		GetLeftIndicatorState() { return Data.LeftIndicator; }
	void			SetLeftIndicatorState(const bool state) { Data.LeftIndicator = state; }
	const bool		GetRightIndicatorState() { return Data.RightIndicator; }
	void			SetRightIndicatorState(const bool state) { Data.RightIndicator = state; }

	const bool		GetInteriorLightState() { return Data.InteriorLight; }
	void			SetInteriorLightState(const bool state) { Data.InteriorLight = state; }

	const bool		GetSirenSoundState() { return Data.SirenSound; }
	void			SetSirenSoundState(const bool state) { Data.SirenSound = state; }
};
extern std::vector<CVehicleEntity> g_Vehicles;