#pragma once

class CObjectEntity
{
private:
	struct ObjectInfo
	{
		int				Entity;
	} Information;

	struct ObjectData
	{
		std::string		Model;
		int				ModelHash;
		bool			Dynamic;

		CVector3		Position;
		CVector3		Rotation;
		CVector3		Velocity;
		CVector4		Quaternion;
	} Data;

	struct ObjectNetwork
	{
		RakNetGUID		Assigned;
		std::chrono::time_point<std::chrono::system_clock> LastSyncSent;
		bool			Synchronized;
	} Network;

public:
	static int Amount;

	CObjectEntity();
	~CObjectEntity() {};

	void Create(std::string model, CVector3 position, CVector4 quaternion, bool dynamic);
	void Create(int hash, CVector3 position, CVector4 quaternion, bool dynamic);
	void Destroy();

	void Pulse();
	void Update(Packet *packet);

	int				GetEntity() { return Information.Entity; };

	std::string		GetModel() { return Data.Model; }
	int				GetHash() { return Data.ModelHash; }
	bool			IsDynamic() { return Data.Dynamic; }

	CVector3		GetPosition() { return Data.Position; };
	void			SetPosition(CVector3 position) { Data.Position = position; };

	CVector4		GetQuaternion() { return Data.Quaternion; }
	void			SetQuaternion(CVector4 quaternion) { Data.Quaternion = quaternion; }

	bool			GetSynchronized() { return Network.Synchronized; }

	RakNetGUID		GetAssignee() { return Network.Assigned; }
	void			SetAssignee(RakNetGUID assignee) { Network.Assigned = assignee; }

	void			RequestData(RakNetGUID requester);
	
	ObjectInfo		GetInfo() { return Information; }
	ObjectData		GetData() { return Data; }
};
extern std::vector<CObjectEntity> g_Objects;