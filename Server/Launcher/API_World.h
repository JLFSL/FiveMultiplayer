#ifndef __APIWORLD_H__
#define __APIWORLD_H__
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

			DLL_PUBLIC static void LoadIPL(const std::wstring ipl);
			DLL_PUBLIC static void LoadIPL(const int entity,  const std::wstring ipl);

			DLL_PUBLIC static void UnloadIPL(const std::wstring ipl);
			DLL_PUBLIC static void UnloadIPL(const int entity, const std::wstring ipl);
		};
	}
}
#endif