#pragma once

class Vehicles {
public:
	void ClearAddress();
	BYTE *GetAddress(Vehicle handle);

	uint16_t GetCurrentGear(Vehicle handle);
	void SetCurrentGear(Vehicle handle, uint16_t value);
	float GetCurrentRPM(Vehicle handle);
	void SetCurrentRPM(Vehicle handle, float value);

	float GetClutch(Vehicle handle);
	void SetClutch(Vehicle handle, float value);
	float GetTurbo(Vehicle handle);
	void SetTurbo(Vehicle handle, float value);
	float GetAcceleration(Vehicle handle);
	void SetAcceleration(Vehicle handle, float value);
	float GetBrake(Vehicle handle);
	void SetBrake(Vehicle handle, float value);

	float GetWheelSpeed(Vehicle handle);
	void SetWheelSpeed(Vehicle handle, float value);
	float GetSteeringAngle(Vehicle handle);
	void SetSteeringAngle(Vehicle handle, float value);
	float GetForwardWheelAngle(Vehicle handle);
	void SetForwardWheelAngle(Vehicle handle, float value);


private:
	BYTE* currAddress = nullptr;
};