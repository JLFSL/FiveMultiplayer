#pragma once
extern "C" {
	namespace API
	{
		namespace World
		{
			DLL_PUBLIC void GetTime(int *hour, int *minute, int *second);
			DLL_PUBLIC void SetTime(int hour, int minute, int second);

			DLL_PUBLIC std::string GetWeather();
			DLL_PUBLIC void SetWeather(std::string weather);
		}
	}
}