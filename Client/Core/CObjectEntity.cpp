#include "stdafx.h"

int CObjectEntity::Amount = 0;

CObjectEntity::CObjectEntity()
{
	Data.Model = 0;
	Data.Dynamic = false;
	Information.Id = -1;

	Game.Object = NULL;
	Game.Created = false;
	Data.Model = 0;
	Network.Assigned = UNASSIGNED_RAKNET_GUID;
}

bool CObjectEntity::Create(int entity, int hash, CVector3 position, CVector4 quaternion, bool dynamic)
{
	if (STREAMING::IS_MODEL_IN_CDIMAGE(hash) && STREAMING::IS_MODEL_VALID(hash))
	{
		Data.Model = hash;
		Data.Dynamic = dynamic;
		Data.Position = position;
		Data.Quaternion = quaternion;
		Information.Id = entity;

		Amount++;

		Network.LastSyncSent = timeGetTime();
		Network.Synchronized = true;

		CServerEntity newServerEntity;
		newServerEntity.Create(entity, CServerEntity::Object);
		g_Entities.push_back(newServerEntity);

		return true;
	}
	else
	{
		std::cout << "[CObjectEntity] " << entity << " has invalid model " << hash << std::endl;
		return false;
	}
}

bool CObjectEntity::CreateObject()
{
	if (!Game.Created)
	{
		if (STREAMING::IS_MODEL_IN_CDIMAGE(Data.Model) && STREAMING::IS_MODEL_VALID(Data.Model))
		{
			STREAMING::REQUEST_MODEL(Data.Model);
			while (!STREAMING::HAS_MODEL_LOADED(Data.Model))
				WAIT(0);

			Game.Object = OBJECT::CREATE_OBJECT_NO_OFFSET(Data.Model, Data.Position.fX, Data.Position.fY, Data.Position.fZ, false, true, Data.Dynamic);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Data.Model);

			ENTITY::SET_ENTITY_QUATERNION(Game.Object, Data.Quaternion.fX, Data.Quaternion.fY, Data.Quaternion.fZ, Data.Quaternion.fW);

			if (!Data.Dynamic)
				ENTITY::FREEZE_ENTITY_POSITION(Game.Object, true);

			Game.Created = true;
			return true;
		}

		std::cout << "[CObjectEntity] Tried to create " << Information.Id << ", but model " << Data.Model << " does not exist!" << std::endl;
		return false;
	}

	std::cout << "[CObjectEntity] Object already created" << std::endl;
	return false;
}

void CObjectEntity::Destroy()
{
	std::cout << "[CObjectEntity] Removing Object [" << Information.Id << "] " << Data.Model << std::endl;

	if (ENTITY::DOES_ENTITY_EXIST(Game.Object))
		ENTITY::DELETE_ENTITY(&Game.Object);

	if (Game.Blip)
		UI::REMOVE_BLIP(&Game.Blip);

	Information = {};
	Data = {};
	Network = {};

	Information.Id = -1;

	Amount--;

	//std::cout << "[CObjectEntity] " << Amount << " objects in the world." << std::endl;
}

void CObjectEntity::Delete()
{
	if (Game.Object)
		ENTITY::DELETE_ENTITY(&Game.Object);

	if (Game.Blip)
		UI::REMOVE_BLIP(&Game.Blip);

	Game.Created = false;
}

void CObjectEntity::Pulse()
{
	if (g_Core->GetNetworkManager()->GetInterface()->GetMyGUID() != Network.Assigned)
	{
		//Interpolate();
	}
	else if (g_Core->GetNetworkManager()->GetInterface()->GetMyGUID() == Network.Assigned)
	{
		BitStream bitstream;
		bitstream.Write((unsigned char)ID_PACKET_OBJECT);

		bitstream.Write(Information.Id);

		bitstream.Write(Data.Position.fX);
		bitstream.Write(Data.Position.fY);
		bitstream.Write(Data.Position.fZ);

		bitstream.Write(Data.Velocity.fX);
		bitstream.Write(Data.Velocity.fY);
		bitstream.Write(Data.Velocity.fZ);

		bitstream.Write(Data.Quaternion.fX);
		bitstream.Write(Data.Quaternion.fY);
		bitstream.Write(Data.Quaternion.fZ);
		bitstream.Write(Data.Quaternion.fW);

		g_Core->GetNetworkManager()->GetInterface()->Send(&bitstream, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 0, g_Core->GetNetworkManager()->GetSystemAddress(), false);

		Network.LastSyncSent = timeGetTime();
	}
}

void CObjectEntity::Update(Packet *packet)
{
	BitStream bitstream(packet->data + 1, packet->length + 1, false);

	bitstream.Read(Information.Id);

	bitstream.Read(Data.Position.fX);
	bitstream.Read(Data.Position.fY);
	bitstream.Read(Data.Position.fZ);

	bitstream.Read(Data.Velocity.fX);
	bitstream.Read(Data.Velocity.fY);
	bitstream.Read(Data.Velocity.fZ);

	bitstream.Read(Data.Quaternion.fX);
	bitstream.Read(Data.Quaternion.fY);
	bitstream.Read(Data.Quaternion.fZ);
	bitstream.Read(Data.Quaternion.fW);
}