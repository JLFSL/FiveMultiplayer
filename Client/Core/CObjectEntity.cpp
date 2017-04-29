#include "stdafx.h"

int CObjectEntity::Amount = 0;

CObjectEntity::CObjectEntity()
{
	Data.Model.Model = 0;
	Data.Model.Dynamic = false;
	Data.Model.textureIndex = 0;

	Information.Id = -1;

	Game.Object = NULL;
	Game.Created = false;
	Network.Assigned = UNASSIGNED_RAKNET_GUID;

	Network.LastSyncSent = timeGetTime();
}

bool CObjectEntity::Create(int entity, int hash, CVector3 position, CVector3 rotation, bool dynamic)
{
	if (STREAMING::IS_MODEL_IN_CDIMAGE(hash) && STREAMING::IS_MODEL_VALID(hash))
	{
		Data.Model.Model = hash;
		Data.Model.Dynamic = dynamic;
		Data.Position = position;
		Data.Rotation = rotation;
		Information.Id = entity;

		Amount++;

		Network.LastSyncSent = timeGetTime();
		Network.Synchronized = true;

		CServerEntity newServerEntity;
		newServerEntity.Create(entity, CServerEntity::Object);
		g_Entities.push_back(newServerEntity);

		STREAMING::REQUEST_MODEL(Data.Model.Model);

		RequestData();

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
		if (STREAMING::IS_MODEL_IN_CDIMAGE(Data.Model.Model) && STREAMING::IS_MODEL_VALID(Data.Model.Model))
		{
			std::cout << "[CObjectEntity] " << Information.Id << " being created." << std::endl;

			STREAMING::REQUEST_MODEL(Data.Model.Model);

			if (!STREAMING::HAS_MODEL_LOADED(Data.Model.Model)) 
				return false;

			Game.Object = OBJECT::CREATE_OBJECT_NO_OFFSET(Data.Model.Model, Data.Position.x, Data.Position.y, Data.Position.z, false, true, Data.Model.Dynamic);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Data.Model.Model);

			ENTITY::SET_ENTITY_ROTATION(Game.Object, Data.Rotation.x, Data.Rotation.y, Data.Rotation.z, 0, true);

			if (!Data.Model.Dynamic)
				ENTITY::FREEZE_ENTITY_POSITION(Game.Object, true);

			Game.Created = true;

			SetTargetData();

			std::cout << "[CObjectEntity] " << Information.Id << " created." << std::endl;
			return true;
		}

		std::cout << "[CObjectEntity] Tried to create " << Information.Id << ", but model " << Data.Model.Model << " does not exist!" << std::endl;
		return false;
	}

	std::cout << "[CObjectEntity] Object already created" << std::endl;
	return false;
}

void CObjectEntity::RequestData()
{
	RakNet::BitStream sData;
	sData.Write(Information.Id);
	CNetworkManager::GetRPC().Signal("RequestEntityData", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, CNetworkManager::GetSystemAddress(), false, false);
}

void CObjectEntity::Destroy()
{
	std::cout << "[CObjectEntity] Removing Object [" << Information.Id << "] " << Data.Model.Model << std::endl;

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
	if (ENTITY::DOES_ENTITY_EXIST(Game.Object))
		ENTITY::DELETE_ENTITY(&Game.Object);

	if (Game.Blip)
		UI::REMOVE_BLIP(&Game.Blip);

	Game.Object = 0;
	Game.Blip = 0;

	if (CNetworkManager::GetInterface()->GetMyGUID() == Network.Assigned)
	{
		RakNet::BitStream sData;
		sData.Write(Information.Id);
		CNetworkManager::GetRPC().Signal("DropEntityAssignment", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, CNetworkManager::GetSystemAddress(), false, false);
	}

	Game.Created = false;
}

void CObjectEntity::Pulse()
{
	if (Game.Created && Information.Id != -1 && Data.Model.Dynamic)
	{
		if (CNetworkManager::GetInterface()->GetMyGUID() != Network.Assigned)
		{
			Interpolate();
		}
		else if (CNetworkManager::GetInterface()->GetMyGUID() == Network.Assigned)
		{
			if (timeGetTime() > Network.LastSyncSent + (1000.0f / 50))
			{
				BitStream bitstream;
				bitstream.Write((unsigned char)ID_PACKET_OBJECT);

				bitstream.Write(Information.Id);

				bitstream.Write(Data.Position.x);
				bitstream.Write(Data.Position.y);
				bitstream.Write(Data.Position.z);

				bitstream.Write(Data.Velocity.x);
				bitstream.Write(Data.Velocity.y);
				bitstream.Write(Data.Velocity.z);

				bitstream.Write(Data.Rotation.x);
				bitstream.Write(Data.Rotation.y);
				bitstream.Write(Data.Rotation.z);

				CNetworkManager::GetInterface()->Send(&bitstream, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 0, CNetworkManager::GetSystemAddress(), false);

				Network.LastSyncSent = timeGetTime();
			}
		}
	}
}

void CObjectEntity::Update(Packet *packet)
{
	BitStream bitstream(packet->data + 1, packet->length + 1, false);

	bitstream.Read(Information.Id);

	bitstream.Read(Data.Position.x);
	bitstream.Read(Data.Position.y);
	bitstream.Read(Data.Position.z);

	bitstream.Read(Data.Velocity.x);
	bitstream.Read(Data.Velocity.y);
	bitstream.Read(Data.Velocity.z);

	bitstream.Read(Data.Rotation.x);
	bitstream.Read(Data.Rotation.y);
	bitstream.Read(Data.Rotation.z);

	Network.LastSyncReceived = timeGetTime();
}

void CObjectEntity::Interpolate()
{
	SetTargetPosition();
	SetTargetRotation();
	SetTargetData();
}

void CObjectEntity::UpdateTargetPosition()
{
	if (Game.Created)
	{
		unsigned long CurrentTime = timeGetTime();
		unsigned int InterpolationTime = CurrentTime - Network.LastSyncReceived;

		// Get our position
		Vector3 Coordinates = ENTITY::GET_ENTITY_COORDS(Game.Object, ENTITY::IS_ENTITY_DEAD(Game.Object));
		CVector3 CurrentPosition(Coordinates.x, Coordinates.y, Coordinates.z);

		// Set the target position
		CVector3 TargetPosition(Data.Position.x, Data.Position.y, Data.Position.z);
		InterpolationData.Position.Target = TargetPosition;

		// Calculate the relative error
		InterpolationData.Position.Error = TargetPosition - CurrentPosition;

		// Apply the error over 400ms (i.e. 1/4 per 100ms)
		InterpolationData.Position.Error *= Math::Lerp<const float>(0.25f, Math::UnlerpClamped(100, InterpolationTime, 400), 1.0f);

		// Get the interpolation interval
		InterpolationData.Position.StartTime = CurrentTime;
		InterpolationData.Position.FinishTime = (CurrentTime + InterpolationTime);

		// Initialize the interpolation
		InterpolationData.Position.LastAlpha = 0.0f;
	}
}

void CObjectEntity::SetTargetPosition()
{
	if (InterpolationData.Position.FinishTime != 0 && Game.Created)
	{
		// Get our position
		Vector3 Coordinates = ENTITY::GET_ENTITY_COORDS(Game.Object, ENTITY::IS_ENTITY_DEAD(Game.Object));
		CVector3 vecCurrentPosition = { Coordinates.x, Coordinates.y, Coordinates.z };

		// Get the factor of time spent from the interpolation start to the current time.
		unsigned long CurrentTime = timeGetTime();
		float fAlpha = Math::Unlerp(InterpolationData.Position.StartTime, CurrentTime, InterpolationData.Position.FinishTime);

		// Don't let it overcompensate the error
		fAlpha = Math::Clamp(0.0f, fAlpha, 1.5f);

		// Get the current error portion to compensate
		float fCurrentAlpha = (fAlpha - InterpolationData.Position.LastAlpha);
		InterpolationData.Position.LastAlpha = fAlpha;

		// Apply the error compensation
		CVector3 vecCompensation = Math::Lerp(CVector3(), fCurrentAlpha, InterpolationData.Position.Error);

		// If we finished compensating the error, finish it for the next pulse
		if (fAlpha == 1.0f)
			InterpolationData.Position.FinishTime = 0;

		// Calculate the new position
		CVector3 vecNewPosition = vecCurrentPosition + vecCompensation;

		// Check if the distance to interpolate is too far
		if (CVector3::Distance(vecCurrentPosition, InterpolationData.Position.Target) > 750.0f)
		{
			// Abort all interpolation
			InterpolationData.Position.FinishTime = 0;
			vecNewPosition = InterpolationData.Position.Target;
		}

		// Set our new position
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(Game.Object, vecNewPosition.x, vecNewPosition.y, vecNewPosition.z, false, false, false);
		ENTITY::SET_ENTITY_VELOCITY(Game.Object, Data.Velocity.x, Data.Velocity.y, Data.Velocity.z);
		ENTITY::SET_ENTITY_ROTATION(Game.Object, Data.Rotation.x, Data.Rotation.y, Data.Rotation.z, 2, true);
	}
}

void CObjectEntity::UpdateTargetRotation()
{
	if (Game.Created)
	{
		unsigned int interpolationtime = timeGetTime() - Network.LastSyncReceived;
		unsigned long CurrentTime = timeGetTime();

		// Get our rotation
		Vector3 CurrentRotationVec = ENTITY::GET_ENTITY_ROTATION(Game.Object, 2);
		CVector3 CurrentRotation(CurrentRotationVec.x, CurrentRotationVec.y, CurrentRotationVec.z);

		// Set the target rotation
		CVector3 TargetRotation = { Data.Rotation.x, Data.Rotation.y, Data.Rotation.z };
		InterpolationData.Rotation.Target = TargetRotation;

		// Get the error
		InterpolationData.Rotation.Error.x = Math::GetOffsetDegrees(CurrentRotation.x, TargetRotation.x);
		InterpolationData.Rotation.Error.y = Math::GetOffsetDegrees(CurrentRotation.y, TargetRotation.y);
		InterpolationData.Rotation.Error.z = Math::GetOffsetDegrees(CurrentRotation.z, TargetRotation.z);
		//InterpolationData.Rotation.Error = TargetRotation - CurrentRotation;
		InterpolationData.Rotation.Error *= Math::Lerp < const float >(0.40f, Math::UnlerpClamped(100, interpolationtime, 400), 1.0f);

		// Get the interpolation interval
		InterpolationData.Rotation.StartTime = CurrentTime;
		InterpolationData.Rotation.FinishTime = (CurrentTime + interpolationtime);

		// Initialize the interpolation
		InterpolationData.Rotation.LastAlpha = 0.0f;
	}
}

void CObjectEntity::SetTargetRotation()
{
	if (Game.Created)
	{
		if (InterpolationData.Rotation.FinishTime != 0)
		{
			// Get our rotation
			Vector3 CurrentRotationVec = ENTITY::GET_ENTITY_ROTATION(Game.Object, 2);
			CVector3 CurrentRotation(CurrentRotationVec.x, CurrentRotationVec.y, CurrentRotationVec.z);

			// Get the factor of time spent from the interpolation start to the current time.
			unsigned long CurrentTime = timeGetTime();
			float fAlpha = Math::Unlerp(InterpolationData.Rotation.StartTime, CurrentTime, InterpolationData.Rotation.FinishTime);

			// Don't let it overcompensate the error
			fAlpha = Math::Clamp(0.0f, fAlpha, 1.0f);

			// Get the current error portion to compensate
			float fCurrentAlpha = (fAlpha - InterpolationData.Rotation.LastAlpha);
			InterpolationData.Rotation.LastAlpha = fAlpha;

			// Apply the error compensation
			CVector3 vecCompensation = Math::Lerp(CVector3(), fCurrentAlpha, InterpolationData.Rotation.Error);

			// If we finished compensating the error, finish it for the next pulse
			if (fAlpha == 1.0f)
				InterpolationData.Rotation.FinishTime = 0;

			// Calculate the new position
			CVector3 vecNewRotation = CurrentRotation + vecCompensation;

			// Set our new position
			ENTITY::SET_ENTITY_ROTATION(Game.Object, vecNewRotation.x, vecNewRotation.y, vecNewRotation.z, 2, true);
		}
	}
}

void CObjectEntity::SetTargetData()
{
	if (Game.Created)
	{
		OBJECT::_SET_OBJECT_TEXTURE_VARIANT(Game.Object, Data.Model.textureIndex);
	}
}

void CObjectEntity::SetTextureVariation(const int textureIndex)
{
	Data.Model.textureIndex = textureIndex;

	if (Game.Created) {
		OBJECT::_SET_OBJECT_TEXTURE_VARIANT(Game.Object, textureIndex);
	}
}