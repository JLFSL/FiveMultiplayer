#pragma once
#include "SharedUtility.hpp"

namespace SharedUtility
{
	unsigned long GetTime()
	{
#ifdef _WIN32
		return timeGetTime();
#else
		timeval ts;
		gettimeofday(&ts, 0);
		return (DWORD)(ts.tv_sec * 1000 + (ts.tv_usec / 1000));
#endif
	}
}