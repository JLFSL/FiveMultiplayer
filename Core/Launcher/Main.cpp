#include "stdafx.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	/*bool console = false;

	if (!console) {
		if (AllocConsole()) {
			freopen("CONIN$", "rb", stdin);
			freopen("CONOUT$", "wb", stdout);
			freopen("CONOUT$", "wb", stderr);
			console = true;
		}
	}*/

	CefEnableHighDPISupport();

	void* sandbox_info = NULL;

	CefMainArgs main_args(hInstance);
	//if (int result = CefExecuteProcess(main_args, NULL, sandbox_info) >= 0)
		//return result;

	CefSettings settings;
	CefRefPtr<CEFLauncher> launcher(new CEFLauncher);

	CefInitialize(main_args, settings, launcher.get(), sandbox_info);

	CefRunMessageLoop();

	CefShutdown();
	//FreeConsole();
	return 0;
}