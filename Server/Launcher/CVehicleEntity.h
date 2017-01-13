#pragma once

class CVehicleEntity
{
private:
	struct VehicleInfo
	{
		int					Id;
		RakNetGUID			Driver;
	} Information;

	struct VehicleData
	{
		string				Model;

		float				ForwardSpeed;
		float				Heading;

		CVector3			Position;
		CVector3			Velocity;
		CVector4			Quaternion;
	} Data;

	struct VehicleNetwork
	{
		RakNetGUID			Assigned;
		unsigned long		LastSyncSent;
		bool				Synchronized;
	} Network;

public:
	static int Amount;

	CVehicleEntity() {};
	~CVehicleEntity() {};

	void Create(std::string model, CVector3 position, float heading);
	void Destroy();

	void Pulse();
	void Update(Packet *packet);

	int				GetId() { return Information.Id; };
	
	CVector3		GetPosition() { return Data.Position; };
	void			SetPosition(CVector3 position) { Data.Position = position; };
	CVector4		GetQuaternion() { return Data.Quaternion; }

	bool			GetSynchronized() { return Network.Synchronized; }

	RakNetGUID		GetAssignee() { return Network.Assigned; }
	void			SetAssignee(RakNetGUID assignee) { Network.Assigned = assignee; }

	VehicleInfo		SetInfo(VehicleInfo newinfo) { Information = newinfo; }
	VehicleData		SetData(VehicleData newdata) { Data = newdata; }

	VehicleInfo		GetInfo() { return Information; }
	VehicleData		GetData() { return Data; }
};
extern vector<CVehicleEntity> g_Vehicles;