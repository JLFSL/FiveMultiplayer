class ClientApp : public CefApp, public CefRenderProcessHandler {
public:
	ClientApp();

	CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler() OVERRIDE
	{
		return this;
	}

	void OnWebKitInitialized() OVERRIDE;

	IMPLEMENT_REFCOUNTING(ClientApp);
};