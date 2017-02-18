#include "stdafx.h"

class TextureRenderHandler : public CefRenderHandler
{
public:
	TextureRenderHandler()
	{
	}

	bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect)
	{
		//rect = CefRect(0, 0, texture->GetWidth(), texture->GetHeight());
		return true;
	}

	void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList &dirtyRects, const void *buffer, int width, int height)
	{
		//texture->SetData(0, 0, 0, width, height, buffer);
	}


	IMPLEMENT_REFCOUNTING(TextureRenderHandler);
};


class TextureClient : public CefClient
{
public:
	CefRefPtr<CefRenderHandler> renderHandler;


	TextureClient(TextureRenderHandler* renderHandler) :
		renderHandler(renderHandler)
	{
	}

	virtual CefRefPtr<CefRenderHandler> GetRenderHandler()
	{
		return renderHandler;
	}


	IMPLEMENT_REFCOUNTING(TextureClient);
};


/*bool CefRenderer::Initialize(HINSTANCE hInstance)
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

	settings.multi_threaded_message_loop = true;
	settings.windowless_rendering_enabled = true;
	settings.single_process = false;

	// Specifiy sub process executable path
	CefString(&settings.browser_subprocess_path).FromASCII("F:\\Git Repositories\\FiveMultiplayer\\bin\\Release\\Client\\cefbin\\Client.CEF.exe");

	bool state = CefInitialize(mainArgs, settings, app, sandboxInfo);

	//CefBrowserHost::CreateBrowserSync(windowinfo, renderHandler.get(), "https://www.google.com", browsersettings, nullptr);
	return state;
}*/

void CefRenderer::OnTick()
{
	CefRunMessageLoop();
}

bool CefRenderer::Initialize()
{
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
	//settings.multi_threaded_message_loop = true;

	return CefInitialize(args, settings, nullptr, nullptr);
}

CefRefPtr<TextureRenderHandler> renderTextureHandler;
CefRefPtr<TextureClient> textureClient;

void CefRenderer::Start()
{
	CefWindowInfo window_info;
	CefBrowserSettings browserSettings;

	// browserSettings.windowless_frame_rate = 60; // 30 is default

	textureClient = new TextureClient(renderTextureHandler.get());
	//CefBrowserHost::CreateBrowser(window_info, textureClient.get(), "http://www.google.com", browserSettings, nullptr);
	//CefBrowserHost::CreateBrowser(window_info, textureClient.get(), "http://www.radiotunes.com/chillout", browserSettings, nullptr);
	CefBrowserHost::CreateBrowser(window_info, textureClient.get(), "https://www.youtube.com/watch?v=yYzGHhhg_og&index=171&list=PL04B59999BC5DA80D", browserSettings, nullptr);
	//browser = CefBrowserHost::CreateBrowserSync(window_info, textureClient.get(), "http://www.google.com", browserSettings, nullptr);
	//browser = CefBrowserHost::CreateBrowserSync(window_info, textureClient.get(), "https://www.youtube.com/watch?v=yYzGHhhg_og&index=171&list=PL04B59999BC5DA80D", browserSettings, nullptr);
}
