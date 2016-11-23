#pragma once

class CEFLauncher : public CefApp, CefBrowserProcessHandler {
public:
	CEFLauncher();

	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
		OVERRIDE { return this; }
	virtual void OnContextInitialized() OVERRIDE;

private:
	IMPLEMENT_REFCOUNTING(CEFLauncher);
};

