#include "stdafx.h"

int CNPCEntity::Amount = 0;

void CNPCEntity::Create(const std::string model, const CVector3 position, const float heading)
{
	CServerEntity newServerEntity;
	newServerEntity.SetType(newServerEntity.NPC);

	Data.Model.Model = RakString(model.c_str());
	Data.Position = position;

	Data.Quaternion = CVector4::calculateQuaternion(0.0f, heading, 0.0f);
	Data.Id = newServerEntity.Create();

	g_Entities.push_back(newServerEntity);

	Amount++;

	std::cout << "[CNPCEntity] Created NPC [" << Data.Id << "] with model " << Data.Model.Model.C_String() << " at " << Data.Position.fX << ", " << Data.Position.fY << ", " << Data.Position.fZ << std::endl;
	std::cout << "[CNPCEntity] " << Amount << " npcs in the world." << std::endl;

	Network.LastSyncSent = std::chrono::system_clock::now();
	Network.Synchronized = true;
}