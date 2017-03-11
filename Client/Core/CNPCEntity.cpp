#include "stdafx.h"

int CNPCEntity::Amount = 0;

CNPCEntity::CNPCEntity()
{
	Data.Id = -1;

	Game.Npc = NULL;
	Game.Created = false;
	//Network.Assigned = UNASSIGNED_RAKNET_GUID;
}

bool CNPCEntity::Create(const int entity, const RakString model, const CVector3 position, const CVector4 quaternion)
{
	Hash hash = GAMEPLAY::GET_HASH_KEY((char*)model.C_String());
	if (STREAMING::IS_MODEL_IN_CDIMAGE(hash) && STREAMING::IS_MODEL_VALID(hash))
	{
		CServerEntity newServerEntity;
		newServerEntity.SetType(newServerEntity.NPC);
		newServerEntity.SetId(entity);

		Data.Model.Model = model;
		Data.Position = position;

		Data.Quaternion = quaternion;
		Data.Id = entity;

		g_Entities.push_back(newServerEntity);

		Amount++;

		std::cout << "[CNPCEntity] Created NPC [" << Data.Id << "] with model " << Data.Model.Model.C_String() << " at " << Data.Position.fX << ", " << Data.Position.fY << ", " << Data.Position.fZ << std::endl;
		std::cout << "[CNPCEntity] " << Amount << " npcs in the world." << std::endl;

		Network.LastSyncSent = std::chrono::system_clock::now();
		Network.Synchronized = true;
		return true;
	}
	else
	{
		std::cout << "[CNPCEntity] " << entity << " has invalid model " << hash << std::endl;
		return false;
	}
}

bool CNPCEntity::CreateNpc()
{
	if (!Game.Created)
	{
		Hash hash = GAMEPLAY::GET_HASH_KEY((char*)Data.Model.Model.C_String());
		if (STREAMING::IS_MODEL_IN_CDIMAGE(hash) && STREAMING::IS_MODEL_VALID(hash))
		{
			STREAMING::REQUEST_MODEL(hash);

			while (!STREAMING::HAS_MODEL_LOADED(hash)) 
				WAIT(0);

			Game.Npc = PED::CREATE_PED(Data.Model.Type, hash, Data.Position.fX, Data.Position.fY, Data.Position.fZ, 0.0f, false, true);

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(hash);

			ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(g_Core->GetLocalPlayer()->GetPed(), Game.Npc, false);
			ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(Game.Npc, g_Core->GetLocalPlayer()->GetPed(), false);

			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(Game.Npc, Data.Position.fX, Data.Position.fY, Data.Position.fZ, false, false, false);

			PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Game.Npc, true);
			PED::SET_PED_FLEE_ATTRIBUTES(Game.Npc, 0, 0);
			PED::SET_PED_COMBAT_ATTRIBUTES(Game.Npc, 17, true);
			PED::SET_PED_CAN_RAGDOLL(Game.Npc, false);
			PED::UNREGISTER_PEDHEADSHOT(Game.Npc);

			WEAPON::SET_PED_DROPS_WEAPONS_WHEN_DEAD(Game.Npc, false);

			AI::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Game.Npc, true);

			Hash relationshipGroup;
			PED::ADD_RELATIONSHIP_GROUP("FIVEMPPLAYER", &relationshipGroup);
			PED::SET_PED_RELATIONSHIP_GROUP_HASH(Game.Npc, relationshipGroup);

			Game.Blip = UI::ADD_BLIP_FOR_ENTITY(Game.Npc);
			UI::SET_BLIP_COLOUR(Game.Blip, 2);

			// Set Component Variations
			for (int i = 0; i < SizeOfArray(Data.ModelComponents); i++)
			{
				GamePed::SetPedComponentVariation(Game.Npc, i, Data.ModelComponents[i].drawableid, Data.ModelComponents[i].textureid, Data.ModelComponents[i].paletteid);
			}

			// Set Headblend
			GamePed::SetPedHeadBlend(Game.Npc, Data.ModelHeadBlend.shapeFirst, Data.ModelHeadBlend.shapeSecond, Data.ModelHeadBlend.shapeThird, Data.ModelHeadBlend.skinFirst, Data.ModelHeadBlend.skinSecond, Data.ModelHeadBlend.skinThird, Data.ModelHeadBlend.shapeMix, Data.ModelHeadBlend.skinMix, Data.ModelHeadBlend.thirdMix);

			// Set Head 
			for (int i = 0; i < SizeOfArray(Data.ModelHeadOverlay); i++)
			{
				GamePed::SetPedHeadOverlayColor(Game.Npc, i, Data.ModelHeadOverlay[i].index, Data.ModelHeadOverlay[i].colorType, Data.ModelHeadOverlay[i].colorID, Data.ModelHeadOverlay[i].secondColorID, Data.ModelHeadOverlay[i].opacity);
			}

			// Set Ped Props
			for (int i = 0; i < SizeOfArray(Data.ModelProp); i++)
			{
				GamePed::SetPedProp(Game.Npc, i, Data.ModelProp[i].drawableid, Data.ModelProp[i].textureid);
			}

			// Set Face Features
			for (int i = 0; i < SizeOfArray(Data.ModelFaceFeature); i++)
			{
				GamePed::SetPedFaceFeature(Game.Npc, i, Data.ModelFaceFeature[i].scale);
			}

			Game.Created = true;
			std::cout << "[CNPCEntity] " << Data.Id << " created." << std::endl;
			return true;
		}
		std::cout << "[CNPCEntity] Tried to create " << Data.Id << ", but model does not exist!" << std::endl;
		return false;
	}
	std::cout << "[CNPCEntity] " << Data.Id << " already created." << std::endl;
	return false;
}

void CNPCEntity::Destroy()
{
	std::cout << "[CNPCEntity] Removing NPC [" << Data.Id << "] " << Data.Model.Model << std::endl;

	if (ENTITY::DOES_ENTITY_EXIST(Game.Npc))
		ENTITY::DELETE_ENTITY(&Game.Npc);

	if (Game.Blip)
		UI::REMOVE_BLIP(&Game.Blip);

	Data = {};
	Network = {};

	Data.Id = -1;

	Amount--;
}

void CNPCEntity::Delete()
{
	if (Game.Npc)
		ENTITY::DELETE_ENTITY(&Game.Npc);

	if (Game.Blip)
		UI::REMOVE_BLIP(&Game.Blip);

	Game.Created = false;
}