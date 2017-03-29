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
		Color			sColor;
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

	const int	GetId() { return Information.Id; }

	const CVector3 GetPosition() { return Data.Position; }
	void		SetPosition(CVector3 position) { Data.Position = position; }

	const CVector3 GetPointTo() { return Data.PointTo; }
	const int	GetType() { return Data.Type; }
	const Color	GetColor() { return Data.sColor; }
	const float GetRadius() { return Data.Radius; }
	const int	GetReserved() { return Data.Reserved; }

	Info		GetInfo() { return Information; }
	EntData		GetData() { return Data; }
};
extern std::vector<CCheckpointEntity> g_Checkpoints;