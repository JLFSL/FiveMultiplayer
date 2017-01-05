#include "stdafx.h"

class CCefApp : public CefApp, public CefRenderProcessHandler
{
public:
	CCefApp() {}
	virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() override { return this; };

	virtual void OnFocusedNodeChanged(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefDOMNode> node) {

	}
	virtual void OnRegisterCustomSchemes(CefRefPtr < CefSchemeRegistrar > registrar) {

	}

	virtual void OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context) {

	}

	static void Javascript_triggerEvent(CefRefPtr<CefFrame> frame, const CefV8ValueList& arguments)
	{
		if (arguments.size() == 0)
			return;


	}

public:
	IMPLEMENT_REFCOUNTING(CCefApp);

private:
	bool m_bHasInputFocus = false;
};

LRESULT WINAPI WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_SIZE:
		return 0;
	case WM_SYSCOMMAND:
		if ((wParam & 0xfff0) == SC_KEYMENU) // Disable ALT application menu
			return 0;
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}

bool CefRenderer::Initialize(HINSTANCE hInstance)
{
	// Create application window
	WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, WndProc, 0L, 0L, GetModuleHandle(NULL), NULL, LoadCursor(NULL, IDC_ARROW), NULL, NULL, "Ceftest", NULL };
	RegisterClassEx(&wc);
	HWND hwnd = CreateWindow("Ceftest", "Ceftest Renderer", WS_OVERLAPPEDWINDOW, 100, 100, 1280, 800, NULL, NULL, wc.hInstance, NULL);

	// Show the window
	ShowWindow(hwnd, SW_SHOWDEFAULT);
	UpdateWindow(hwnd);

	//SetParent(hwnd, FindWindow(NULL, "Grand Theft Auto V"));

	CefMainArgs mainArgs((HMODULE)GetWindowLong(hwnd, -6));
	CefRefPtr<RenderHandler> renderHandler;
	CefSettings settings;
	CefBrowserSettings browsersettings;
	CefWindowInfo windowinfo;

	settings.multi_threaded_message_loop = false;
	settings.windowless_rendering_enabled = true;
	browsersettings.windowless_frame_rate = 30;

	CefExecuteProcess(mainArgs, nullptr, nullptr);
	bool state = CefInitialize(mainArgs, settings, nullptr, nullptr);

	//CefBrowserHost::CreateBrowserSync(windowinfo, renderHandler.get(), "https://www.google.com", browsersettings, nullptr);
	return state;
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
