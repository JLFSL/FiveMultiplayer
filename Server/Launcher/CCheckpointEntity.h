#pragma once

#pragma once

class CCheckpointEntity
{
private:
	struct Info
	{
		int				Id;
	} Information;

	struct EntData
	{
		int				Type;
		float			Radius;
		Color			Color;
		int				Reserved;

		float			NearHeight;
		float			FarHeight;

		CVector3		Position;
		CVector3		PointTo;
		CVector3		Velocity;
	} Data;

public:
	static int Amount;

	CCheckpointEntity();
	~CCheckpointEntity() {}

	void Create(const CVector3 position, const CVector3 pointto, const int type, const float radius, const Color color, const int reserved);
	void Destroy();

	int			GetId() { return Information.Id; }

	CVector3	GetPosition() { return Data.Position; }
	void		SetPosition(CVector3 position) { Data.Position = position; }

	Info		GetInfo() { return Information; }
	EntData		GetData() { return Data; }
};
extern std::vector<CCheckpointEntity> g_Checkpoints;