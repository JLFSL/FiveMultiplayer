#include "stdafx.h"

bool CefRenderer::Initialize(HINSTANCE hInstance)
{
	CefMainArgs mainArgs;
	void* sandboxInfo = nullptr;
	CefRefPtr<CWebApp> app(new CWebApp);

#ifdef CEF_ENABLE_SANDBOX
	CefScopedSandboxInfo scopedSandbox;
	sandboxInfo = scopedSandbox.sandbox_info();
#endif

	CefSettings settings;
#ifndef CEF_ENABLE_SANDBOX
	settings.no_sandbox = true;
#endif

	// Specifiy sub process executable path
	CefString(&settings.browser_subprocess_path).FromASCII("H:\\GitHub Repositories\\Five-Multiplayer\\bin\\Release\\Client\\cefbin\\Client.CEF.exe");

	settings.multi_threaded_message_loop = true;
	settings.windowless_rendering_enabled = true;
	settings.single_process = false;

	bool state = CefInitialize(mainArgs, settings, app, sandboxInfo);

	//CefBrowserHost::CreateBrowserSync(windowinfo, renderHandler.get(), "https://www.google.com", browsersettings, nullptr);
	return state;
}

void CefRenderer::OnTick()
{
	CefRunMessageLoop();
}
