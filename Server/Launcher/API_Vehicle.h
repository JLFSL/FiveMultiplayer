#pragma once
extern "C" {
	namespace API
	{
		class Vehicle
		{
			static const char *ThisNamespace;

		public:
			DLL_PUBLIC static const int Create(const std::string model, const CVector3 position, const float heading);
			DLL_PUBLIC static const int Create(const std::string model, const CVector3 position, const CVector3 rotation);
		};
	}
}