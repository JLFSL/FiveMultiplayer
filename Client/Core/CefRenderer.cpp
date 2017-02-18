#include "stdafx.h"

bool CefRenderer::Initialize()
{
	CefEnableHighDPISupport();

	CefMainArgs args;
	{
		int result = CefExecuteProcess(args, nullptr, nullptr);
		// checkout CefApp, derive it and set it as second parameter, for more control on
		// command args and resources.
		if (result >= 0) // child proccess has endend, so exit.
		{
			//return;
		}
		if (result == -1)
		{
			// we are here in the father proccess.
		}
	}


	CefSettings settings;

	// checkout detailed settings options http://magpcss.org/ceforum/apidocs/projects/%28default%29/_cef_settings_t.html
	settings.windowless_rendering_enabled = true;
	settings.single_process = true;
	settings.multi_threaded_message_loop = false;

	return CefInitialize(args, settings, CefRefPtr<CefApp>(), nullptr);
}

void CefRenderer::Start()
{
	OffscreenClient* renderHandler;
	{
		renderHandler = new OffscreenClient();
	}

	CefWindowInfo window_info;
	CefBrowserSettings browserSettings;
	CefRefPtr<BrowserClient> browserClient;

	window_info.height = 720;
	window_info.width = 1280;

	//browserSettings.windowless_frame_rate = 60; // 30 is default

	//CefBrowserHost::CreateBrowser(window_info, textureClient.get(), "http://www.google.com", browserSettings, nullptr);
	//CefBrowserHost::CreateBrowser(window_info, textureClient.get(), "http://www.radiotunes.com/chillout", browserSettings, nullptr);
	CefRefPtr<CefBrowser> browser = CefBrowserHost::CreateBrowserSync(window_info, browserClient.get(), "https://www.youtube.com/watch?v=yYzGHhhg_og&index=171&list=PL04B59999BC5DA80D", browserSettings, nullptr);
	//browser = CefBrowserHost::CreateBrowserSync(window_info, textureClient.get(), "http://www.google.com", browserSettings, nullptr);
	//browser = CefBrowserHost::CreateBrowserSync(window_info, textureClient.get(), "https://www.youtube.com/watch?v=yYzGHhhg_og&index=171&list=PL04B59999BC5DA80D", browserSettings, nullptr);
}

void CefRenderer::OnTick()
{
	CefRunMessageLoop();
}