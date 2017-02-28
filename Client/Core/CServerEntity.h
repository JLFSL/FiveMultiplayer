#pragma once
/*
* The global server entity ids
*/
class CServerEntity
{
public:
	enum Type
	{
		Unknown = -1,
		Player = 0,
		Vehicle = 1,
		Object = 2
	};
private:
	struct Entity
	{
		int Id;
		Type type;
	} Data;

public:
	CServerEntity();
	~CServerEntity() {}

	void Create(int entity, Type type);
	void Destroy();

	int	GetId()			{ return Data.Id; }
	void SetId(int id)	{ Data.Id = id; }

	Type GetType() { return Data.type; }
	void SetType(Type type);

	CVector3	GetPosition();
	void		SetPosition(CVector3 position);

	void		SetQuaternion(CVector4 quaternion);

	void		SetAssignement(RakNetGUID guid);
};
extern std::vector<CServerEntity> g_Entities;

namespace ServerEntity
{
	bool		IsValid(int entity);
	RakNetGUID	GetAssignee(int entity);
	void		SetAssignee(int entity, RakNetGUID assignee);
}