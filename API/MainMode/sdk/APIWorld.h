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
			DLL_PUBLIC_I static void SetTime(const int hour, const int minute, const int second);
			/// <summary>
			/// Gets the Weather
			/// </summary>
			/// <returns>The current weather on the server</returns>
			DLL_PUBLIC_I static const std::wstring GetWeather();
			/// <summary>
			/// Sets the Weather
			/// </summary>
			/// <param name="weather">The weather you wish to set</param>
			DLL_PUBLIC_I static void SetWeather(const std::wstring weather);
			/// <summary>
			/// Loads an IPL for all players and future newly connected players
			/// </summary>
			/// <param name="ipl">The name of the IPL</param>
			DLL_PUBLIC_I static void LoadIPL(const std::wstring ipl);
			/// <summary>
			/// Loads an IPL for a specific player
			/// </summary>
			/// <param name="ipl">The name of the IPL</param>
			/// <param name="ipl">The entity of the player you wish to load the ipl for</param>
			DLL_PUBLIC_I static void LoadIPL(const int entity, const std::wstring v);
			/// <summary>
			/// Unloads an IPL for all players and future newly connected players
			/// </summary>
			/// <param name="ipl">The name of the IPL</param>
			DLL_PUBLIC_I static void UnloadIPL(const std::wstring ipl);
			/// <summary>
			/// Unloads an IPL for a specific player
			/// </summary>
			/// <param name="ipl">The name of the IPL</param>
			/// <param name="ipl">The entity of the player you wish to unload the ipl for</param>
			DLL_PUBLIC_I static void UnloadIPL(const int entity, const std::wstring ipl);
		};
	}
#ifdef __cplusplus
}
#endif