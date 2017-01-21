#pragma once

class CWorld
{
private:
	static std::unique_ptr<CWorld> s_instance;

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
	CWorld();
	~CWorld() {}

	static CWorld *instance()
	{
		if (!s_instance)
			s_instance = std::unique_ptr<CWorld>(new CWorld);
		return s_instance.get();
	}

	WorldTime		GetTime() { return Time; };
	void			SetTime(int hour, int minute, int second);

	WorldWeather	GetWeather() { return Weather; }
	void			SetWeather(std::string weather);
	void			SetGroundSnow(bool grndsnow) { Weather.GroundSnow = grndsnow; }
};