#include "stdafx.h"

namespace API
{
	const char *Vehicle::ThisNamespace = "API::Vehicle";

	const int Vehicle::Create(const std::wstring model, const CVector3 position, const float heading)
	{
		CVehicleEntity newVehicle;
		newVehicle.Create(model, position, heading);
		g_Vehicles.push_back(newVehicle);

		return newVehicle.GetId();
	}
	const int Vehicle::Create(const std::wstring model, const CVector3 position, const CVector3 rotation)
	{
		CVehicleEntity newVehicle;
		newVehicle.Create(model, position, rotation);
		g_Vehicles.push_back(newVehicle);

		return newVehicle.GetId();
	}
}
