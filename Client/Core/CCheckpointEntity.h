#pragma once

class CCheckpointEntity
{
private:
	struct GameData {
		int		Checkpoint;
		Blip	Blip;
	} Game;

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

		bool			Triggered;
	} Data;

public:
	static int Amount;

	CCheckpointEntity();
	~CCheckpointEntity() {}

	void Create(const int entity, const CVector3 position, const CVector3 pointto, const int type, const float radius, const Color color, const int reserved);
	void Destroy();

	void Show();
	void Hide();

	void Pulse();

	void RequestData();

	void SetHeight(const float nearHeight, const float farHeight);

	int			GetId() { return Information.Id; }

	bool		IsTriggered() { return Data.Triggered; }
	void		SetTriggered(bool toggle) { Data.Triggered = toggle; }

	CVector3	GetPosition() { return Data.Position; }
	void		SetPosition(CVector3 position);

	Info		GetInfo() { return Information; }
	EntData		GetData() { return Data; }
};
extern std::vector<CCheckpointEntity> g_Checkpoints;