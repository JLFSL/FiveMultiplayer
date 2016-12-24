#include "stdafx.h"

void CPlayerEntity::Create(std::string Name, RakNetGUID GUID) {
	Information.Name = Name;
	Information.Id = g_Players.size();
	Network.GUID = GUID;

	std::cout << "[CPlayerEntity] Added Player: " << Information.Name << std::endl;
}

void CPlayerEntity::CreatePed()
{
	char *name = "a_f_y_tourist_02";
	int PedHash = GAMEPLAY::GET_HASH_KEY(name);
	if (STREAMING::IS_MODEL_IN_CDIMAGE(PedHash) && STREAMING::IS_MODEL_VALID(PedHash))
	{
		STREAMING::REQUEST_MODEL(PedHash);
		while (!STREAMING::HAS_MODEL_LOADED(PedHash)) WAIT(0);
		Game.Ped = PED::CREATE_PED(26, PedHash, Data.Position.fX, Data.Position.fY, Data.Position.fZ, 0.0f, false, true);

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PedHash);

		ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(g_Core->GetLocalPlayer()->GetPed(), Game.Ped, false);
		ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(Game.Ped, g_Core->GetLocalPlayer()->GetPed(), false);

		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(Game.Ped, Data.Position.fX, Data.Position.fY, Data.Position.fZ, false, false, false);

		PED::SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Game.Ped, true);
		PED::SET_PED_FLEE_ATTRIBUTES(Game.Ped, 0, 0);
		PED::SET_PED_COMBAT_ATTRIBUTES(Game.Ped, 17, true);
		PED::SET_PED_CAN_RAGDOLL(Game.Ped, false);
		PED::UNREGISTER_PEDHEADSHOT(Game.Ped);

		WEAPON::SET_PED_DROPS_WEAPONS_WHEN_DEAD(Game.Ped, false);

		AI::TASK_SET_BLOCKING_OF_NON_TEMPORARY_EVENTS(Game.Ped, true);

		Game.Blip = UI::ADD_BLIP_FOR_ENTITY(Game.Ped);
		UI::SET_BLIP_AS_FRIENDLY(Game.Blip, true);

		Game.Created = true;
		std::cout << "[CPlayerEntity] Created Ped" << std::endl;
	}
}

void CPlayerEntity::Destroy()
{
	std::cout << "[CPlayerEntity] Removing Player: " << Information.Name << std::endl;
	
	ENTITY::DELETE_ENTITY(&Game.Ped);
	Game.Created = false;
	UI::REMOVE_BLIP(&Game.Blip);

	Game = {};
	Information = {};
	Statistics = {};
	Data = {};
	Network = {};
	InterpolationData = {};

	Information.Id = -1;
}

void CPlayerEntity::Pulse()
{
	if(Game.Created)
		Interpolate();
}

void CPlayerEntity::Update(Packet *packet)
{
	BitStream bitstream(packet->data + 1, packet->length + 1, false);

	bitstream.Read(Network.GUID);
	bitstream.Read(Information.Id);
	bitstream.Read(Information.Name);

	bitstream.Read(Statistics.Score);

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

	if(g_Core->GetNetworkManager()->GetInterface()->GetMyGUID() != Network.GUID) {
		if (!Game.Created)
			CreatePed();

		UpdateTargetPosition();
	}
	//UpdateTargetRotation();
}

void CPlayerEntity::Interpolate()
{
	SetTargetPosition();
	//SetTargetRotation();
}

void CPlayerEntity::UpdateTargetPosition()
{
	if (Game.Created) {
		unsigned long CurrentTime = timeGetTime();
		unsigned int InterpolationTime = CurrentTime - Network.LastSyncReceived;

		// Get our position
		Vector3 Coordinates = ENTITY::GET_ENTITY_COORDS(Game.Ped, ENTITY::IS_ENTITY_DEAD(Game.Ped));
		CVector3 CurrentPosition = { Coordinates.x, Coordinates.y, Coordinates.z };

		// Set the target position
		CVector3 TargetPosition = { Data.Position.fX, Data.Position.fY, Data.Position.fZ };
		InterpolationData.Position.Target = TargetPosition;

		// Calculate the relative error
		InterpolationData.Position.Error = TargetPosition - CurrentPosition;

		// Get the interpolation interval
		InterpolationData.Position.StartTime = CurrentTime;
		InterpolationData.Position.FinishTime = (CurrentTime + InterpolationTime);

		// Initialize the interpolation
		InterpolationData.Position.LastAlpha = 0.0f;

		Network.LastSyncReceived = timeGetTime();
	}
}

void CPlayerEntity::SetTargetPosition()
{
	if (InterpolationData.Position.FinishTime != 0 && Game.Created) {
		// Get our position
		Vector3 Coordinates = ENTITY::GET_ENTITY_COORDS(Game.Ped, ENTITY::IS_ENTITY_DEAD(Game.Ped));
		CVector3 vecCurrentPosition = { Coordinates.x, Coordinates.y, Coordinates.z };

		// Get the factor of time spent from the interpolation start to the current time.
		unsigned long CurrentTime = timeGetTime();
		float fAlpha = Math::Unlerp(InterpolationData.Position.StartTime, CurrentTime, InterpolationData.Position.FinishTime);

		// Don't let it overcompensate the error
		fAlpha = Math::Clamp(0.0f, fAlpha, 1.0f);

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
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(Game.Ped, vecNewPosition.fX, vecNewPosition.fY, vecNewPosition.fZ, false, false, false);
		ENTITY::SET_ENTITY_VELOCITY(Game.Ped, Data.Velocity.fX, Data.Velocity.fY, Data.Velocity.fZ);
		ENTITY::SET_ENTITY_QUATERNION(Game.Ped, Data.Quaternion.fX, Data.Quaternion.fY, Data.Quaternion.fZ, Data.Quaternion.fW);
	}
}

void CPlayerEntity::UpdateTargetRotation()
{
	unsigned int interpolationtime = timeGetTime() - Network.LastSyncReceived;
	unsigned long ulTime = timeGetTime();

	// Get our position
	CVector3 vecLocalRotation;
	float unusedw;
	ENTITY::GET_ENTITY_QUATERNION(Game.Ped, &vecLocalRotation.fX, &vecLocalRotation.fY, &vecLocalRotation.fZ, &unusedw);

	// Set the target rotation
	CVector3 vecRotation = { Data.Quaternion.fX, Data.Quaternion.fY, Data.Quaternion.fZ };
	InterpolationData.Rotation.Target = vecRotation;

	// Get the error
	InterpolationData.Rotation.Error = Math::GetOffsetDegrees(vecLocalRotation, vecRotation);
	InterpolationData.Rotation.Error *= Math::Lerp < const float >(0.40f, Math::UnlerpClamped(100, interpolationtime, 400), 1.0f);

	// Get the interpolation interval
	InterpolationData.Rotation.StartTime = ulTime;
	InterpolationData.Rotation.FinishTime = (ulTime + interpolationtime);

	// Initialize the interpolation
	InterpolationData.Rotation.LastAlpha = 0.0f;
}

void CPlayerEntity::SetTargetRotation()
{
	if (InterpolationData.Rotation.FinishTime != 0) {
		CVector3 vecCurrentRotation;

		// Get our rotation
		float unusedw;
		ENTITY::GET_ENTITY_QUATERNION(Game.Ped, &vecCurrentRotation.fX, &vecCurrentRotation.fY, &vecCurrentRotation.fZ, &unusedw);

		// Get the factor of time spent from the interpolation start to the current time.
		unsigned long ulCurrentTime = timeGetTime();
		float fAlpha = Math::Unlerp(InterpolationData.Rotation.StartTime, ulCurrentTime, InterpolationData.Rotation.FinishTime);

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

		// Set our new position
		ENTITY::SET_ENTITY_QUATERNION(Game.Ped, vecNewRotation.fX, vecNewRotation.fY, vecNewRotation.fZ, unusedw);
	}
}
