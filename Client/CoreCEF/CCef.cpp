#include "stdafx.h"

CCef::CCef()
{
	SandboxInfo = nullptr;
}


CCef::~CCef()
{
	SandboxInfo = nullptr;
}

bool CCef::Initialize(HINSTANCE hInstance)
{
	bool state = false;

	CefMainArgs Arguments(hInstance);
	CefSettings Settings;

	CefRefPtr<CCefApp> Application(new CCefApp);

	CefEnableHighDPISupport();

	if (!CefExecuteProcess(Arguments, Application, SandboxInfo) >= 0)
		state = true;

	return state;
}

bool CCef::Close()
{
	CefShutdown();
	return false;
}

bool CCef::CreateNewWindow()
{
	return false;
}

void CCef::Pulse()
{
	CefRunMessageLoop();
}
