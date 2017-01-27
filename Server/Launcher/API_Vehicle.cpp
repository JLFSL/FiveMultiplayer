#include "stdafx.h"

namespace API
{
	namespace Vehicle
	{
		const char *ThisNamespace = "API::Vehicle";

		int CreateVehicle(std::string model, CVector3 position, float heading)
		{
			CVehicleEntity newVehicle;
			newVehicle.Create(model, position, heading);
			g_Vehicles.push_back(newVehicle);

			return newVehicle.GetId();
		}

		void RemoveVehicle(int entity)
		{
			if (!g_Vehicles.empty())
			{
				for (int i = 0; i < g_Vehicles.size(); i++)
				{
					if (g_Vehicles[i].GetId() == entity)
					{
						g_Vehicles[i].Destroy();
					}
				}
			}
		}
	}
}
