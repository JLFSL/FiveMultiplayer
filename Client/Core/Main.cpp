#include "stdafx.h"

DWORD WINAPI MainThread(LPVOID lpParam)
{
	Hooking::Start((HMODULE)lpParam);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		AllocConsole();
		freopen("CONOUT$", "w", stdout);

		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)MainThread, hModule, NULL, NULL);
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		FreeConsole();
		Hooking::Cleanup();
		break;
	}
	return TRUE;
}