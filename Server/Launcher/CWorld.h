#pragma once

class CWorld
{
private:
	static struct WorldTime
	{
		int	Hour;
		int	Minute;
		int Second;
	} Time;

	static struct WorldWeather
	{
		std::wstring	Weather;
		bool			GroundSnow;
	} Weather;

	static struct IPL
	{
		std::wstring	ipl;
		bool			enabled;
	};

public:
	static std::vector<IPL> g_IPLs;

	static void			Initialize();

	static WorldTime	GetTime() { return Time; };
	static void			SetTime(int hour, int minute, int second);

	static WorldWeather	GetWeather() { return Weather; }
	static void			SetWeather(std::wstring weather);
	static void			SetGroundSnow(bool grndsnow) { Weather.GroundSnow = grndsnow; }

	static void			LoadIPL(std::wstring ipl);
	static void			UnloadIPL(std::wstring ipl);
};