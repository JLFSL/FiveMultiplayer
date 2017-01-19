#pragma once
extern "C" {
	namespace API
	{
		namespace Vehicle
		{
			DLL_PUBLIC int CreateVehicle(std::string model, CVector3 position, float heading);
		}
	}
}