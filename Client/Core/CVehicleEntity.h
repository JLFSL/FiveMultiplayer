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
		Hash		Model;

		float			ForwardSpeed;

		float			Heading;
		CVector3		Position;
		CVector3		Velocity;
		CVector4		Quaternion;
	} Data;

	struct VehicleNetwork {
		unsigned long	LastSyncReceived;
		RakNetGUID		GUID;
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

public:
	CVehicleEntity() { Game.Created = false; Game.Vehicle = NULL; };
	~CVehicleEntity() { };

	void Create(Hash Model, CVector3 Position);
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

	int GetId() { return Information.Id; };

	CVector3 GetPosition() { return Data.Position; };
	CVector4 GetQuaternion() { return Data.Quaternion; };

	RakNetGUID GetGUID() { return Network.GUID; };

	void SetInfo(VehicleInfo newinfo) { Information = newinfo; }
	void SetData(VehicleData newdata) { Data = newdata; }

	VehicleInterpolationData InterpolationData;
};
extern std::vector<CVehicleEntity> g_Vehicles;