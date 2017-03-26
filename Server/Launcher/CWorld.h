#pragma once

class CWorld
{
private:
	struct WorldTime
	{
		int	Hour;
		int	Minute;
		int Second;
	} Time;

	struct WorldWeather
	{
		std::wstring	Weather;
		bool			GroundSnow;
	} Weather;

public:
	CWorld();
	~CWorld() {}

	WorldTime		GetTime() { return Time; };
	void			SetTime(int hour, int minute, int second);

	WorldWeather	GetWeather() { return Weather; }
	void			SetWeather(std::wstring weather);
	void			SetGroundSnow(bool grndsnow) { Weather.GroundSnow = grndsnow; }
};