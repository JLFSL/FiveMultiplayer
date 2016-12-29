#include "stdafx.h"

bool CefRenderer::Initialize(HINSTANCE hInstance)
{
	CefEnableHighDPISupport();

	CefMainArgs Arguments(hInstance);
	CefRefPtr<RenderHandler> renderHandler;
	CefSettings Settings;
	CefWindowInfo WindowInformation;
	CefBrowserSettings BrowserSettings;

	// CefSettings
	Settings.multi_threaded_message_loop = false;

	if (CefExecuteProcess(Arguments, nullptr, nullptr) >= 0)
		return false;
	
	if (!CefInitialize(Arguments, Settings, CefRefPtr<CefApp>(), nullptr))
		return false;

	renderHandler = new RenderHandler();
	CefBrowserHost::CreateBrowserSync(WindowInformation, renderHandler.get(), "https://www.google.com/", BrowserSettings, nullptr);
	return true;
}

void CefRenderer::OnTick()
{
	MSG Message;
	ZeroMemory(&Message, sizeof(Message));

	while (Message.message != WM_QUIT)
	{
		assert(offscreenClient->m_browser);
		CefDoMessageLoopWork();

		if (PeekMessage(&Message, NULL, 0U, 0U, PM_REMOVE))
		{
			TranslateMessage(&Message);
			DispatchMessage(&Message);
			continue;
		}
	}
}
