#include "stdafx.h"

CServer * g_Server = NULL;

EXPORT CServer *GetServerInterface()
{
	SAFE_DELETE(g_Server);
	g_Server = new CServer();
	return g_Server;
}

EXPORT void DestroyServerInterface(CServer *pServer)
{
	SAFE_DELETE(g_Server);
}

#ifdef _WIN32
bool WINAPI DllMain(HMODULE hModule, DWORD dwReason, void *)
{
	if(dwReason == DLL_PROCESS_ATTACH)
	{
		// Disable thread calls
		DisableThreadLibraryCalls(hModule);
	}
	return true;
}
#endif
