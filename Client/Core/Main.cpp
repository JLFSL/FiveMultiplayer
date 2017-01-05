#include "stdafx.h"

DWORD WINAPI MainThread(LPVOID lpParam)
{
	Hooking::Start((HMODULE)lpParam);
	return 0;
}

DWORD WINAPI CEFThread(LPVOID lpParam)
{
	if (CefRenderer::Initialize((HMODULE)lpParam))
		CefRenderer::OnTick();
	return 0;
}

DWORD WINAPI DXThread(LPVOID lpParam)
{
	DirectXRenderer *Renderer = new DirectXRenderer;
	memset(Renderer->GetBuffer(), 0, (sizeof(Renderer->GetBuffer()) * sizeof(void*)));
	Renderer->Initialize();
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
		//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)CEFThread, (LPVOID)hModule, NULL, NULL);
		//CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)DXThread, (LPVOID)hModule, NULL, NULL);
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