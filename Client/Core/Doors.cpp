#include "stdafx.h"

void Doors::Pulse()
{
	CLocalPlayer& player = CLocalPlayer::CLocalPlayer();
	for (int i = 0; i < MAXDOORS; i++)
	{
		DoorsInfo doorinfo = GetDoorInfo(i);
		if (CVector3::Distance(player.GetPosition(), doorinfo.coords) < 400.0f)
		{
			OBJECT::SET_STATE_OF_CLOSEST_DOOR_OF_TYPE(doorinfo.doorHash, doorinfo.coords.x, doorinfo.coords.y, doorinfo.coords.z, 0, 1.0f, 0);
			OBJECT::SET_STATE_OF_CLOSEST_DOOR_OF_TYPE(doorinfo.modelInfoHash, doorinfo.coords.x, doorinfo.coords.y, doorinfo.coords.z, 0, 1.0f, 0);
		}
	}
}