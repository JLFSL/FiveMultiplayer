#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		namespace Vehicle
		{
			/// <summary>
			/// Creates a vehicle of a desired model at the position defined
			/// </summary>
			/// <param name="model">The model of the vehicle you wish to create</param>
			/// <param name="position">The position you wish to create the vehicle at</param>
			/// <param name="heading">The direction you wish the vehicle to be facing</param>
			/// <returns name="entity">The vehicles server entity id</returns>
			DLL_PUBLIC_I int CreateVehicle(std::string model, CVector3 position, float heading);
		}
	}
#ifdef __cplusplus
}
#endif