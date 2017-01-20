#include "stdafx.h"

namespace API
{
	namespace World
	{
		char *ThisNamespace = "API::World";

		void GetTime(int *hour, int *minute, int *second)
		{
			*hour = g_Server->GetWorld()->GetTime().Hour;
			*minute = g_Server->GetWorld()->GetTime().Minute;
			*second = g_Server->GetWorld()->GetTime().Second;
		}

		void SetTime(int hour, int minute, int second)
		{
			if (g_Server->GetWorld() == nullptr)
			{
				std::cout << "RAWRA" << std::endl;
			}
			std::cout << "RAWRA2" << std::endl;
			g_Server->GetWorld()->SetTime(hour, minute, second);
		}

		std::string GetWeather()
		{
			return g_Server->GetWorld()->GetWeather().Weather;
		}

		void SetWeather(const std::string weather)
		{
			g_Server->GetWorld()->SetWeather(weather);
		}
	}
}
