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
		std::string		Model;

		float			ForwardSpeed;

		float			Heading;
		CVector3		Position;
		CVector3		Velocity;
		CVector4		Quaternion;
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

	int Occupants[12];

public:
	CVehicleEntity();
	~CVehicleEntity() { };

	void Create(int entityid);
	void CreateVehicle();
	void Destroy();

	void Pulse();
	void Update(Packet *packet);

	void Interpolate();

	void UpdateTargetPosition();
	void SetTargetPosition();

	void UpdateTargetRotation();
	void SetTargetRotation();

	void UpdateTargetData();

	int				GetId() { return Information.Id; }
	Vehicle			GetEntity() { return Game.Vehicle; }

	CVector3		GetPosition() { return Data.Position; }
	CVector4		GetQuaternion() { return Data.Quaternion; }

	RakNetGUID		GetAssignee() { return Network.Assigned; }
	void			SetAssignee(RakNetGUID assignee) { Network.Assigned = assignee; }

	void			SetInfo(VehicleInfo newinfo) { Information = newinfo; }
	void			SetData(VehicleData newdata) { Data = newdata; }

	VehicleInterpolationData InterpolationData;
};
extern std::vector<CVehicleEntity> g_Vehicles;