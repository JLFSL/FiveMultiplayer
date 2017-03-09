#include "stdafx.h"

namespace API
{
	const char *Vehicle::ThisNamespace = "API::Vehicle";

	const int Vehicle::Create(const std::string model, const CVector3 position, const float heading)
	{
		CVehicleEntity newVehicle;
		newVehicle.Create(model, position, heading);
		g_Vehicles.push_back(newVehicle);

		return newVehicle.GetId();
	}
}
