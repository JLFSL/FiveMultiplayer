#include "stdafx.h"

CAPI::CAPI()
{
	Instance = nullptr;
}


CAPI::~CAPI()
{
	Instance = nullptr;
}

bool CAPI::Load()
{
#ifdef _WIN32
	Instance = ::LoadLibraryA(std::string("./plugin/" + Module).c_str());
#else
	Instance = dlopen(s.c_str(), RTLD_LAZY | RTLD_GLOBAL);
#endif
	if (!Instance)
	{
#ifdef _WIN32
		std::cout << "[CAPI] " << ModuleName() << " could not be loaded" << std::endl;
#else
		std::cout << "[CAPI] Cannot open library " << ModuleName() << ", " << dlerror() << std::endl;
#endif
		return false;
	}

	std::cout << "[CAPI] " << ModuleName() << " loaded." << std::endl;
	return true;
}

bool CAPI::Unload()
{
	if (Instance) 
	{
#ifdef _WIN32
		FreeLibrary((HMODULE)Instance);
#else
		dlclose(Instance);
#endif
		if (!Instance) {
			std::cout << "[CAPI] " << ModuleName() << " unloaded." << std::endl;
			return true;
		}
		return false;
	}
	return false;
}

bool CAPI::Initialize()
{
	if (Instance) 
	{
		typedef void(*API_Initialize_t)();
#ifdef WIN32
		API_Initialize_t API_Initialize = (API_Initialize_t)::GetProcAddress((HMODULE)Instance, "API_Initialize");
#else
		API_Initialize_t API_Initialize = (API_Initialize_t)dlsym(Instance, "API_Initialize");
#endif
		
		if (!API_Initialize)
			return false;

		API_Initialize();
		std::cout << "[CAPI] " << ModuleName() << " initialized" << std::endl;
		return true;
	}
	return false;
}

bool CAPI::Close()
{
	if (Instance)
	{
		typedef void(*API_Close_t)();
#ifdef WIN32
		API_Close_t API_Close = (API_Close_t)::GetProcAddress((HMODULE)Instance, "API_Close");
#else
		API_Close_t API_Close = (API_Close_t)dlsym(Instance, "API_Close");
#endif
		
		if (!API_Close)
			return false;

		API_Close();
		std::cout << "[CAPI] " << ModuleName() << " closed" << std::endl;
		return true;
	}
	return false;
}

bool CAPI::OnTick()
{
	if (Instance)
	{
		typedef void(*API_OnTick_t)();
#ifdef WIN32
		API_OnTick_t API_OnTick = (API_OnTick_t)::GetProcAddress((HMODULE)Instance, "API_OnTick");
#else
		API_OnTick_t API_OnTick = (API_OnTick_t)dlsym(Instance, "API_OnTick");
#endif
		
		if (!API_OnTick)
			return false;

		API_OnTick();
		return true;
	}
	return false;
}