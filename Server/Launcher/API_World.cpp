#include "stdafx.h"

namespace API
{
	const char *World::ThisNamespace = "API::World";

	void World::GetTime(int *hour, int *minute, int *second)
	{
		*hour = g_Server->GetWorld()->GetTime().Hour;
		*minute = g_Server->GetWorld()->GetTime().Minute;
		*second = g_Server->GetWorld()->GetTime().Second;
	}

	void World::SetTime(const int hour, const int minute, const int second)
	{
		g_Server->GetWorld()->SetTime(hour, minute, second);
	}

	const std::wstring World::GetWeather()
	{
		return g_Server->GetWorld()->GetWeather().Weather;
	}

	void World::SetWeather(const std::wstring weather)
	{
		g_Server->GetWorld()->SetWeather(weather);
	}
}