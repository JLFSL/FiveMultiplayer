#include "stdafx.h"

namespace API
{
	namespace World
	{
		char *ThisNamespace = "API::World";

		void GetTime(int *hour, int *minute, int *second)
		{
			*hour = CWorld::instance()->GetTime().Hour;
			*minute = CWorld::instance()->GetTime().Minute;
			*second = CWorld::instance()->GetTime().Second;
		}

		void SetTime(int hour, int minute, int second)
		{
			CWorld::instance()->SetTime(hour, minute, second);
		}

		std::string GetWeather()
		{
			return CWorld::instance()->GetWeather().Weather;
		}

		void SetWeather(const std::string weather)
		{
			CWorld::instance()->SetWeather(weather);
		}
	}
}
