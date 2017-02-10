#include "stdafx.h"

int CObjectEntity::Amount = 0;

CObjectEntity::CObjectEntity()
{
	Game.Created = false;
	Data.ModelHash = 0;
	Network.Assigned = UNASSIGNED_RAKNET_GUID;
}

void CObjectEntity::Create(int entity, std::string model, CVector3 position, CVector4 quaternion, bool dynamic)
{
	CServerEntity newServerEntity;
	newServerEntity.SetId(entity);
	newServerEntity.SetType(newServerEntity.Object);
	newServerEntity.SetEntity(this);

	Data.Model = model;
	Data.Dynamic = dynamic;
	Data.Position = position;
	Data.Quaternion = quaternion;
	Information.Entity = entity;

	g_Entities.push_back(newServerEntity);

	Amount++;

	CreateObject();

	std::cout << "[CObjectEntity] " << Amount << " objects in the world." << std::endl;

	Network.LastSyncSent = timeGetTime();
	Network.Synchronized = true;
}

void CObjectEntity::Create(int entity, int hash, CVector3 position, CVector4 quaternion, bool dynamic)
{
	CServerEntity newServerEntity;
	newServerEntity.SetId(entity);
	newServerEntity.SetType(newServerEntity.Object);
	newServerEntity.SetEntity(this);

	Data.ModelHash = hash;
	Data.Dynamic = dynamic;
	Data.Position = position;
	Data.Quaternion = quaternion;
	Information.Entity = entity;

	g_Entities.push_back(newServerEntity);

	Amount++;

	CreateObject();

	std::cout << "[CObjectEntity] " << Amount << " objects in the world." << std::endl;

	Network.LastSyncSent = timeGetTime();
	Network.Synchronized = true;
}

void CObjectEntity::CreateObject()
{
	if (!Game.Created)
	{
		Hash model;
		if (Data.ModelHash == 0)
			model = GAMEPLAY::GET_HASH_KEY((char*)Data.Model.c_str());
		else
			model = Data.ModelHash;

		if (STREAMING::IS_MODEL_IN_CDIMAGE(model) && STREAMING::IS_MODEL_VALID(model))
		{
			STREAMING::REQUEST_MODEL(model);
			while (!STREAMING::HAS_MODEL_LOADED(model))
				WAIT(0);

			Game.Object = OBJECT::CREATE_OBJECT_NO_OFFSET(model, Data.Position.fX, Data.Position.fY, Data.Position.fZ, false, true, Data.Dynamic);
			//STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(model);

			ENTITY::SET_ENTITY_QUATERNION(Game.Object, Data.Quaternion.fX, Data.Quaternion.fY, Data.Quaternion.fZ, Data.Quaternion.fW);
			//ENTITY::SET_ENTITY_ROTATION(Game.Object, Data.Rotation.fX, Data.Rotation.fY, Data.Rotation.fZ, 2, 1);

			if (!Data.Dynamic)
				ENTITY::FREEZE_ENTITY_POSITION(Game.Object, true);

			Game.Created = true;
			std::cout << "[CObjectEntity] Created Object" << std::endl;
			return;
		}

		std::cout << "[CObjectEntity] Tried to create " << Information.Entity << ", but model does not exist!" << std::endl;
		return;
	}

	std::cout << "[CObjectEntity] Object all ready created" << std::endl;
}

void CObjectEntity::Destroy()
{
	std::cout << "[CObjectEntity] Removing Object [" << Information.Entity << "] " << Data.Model.c_str() << std::endl;

	if (ENTITY::DOES_ENTITY_EXIST(Game.Object))
		ENTITY::DELETE_ENTITY(&Game.Object);

	if (Game.Blip)
		UI::REMOVE_BLIP(&Game.Blip);

	Information = {};
	Data = {};
	Network = {};

	Information.Entity = -1;

	Amount--;

	std::cout << "[CObjectEntity] " << Amount << " objects in the world." << std::endl;
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

		bitstream.Write(Information.Entity);

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

	bitstream.Read(Information.Entity);

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