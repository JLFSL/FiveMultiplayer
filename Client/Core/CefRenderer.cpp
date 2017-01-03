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


bool CefRenderer::Initialize(HINSTANCE hInstance)
{
	CefMainArgs mainArgs(GetModuleHandle(NULL));
	CefRefPtr<RenderHandler> renderHandler;
	CefRefPtr<CCefApp> app{ new CCefApp };
	CefSettings settings;
	CefBrowserSettings browsersettings;
	CefWindowInfo windowinfo;

	settings.no_sandbox = true;
	settings.multi_threaded_message_loop = true;
	settings.windowless_rendering_enabled = true;

	void* sandboxInfo = nullptr;

	std::cout << CefExecuteProcess(mainArgs, app, sandboxInfo) << std::endl;
	bool state = CefInitialize(mainArgs, settings, app, sandboxInfo);
	std::cout << state << std::endl;
	CefBrowserHost::CreateBrowserSync(windowinfo, renderHandler.get(), "https://www.google.com", browsersettings, nullptr);

	return state;
}

void CefRenderer::OnTick()
{
	/*MSG Message;
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
	}*/
}
