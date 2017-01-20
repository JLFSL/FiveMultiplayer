#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		namespace World
		{
			/// <summary>
			/// Gets the World Time
			/// </summary>
			/// <param name="hour">The Hour (this is a pointer)</param>
			/// <param name="minute">The Minute (this is a pointer)</param>
			/// <param name="second">The Second (this is a pointer)</param>
			/// <returns></returns>
			DLL_PUBLIC_I void GetTime(int *hour, int *minute, int *second);
			/// <summary>
			/// Sets the World Time
			/// </summary>
			/// <param name="hour">The Hour you wish to set</param>
			/// <param name="minute">The Minute you wish to set</param>
			/// <param name="second">The Second you wish to set</param>
			/// <returns></returns>
			DLL_PUBLIC_I void SetTime(const int hour, const int minute, const int second);
			/// <summary>
			/// Gets the Weather
			/// </summary>
			/// <returns></returns>
			DLL_PUBLIC_I std::string GetWeather();
			/// <summary>
			/// Sets the Weather
			/// </summary>
			/// <param name="weather">The weather you wish to set</param>
			/// <returns></returns>
			DLL_PUBLIC_I void SetWeather(const std::string weather);
		}
	}
#ifdef __cplusplus
}
#endif