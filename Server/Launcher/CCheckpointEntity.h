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
	} Data;

public:
	static int Amount;

	CCheckpointEntity();
	~CCheckpointEntity() {}

	void Create(const CVector3 position, const CVector3 pointto, const int type, const float radius, const Color color, const int reserved);
	void Destroy();

	void			RequestData(RakNetGUID requester);

	const int		GetId() { return Information.Id; }

	const CVector3	GetPosition() { return Data.Position; }
	void			SetPosition(CVector3 position) { Data.Position = position; }

	const CVector3	GetPointTo() { return Data.PointTo; }
	const int		GetType() { return Data.Type; }
	const Color		GetColor() { return Data.sColor; }
	const float		GetRadius() { return Data.Radius; }
	const int		GetReserved() { return Data.Reserved; }

	const float		GetNearHeight() { return Data.NearHeight; }
	void			SetNearHeight(const float height) { Data.NearHeight = height; }

	const float		GetFarHeight() { return Data.FarHeight; }
	void			SetFarHeight(const float height) { Data.FarHeight = height; }

	Info		GetInfo() { return Information; }
	EntData		GetData() { return Data; }
};
extern std::vector<CCheckpointEntity> g_Checkpoints;