#include "stdafx.h"

// Wheel angle, steering lock dependent
float Vehicles::GetSteeringAngle(Vehicle handle) {
	auto address = GetAddress(handle);
	auto offset = 0x8F4;

	return *reinterpret_cast<float *>(address + offset);
}

void Vehicles::SetSteeringAngle(Vehicle handle, float value) {
	auto address = GetAddress(handle);
	auto offset = 0x8F4;

	*reinterpret_cast<float *>(address + offset) = value;
}

BYTE * Vehicles::GetAddress(Vehicle handle)
{
	if (currAddress == nullptr) {
		MemoryAccess mem;
		currAddress = reinterpret_cast<BYTE *>(mem.GetAddressOfEntity(handle));
	}
	return currAddress;
}
