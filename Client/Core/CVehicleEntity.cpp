#include "stdafx.h"
#include "CVehicleEntity.h"

void CVehicleEntity::Create(Hash Model)
{
	Information.Id = g_Players.size() + 1;

	std::cout << "[CVehicleEntity] Added Vehicle: " << Information.Id << std::endl;
}

void CVehicleEntity::CreateVehicle()
{
	if (!STREAMING::IS_MODEL_IN_CDIMAGE(Data.Model) && STREAMING::IS_MODEL_VALID(Data.Model))
		Data.Model = GAMEPLAY::GET_HASH_KEY("dilettante");

	STREAMING::REQUEST_COLLISION_AT_COORD(Data.Position.fX, Data.Position.fY, Data.Position.fZ);
	STREAMING::REQUEST_MODEL(Data.Model);
	while (!STREAMING::HAS_MODEL_LOADED(Data.Model)) 
		WAIT(0);

	Game.Vehicle = VEHICLE::CREATE_VEHICLE(Data.Model, Data.Position.fX, Data.Position.fY, Data.Position.fZ, Data.Heading, false, true);

	ENTITY::FREEZE_ENTITY_POSITION(Game.Vehicle, true);
	ENTITY::SET_ENTITY_COLLISION(Game.Vehicle, true, false);
	ENTITY::SET_ENTITY_LOAD_COLLISION_FLAG(Game.Vehicle, true);
	ENTITY::SET_ENTITY_QUATERNION(Game.Vehicle, Data.Quaternion.fX, Data.Quaternion.fY, Data.Quaternion.fZ, Data.Quaternion.fW);

	VEHICLE::SET_VEHICLE_MOD_KIT(Game.Vehicle, 0);
	//VEHICLE::SET_VEHICLE_COLOURS(Game.Vehicle, color1, color2);
	VEHICLE::SET_TAXI_LIGHTS(Game.Vehicle, true);
	VEHICLE::SET_VEHICLE_NUMBER_PLATE_TEXT(Game.Vehicle, "FiveMP");

	const int Class = VEHICLE::GET_VEHICLE_CLASS(Game.Vehicle);
	if (Class == 18 || Class == 17 || Class == 15 || Class == 16 || Class == 20 || Class == 14) {
		VEHICLE::SET_VEHICLE_MOD(Game.Vehicle, 48, 0, 0);
		VEHICLE::SET_VEHICLE_LIVERY(Game.Vehicle, 0);
	}

	DECORATOR::DECOR_REGISTER("FiveMP_Vehicle", 2);
	DECORATOR::DECOR_SET_BOOL(Game.Vehicle, "FiveMP_Vehicle", true);

	std::cout << "[CVehicleEntity] Created Vehicle" << std::endl;
	Game.Created = true;
}

void CVehicleEntity::Destroy()
{
	std::cout << "[CVehicleEntity] Removing Vehicle: " << Information.Id << std::endl;

	ENTITY::DELETE_ENTITY(&Game.Vehicle);
	Game.Created = false;
	UI::REMOVE_BLIP(&Game.Blip);

	Game = {};
	Information = {};
	Data = {};
	Network = {};
	InterpolationData = {};

	Information.Id = -1;
}

void CVehicleEntity::Pulse()
{
	if (Game.Created)
		Interpolate();
}

void CVehicleEntity::Update(Packet * packet)
{
	BitStream bitstream(packet->data + 1, packet->length + 1, false);

	bitstream.Read(Information.Id);

	bitstream.Read(Data.Model);

	bitstream.Read(Data.ForwardSpeed);

	bitstream.Read(Data.Heading);
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

	if (g_Core->GetNetworkManager()->GetInterface()->GetMyGUID() != Network.GUID) {
		if (!Game.Created)
			CreateVehicle();

		UpdateTargetPosition();
		UpdateTargetData();
		//UpdateTargetRotation();
	}
}

void CVehicleEntity::Interpolate()
{
	SetTargetPosition();
	//SetTargetRotation();
}

void CVehicleEntity::UpdateTargetPosition()
{
	if (Game.Created) {
		unsigned long CurrentTime = timeGetTime();
		unsigned int InterpolationTime = CurrentTime - Network.LastSyncReceived;

		// Get our position
		Vector3 Coordinates = ENTITY::GET_ENTITY_COORDS(Game.Vehicle, ENTITY::IS_ENTITY_DEAD(Game.Vehicle));
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

void CVehicleEntity::SetTargetPosition()
{
	if (InterpolationData.Position.FinishTime != 0 && Game.Created) {
		// Get our position
		Vector3 Coordinates = ENTITY::GET_ENTITY_COORDS(Game.Vehicle, ENTITY::IS_ENTITY_DEAD(Game.Vehicle));
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
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(Game.Vehicle, vecNewPosition.fX, vecNewPosition.fY, vecNewPosition.fZ, false, false, false);
		ENTITY::SET_ENTITY_VELOCITY(Game.Vehicle, Data.Velocity.fX, Data.Velocity.fY, Data.Velocity.fZ);
		ENTITY::SET_ENTITY_QUATERNION(Game.Vehicle, Data.Quaternion.fX, Data.Quaternion.fY, Data.Quaternion.fZ, Data.Quaternion.fW);
	}
}

void CVehicleEntity::UpdateTargetRotation()
{
	unsigned int interpolationtime = timeGetTime() - Network.LastSyncReceived;
	unsigned long ulTime = timeGetTime();

	// Get our position
	CVector3 vecLocalRotation;
	float unusedw;
	ENTITY::GET_ENTITY_QUATERNION(Game.Vehicle, &vecLocalRotation.fX, &vecLocalRotation.fY, &vecLocalRotation.fZ, &unusedw);

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

void CVehicleEntity::SetTargetRotation()
{
	if (InterpolationData.Rotation.FinishTime != 0) {
		CVector3 vecCurrentRotation;

		// Get our rotation
		float unusedw;
		ENTITY::GET_ENTITY_QUATERNION(Game.Vehicle, &vecCurrentRotation.fX, &vecCurrentRotation.fY, &vecCurrentRotation.fZ, &unusedw);

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
		ENTITY::SET_ENTITY_QUATERNION(Game.Vehicle, vecNewRotation.fX, vecNewRotation.fY, vecNewRotation.fZ, unusedw);
	}
}

void CVehicleEntity::UpdateTargetData()
{
}
