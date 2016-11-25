#include "stdafx.h"

CAPI::CAPI()
{
	Instance = nullptr;

	cout << "CAPI::Constructed" << endl;
}


CAPI::~CAPI()
{
	Instance = nullptr;
	Module = NULL;

	cout << "CAPI::Deconstructed" << endl;
}

bool CAPI::Load(LPCSTR Filename)
{
	Instance = ::LoadLibraryA(Filename);
	Module = Filename;
	if (!Instance)
		return false;
	cout << endl << "CAPI::" << ModuleName() << " loaded" << endl;
	return true;
}

bool CAPI::Unload()
{
	if (Instance) 
	{
		FreeLibrary(Instance);
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
		LPFN_DHFDLL API_Initialize = (LPFN_DHFDLL)::GetProcAddress(Instance, "API_Initialize");
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
		LPFN_DHFDLL API_Close = (LPFN_DHFDLL)::GetProcAddress(Instance, "API_Close");
		API_Close();
		if (!API_Close)
			return false;
		cout << "CAPI::" << ModuleName() << " closed" << endl;
		return true;
	}
	return false;
}
