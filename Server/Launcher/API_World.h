#pragma once
extern "C" {
	namespace API
	{
		class World
		{
			static const char *ThisNamespace;

		public:
			DLL_PUBLIC static void GetTime(int *hour, int *minute, int *second);
			DLL_PUBLIC static void SetTime(const int hour, const int minute, const int second);

			DLL_PUBLIC static const std::wstring GetWeather();
			DLL_PUBLIC static void SetWeather(const std::wstring weather);
		};
	}
}