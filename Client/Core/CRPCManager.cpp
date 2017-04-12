#include "stdafx.h"

CRPCManager::RPCMessage rpcmessages[] = {
#pragma region Visual
	{ "ShowMessageAboveMap", CRPCVisual::ShowMessageAboveMap },
#pragma endregion
#pragma region World
	{ "SetTime", CRPCWorld::SetTime },
	{ "SetWeather", CRPCWorld::SetWeather },
	{ "LoadIPL", CRPCWorld::LoadIPL },
	{ "UnloadIPL", CRPCWorld::UnloadIPL },
#pragma endregion
#pragma region Entity
	{ "DestroyEntity", CRPCEntity::Destroy },
	{ "SetPosition", CRPCEntity::SetPosition },
	{ "SetRotation", CRPCEntity::SetRotation },
	{ "TakeEntityAssignment", CRPCEntity::TakeEntityAssignment },
	{ "DropEntityAssignment", CRPCEntity::DropEntityAssignment },
	{ "PedComponent", CRPCEntity::PedComponent },
	{ "PedHeadBlend", CRPCEntity::PedHeadBlend },
	{ "PedHeadOverlay", CRPCEntity::PedHeadOverlay },
	{ "PedProp", CRPCEntity::PedProp },
	{ "PedFaceFeature", CRPCEntity::PedFaceFeature },
	{ "SetViewDistance", CRPCEntity::SetViewDistance },
#pragma endregion
#pragma region Player
	{ "PlayerModel", CRPCPlayer::PlayerModel },
#pragma endregion
#pragma region Object
	{ "CreateObject", CRPCObject::Create },
	{ "SetTextureVariation", CRPCObject::SetTextureVariation },
#pragma endregion
#pragma region Npc
	{ "CreateNPC", CRPCNpc::Create },
#pragma endregion
#pragma region Checkpoint
	{ "CreateCheckpoint", CRPCCheckpoint::Create  },
	{ "ShowCheckpoint", CRPCCheckpoint::Show },
	{ "HideCheckpoint", CRPCCheckpoint::Hide },
	{ "SetCheckpointHeight", CRPCCheckpoint::SetHeight },
#pragma endregion
#pragma region Vehicle
	{ "SetStandardColor", CRPCVehicle::SetStandardColor},
	{ "SetCustomColor", CRPCVehicle::SetCustomColor },
	{ "SetNumberPlate", CRPCVehicle::SetNumberPlate },
	{ "SetMod", CRPCVehicle::SetMod },
	{ "SetEngineState", CRPCVehicle::SetEngineState },
	{ "SetDoorsLockState", CRPCVehicle::SetDoorsLockState }
#pragma endregion
};

void CRPCManager::RegisterRPCMessages()
{
	for (int i = 0; i < /*sizeof(rpcmessages) / sizeof(RPCMessage)*/SizeOfArray(rpcmessages); i++)
	{
		CNetworkManager::GetRPC().RegisterSlot(rpcmessages[i].name, rpcmessages[i].functionPointer, 0);
	}

	Logger::Msg("CRPCManager:: Registered RPC Messages");
}

void CRPCManager::UnregisterRPCMessages()
{
	for (int i = 0; i < /*sizeof(rpcmessages) / sizeof(RPCMessage)*/SizeOfArray(rpcmessages); i++)
	{
		CNetworkManager::GetRPC().UnregisterSlot(rpcmessages[i].name);
	}

	Logger::Msg("CRPCManager:: Unregistered RPC Messages");
}