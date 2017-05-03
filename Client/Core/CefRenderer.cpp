#include "stdafx.h"

// class inits to prevent LNK2001
HHOOK CefRenderer::msgHook;
HWND CefRenderer::curProc;

CefMainArgs CefRenderer::args;
CefRefPtr<OffscreenClient> CefRenderer::offscreenClient;
CefSettings CefRenderer::settings;
CefWindowInfo CefRenderer::window_info;
CefBrowserSettings CefRenderer::browserSettings;
CefRefPtr<CefBrowser> CefRenderer::browser;

LRESULT CALLBACK MsgHookRet(int nCode, WPARAM wParam, LPARAM lParam)
{
	CWPRETSTRUCT* msg = (CWPRETSTRUCT*)lParam;

	switch (msg->message)
	{
	case WM_SIZE:
		if (DirectXRenderer::pDevice != NULL && wParam != SIZE_MINIMIZED)
		{
			CefTexture::CleanupRenderTarget();
			DirectXRenderer::pSwapChain->ResizeBuffers(0, (UINT)LOWORD(lParam), (UINT)HIWORD(lParam), DXGI_FORMAT_UNKNOWN, 0);
			CefTexture::CreateRenderTarget();
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

bool CefRenderer::Initialize()
{
	msgHook = SetWindowsHookExA(WH_CALLWNDPROCRET, MsgHookRet, GetModuleHandle(NULL), 0);

	CefEnableHighDPISupport();

	CefRefPtr<ClientApp> app(new ClientApp);

	int result = CefExecuteProcess(args, app.get(), NULL);
	if (result >= 0)
	{
		std::cout << "cef execute failed" << std::endl;
		return false;
	}
	if (result == -1)
	{
		// checkout detailed settings options http://magpcss.org/ceforum/apidocs/projects/%28default%29/_cef_settings_t.html
		settings.windowless_rendering_enabled = true;
		settings.single_process = true;
		settings.multi_threaded_message_loop = false;

		if (!CefInitialize(args, settings, app.get(), NULL))
		{
			std::cout << "cef initialize failed" << std::endl;
			return false;
		}

		offscreenClient = new OffscreenClient;

		window_info.width = 1600;
		window_info.height = 900;

		curProc = FindWindowA(NULL, "Grand Theft Auto V");
		window_info.SetAsWindowless(curProc, true);

		browserSettings.windowless_frame_rate = 60; // 30 is default
		browserSettings.javascript = STATE_ENABLED;
		browserSettings.web_security = STATE_DISABLED;
		return true;
	}
	return false;
}

void CefRenderer::Start()
{
	CefInput::InstallHook();

	//CefBrowserHost::CreateBrowser(window_info, textureClient.get(), "http://www.google.com", browserSettings, nullptr);
	//CefBrowserHost::CreateBrowser(window_info, textureClient.get(), "http://www.radiotunes.com/chillout", browserSettings, nullptr);
	//CefRefPtr<CefBrowser> browser = CefBrowserHost::CreateBrowserSync(window_info, offscreenClient.get(), "http://itseasy.dk/fivemp/index.html", browserSettings, nullptr);
	//browser = CefBrowserHost::CreateBrowserSync(window_info, offscreenClient.get(), "http://www.google.com", browserSettings, nullptr);
	//browser = CefBrowserHost::CreateBrowserSync(window_info, textureClient.get(), "https://www.youtube.com/watch?v=yYzGHhhg_og&index=171&list=PL04B59999BC5DA80D", browserSettings, nullptr);

	//char url[MAX_PATH], buffer[MAX_PATH];
	//GetCurrentDirectoryA(sizeof(buffer), buffer);

	//sprintf(url, "%s/html/index.html", buffer);
	browser = CefBrowserHost::CreateBrowserSync(window_info, offscreenClient.get(), "about:blank", browserSettings, nullptr);
}

void CefRenderer::OnTick()
{
	CefRunMessageLoop();
}

