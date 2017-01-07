#pragma once
/*
 * The global server entity ids
*/
class CServerEntity {
public:
	enum Type
	{
		Player = 0,
		Vehicle = 1,
		Object = 2
	};
private:
	struct Entity {
		int Id;
		Type type;
	} Data;

public:
	CServerEntity() { };
	~CServerEntity() { };

	int			Create();
	void		SetType(Type type);

	int			GetId() { return Data.Id; };

	CVector3	GetPosition();
	void		SetPosition(CVector3 position);
};
extern vector<CServerEntity> g_Entities;