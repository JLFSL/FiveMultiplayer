#pragma once

class CServerEntity {
private:
	enum Type
	{
		Player = 0,
		Vehicle = 1,
		Object = 2
	};

	struct Entity {
		int Id;
		Type type;
	} Data;

public:
	CServerEntity() { };
	~CServerEntity() { };

	int Create();
	//int Create(CVehicleEntity player);
	//int Create(CObjectEntity player);

	CVector3 GetPosition();
	void SetPosition(CVector3 position);
};
extern vector<CServerEntity> g_Entities;