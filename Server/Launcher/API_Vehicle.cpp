#include "stdafx.h"

namespace API
{
	namespace Vehicle
	{
		char *ThisNamespace = "API::Vehicle";

		int CreateVehicle(std::string model, CVector3 position, float heading)
		{
			CVehicleEntity newVehicle;
			newVehicle.Create(model, position, heading);
			g_Vehicles.push_back(newVehicle);

			return newVehicle.GetId();
		}
	}
}
