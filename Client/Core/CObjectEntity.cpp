#include "stdafx.h"

int CObjectEntity::Amount = 0;

CObjectEntity::CObjectEntity()
{
	Data.Model.Model = 0;
	Data.Model.Dynamic = false;
	Information.Id = -1;

	Game.Object = NULL;
	Game.Created = false;
	Data.Model.Model = 0;
	Network.Assigned = UNASSIGNED_RAKNET_GUID;
}

bool CObjectEntity::Create(int entity, int hash, CVector3 position, CVector4 quaternion, bool dynamic)
{
	if (STREAMING::IS_MODEL_IN_CDIMAGE(hash) && STREAMING::IS_MODEL_VALID(hash))
	{
		Data.Model.Model = hash;
		Data.Model.Dynamic = dynamic;
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
		if (STREAMING::IS_MODEL_IN_CDIMAGE(Data.Model.Model) && STREAMING::IS_MODEL_VALID(Data.Model.Model))
		{
			std::cout << "[CObjectEntity] " << Information.Id << " being created." << std::endl;

			STREAMING::REQUEST_MODEL(Data.Model.Model);
			/*while (!STREAMING::HAS_MODEL_LOADED(Data.Model.Model)) //Removed this for now as abit of a test as this can get stuck.
				WAIT(0);*/

			Game.Object = OBJECT::CREATE_OBJECT_NO_OFFSET(Data.Model.Model, Data.Position.fX, Data.Position.fY, Data.Position.fZ, false, true, Data.Model.Dynamic);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Data.Model.Model);

			ENTITY::SET_ENTITY_QUATERNION(Game.Object, Data.Quaternion.fX, Data.Quaternion.fY, Data.Quaternion.fZ, Data.Quaternion.fW);

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
	if (Game.Object)
		ENTITY::DELETE_ENTITY(&Game.Object);

	if (Game.Blip)
		UI::REMOVE_BLIP(&Game.Blip);

	Game.Created = false;
}

void CObjectEntity::Pulse()
{
	if (Game.Created && Information.Id != -1 && Data.Model.Dynamic)
	{
		if (g_Core->GetNetworkManager()->GetInterface()->GetMyGUID() != Network.Assigned)
		{
			Interpolate();
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
		CVector3 CurrentPosition = { Coordinates.x, Coordinates.y, Coordinates.z };

		// Set the target position
		CVector3 TargetPosition = { Data.Position.fX, Data.Position.fY, Data.Position.fZ };
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
		if ((vecCurrentPosition - InterpolationData.Position.Target).Length() > 750.0f)
		{
			// Abort all interpolation
			InterpolationData.Position.FinishTime = 0;
			vecNewPosition = InterpolationData.Position.Target;
		}

		// Set our new position
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(Game.Object, vecNewPosition.fX, vecNewPosition.fY, vecNewPosition.fZ, false, false, false);
		ENTITY::SET_ENTITY_VELOCITY(Game.Object, Data.Velocity.fX, Data.Velocity.fY, Data.Velocity.fZ);
		ENTITY::SET_ENTITY_QUATERNION(Game.Object, Data.Quaternion.fX, Data.Quaternion.fY, Data.Quaternion.fZ, Data.Quaternion.fW);
	}
}

void CObjectEntity::UpdateTargetRotation()
{
	if (Game.Created)
	{
		unsigned int interpolationtime = timeGetTime() - Network.LastSyncReceived;
		unsigned long CurrentTime = timeGetTime();

		// Get our quaternion
		CVector4 CurrentQuaternion;
		ENTITY::GET_ENTITY_QUATERNION(Game.Object, &CurrentQuaternion.fX, &CurrentQuaternion.fY, &CurrentQuaternion.fZ, &CurrentQuaternion.fW);

		// Get our rotation
		CVector3 CurrentRotation = CVector3::calculateEuler(CurrentQuaternion.fX, CurrentQuaternion.fY, CurrentQuaternion.fZ, CurrentQuaternion.fW);

		// Set the target rotation from target quaternion
		CVector3 TargetQuaternion = CVector3::calculateEuler(Data.Quaternion.fX, Data.Quaternion.fY, Data.Quaternion.fZ, Data.Quaternion.fW);
		CVector3 TargetRotation = { TargetQuaternion.fX, TargetQuaternion.fY, TargetQuaternion.fZ };
		InterpolationData.Rotation.Target = TargetRotation;

		// Get the error
		//InterpolationData.Rotation.Error = Math::GetOffsetDegrees(vecLocalRotation, vecRotation);
		InterpolationData.Rotation.Error = TargetRotation - CurrentRotation;
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
			CVector4 vecCurrentQuaternion;
			ENTITY::GET_ENTITY_QUATERNION(Game.Object, &vecCurrentQuaternion.fX, &vecCurrentQuaternion.fY, &vecCurrentQuaternion.fZ, &vecCurrentQuaternion.fW);
			CVector3 vecCurrentRotation = CVector3::calculateEuler(vecCurrentQuaternion.fX, vecCurrentQuaternion.fY, vecCurrentQuaternion.fZ, vecCurrentQuaternion.fW);

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
			CVector3 vecNewRotation = vecCurrentRotation + vecCompensation;
			CVector4 vecNewQuaternion = CVector4::calculateQuaternion(vecNewRotation.fX, vecNewRotation.fY, vecNewRotation.fZ);

			// Set our new position
			ENTITY::SET_ENTITY_QUATERNION(Game.Object, vecNewQuaternion.fX, vecNewQuaternion.fY, vecNewQuaternion.fZ, vecNewQuaternion.fW);
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