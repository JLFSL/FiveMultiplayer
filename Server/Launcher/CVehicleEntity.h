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
		std::string		Model;

		float			ForwardSpeed;

		bool		EngineState			= 0;

		uint16_t	Gear				= 0;
		float		RPM					= .0f;

		float		Clutch				= .0f;
		float		Turbo				= .0f;
		float		Acceleration		= .0f;
		float		Brake				= .0f;

		float		WheelSpeed			= .0f;
		float		SteeringAngle		= .0f;
		float		ForwardWheelAngle	= .0f;

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

	void Create(std::string model, CVector3 position, float heading);
	void Create(std::string model, CVector3 position, CVector3 rotation);
	void Destroy();

	void Pulse();
	void Update(Packet *packet);

	int				GetId() { return Information.Id; };

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
};
extern std::vector<CVehicleEntity> g_Vehicles;