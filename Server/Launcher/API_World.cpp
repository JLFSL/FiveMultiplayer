#include "stdafx.h"

namespace API
{
	namespace World
	{
		char *ThisNamespace = "API::World";

		void GetTime(int *hour, int *minute, int *second)
		{
			*hour = g_World->GetTime().Hour;
			*minute = g_World->GetTime().Minute;
			*second = g_World->GetTime().Second;
		}

		void SetTime(int hour, int minute, int second)
		{
			g_World->SetTime(hour, minute, second);
		}

		std::string GetWeather()
		{
			return g_World->GetWeather().Weather;
		}

		void SetWeather(std::string weather)
		{
			g_World->SetWeather(weather);
		}
	}
}
