#include "stdafx.h"

void CPlayerEntity::Create(std::string Name, RakNetGUID GUID, int entity) {
	CServerEntity newServerEntity;
	newServerEntity.Create(entity);
	newServerEntity.SetType(newServerEntity.Player);
	g_Entities.push_back(newServerEntity);

	Information.Name = Name;
	Information.Id = entity;
	Network.GUID = GUID;

	std::cout << "[CPlayerEntity] Added Player: " << Information.Name << std::endl;
}

void CPlayerEntity::CreatePed()
{
	if (STREAMING::IS_MODEL_IN_CDIMAGE(Data.Model.Model) && STREAMING::IS_MODEL_VALID(Data.Model.Model))
	{
		STREAMING::REQUEST_MODEL(Data.Model.Model);
		while (!STREAMING::HAS_MODEL_LOADED(Data.Model.Model)) WAIT(0);
		Game.Ped = PED::CREATE_PED(Data.Model.Type, Data.Model.Model, Data.Position.fX, Data.Position.fY, Data.Position.fZ, 0.0f, false, true);

		STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Data.Model.Model);

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

		Hash relationshipGroup;
		PED::ADD_RELATIONSHIP_GROUP("FIVEMPPLAYER", &relationshipGroup);
		PED::SET_PED_RELATIONSHIP_GROUP_HASH(Game.Ped, relationshipGroup);

		Game.Blip = UI::ADD_BLIP_FOR_ENTITY(Game.Ped);
		UI::SET_BLIP_AS_FRIENDLY(Game.Blip, true);

		Game.Created = true;
		std::cout << "[CPlayerEntity] Created Ped" << std::endl;
		return;
	}
	std::cout << "[CPlayerEntity] Tried to create" << Information.Id << ", but model does not exist!" << std::endl;
}

void CPlayerEntity::Destroy()
{
	std::cout << "[CPlayerEntity] Removing Player: " << Information.Id << std::endl;
	
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

	bitstream.Read(Data.Model.Model);
	bitstream.Read(Data.Model.Type);

	bitstream.Read(Data.Weapon.Weapon);
	bitstream.Read(Data.Weapon.Reload);

	bitstream.Read(Data.ForwardSpeed);

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
			CreatePed();

		UpdateTargetPosition();
		UpdateTargetAnimations();
		UpdateTargetData();
		//UpdateTargetRotation();
	}
	/*else
	{
		// Simple way to make the local player aware of its own server entity id.
		if (Information.Id != g_Core->GetLocalPlayer()->GetId())
			g_Core->GetLocalPlayer()->SetId(Information.Id);
	}*/
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

void CPlayerEntity::UpdateTargetAnimations()
{
	Animations& animation = Animations();
	if (IsTargetAnimal())
	{
		std::string dict;
		std::string name;

		if (Data.ForwardSpeed < 2.0f && Data.ForwardSpeed > 1.0f && Data.Model.MovementState != 1)
		{
			animation.GetAnimalAnimation(Data.Model.Model, 1, &dict, &name);

			if (!STREAMING::HAS_ANIM_DICT_LOADED((char*)dict.c_str()))
				STREAMING::REQUEST_ANIM_DICT((char*)dict.c_str());

			AI::TASK_PLAY_ANIM(Game.Ped, (char*)dict.c_str(), (char*)name.c_str(), 8.0f, 0.0f, -1, 1, 0.0f, false, false, false);
			Data.Model.MovementState = 1;
		}
		else if (Data.ForwardSpeed > 2.0f && Data.ForwardSpeed <= 5.2f && Data.Model.MovementState != 2)
		{
			animation.GetAnimalAnimation(Data.Model.Model, 2, &dict, &name);

			if (!STREAMING::HAS_ANIM_DICT_LOADED((char*)dict.c_str()))
				STREAMING::REQUEST_ANIM_DICT((char*)dict.c_str());

			AI::TASK_PLAY_ANIM(Game.Ped, (char*)dict.c_str(), (char*)name.c_str(), 8.0f, 0.0f, -1, 1, 0.0f, false, false, false);
			Data.Model.MovementState = 2;
		}
		else if (Data.ForwardSpeed > 5.2f && Data.Model.MovementState != 3)
		{
			animation.GetAnimalAnimation(Data.Model.Model, 3, &dict, &name);

			if (!STREAMING::HAS_ANIM_DICT_LOADED((char*)dict.c_str()))
				STREAMING::REQUEST_ANIM_DICT((char*)dict.c_str());

			AI::TASK_PLAY_ANIM(Game.Ped, (char*)dict.c_str(), (char*)name.c_str(), 8.0f, 0.0f, -1, 1, 0.0f, false, false, false);
			Data.Model.MovementState = 3;
		}
		else if (Data.ForwardSpeed < 1.0f && Data.Model.MovementState != 0)
		{
			animation.GetAnimalAnimation(Data.Model.Model, 0, &dict, &name);

			if (!STREAMING::HAS_ANIM_DICT_LOADED((char*)dict.c_str()))
				STREAMING::REQUEST_ANIM_DICT((char*)dict.c_str());

			AI::TASK_PLAY_ANIM(Game.Ped, (char*)dict.c_str(), (char*)name.c_str(), 8.0f, 0.0f, -1, 1, 0.0f, false, false, false);
			Data.Model.MovementState = 0;
		}
	}
	else
	{
		if (!STREAMING::HAS_ANIM_DICT_LOADED("move_m@generic"))
			STREAMING::REQUEST_ANIM_DICT("move_m@generic");

		if (Data.ForwardSpeed < 2.0f && Data.ForwardSpeed > 1.0f && Data.Model.MovementState != 1)
		{
			AI::TASK_PLAY_ANIM(Game.Ped, "move_m@generic", "walk", 8.0f, 0.0f, -1, 1, 0.0f, false, false, false);
			Data.Model.MovementState = 1;
		}
		else if (Data.ForwardSpeed > 2.0f && Data.ForwardSpeed <= 5.2f && Data.Model.MovementState != 2)
		{
			AI::TASK_PLAY_ANIM(Game.Ped, "move_m@generic", "run", 8.0f, 0.0f, -1, 1, 0.0f, false, false, false);
			Data.Model.MovementState = 2;
		}
		else if (Data.ForwardSpeed > 5.2f && Data.Model.MovementState != 3)
		{
			AI::TASK_PLAY_ANIM(Game.Ped, "move_m@generic", "sprint", 8.0f, 0.0f, -1, 1, 0.0f, false, false, false);
			Data.Model.MovementState = 3;
		}
		else if (Data.ForwardSpeed < 1.0f && Data.Model.MovementState != 0)
		{
			AI::TASK_PLAY_ANIM(Game.Ped, "move_m@generic", "idle", 8.0f, 0.0f, -1, 1, 0.0f, false, false, false);
			Data.Model.MovementState = 0;
		}
	}
}

void CPlayerEntity::UpdateTargetData()
{
	if (WEAPON::GET_SELECTED_PED_WEAPON(Game.Ped) != Data.Weapon.Weapon) {
		WEAPON::GIVE_WEAPON_TO_PED(Game.Ped, Data.Weapon.Weapon, 999, true, true);
	}

	unsigned long CurrentTime;
	if (Data.Weapon.Reload && CurrentTime >= Data.Weapon.LastReload + 2000)
	{
		WEAPON::MAKE_PED_RELOAD(Game.Ped);

		Data.Weapon.LastReload = CurrentTime;
		Data.Weapon.Reload = false;
	}

	if (PED::IS_PED_DEAD_OR_DYING(Game.Ped, 1) && ENTITY::GET_ENTITY_HEALTH(Game.Ped) > 0) {
		PED::RESURRECT_PED(Game.Ped);
		PED::CLEAR_PED_BLOOD_DAMAGE(Game.Ped);
		AI::CLEAR_PED_TASKS_IMMEDIATELY(Game.Ped);
	}
}

bool CPlayerEntity::IsTargetAnimal()
{
	switch (Data.Model.Model)
	{
	case -832573324:
	case 1462895032:
	case -1430839454:
	case 51016938:
	case 1126154828:
	case 1457690978:
	case -50684386:
	case 1682622302:
	case 402729631:
	case -664053099:
	case -1950698411:
	case 802685111:
	case 1794449327:
	case 1193010354:
	case 1318032802:
	case -1920284487:
	case -1323586730:
	case 111281960:
	case 1125994524:
	case 1832265812:
	case -1384627013:
	case -541762431:
	case -1011537562:
	case 882848737:
	case -1788665315:
	case -745300483:
	case 1015224100:
	case 113504370:
	case -1589092019:
		return true;
	default:
		return false;
	}
}