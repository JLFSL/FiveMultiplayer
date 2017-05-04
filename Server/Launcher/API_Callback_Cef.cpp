#include "stdafx.h"

namespace API
{
	namespace Cef
	{
		void OnCefFinishLoad(void *Instance, const int entity)
		{
			if (Instance)
			{
				typedef void(*API_OnCefFinishLoad_t)(int);
#ifdef WIN32
				API_OnCefFinishLoad_t API_OnCefFinishLoad = (API_OnCefFinishLoad_t)::GetProcAddress((HMODULE)Instance, "API_OnCefFinishLoad");
#else
				API_OnCefFinishLoad_t API_OnCefFinishLoad = (API_OnCefFinishLoad_t)dlsym(Instance, "API_OnCefFinishLoad");
#endif
				API_OnCefFinishLoad(entity);
			}
		}

		void OnCefSendData(void *Instance, const int entity, const std::string data)
		{
			if (Instance)
			{
				typedef void(*API_OnCefSendData_t)(int, std::string);
#ifdef WIN32
				API_OnCefSendData_t API_OnCefSendData = (API_OnCefSendData_t)::GetProcAddress((HMODULE)Instance, "API_OnCefSendData");
#else
				API_OnCefSendData_t API_OnCefSendData = (API_OnCefSendData_t)dlsym(Instance, "API_OnCefSendData");
#endif
				API_OnCefSendData(entity, data);
			}
		}
	}
}