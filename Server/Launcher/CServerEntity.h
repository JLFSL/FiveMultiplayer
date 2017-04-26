#pragma once
/*
 * The global server entity ids
*/
class CServerEntity {
public:
	enum Type
	{
		Unknown = -1,
		Player = 0,
		Vehicle = 1,
		Object = 2,
		NPC = 3,
		Checkpoint = 4
	};
private:
	struct Entity {
		int Id;
		Type type;

		float viewDistance;
	} Data;

public:
	CServerEntity();
	~CServerEntity() { }

	int			Create();
	void		Destroy();

	Type		GetType() { return Data.type; }
	void		SetType(Type type);

	int			GetId() { return Data.Id; }
	void		SetId(int entity) { Data.Id = entity;  }

	CVector3	GetPosition();
	void		SetPosition(CVector3 position);

	CVector3	GetRotation();
	void		SetRotation(CVector3 rotation);

	float		GetViewDistance() { return Data.viewDistance; };
	void		SetViewDistance(const float distance) { Data.viewDistance = distance; };
};
extern std::vector<CServerEntity> g_Entities;

namespace ServerEntity
{
	int			GetIndex(int entity);
	bool		IsValid(int entity);
	RakNetGUID	GetAssignee(int entity);
	void		SetAssignee(int entity, RakNetGUID assignee);
	void		RequestData(int entity, RakNetGUID requester);
}