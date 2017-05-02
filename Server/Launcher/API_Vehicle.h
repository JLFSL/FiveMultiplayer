#ifndef __APIVEHICLE_H__
#define __APIVEHICLE_H__
extern "C" {
	namespace API
	{
		class Vehicle
		{
			static const char *ThisNamespace;

		public:
			DLL_PUBLIC static const int Create(const std::wstring model, const CVector3 position, const float heading);
			DLL_PUBLIC static const int Create(const std::wstring model, const CVector3 position, const CVector3 rotation);

			DLL_PUBLIC static void SetColor(const int entity, const int layer, const int painttype, const int color);
			DLL_PUBLIC static void SetColor(const int entity, const int layer, const Color color);

			DLL_PUBLIC static void SetNumberPlate(const int entity, std::wstring plate);
			DLL_PUBLIC static const std::wstring GetNumberPlate(const int entity);

			DLL_PUBLIC static const int GetMod(const int entity, const int modType);
			DLL_PUBLIC static void SetMod(const int entity, const int modType, const int modIndex);

			DLL_PUBLIC static const bool GetEngineState(const int entity);
			DLL_PUBLIC static void SetEngineState(const int entity, const bool state);

			DLL_PUBLIC static const int GetDoorsLockState(const int entity);
			DLL_PUBLIC static void SetDoorsLockState(const int entity, const int state);
			DLL_PUBLIC static void SetDoorsLockState(const int entity, const int state, const int player);

			DLL_PUBLIC static const std::wstring GetModel(const int entity);

			//DLL_PUBLIC static void SetLivery(const int entity, const int livery);

			DLL_PUBLIC static const int GetNumberPlateStyle(const int entity);
			DLL_PUBLIC static void SetNumberPlateStyle(const int entity, const int style);

			DLL_PUBLIC static const bool GetExtra(const int entity, const int extra);
			DLL_PUBLIC static void SetExtra(const int entity, const int extra, const bool toggle);

			DLL_PUBLIC static const float GetEngineHealth(const int entity);
			DLL_PUBLIC static void SetEngineHealth(const int entity, const float health);

			DLL_PUBLIC static const float GetFuelTankHealth(const int entity);
			DLL_PUBLIC static void SetFuelTankHealth(const int entity, const float health);

			DLL_PUBLIC static void FixDeformation(const int entity);

			DLL_PUBLIC static const int GetOccupant(const int entity, const int seat);
			DLL_PUBLIC static const std::vector<int> GetOccupants(const int entity);

			DLL_PUBLIC static const bool GetTaxiLightState(const int entity);
			DLL_PUBLIC static void SetTaxiLightState(const int entity, const bool state);
		};
	}
}
#endif