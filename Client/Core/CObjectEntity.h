#pragma once

class CObjectEntity
{
private:
	struct GameInfo
	{
		Object		Object;
		bool		Created;

		Blip		Blip;
	} Game;

	struct ObjectInfo
	{
		int				Id;
	} Information;

	struct ObjectData
	{
		struct ModelData {
			int				Model;
			bool			Dynamic;
			int				textureIndex;
		} Model;

		CVector3		Position;
		CVector3		Rotation;
		CVector3		Velocity;
		CVector4		Quaternion;
	} Data;

	struct ObjectNetwork
	{
		RakNetGUID		Assigned;
		unsigned long	LastSyncSent;
		unsigned long	LastSyncReceived;
		bool			Synchronized;
	} Network;

	struct ObjectInterpolationData
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
	} InterpolationData;

public:
	static int Amount;

	CObjectEntity();
	~CObjectEntity() {}

	bool Create(int entity, int hash, CVector3 position, CVector4 quaternion, bool dynamic);
	bool CreateObject();
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

	int				GetId() { return Information.Id; }
	Object			GetEntity() { return Game.Object; }
	bool			IsCreated() { return Game.Created; }

	void			SetTextureVariation(const int textureIndex);

	CVector3		GetPosition() { return Data.Position; }
	void			SetPosition(CVector3 position) { Data.Position = position; }
	CVector4		GetQuaternion() { return Data.Quaternion; }
	void			SetQuaternion(CVector4 q) { Data.Quaternion = q; }

	bool			GetSynchronized() { return Network.Synchronized; }

	RakNetGUID		GetAssignee() { return Network.Assigned; }
	void			SetAssignee(RakNetGUID assignee) { Network.Assigned = assignee; }

	ObjectInfo		GetInfo() { return Information; }
	ObjectData		GetData() { return Data; }
};
extern std::vector<CObjectEntity> g_Objects;