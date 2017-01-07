#pragma once
extern "C" {
	namespace API
	{
		namespace Vehicle
		{
			DLL_PUBLIC int CreateVehicle(string model, CVector3 position, float heading);
		}
	}
}