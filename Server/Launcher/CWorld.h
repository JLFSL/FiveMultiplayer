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
		std::string	Weather;
		bool		GroundSnow;
	} Weather;

public:
	CWorld() {
		Time.Hour = 12;
		Time.Minute = 00;
		Time.Second = 00;
		Weather.Weather = "CLEAR";
		Weather.GroundSnow = false;
	};
	~CWorld() {};

	WorldTime		GetTime() { return Time; };
	void			SetTime(int hour, int minute, int second);

	WorldWeather	GetWeather() { return Weather; };
	void			SetWeather(std::string weather);
	void			SetGroundSnow(bool grndsnow) { Weather.GroundSnow = grndsnow; }
};