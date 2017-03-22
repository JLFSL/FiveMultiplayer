#include "stdafx.h"

void Vehicles::ClearAddress() {
	currAddress = nullptr;
}

BYTE *Vehicles::GetAddress(Vehicle handle) {
	if (currAddress == nullptr) {
		MemoryAccess mem;
		currAddress = reinterpret_cast<BYTE *>(mem.GetAddressOfEntity(handle));
	}
	return currAddress;
}

uint16_t Vehicles::GetCurrentGear(Vehicle handle) {
	auto address = GetAddress(handle);

	auto offset = (g_Config->GetLatestVersion() ? 0x7E0 : 0x7C2);
	
	return address == nullptr ? 0 : *reinterpret_cast<const uint16_t *>(address + offset);
}

void Vehicles::SetCurrentGear(Vehicle handle, uint16_t value) {
	auto address = GetAddress(handle);

	if (g_Config->GetLatestVersion())
	{
		*reinterpret_cast<uint32_t *>(address + 0x7E0) = value;
	}
	else
	{
		*reinterpret_cast<uint32_t *>(address + 0x7C0) = value;
	}
}

float Vehicles::GetCurrentRPM(Vehicle handle) {
	auto address = GetAddress(handle);

	auto offset = 0x814;

	return address == nullptr ? 0.0f : *reinterpret_cast<const float *>(address + offset);
}

void Vehicles::SetCurrentRPM(Vehicle handle, float value) {
	auto address = GetAddress(handle);

	auto offset = 0x814;

	*reinterpret_cast<float *>(address + offset) = value;
}

float Vehicles::GetClutch(Vehicle handle) {
	auto address = GetAddress(handle);

	auto offset = 0x820;

	return address == nullptr ? 0 : *reinterpret_cast<const float *>(address + offset);
}

void Vehicles::SetClutch(Vehicle handle, float value) {
	auto address = GetAddress(handle);

	auto offset = 0x820;

	*reinterpret_cast<float *>(address + offset) = value;
}

float Vehicles::GetTurbo(Vehicle handle) {
	auto address = GetAddress(handle);

	auto offset = 0x838;

	return address == nullptr ? 0 : *reinterpret_cast<const float *>(address + offset);
}

void Vehicles::SetTurbo(Vehicle handle, float value) {
	auto address = GetAddress(handle);

	auto offset = 0x838;

	*reinterpret_cast<float *>(address + offset) = value;
}

float Vehicles::GetAcceleration(Vehicle handle) {
	auto address = GetAddress(handle);

	auto offset = 0x824;

	return *reinterpret_cast<float *>(address + offset);
}

void Vehicles::SetAcceleration(Vehicle handle, float value) {
	auto address = GetAddress(handle);

	auto offset = 0x824;

	*reinterpret_cast<float *>(address + offset) = value;
}

float Vehicles::GetBrake(Vehicle handle) {
	auto address = GetAddress(handle);

	auto offset = 0x900;

	return *reinterpret_cast<float *>(address + offset);
}

void Vehicles::SetBrake(Vehicle handle, float value) {
	auto address = GetAddress(handle);

	auto offset = 0x900;

	*reinterpret_cast<float *>(address + offset) = value;
}

// Front wheel angle
float Vehicles::GetWheelSpeed(Vehicle handle) {
	auto address = GetAddress(handle);

	auto offset = 0x9F0;

	return *reinterpret_cast<float *>(address + offset);
}

void Vehicles::SetWheelSpeed(Vehicle handle, float value) {
	auto address = GetAddress(handle);

	auto offset = 0x9F0;

	*reinterpret_cast<float *>(address + offset) = value;
}

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

float Vehicles::GetForwardWheelAngle(Vehicle handle) {
	auto address = GetAddress(handle);

	auto offset = 0x8FC;

	return *reinterpret_cast<float *>(address + offset);
}

void Vehicles::SetForwardWheelAngle(Vehicle handle, float value) {
	auto address = GetAddress(handle);

	auto offset = 0x8FC;

	*reinterpret_cast<float *>(address + offset) = value;
}


/*uint16_t Vehicles::GetGearNext(Vehicle handle) {
auto address = GetAddress(handle);

auto offset = (gameVersion > 3 ? 0x7A0 : 0x790);
offset = (gameVersion > 25 ? 0x7C0 : offset);
offset = (gameVersion > 27 ? 0x7E0 : offset);

return address == nullptr ? 0 : *reinterpret_cast<const uint16_t *>(address + offset);
}

void Vehicles::SetGearNext(Vehicle handle, uint16_t value) {
auto address = GetAddress(handle);

auto offset = (gameVersion > 3 ? 0x7A2 : 0x792);
offset = (gameVersion > 25 ? 0x7C2 : offset);
offset = (gameVersion > 27 ? 0x7E2 : offset);

*reinterpret_cast<uint32_t *>(address + offset) = value;
}

uint32_t Vehicles::GetGears(Vehicle handle) {
auto address = GetAddress(handle);

auto offset = (gameVersion > 3 ? 0x7A0 : 0x790);
offset = (gameVersion > 25 ? 0x7C0 : offset);
offset = (gameVersion > 27 ? 0x7E0 : offset);

return address == nullptr ? 0 : *reinterpret_cast<const uint32_t *>(address + offset);
}

void Vehicles::SetGears(Vehicle handle, uint32_t value) {
auto address = GetAddress(handle);

auto offset = (gameVersion > 3 ? 0x7A0 : 0x790);
offset = (gameVersion > 25 ? 0x7C0 : offset);
offset = (gameVersion > 27 ? 0x7E0 : offset);

*reinterpret_cast<uint32_t *>(address + offset) = value;
}

uint32_t Vehicles::GetTopGear(Vehicle handle) {
auto address = GetAddress(handle);

auto offset = (gameVersion > 3 ? 0x7A6 : 0x796);
offset = (gameVersion > 25 ? 0x7C6 : offset);
offset = (gameVersion > 27 ? 0x7E6 : offset);

return address == nullptr ? 0 : *reinterpret_cast<const unsigned char *>(address + offset);
}

float Vehicles::GetFuelLevel(Vehicle handle) {
auto address = GetAddress(handle);

auto offset = (gameVersion > 3 ? 0x768 : 0x758);
offset = (gameVersion > 25 ? 0x788 : offset);
offset = (gameVersion > 27 ? 0x7A8 : offset);

return *reinterpret_cast<float *>(address + offset);
}

void Vehicles::SetFuelLevel(Vehicle handle, float value) {
auto address = GetAddress(handle);

auto offset = (gameVersion > 3 ? 0x768 : 0x758);
offset = (gameVersion > 25 ? 0x788 : offset);
offset = (gameVersion > 27 ? 0x7A8 : offset);

*reinterpret_cast<float *>(address + offset) = value;
}

uint64_t Vehicles::GetWheelsPtr(Vehicle handle) {
auto address = GetAddress(handle);

auto offset = (gameVersion > 3 ? 0xAA0 : 0xA80);
offset = (gameVersion > 23 ? 0xAB0 : offset);
if (gameVersion == 06 || gameVersion == 07) {
offset = 0xA90; // FiveM
}
offset = (gameVersion > 25 ? 0xAE0 : offset);
offset = (gameVersion > 27 ? 0xB10 : offset);

return *reinterpret_cast<uint64_t *>(address + offset);
}

void Vehicles::SetWheelsHealth(Vehicle handle, float health) {
auto wheelPtr = GetWheelsPtr(handle);  // pointer to wheel pointers

uint64_t wheels[6] = {};
for (auto i = 0; i < 6; i++) {
wheels[i] = *reinterpret_cast<uint64_t *>(wheelPtr + 0x008 * i); // iterate through wheels
if (wheels[i]) {
*reinterpret_cast<float *>(wheels[i] + (gameVersion > 3 ? 0x1E0 : 0x1D0)) = health;
}
}
}

// Don't use this on non-cars
std::vector<float> Vehicles::GetWheelsCompression(Vehicle handle) {
auto wheelPtr = GetWheelsPtr(handle);

uint64_t wheels[6] = {};
std::vector<float> compressions;

for (auto i = 0; i < 6; i++) {
wheels[i] = *reinterpret_cast<uint64_t *>(wheelPtr + 0x008 * i); // iterate through wheels
if (wheels[i]) {
compressions.push_back(*reinterpret_cast<float *>(wheels[i] + (gameVersion > 3 ? 0x160 : 0x150)));
}
}
return compressions;
}

// Steering input angle, steering lock independent
float Vehicles::GetSteeringInputAngle(Vehicle handle) {
auto address = GetAddress(handle);

auto offset = (gameVersion > 3 ? 0x8A4 : 0x894);
offset = (gameVersion > 25 ? 0x8C4 : offset);
offset = (gameVersion > 27 ? 0x8EC : offset);

return *reinterpret_cast<float *>(address + offset);
}

void Vehicles::SetSteeringInputAngle(Vehicle handle, float value) {
auto address = GetAddress(handle);

auto offset = (gameVersion > 3 ? 0x8A4 : 0x894);
offset = (gameVersion > 25 ? 0x8C4 : offset);
offset = (gameVersion > 27 ? 0x8EC : offset);

*reinterpret_cast<float *>(address + offset) = value;
}

float Vehicles::GetEngineTemp(Vehicle handle) {
	auto address = GetAddress(handle);

	auto offset = (gameVersion > 27 ? 0x9AC : -1);
	if (offset == -1)
		return 0;

	return *reinterpret_cast<float *>(address + offset);
}

float Vehicles::GetDirtLevel(Vehicle handle) {
	auto address = GetAddress(handle);


	auto offset = (gameVersion > 27 ? 0x938 : -1);
	if (offset == -1)
		return 0;

	return *reinterpret_cast<float *>(address + offset);
}

float Vehicles::GetDashSpeed(Vehicle handle) {
	auto address = GetAddress(handle);


	auto offset = (gameVersion > 27 ? 0x9F0 : -1);
	if (offset == -1)
		return 0;

	return *reinterpret_cast<float *>(address + offset);
}
*/