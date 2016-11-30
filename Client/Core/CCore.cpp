#include "stdafx.h"

CCore::CCore()
{
	// Construct CNetworkManager
	g_NetworkManager = new CNetworkManager;
}


CCore::~CCore()
{
	SAFE_DELETE(g_NetworkManager);
}

bool CCore::Initialize()
{
	// Check if CServer is created
	if (!g_NetworkManager)
	{
		Logger::Msg("CNetworkManager is invalid");
		return false;
	}

	// Call OnLoad
	if (!g_NetworkManager->Start())
	{
		Logger::Msg("CNetworkManager could not be started");
		return false;
	}

	return true;
}

bool cloned = false;
Ped clonedped;

void CCore::OnGameTick()
{
	Player player = PLAYER::PLAYER_ID();
	Ped ped = PLAYER::GET_PLAYER_PED(player);

	if (!PLAYER::IS_PLAYER_PLAYING(player)) return;

	Vector3 coords = ENTITY::GET_ENTITY_COORDS(ped, ENTITY::IS_ENTITY_DEAD(ped));;
	Vector4 rotation;

	float heading;
	ENTITY::GET_ENTITY_HEADING(ped);

	ENTITY::GET_ENTITY_QUATERNION(ped, &rotation.x, &rotation.y, &rotation.z, &rotation.w);

	if (!cloned)
	{
		char *name = "a_f_y_tourist_02";
		int PedHash = GAMEPLAY::GET_HASH_KEY(name);
		if (STREAMING::IS_MODEL_IN_CDIMAGE(PedHash) && STREAMING::IS_MODEL_VALID(PedHash))
		{
			Logger::Msg("%s %x", name, PedHash);;
			STREAMING::REQUEST_MODEL(PedHash);
			while (!STREAMING::HAS_MODEL_LOADED(PedHash)) WAIT(0);
			clonedped = PED::CREATE_PED(26, PedHash, coords.x, coords.y, coords.z, heading, 1, true);
			STREAMING::SET_MODEL_AS_NO_LONGER_NEEDED(PedHash);

			cloned = !cloned;
		}
	}
	else
	{
		ENTITY::SET_ENTITY_COORDS(clonedped, coords.x + 2.0f, coords.y + 2.0f, coords.z, false, false, false, false);
		ENTITY::SET_ENTITY_QUATERNION(clonedped, rotation.x, rotation.y, rotation.z, rotation.w);
	}
}
