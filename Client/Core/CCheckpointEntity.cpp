#include "stdafx.h"

int CCheckpointEntity::Amount = 0;

CCheckpointEntity::CCheckpointEntity() {
	Game.Checkpoint = -1;
	Data.NearHeight = 10.0f;
	Data.FarHeight = 20.0f;

	Data.sColor = { 255, 255, 255, 255 };
}

void CCheckpointEntity::Create(const int entity, const CVector3 position, const CVector3 pointto, const int type, const float radius, const Color color, const int reserved)
{
	CServerEntity newServerEntity;
	newServerEntity.SetType(CServerEntity::Checkpoint);
	newServerEntity.SetId(entity);

	Data.Position = position;
	Data.PointTo = pointto;
	Data.Type = type;
	Data.Radius = radius;
	Data.sColor = color;
	Data.Reserved = reserved;

	Information.Id = entity;

	g_Entities.push_back(newServerEntity);

	Amount++;

	std::cout << "[CCheckpointEntity] Created checkpoint [" << Information.Id << "] at " << Data.Position.fX << ", " << Data.Position.fY << ", " << Data.Position.fZ << std::endl;
	std::cout << "[CCheckpointEntity] " << Amount << " checkpoints in the world." << std::endl;
}

void CCheckpointEntity::Destroy()
{
	std::cout << "[CCheckpointEntity] Removing checkpoint " << Information.Id << std::endl;

	if (Game.Checkpoint != -1) {
		Hide();
	}

	Information = {};
	Data = {};

	Information.Id = -1;

	Amount--;

	std::cout << "[CCheckpointEntity] " << Amount << " checkpoints in the world." << std::endl;
}

void CCheckpointEntity::Show()
{
	Hide();

	Game.Checkpoint = GRAPHICS::CREATE_CHECKPOINT(Data.Type, Data.Position.fX, Data.Position.fY, Data.Position.fZ, Data.PointTo.fX, Data.PointTo.fY, Data.PointTo.fZ, Data.Radius, Data.sColor.Red, Data.sColor.Green, Data.sColor.Blue, Data.sColor.Alpha, Data.Reserved);
	GRAPHICS::SET_CHECKPOINT_CYLINDER_HEIGHT(Game.Checkpoint, Data.NearHeight, Data.FarHeight, Data.Radius);
}

void CCheckpointEntity::Hide() {
	if (Game.Checkpoint != -1) {
		GRAPHICS::DELETE_CHECKPOINT(Game.Checkpoint);
		Game.Checkpoint = -1;
	}
}

void CCheckpointEntity::SetPosition(CVector3 position)
{
	bool a;
	if (Game.Checkpoint == -1)
		a = false;
	else
		a = true;

	Hide();

	Data.Position = position;

	if (a)
		Show();
}