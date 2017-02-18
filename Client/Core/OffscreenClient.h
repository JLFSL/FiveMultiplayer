#pragma once

class OffscreenClient : public CefClient, public CefLifeSpanHandler, public CefRenderHandler
{
public:
	OffscreenClient();
	virtual ~OffscreenClient();

	virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE {
		return this;
	}

	virtual CefRefPtr<CefRenderHandler> GetRenderHandler() OVERRIDE {
		return this;
	}

	virtual void OnPaint(CefRefPtr<CefBrowser> browser,
		PaintElementType type,
		const RectList& dirtyRects,
		const void* buffer,
		int width, int height) OVERRIDE;

	// CefLifeSpanHandler methods
	virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
	virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;
	// virtual bool DoClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

	CefRefPtr<CefBrowser> GetBrowser() { return m_browser; }

	virtual bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) OVERRIDE { rect.Set(0, 0, 1280, 720);  return true; };

	// private:
	// The child browser window
	CefRefPtr<CefBrowser> m_browser;

	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(OffscreenClient);
	// Include the default locking implementation.
	// IMPLEMENT_LOCKING(OffscreenClient);
};

// for manual render handler
class BrowserClient : public CefClient
{
public:
	BrowserClient(OffscreenClient *renderHandler)
		: m_renderHandler(renderHandler)
	{
		;
	}

	virtual CefRefPtr<CefRenderHandler> GetRenderHandler() {
		return m_renderHandler;
	}

	CefRefPtr<CefRenderHandler> m_renderHandler;

	IMPLEMENT_REFCOUNTING(BrowserClient);
};
