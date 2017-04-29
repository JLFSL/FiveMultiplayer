#include "stdafx.h"

CPlayerEntity::CPlayerEntity() {
	Game.Created = false; 
	Game.Ped = NULL; 
	Game.Blip = NULL;

	Information.Id = -1;
}

void CPlayerEntity::Create(std::string Name, RakNetGUID GUID, int entity) {
	Game.Ped = 0;
	Game.Blip = 0;

	Information.Name = Name;
	Information.Id = entity;
	Network.GUID = GUID;

	Data.Vehicle.VehicleID = -1;
	Data.Vehicle.Seat = -1;

	CServerEntity newServerEntity;
	newServerEntity.Create(entity, CServerEntity::Player);
	g_Entities.push_back(newServerEntity);

	if (CNetworkManager::GetInterface()->GetMyGUID() == Network.GUID)
	{
		// Simple way to make the local player aware of its own server entity id.
		if (Information.Id != CLocalPlayer::GetId())
			CLocalPlayer::SetId(Information.Id);
	}
	else
	{
		RequestData();
	}

	std::cout << "[CPlayerEntity] Added Player: " << Information.Name << std::endl;
}

bool CPlayerEntity::CreatePed()
{
	if (!Game.Created)
	{
		Data.Model.hModel = GAMEPLAY::GET_HASH_KEY((char*)Data.Model.Model.c_str());
		if (STREAMING::IS_MODEL_IN_CDIMAGE(Data.Model.hModel) && STREAMING::IS_MODEL_VALID(Data.Model.hModel))
		{
			STREAMING::REQUEST_MODEL(Data.Model.hModel);

			if (!STREAMING::HAS_MODEL_LOADED(Data.Model.hModel))
				return false;

			Game.Ped = PED::CREATE_PED(Data.Model.Type, Data.Model.hModel, Data.Position.x, Data.Position.y, Data.Position.z, 0.0f, false, true);

			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(Data.Model.hModel);

			ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(CLocalPlayer::GetPed(), Game.Ped, false);
			ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(Game.Ped, CLocalPlayer::GetPed(), false);

			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(Game.Ped, Data.Position.x, Data.Position.y, Data.Position.z, false, false, false);

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

			// Set Component Variations
			for (int i = 0; i < SizeOfArray(Data.ModelComponents); i++)
			{
				GamePed::SetPedComponentVariation(Game.Ped, i, Data.ModelComponents[i].drawableid, Data.ModelComponents[i].textureid, Data.ModelComponents[i].paletteid);
			}

			// Set Headblend
			GamePed::SetPedHeadBlend(Game.Ped, Data.ModelHeadBlend.shapeFirst, Data.ModelHeadBlend.shapeSecond, Data.ModelHeadBlend.shapeThird, Data.ModelHeadBlend.skinFirst, Data.ModelHeadBlend.skinSecond, Data.ModelHeadBlend.skinThird, Data.ModelHeadBlend.shapeMix, Data.ModelHeadBlend.skinMix, Data.ModelHeadBlend.thirdMix);

			// Set Head 
			for (int i = 0; i < SizeOfArray(Data.ModelHeadOverlay); i++)
			{
				GamePed::SetPedHeadOverlayColor(Game.Ped, i, Data.ModelHeadOverlay[i].index, Data.ModelHeadOverlay[i].colorType, Data.ModelHeadOverlay[i].colorID, Data.ModelHeadOverlay[i].secondColorID, Data.ModelHeadOverlay[i].opacity);
			}

			// Set Ped Props
			for (int i = 0; i < SizeOfArray(Data.ModelProp); i++)
			{
				GamePed::SetPedProp(Game.Ped, i, Data.ModelProp[i].drawableid, Data.ModelProp[i].textureid);
			}

			// Set Face Features
			for (int i = 0; i < SizeOfArray(Data.ModelFaceFeature); i++)
			{
				GamePed::SetPedFaceFeature(Game.Ped, i, Data.ModelFaceFeature[i].scale);
			}

			Game.Created = true;

			std::cout << "[CPlayerEntity] Created Ped" << std::endl;
			return true;
		}
		std::cout << "[CPlayerEntity] Tried to create " << Information.Id << ", but model does not exist!" << std::endl;
		return false;
	}
	std::cout << "[CPlayerEntity] Ped" << Information.Id << " already created." << std::endl;
	return false;
}

// Gets the data thats only needed once thats not synced constantly
void CPlayerEntity::RequestData()
{
	RakNet::BitStream sData;
	sData.Write(Information.Id);
	CNetworkManager::GetRPC().Signal("RequestEntityData", &sData, HIGH_PRIORITY, RELIABLE_ORDERED, 0, CNetworkManager::GetSystemAddress(), false, false);
}

void CPlayerEntity::Destroy()
{
	std::cout << "[CPlayerEntity] Removing Player: " << Information.Id << std::endl;

	AI::TASK_STAND_STILL(Game.Ped, 1);
	
	if(ENTITY::DOES_ENTITY_EXIST(Game.Ped))
		ENTITY::DELETE_ENTITY(&Game.Ped);

	Game.Created = false;

	if(Game.Blip)
		UI::REMOVE_BLIP(&Game.Blip);

	Game = {};
	Information = {};
	Statistics = {};
	Data = {};
	Network = {};
	InterpolationData = {};

	Information.Id = -1;

	Data.Vehicle.VehicleID = -1;
	Data.Vehicle.Seat = -1;
}

void CPlayerEntity::Delete()
{
	if (ENTITY::DOES_ENTITY_EXIST(Game.Ped))
		ENTITY::DELETE_ENTITY(&Game.Ped);

	if (Game.Blip)
		UI::REMOVE_BLIP(&Game.Blip);

	Game.Ped = 0;
	Game.Blip = 0;

	Game.Created = false;
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

	RakString name;
	bitstream.Read(name);
	Information.Name = name.C_String();

	bitstream.Read(Statistics.Score);

	RakWString model;
	bitstream.Read(model);
	Data.Model.Model = CString::utf16ToUtf8(model.C_String());

	bitstream.Read(Data.Model.Type);

	bitstream.Read(Data.Weapon.Weapon);
	bitstream.Read(Data.Weapon.Reload);

	bitstream.Read(Data.ForwardSpeed);

	bitstream.Read(Data.Position.x);
	bitstream.Read(Data.Position.y);
	bitstream.Read(Data.Position.z);

	bitstream.Read(Data.Velocity.x);
	bitstream.Read(Data.Velocity.y);
	bitstream.Read(Data.Velocity.z);

	bitstream.Read(Data.Rotation.x);
	bitstream.Read(Data.Rotation.y);
	bitstream.Read(Data.Rotation.z);

	bitstream.Read(Data.Vehicle.VehicleID);
	bitstream.Read(Data.Vehicle.Seat);

	bitstream.Read(Data.Task);

	if (CNetworkManager::GetInterface()->GetMyGUID() != Network.GUID) {
		if (Data.Model.hModel != GAMEPLAY::GET_HASH_KEY((char*)Data.Model.Model.c_str()) && Game.Created)
			UpdatePlayerModel();

		UpdateTargetPosition();
		UpdateTargetRotation();
		UpdateTargetAnimations();
		UpdateTargetData();

		Network.LastSyncReceived = timeGetTime();
	}
}

void CPlayerEntity::Interpolate()
{
	SetTargetPosition();
	SetTargetRotation();
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
		CVector3 TargetPosition = { Data.Position.x, Data.Position.y, Data.Position.z };
		InterpolationData.Position.Target = TargetPosition;

		// Calculate the relative error
		InterpolationData.Position.Error = TargetPosition - CurrentPosition;

		// Get the interpolation interval
		InterpolationData.Position.StartTime = CurrentTime;
		InterpolationData.Position.FinishTime = (CurrentTime + InterpolationTime);

		// Initialize the interpolation
		InterpolationData.Position.LastAlpha = 0.0f;
	}
}

void CPlayerEntity::SetTargetPosition()
{
	if (InterpolationData.Position.FinishTime != 0 && Game.Created && Data.Vehicle.VehicleID == -1) {
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
		if (CVector3::Distance(vecCurrentPosition, InterpolationData.Position.Target) > 150.0f)
		{
			// Abort all interpolation
			InterpolationData.Position.FinishTime = 0;
			vecNewPosition = InterpolationData.Position.Target;
		}

		// Set our new position
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(Game.Ped, vecNewPosition.x, vecNewPosition.y, vecNewPosition.z, false, false, false);
		ENTITY::SET_ENTITY_VELOCITY(Game.Ped, Data.Velocity.x, Data.Velocity.y, Data.Velocity.z);
	}
}

void CPlayerEntity::UpdateTargetRotation()
{
	if (Game.Created) {
		unsigned long CurrentTime = timeGetTime();
		unsigned int interpolationtime = CurrentTime - Network.LastSyncReceived;

		// Get our rotation
		Vector3 CurrentRotationVec = ENTITY::GET_ENTITY_ROTATION(Game.Ped, 2);
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

void CPlayerEntity::SetTargetRotation()
{
	if (InterpolationData.Rotation.FinishTime != 0 && Game.Created && Data.Vehicle.VehicleID == -1) {

		// Get our rotation
		Vector3 CurrentRotationVec = ENTITY::GET_ENTITY_ROTATION(Game.Ped, 2);
		CVector3 CurrentRotation(CurrentRotationVec.x, CurrentRotationVec.y, CurrentRotationVec.z);

		if (InterpolationData.Rotation.Target.z > 178.0f || InterpolationData.Rotation.Target.z < -178.0f)
		{
			ENTITY::SET_ENTITY_ROTATION(Game.Ped, Data.Rotation.x, Data.Rotation.y, Data.Rotation.z, 2, true);
			InterpolationData.Rotation.FinishTime = 0;
		}
		else
		{
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
			ENTITY::SET_ENTITY_ROTATION(Game.Ped, vecNewRotation.x, vecNewRotation.y, vecNewRotation.z, 2, true);
		}
	}
}

void CPlayerEntity::UpdateTargetAnimations()
{
	if (Game.Created && Data.Vehicle.VehicleID == -1)
	{
		if (IsTargetAnimal())
		{
			std::string dict;
			std::string name;

			if (Data.ForwardSpeed < 2.0f && Data.ForwardSpeed > 1.0f && Data.Model.MovementState != 1)
			{
				Animations::GetAnimalAnimation(Data.Model.hModel, 1, &dict, &name);

				if (!STREAMING::HAS_ANIM_DICT_LOADED((char*)dict.c_str()))
					STREAMING::REQUEST_ANIM_DICT((char*)dict.c_str());

				AI::TASK_PLAY_ANIM(Game.Ped, (char*)dict.c_str(), (char*)name.c_str(), 8.0f, 0.0f, -1, 1, 0.0f, false, false, false);
				//PED::FORCE_PED_MOTION_STATE(Game.Ped, GAMEPLAY::GET_HASH_KEY("motionstate_walk"), false, false, false);
				Data.Model.MovementState = 1;
			}
			else if (Data.ForwardSpeed > 2.0f && Data.ForwardSpeed <= 5.2f && Data.Model.MovementState != 2)
			{
				Animations::GetAnimalAnimation(Data.Model.hModel, 2, &dict, &name);

				if (!STREAMING::HAS_ANIM_DICT_LOADED((char*)dict.c_str()))
					STREAMING::REQUEST_ANIM_DICT((char*)dict.c_str());

				AI::TASK_PLAY_ANIM(Game.Ped, (char*)dict.c_str(), (char*)name.c_str(), 8.0f, 0.0f, -1, 1, 0.0f, false, false, false);
				//PED::FORCE_PED_MOTION_STATE(Game.Ped, GAMEPLAY::GET_HASH_KEY("motionstate_run"), false, false, false);
				Data.Model.MovementState = 2;
			}
			else if (Data.ForwardSpeed > 5.2f && Data.Model.MovementState != 3)
			{
				Animations::GetAnimalAnimation(Data.Model.hModel, 3, &dict, &name);

				if (!STREAMING::HAS_ANIM_DICT_LOADED((char*)dict.c_str()))
					STREAMING::REQUEST_ANIM_DICT((char*)dict.c_str());

				AI::TASK_PLAY_ANIM(Game.Ped, (char*)dict.c_str(), (char*)name.c_str(), 8.0f, 0.0f, -1, 1, 0.0f, false, false, false);
				//PED::FORCE_PED_MOTION_STATE(Game.Ped, -1115154469, false, false, false);
				Data.Model.MovementState = 3;
			}
			else if (Data.ForwardSpeed < 1.0f && Data.Model.MovementState != 0)
			{
				Animations::GetAnimalAnimation(Data.Model.hModel, 0, &dict, &name);

				if (!STREAMING::HAS_ANIM_DICT_LOADED((char*)dict.c_str()))
					STREAMING::REQUEST_ANIM_DICT((char*)dict.c_str());

				AI::TASK_PLAY_ANIM(Game.Ped, (char*)dict.c_str(), (char*)name.c_str(), 8.0f, 0.0f, -1, 1, 0.0f, false, false, false);
				//PED::FORCE_PED_MOTION_STATE(Game.Ped, GAMEPLAY::GET_HASH_KEY("motionstate_idle"), false, false, false);
				Data.Model.MovementState = 0;
			}
		}
		else
		{
			if (!STREAMING::HAS_ANIM_DICT_LOADED("move_m@generic"))
				STREAMING::REQUEST_ANIM_DICT("move_m@generic");

			if (Data.ForwardSpeed < 2.0f && Data.ForwardSpeed > 1.0f && Data.Model.MovementState != 1)
			{
				PED::FORCE_PED_MOTION_STATE(Game.Ped, GAMEPLAY::GET_HASH_KEY("motionstate_walk"), false, false, false);
				AI::TASK_PLAY_ANIM(Game.Ped, "move_m@generic", "walk", 8.0f, 0.0f, -1, 1, 0.0f, false, false, false);
				Data.Model.MovementState = 1;
			}
			else if (Data.ForwardSpeed > 2.0f && Data.ForwardSpeed <= 5.2f && Data.Model.MovementState != 2)
			{
				PED::FORCE_PED_MOTION_STATE(Game.Ped, GAMEPLAY::GET_HASH_KEY("motionstate_run"), false, false, false);
				AI::TASK_PLAY_ANIM(Game.Ped, "move_m@generic", "run", 8.0f, 0.0f, -1, 1, 0.0f, false, false, false);
				Data.Model.MovementState = 2;
			}
			else if (Data.ForwardSpeed > 5.2f && Data.Model.MovementState != 3)
			{
				PED::FORCE_PED_MOTION_STATE(Game.Ped, -1115154469, false, false, false);
				AI::TASK_PLAY_ANIM(Game.Ped, "move_m@generic", "sprint", 8.0f, 0.0f, -1, 1, 0.0f, false, false, false);
				Data.Model.MovementState = 3;
			}
			else if (Data.ForwardSpeed < 1.0f && Data.Model.MovementState != 0)
			{
				PED::FORCE_PED_MOTION_STATE(Game.Ped, GAMEPLAY::GET_HASH_KEY("motionstate_idle"), false, false, false);
				AI::TASK_PLAY_ANIM(Game.Ped, "move_m@generic", "idle", 8.0f, 0.0f, -1, 1, 0.0f, false, false, false);
				Data.Model.MovementState = 0;
			}
		}
	}
}

void CPlayerEntity::UpdateTargetData()
{
	if (Game.Created)
	{
		if (WEAPON::GET_SELECTED_PED_WEAPON(Game.Ped) != Data.Weapon.Weapon)
		{
			WEAPON::REMOVE_ALL_PED_WEAPONS(Game.Ped, true);
			WEAPON::GIVE_WEAPON_TO_PED(Game.Ped, Data.Weapon.Weapon, 999, true, true);
		}

		unsigned long CurrentTime = timeGetTime();
		if (Data.Weapon.Reload && CurrentTime >= Data.Weapon.LastReload + 2000)
		{
			WEAPON::MAKE_PED_RELOAD(Game.Ped);

			Data.Weapon.LastReload = CurrentTime;
			Data.Weapon.Reload = false;
		}

		if (PED::IS_PED_DEAD_OR_DYING(Game.Ped, TRUE) && ENTITY::GET_ENTITY_HEALTH(Game.Ped) > 0)
		{
			PED::RESURRECT_PED(Game.Ped);
			PED::CLEAR_PED_BLOOD_DAMAGE(Game.Ped);
			AI::CLEAR_PED_TASKS_IMMEDIATELY(Game.Ped);
		}

		if (Data.Vehicle.VehicleID > -1 && !GamePed::GetVehicle(Game.Ped))
		{
			AI::CLEAR_PED_TASKS_IMMEDIATELY(Game.Ped);
			for (int v = 0; v < g_Vehicles.size(); v++)
			{
				if (g_Vehicles[v].GetId() == Data.Vehicle.VehicleID)
				{
					PED::SET_PED_INTO_VEHICLE(Game.Ped, g_Vehicles[v].GetEntity(), Data.Vehicle.Seat - 1);
					break;
				}
			}
		}
		else if (GamePed::GetVehicle(Game.Ped) && Data.Vehicle.VehicleID == -1)
		{
			AI::TASK_LEAVE_VEHICLE(Game.Ped, GamePed::GetVehicle(Game.Ped), 16);
		}


		if (Data.Task == 290) { //GunAim
			AI::CLEAR_PED_TASKS(Game.Ped);
			AI::TASK_AIM_GUN_AT_COORD(Game.Ped, 0, 0, 0, 5000, 1, 0);
		}

		if (!AI::GET_IS_TASK_ACTIVE(Game.Ped, Data.Task)) {
			if (Data.Task == 47) {
				AI::TASK_CLIMB_LADDER(Game.Ped, true);
			}
			else if (Data.Task == 51) {
				AI::SET_PED_PATH_CAN_DROP_FROM_HEIGHT(Game.Ped, true);
			}
			else if (Data.Task == 128) {
				//melee aim
			}
			else if (Data.Task == 130) {
				//melee swing
			}
			else if (Data.Task == 161) { //Start Getting In Vehicle
				int index = GamePed::GetVehicleID(Game.Ped);
				if (index != -1) {
					if (ENTITY::DOES_ENTITY_EXIST(GamePed::GetVehicle(Game.Ped))) {
						AI::TASK_OPEN_VEHICLE_DOOR(Game.Ped, GamePed::GetVehicle(Game.Ped), 1000, Data.Vehicle.Seat - 1, 2.0f);
					}
				}
			}
			else if (Data.Task == 298) { //ReloadWeapon
				WEAPON::MAKE_PED_RELOAD(Game.Ped);
				AI::TASK_RELOAD_WEAPON(Game.Ped, true);
			}
			else if (Data.Task == 300) { //GetInCover
				if (!PED::IS_PED_IN_COVER(Game.Ped, 0)) {
					//AI::TASK_SEEK_COVER_TO_COORDS(playerData[i].pedPed, playerData[i].x, playerData[i].y, playerData[i].z, playerData[i].x, playerData[i].y, playerData[i].z, 0, 0);
					AI::TASK_PUT_PED_DIRECTLY_INTO_COVER(Game.Ped, Data.Position.x, Data.Position.y, Data.Position.z, 2500, 0, 0, 0, 0, 0, 0);
				}
			}
			else if (Data.Task == 301) { //ExitCover
				AI::TASK_EXIT_COVER(Game.Ped, 1000, 0, 0, 0);
			}
			else if (Data.Task == 309) { //InCover
				if (!PED::IS_PED_IN_COVER(Game.Ped, 0)) {
					AI::TASK_PUT_PED_DIRECTLY_INTO_COVER(Game.Ped, Data.Position.x, Data.Position.y, Data.Position.z, 1000, 0, 0, 0, 0, 0, 0);
				}
				else {
					AI::TASK_STAY_IN_COVER(Game.Ped);
				}
			}
			else if (Data.Task == 407) { //Ragdoll
				//PED::SET_PED_TO_RAGDOLL(playerData[i].pedPed, 10000, 10000 * 1000, 0, 0, 0, 0);
			}
			else if (Data.Task == 420) { //Climb/Vault
				AI::TASK_CLIMB(Game.Ped, true);
			}
			else if (Data.Task == 421 && !Data.isJumping) { //jump
				if (!PED::IS_PED_JUMPING(Game.Ped)) {
					AI::TASK_JUMP(Game.Ped, false);
					Data.isJumping = true;
				}
			}
			else if (Data.Task == 422) { //Fall

			}
			else {
				Data.isJumping = false;
			}
		}
	}
}

bool CPlayerEntity::IsTargetAnimal()
{
	switch (Data.Model.hModel)
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

void CPlayerEntity::UpdatePlayerModel()
{
	if (Game.Created)
	{
		Data.Model.hModel = GAMEPLAY::GET_HASH_KEY((char*)Data.Model.Model.c_str());

		if (STREAMING::IS_MODEL_IN_CDIMAGE(Data.Model.hModel) && STREAMING::IS_MODEL_VALID(Data.Model.hModel))
		{
			ENTITY::DELETE_ENTITY(&Game.Ped);

			STREAMING::REQUEST_MODEL(Data.Model.hModel);
			while (!STREAMING::HAS_MODEL_LOADED(Data.Model.hModel))
				WAIT(0);

			Game.Ped = PED::CREATE_PED(26, Data.Model.hModel, Data.Position.x, Data.Position.y, Data.Position.z, 0.0f, false, true);

			ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(CLocalPlayer::GetPed(), Game.Ped, false);
			ENTITY::SET_ENTITY_NO_COLLISION_ENTITY(Game.Ped, CLocalPlayer::GetPed(), false);

			ENTITY::SET_ENTITY_COORDS_NO_OFFSET(Game.Ped, Data.Position.x, Data.Position.y, Data.Position.z, false, false, false);

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

			if (UI::DOES_BLIP_EXIST(Game.Blip))
				UI::REMOVE_BLIP(&Game.Blip);

			Game.Blip = UI::ADD_BLIP_FOR_ENTITY(Game.Ped);
			UI::SET_BLIP_AS_FRIENDLY(Game.Blip, true);

			std::cout << "[CPlayerEntity] Updated player " << Information.Id << " model" << std::endl;
			return;
		}
		std::cout << "[CPlayerEntity] Tried to update player " << Information.Id << " model to " << Data.Model.Model << ", but model does not exist!" << std::endl;
	}
}

void CPlayerEntity::SetModelComponent(const int componentid, const int drawableid, const int textureid, const int paletteid)
{
	Data.ModelComponents[componentid].drawableid = drawableid;
	Data.ModelComponents[componentid].textureid = textureid;
	Data.ModelComponents[componentid].paletteid = paletteid;

	if(Game.Created)
		GamePed::SetPedComponentVariation(Game.Ped, componentid, drawableid, textureid, paletteid);
}

void CPlayerEntity::SetModelHeadBlend(const int shapeFirst, const int shapeSecond, const int shapeThird, const int skinFirst, const int skinSecond, const int skinThird, const float shapeMix, const float skinMix, const float thirdMix)
{
	Data.ModelHeadBlend.shapeFirst = shapeFirst;
	Data.ModelHeadBlend.shapeSecond = shapeSecond;
	Data.ModelHeadBlend.shapeThird = shapeThird;
	Data.ModelHeadBlend.skinFirst = skinFirst;
	Data.ModelHeadBlend.skinSecond = skinSecond;
	Data.ModelHeadBlend.skinThird = skinThird;
	Data.ModelHeadBlend.shapeMix = shapeMix;
	Data.ModelHeadBlend.skinMix = skinMix;
	Data.ModelHeadBlend.thirdMix = thirdMix;

	if(Game.Created)
		GamePed::SetPedHeadBlend(Game.Ped, shapeFirst, shapeSecond, shapeThird, skinFirst, skinSecond, skinThird, shapeMix, skinMix, thirdMix);
}

void CPlayerEntity::SetModelHeadOverlay(const int overlayid, const int index, const int colorType, const int colorid, const int secondColorid, const float opacity)
{
	Data.ModelHeadOverlay[overlayid].index = index;
	Data.ModelHeadOverlay[overlayid].colorType = colorType;
	Data.ModelHeadOverlay[overlayid].colorID = colorid;
	Data.ModelHeadOverlay[overlayid].secondColorID = secondColorid;
	Data.ModelHeadOverlay[overlayid].opacity = opacity;

	if(Game.Created)
		GamePed::SetPedHeadOverlayColor(Game.Ped, overlayid, index, colorType, colorid, secondColorid, opacity);
}

void CPlayerEntity::SetModelProp(const int componentid, const int drawableid, const int textureid)
{
	Data.ModelProp[componentid].drawableid = drawableid;
	Data.ModelProp[componentid].textureid = textureid;

	if(Game.Created)
		GamePed::SetPedProp(Game.Ped, componentid, drawableid, textureid);
}

void CPlayerEntity::SetModelFaceFeature(const int index, const float scale)
{
	Data.ModelFaceFeature[index].scale = scale;

	if(Game.Created)
		GamePed::SetPedFaceFeature(Game.Created, index, scale);
}