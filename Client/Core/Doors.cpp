#include "stdafx.h"

void Doors::Pulse()
{
	for (int i = 0; i < MAXDOORS; i++)
	{
		DoorsInfo doorinfo = GetDoorInfo(i);
		OBJECT::SET_STATE_OF_CLOSEST_DOOR_OF_TYPE(doorinfo.doorHash, doorinfo.coords.fX, doorinfo.coords.fY, doorinfo.coords.fZ, 0, 1.0f, 0);
		OBJECT::SET_STATE_OF_CLOSEST_DOOR_OF_TYPE(doorinfo.modelInfoHash, doorinfo.coords.fX, doorinfo.coords.fY, doorinfo.coords.fZ, 0, 1.0f, 0);
	}
}