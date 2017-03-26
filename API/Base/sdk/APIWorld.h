#pragma once

#ifdef __cplusplus
extern "C" {
#endif
	namespace API
	{
		class World
		{
		public:
			/// <summary>
			/// Gets the World Time
			/// </summary>
			/// <param name="hour">The Hour (this is a pointer)</param>
			/// <param name="minute">The Minute (this is a pointer)</param>
			/// <param name="second">The Second (this is a pointer)</param>
			/// <returns></returns>
			DLL_PUBLIC_I static void GetTime(int *hour, int *minute, int *second);
			/// <summary>
			/// Sets the World Time
			/// </summary>
			/// <param name="hour">The Hour you wish to set</param>
			/// <param name="minute">The Minute you wish to set</param>
			/// <param name="second">The Second you wish to set</param>
			/// <returns></returns>
			DLL_PUBLIC_I static void SetTime(const int hour, const int minute, const int second);
			/// <summary>
			/// Gets the Weather
			/// </summary>
			/// <returns></returns>
			DLL_PUBLIC_I static const std::wstring GetWeather();
			/// <summary>
			/// Sets the Weather
			/// </summary>
			/// <param name="weather">The weather you wish to set</param>
			/// <returns></returns>
			DLL_PUBLIC_I static void SetWeather(const std::wstring weather);
		};
	}
#ifdef __cplusplus
}
#endif