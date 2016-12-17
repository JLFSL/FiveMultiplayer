#include "stdafx.h"

CAPI::CAPI()
{
	Instance = nullptr;

	cout << "CAPI::Constructed" << endl;
}


CAPI::~CAPI()
{
	Instance = nullptr;

	cout << "CAPI::Deconstructed" << endl;
}

bool CAPI::Load(LPCSTR Filename)
{
#ifdef _WIN32
	Instance = ::LoadLibraryA(Filename);
#else
	Instance = dlopen(Filename, RTLD_LAZY);
#endif
	Module = (char *)Filename;
	if (!Instance)
		return false;
	cout << endl << "CAPI::" << ModuleName() << " loaded" << endl;
	return true;
}

bool CAPI::Unload()
{
	if (Instance) 
	{
#ifdef _WIN32
		FreeLibrary(Instance);
#else
		dlclose(Instance);
#endif
		if (!Instance) {
			cout << "CAPI::" << ModuleName() << " unloaded" << endl;
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
		API_Initialize_t API_Initialize = (API_Initialize_t)::GetProcAddress(Instance, "API_Initialize");
#else
		API_Initialize_t API_Initialize = (API_Initialize_t)dlsym(handle, "API_Initialize");
#endif
		API_Initialize();
		if (!API_Initialize)
			return false;
		cout << endl << "CAPI::" << ModuleName() << " initialized" << endl;
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
		API_Close_t API_Close = (API_Close_t)::GetProcAddress(Instance, "API_Initialize");
#else
		API_Close_t API_Close = (API_Close_t)dlsym(handle, "API_Initialize");
#endif
		API_Close();
		if (!API_Close)
			return false;
		cout << "CAPI::" << ModuleName() << " closed" << endl;
		return true;
	}
	return false;
}
