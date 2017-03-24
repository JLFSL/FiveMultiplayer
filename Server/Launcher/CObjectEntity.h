#pragma once

class CObjectEntity
{
private:
	struct ObjectInfo
	{
		int				Id;
	} Information;

	struct ObjectData
	{
		struct ModelData {
			std::string		Model;
			int				ModelHash;
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

	int				GetId() { return Information.Id; };

	std::string		GetModel() { return Data.Model.Model; }
	int				GetHash() { return Data.Model.ModelHash; }
	bool			IsDynamic() { return Data.Model.Dynamic; }

	const int		GetTextureVariantion() { return Data.Model.textureIndex; }
	void			SetTextureVariation(const int textureindex) { Data.Model.textureIndex = textureindex; }

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