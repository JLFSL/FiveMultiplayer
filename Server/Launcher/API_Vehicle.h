#pragma once
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
		};
	}
}