class ClientApp : public CefApp, public CefRenderProcessHandler, public CefLoadHandler {
public:
	ClientApp();

	CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE
	{
		return this;
	}

	virtual void OnWebKitInitialized() OVERRIDE;

	IMPLEMENT_REFCOUNTING(ClientApp);
};