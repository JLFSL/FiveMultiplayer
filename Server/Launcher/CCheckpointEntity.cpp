#include "stdafx.h"

int CCheckpointEntity::Amount = 0;

CCheckpointEntity::CCheckpointEntity() {
	Data.NearHeight = 10.0f;
	Data.FarHeight = 20.0f;

	Data.sColor = { 255, 255, 255, 255 };
}

void CCheckpointEntity::Create(const CVector3 position, const CVector3 pointto, const int type, const float radius, const Color color, const int reserved)
{
	CServerEntity newServerEntity;
	newServerEntity.SetType(newServerEntity.Checkpoint);

	Data.Position = position;
	Data.PointTo = pointto;
	Data.Type = type;
	Data.Radius = radius;
	Data.sColor = color;
	Data.Reserved = reserved;

	Information.Id = newServerEntity.Create();

	g_Entities.push_back(newServerEntity);

	Amount++;

	std::cout << "[CCheckpointEntity] Created checkpoint [" << Information.Id << "] at " << Data.Position.x << ", " << Data.Position.y << ", " << Data.Position.z << std::endl;
	std::cout << "[CCheckpointEntity] " << Amount << " checkpoints in the world." << std::endl;
}

void CCheckpointEntity::Destroy()
{
	std::cout << "[CCheckpointEntity] Removing checkpoint " << Information.Id <<  std::endl;

	Information = {};
	Data = {};

	Information.Id = -1;

	Amount--;

	std::cout << "[CCheckpointEntity] " << Amount << " checkpoints in the world." << std::endl;
}