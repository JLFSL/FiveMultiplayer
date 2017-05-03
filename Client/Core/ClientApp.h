class ClientApp : public CefApp, public CefRenderProcessHandler, public CefLoadHandler {
public:
	ClientApp();

	CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE
	{
		return this;
	}

	virtual void OnWebKitInitialized() OVERRIDE;

	virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) OVERRIDE;

	IMPLEMENT_REFCOUNTING(ClientApp);
};