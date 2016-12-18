#include "stdafx.h"

CLocalPlayer::CLocalPlayer()
{
	Game.Player		= PLAYER::PLAYER_ID();
	Game.Ped		= PLAYER::GET_PLAYER_PED(Game.Player);
}

CLocalPlayer::~CLocalPlayer()
{
	Game.Player		= NULL;
	Game.Ped		= NULL;
}

void CLocalPlayer::Pulse()
{
	unsigned long ulCurrentTime = timeGetTime();
	if (ulCurrentTime >= Network.LastSyncSent + (1000.0f / 50))
	{
		//if (g_ConnectionState == CONSTATE_CONN)
		//	return;

		Vector3 Coordinates = ENTITY::GET_ENTITY_COORDS(Game.Ped, ENTITY::IS_ENTITY_DEAD(Game.Ped));
		Vector4 Quaternion; ENTITY::GET_ENTITY_QUATERNION(Game.Ped, &Quaternion.fX, &Quaternion.fY, &Quaternion.fZ, &Quaternion.fW);
		Vector3 Velocity = ENTITY::GET_ENTITY_VELOCITY(Game.Ped);

		Data.Position = { Coordinates.x, Coordinates.y, Coordinates.z };
		Data.Quaternion = { Quaternion.fX, Quaternion.fY, Quaternion.fZ, Quaternion.fW };
		Data.Velocity = { Velocity.x, Velocity.y, Velocity.z };

		BitStream bitstream;
		bitstream.Write((unsigned char)ID_PACKET_TEST);
		bitstream.Write(Information);
		bitstream.Write(Statistics);
		bitstream.Write(Data);
		g_Core->GetNetworkManager()->GetInterface()->Send(&bitstream, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 0, g_Core->GetNetworkManager()->GetSystemAddress(), false);

		Network.LastSyncSent = timeGetTime();
	}
}
