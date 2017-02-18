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

	return CefInitialize(args, settings, nullptr, nullptr);
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

HHOOK m_pWndProcedure;
DirectXRenderer *curInstance2;

LRESULT CALLBACK MsgHookRet(int nCode, WPARAM wParam, LPARAM lParam)
{
	CWPRETSTRUCT* msg = (CWPRETSTRUCT*)lParam;

	switch (msg->message)
	{
	case WM_SIZE:
		curInstance2 = DirectXRenderer::GetInstance();
		if (curInstance2->pDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			CleanupRenderTarget();
			curInstance2->pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
			CreateRenderTarget();
		}
		break;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			break;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return CallNextHookEx(0, nCode, wParam, lParam);
}

void CefRenderer::OnTick()
{
	HHOOK msgHook = SetWindowsHookExA(WH_CALLWNDPROCRET, MsgHookRet, GetModuleHandle(NULL), 0);

	CefRunMessageLoop();
}